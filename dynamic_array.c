#include "dynamic_array.h"
#include <stdlib.h>
#include <string.h>

const int ARRAY_MIN_SIZE = 1024;


struct array_t_ {
  int length;
  int element_size;
  int allocated_size;
  void *data;
};


static void
array_init(array_t *array, int element_size)
{
  array->length = 0;
  array->element_size = element_size;
  array->allocated_size = ARRAY_MIN_SIZE;
  array->data = malloc(array->element_size * array->allocated_size);
}


array_t *
array_create(int element_size)
{
  array_t *array = (array_t *) malloc(sizeof(array_t));

  array_init(array, element_size);
  return array;
}


static void
array_destroy(array_t *array)
{
  free(array->data);
  array->data = NULL;
  array->allocated_size = 0;
}


void
array_free(array_t **array)
{
  array_destroy(*array);
  free(*array);
  *array = NULL;
}



int
array_length(array_t *array)
{
  return array->length;
}


bool
array_empty(array_t *array)
{
  return array->length == 0;
}


void
array_resize(array_t *array, int length)
{
  if (length > array->allocated_size) {
    while (length > array->allocated_size) {
      array->allocated_size *= 2;
    }

    array->data = realloc(array->data, array->allocated_size * array->element_size);
  }

  if (array->allocated_size > ARRAY_MIN_SIZE && length <= array->allocated_size / 2) {
    while (length <= array->allocated_size / 2) {
      array->allocated_size /= 2;
    }

    array->data = realloc(array->data, array->allocated_size * array->element_size);
  }

  array->length = length;
}


const void *
array_get(array_t *array, int index)
{
  return (const void *) array->data + (index * array->element_size);
}


void
array_get_copy(array_t *array, int index, void *element)
{
  memcpy(element, array->data + (index * array->element_size), array->element_size);
}


void
array_set(array_t *array, int index, const void *element)
{
  memcpy(array->data + (index * array->element_size), element, array->element_size);
}


void
array_push(array_t *array, const void *element)
{
  array_resize(array, array->length + 1);
  array_set(array, array->length - 1, element);
}


void
array_pop(array_t *array, void *element)
{
  memcpy(element, array_get(array, array->length - 1), array->element_size);
  array_resize(array, array->length - 1);
}
