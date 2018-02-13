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

#include "renderer.h"
#include <stdbool.h>
#include <stdio.h>


static void
render_junction(bool top, bool right, bool bottom, bool left)
{
  int total_walls = top + right + bottom + left;

  switch (total_walls) {
    case 3:
    case 4:
      printf("+");
      break;

    case 2:
      if (top && bottom) {
        printf("|");
      }
      else if (left && right) {
        printf("-");
      }
      else if (top) {
        printf("'");
      }
      else {
        printf(".");
      }

      break;

    case 1:
      if (top) {
        printf("'");
      }
      else if (bottom) {
        printf(".");
      }
      else {
        printf("-");
      }
      break;

    case 0:
    default:
      printf(" ");
  }
}


static void
render_horizontal_walls(maze_t *maze, int y)
{
  int width = maze_get_width(maze);

  render_junction(
    true,
    maze_has_wall_between(maze, 0, y, 0, y + 1),
    true,
    false
  );

  for (int x = 0; x < width - 1; ++x) {
    if (maze_has_wall_between(maze, x, y, x, y + 1)) {
      printf("--");
    }
    else {
      printf("  ");
    }

    render_junction(
      maze_has_wall_between(maze, x, y, x + 1, y),
      maze_has_wall_between(maze, x + 1, y, x + 1, y + 1),
      maze_has_wall_between(maze, x, y + 1, x + 1, y + 1),
      maze_has_wall_between(maze, x, y, x, y + 1)
    );
  }

  if (maze_has_wall_between(maze, width - 1, y, width - 1, y + 1)) {
    printf("--");
  }
  else {
    printf("  ");
  }

  render_junction(
    true,
    false,
    true,
    maze_has_wall_between(maze, width - 1, y, width - 1, y + 1)
  );

  printf("\n");
}


static void
render_top_wall(maze_t *maze)
{
  int width = maze_get_width(maze);

  render_junction(false, true, true, false);

  printf("--");

  for (int x = 0; x < width - 1; ++x) {
    render_junction(
      false,
      true,
      maze_has_wall_between(maze, x, 0, x + 1, 0),
      true
    );
    printf("--");
  }

  render_junction(false, false, true, true);

  printf("\n");
}


static void
render_bottom_wall(maze_t *maze)
{
  int width = maze_get_width(maze);
  int height = maze_get_height(maze);

  render_junction(true, true, false, false);

  printf("--");

  for (int x = 0; x < width - 1; ++x) {
    render_junction(
      maze_has_wall_between(maze, x, height - 1, x + 1, height - 1),
      true,
      false,
      true
    );
    printf("--");
  }

  render_junction(true, false, false, true);

  printf("\n");
}


static void
render_vertical_walls(maze_t *maze, int y)
{
  int width = maze_get_width(maze);

  printf("|");

  for (int x = 0; x < width - 1; ++x) {
    if (maze_has_wall_between(maze, x, y, x + 1, y)) {
      printf("  |");
    }
    else {
      printf("   ");
    }
  }

  printf("  |\n");
}


void
render_maze(maze_t *maze)
{
  int height = maze_get_height(maze);

  render_top_wall(maze);

  for (int y = 0; y < height - 1; ++y) {
    render_vertical_walls(maze, y);
    render_horizontal_walls(maze, y);
  }

  render_vertical_walls(maze, height - 1);
  render_bottom_wall(maze);
}
