#include "bitmap.h"
#include <assert.h>
#include <stdlib.h>

typedef unsigned int bitmap_int_t;
const int BITMAP_INT_BIT_SIZE = sizeof(bitmap_int_t) * 8;


struct bitmap_t_ {
  int size;
  int data_size;
  bitmap_int_t *data;
};


static void
bitmap_init(bitmap_t *bitmap, int size)
{
  assert(bitmap);

  bitmap->size = size;
  bitmap->data_size = size / BITMAP_INT_BIT_SIZE;

  if (bitmap->data_size * BITMAP_INT_BIT_SIZE < size)
    ++bitmap->data_size;

  bitmap->data = (bitmap_int_t *) malloc(bitmap->data_size * sizeof(bitmap_int_t));
}


bitmap_t *
bitmap_create(int size)
{
  bitmap_t *bitmap = (bitmap_t *) malloc(sizeof(bitmap_t));

  bitmap_init(bitmap, size);
  return bitmap;
}


static void
bitmap_destroy(bitmap_t *bitmap)
{
  assert(bitmap);
  free(bitmap->data);
  bitmap->data = NULL;
}


void
bitmap_free(bitmap_t **bitmap)
{
  assert(bitmap);
  assert(*bitmap);

  bitmap_destroy(*bitmap);
  free(*bitmap);
  *bitmap = NULL;
}


bool
bitmap_get(bitmap_t *bitmap, int bit)
{
  assert(bitmap);
  assert(bit >= 0 && bit < bitmap->size);

  int word_idx = bit / BITMAP_INT_BIT_SIZE;
  int bit_idx = bit % BITMAP_INT_BIT_SIZE;
  bitmap_int_t word = bitmap->data[word_idx];

  return word & (1 << bit_idx);
}


void
bitmap_set(bitmap_t *bitmap, int bit, bool value)
{
  assert(bitmap);
  assert(bit >= 0 && bit < bitmap->size);

  int word_idx = bit / BITMAP_INT_BIT_SIZE;
  int bit_idx = bit % BITMAP_INT_BIT_SIZE;

  if (value) {
    bitmap->data[word_idx] |= (1 << bit_idx);
  }
  else {
    bitmap->data[word_idx] &= ~(1 << bit_idx);
  }
}


void
bitmap_fill(bitmap_t *bitmap, bool value)
{
  assert(bitmap);

  bitmap_int_t word_value = 0;

  if (value) {
    /* This will set word_value to all 1s, independent of size */
    --word_value;
  }

  for (int i = 0; i < bitmap->data_size; ++i) {
    bitmap->data[i] = word_value;
  }
}
