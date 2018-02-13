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
