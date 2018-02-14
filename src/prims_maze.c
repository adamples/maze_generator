/* Copyright (c) 2018 Adam Ples
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#include "prims_maze.h"
#include <stdlib.h>
#include <stdbool.h>
#include "bitmap.h"
#include "dynamic_array.h"


typedef struct cell_t_ {
  int x;
  int y;
} cell_t;


typedef struct wall_t_ {
  cell_t c1;
  cell_t c2;
} wall_t;


typedef struct prims_t_ {
  maze_t *maze;
  int width;
  int height;
  bitmap_t *visited_cells;
  array_t *walls;
} prims_t;




static void
prims_init(prims_t *prims, maze_t *maze)
{
  prims->maze = maze;
  prims->width = maze_get_width(maze);
  prims->height = maze_get_height(maze);
  prims->walls = array_create(sizeof(wall_t));
  prims->visited_cells = bitmap_create(prims->width * prims->height);
}


static void
prims_destroy(prims_t *prims)
{
  array_free(&(prims->walls));
  bitmap_free(&(prims->visited_cells));
}


static bool
prims_cell_was_visited(const prims_t *prims, const cell_t *cell)
{
  return bitmap_get(prims->visited_cells, cell->y * prims->width + cell->x);
}


static void
prims_cell_set_visited(prims_t *prims, const cell_t *cell)
{
  bitmap_set(prims->visited_cells, cell->y * prims->width + cell->x, true);
}


static bool
prims_get_next_wall(const prims_t *prims, wall_t *wall)
{
  int length = array_length(prims->walls);

  if (length == 0) {
    return false;
  }

  const wall_t *last_element = array_get(prims->walls, length - 1);
  int index = rand() % array_length(prims->walls);

  array_get_copy(prims->walls, index, wall);
  array_set(prims->walls, index, last_element);
  array_resize(prims->walls, length - 1);

  return true;
}


static void
prims_add_wall(prims_t *prims, const wall_t *wall)
{
  array_push(prims->walls, wall);
}


static void
prims_remove_wall(prims_t *prims, const wall_t *wall)
{
  maze_remove_wall_between(prims->maze, wall->c1.x, wall->c1.y, wall->c2.x, wall->c2.y);
}


static void
prims_add_wall_if_exists(prims_t *prims, wall_t *wall)
{
  if (wall->c1.x < 0 || wall->c1.x >= prims->width ||
      wall->c1.y < 0 || wall->c1.y >= prims->height ||
      wall->c2.x < 0 || wall->c2.x >= prims->width ||
      wall->c2.y < 0 || wall->c2.y >= prims->height)
  {
    return;
  }

  if (maze_has_wall_between(prims->maze, wall->c1.x, wall->c1.y, wall->c2.x, wall->c2.y)) {
    prims_add_wall(prims, wall);
  }
}


static void
prims_visit_cell(prims_t *prims, cell_t *cell)
{
  cell_t displacements[4] = {
    { -1, 0 },
    { 1, 0 },
    { 0, -1 },
    { 0, 1 }
  };

  prims_cell_set_visited(prims, cell);

  for (int i = 0; i < 4; ++i) {
    wall_t wall;

    wall.c1 = *cell;
    wall.c2 = *cell;
    wall.c2.x += displacements[i].x;
    wall.c2.y += displacements[i].y;

    prims_add_wall_if_exists(prims, &wall);
  }
}


static void
prims_select_and_visit_starting_cell(prims_t *prims)
{
  cell_t cell;

  cell.x = rand() % prims->width;
  cell.y = rand() % prims->height;

  prims_visit_cell(prims, &cell);
}


void
prims_maze_generate(maze_t *maze)
{
  prims_t prims;
  wall_t wall;

  prims_init(&prims, maze);

  maze_add_all_walls(prims.maze);
  bitmap_fill(prims.visited_cells, false);

  prims_select_and_visit_starting_cell(&prims);

  while (prims_get_next_wall(&prims, &wall)) {
    bool c1_visited = prims_cell_was_visited(&prims, &(wall.c1));
    bool c2_visited = prims_cell_was_visited(&prims, &(wall.c2));

    if (c1_visited ^ c2_visited) {
      prims_remove_wall(&prims, &wall);

      if (c1_visited) {
        prims_visit_cell(&prims, &(wall.c2));
      }
      else {
        prims_visit_cell(&prims, &(wall.c1));
      }
    }
  }

  prims_destroy(&prims);
}
