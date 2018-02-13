#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "model.h"
#include "renderer.h"
#include "prims_maze.h"


int
main(int argc, char *argv[])
{
  maze_t *maze = maze_create(30, 20);

  srand(time(NULL));

  prims_maze_generate(maze);
  render_maze(maze);

  maze_free(&maze);
  return 0;
}
