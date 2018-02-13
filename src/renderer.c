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
