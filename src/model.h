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

#ifndef MAZE_MODEL_H
#define MAZE_MODEL_H

#include <stdbool.h>


typedef struct maze_t_ maze_t;


maze_t *maze_create(int width, int height);
void maze_free(maze_t **maze);

int maze_get_width(maze_t *maze);
int maze_get_height(maze_t *maze);

bool maze_has_wall_between(maze_t *maze, int c1_x, int c1_y, int c2_x, int c2_y);
void maze_add_wall_between(maze_t *maze, int c1_x, int c1_y, int c2_x, int c2_y);
void maze_remove_wall_between(maze_t *maze, int c1_x, int c1_y, int c2_x, int c2_y);

void maze_add_all_walls(maze_t *maze);
void maze_remove_all_walls(maze_t *maze);

#endif
