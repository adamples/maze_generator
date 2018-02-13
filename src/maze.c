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

#include <stdlib.h>
#include <stdio.h>
#include <inttypes.h>
#include <errno.h>
#include <time.h>
#include "model.h"
#include "renderer.h"
#include "prims_maze.h"


int
error(const char *message)
{
  fprintf(stderr, "maze: %s\n", message);
  fprintf(stderr, "usage: maze width height [ random_seed ]\n");
  return -1;
}


int
main(int argc, char *argv[])
{
  maze_t *maze;
  int random_seed;

  if (argc < 3 || argc > 4) {
    return error("Wrong number of arguments");
  }

  int width = strtoimax(argv[1], NULL, 10);

  if (errno != 0 || width < 2) {
    return error("Invalid width value");
  }

  int height = strtoimax(argv[2], NULL, 10);

  if (errno != 0 || height < 2) {
    return error("Invalid height value");
  }

  if (argc == 4) {
    random_seed = strtoimax(argv[3], NULL, 10);

    if (errno != 0) {
      return error("Invalid random seed value");
    }
  }
  else {
    random_seed = time(NULL);
  }

  printf("Random seed is %d\n\n", random_seed);
  srand(random_seed);

  maze = maze_create(width, height);

  prims_maze_generate(maze);
  render_maze(maze);

  maze_free(&maze);
  return 0;
}
