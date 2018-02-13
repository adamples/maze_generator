#include "model.h"
#include <stdlib.h>
#include <assert.h>
#include "bitmap.h"


struct maze_t_ {
  int width;
  int height;
  bitmap_t *h_walls;
  bitmap_t *v_walls;
};


static int
int_min(int a, int b) {
  return (a < b) ? a : b;
}


void
maze_init(maze_t *maze, int width, int height)
{
  maze->width = width;
  maze->height = height;

  maze->h_walls = bitmap_create((height - 1) * width);
  maze->v_walls = bitmap_create((width - 1) * height);
}


maze_t *
maze_create(int width, int height)
{
  maze_t *maze = (maze_t *) malloc(sizeof(maze_t));

  maze_init(maze, width, height);
  return maze;
}


void
maze_destroy(maze_t *maze)
{
  bitmap_free(&(maze->h_walls));
  maze->h_walls = NULL;
  bitmap_free(&(maze->v_walls));
  maze->v_walls = NULL;
}


void
maze_free(maze_t **maze)
{
  maze_destroy(*maze);
  free(*maze);
  *maze = NULL;
}


int
maze_get_width(maze_t *maze)
{
  assert(maze);
  return maze->width;
}


int
maze_get_height(maze_t *maze)
{
  assert(maze);
  return maze->height;
}


static bool
cells_are_adjacent(int c1_x, int c1_y, int c2_x, int c2_y)
{
  return (abs(c1_x - c2_x) == 1 && c1_y == c2_y) || (c1_x == c2_x && abs(c1_y - c2_y) == 1);
}


static bool
cell_in_maze(maze_t *maze, int x, int y)
{
  return x >= 0 && x < maze->width && y >=0 && y < maze->height;
}


static int
maze_h_wall_bit(maze_t *maze, int x, int y)
{
  return x * (maze->height - 1) + y;
}


static int
maze_v_wall_bit(maze_t *maze, int x, int y)
{
  return y * (maze->width - 1) + x;
}


bool
maze_has_wall_between(maze_t *maze, int c1_x, int c1_y, int c2_x, int c2_y)
{
  assert(maze);
  assert(cells_are_adjacent(c1_x, c1_y, c2_x, c2_y));
  assert(cell_in_maze(maze, c1_x, c1_y));
  assert(cell_in_maze(maze, c2_x, c2_y));

  int x = int_min(c1_x, c2_x);
  int y = int_min(c1_y, c2_y);

  if (c1_x == c2_x) {
    /* Horizontal wall */
    return bitmap_get(maze->h_walls, maze_h_wall_bit(maze, x, y));
  }
  else {
    /* Vertical wall */
    return bitmap_get(maze->v_walls, maze_v_wall_bit(maze, x, y));
  }
}


static void
maze_set_wall_between(maze_t *maze, int c1_x, int c1_y, int c2_x, int c2_y, bool exists)
{
  assert(maze);
  assert(cells_are_adjacent(c1_x, c1_y, c2_x, c2_y));
  assert(cell_in_maze(maze, c1_x, c1_y));
  assert(cell_in_maze(maze, c2_x, c2_y));

  int x = int_min(c1_x, c2_x);
  int y = int_min(c1_y, c2_y);

  if (c1_x == c2_x) {
    /* Horizontal wall */
    return bitmap_set(maze->h_walls, maze_h_wall_bit(maze, x, y), exists);
  }
  else {
    /* Vertical wall */
    return bitmap_set(maze->v_walls, maze_v_wall_bit(maze, x, y), exists);
  }
}


void
maze_add_wall_between(maze_t *maze, int c1_x, int c1_y, int c2_x, int c2_y)
{
  maze_set_wall_between(maze, c1_x, c1_y, c2_x, c2_y, true);
}


void
maze_remove_wall_between(maze_t *maze, int c1_x, int c1_y, int c2_x, int c2_y)
{
  maze_set_wall_between(maze, c1_x, c1_y, c2_x, c2_y, false);
}


void maze_add_all_walls(maze_t *maze)
{
  assert(maze);

  bitmap_fill(maze->h_walls, true);
  bitmap_fill(maze->v_walls, true);
}


void maze_remove_all_walls(maze_t *maze)
{
  assert(maze);

  bitmap_fill(maze->h_walls, false);
  bitmap_fill(maze->v_walls, false);
}
