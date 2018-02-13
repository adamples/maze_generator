#ifndef DYNAMIC_ARRAY_H
#define DYNAMIC_ARRAY_H

#include <stdbool.h>


typedef struct array_t_ array_t;


array_t *array_create(int element_size);
void array_free(array_t **array);

void array_resize(array_t *array, int length);
int array_length(array_t *array);
bool array_empty(array_t *array);

const void *array_get(array_t *array, int index);
void array_get_copy(array_t *array, int index, void *element);
void array_set(array_t *array, int index, const void *element);

void array_push(array_t *array, const void *element);
void array_pop(array_t *array, void *element);

#endif
