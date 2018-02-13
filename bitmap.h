#ifndef BITMAP_H
#define BITMAP_H

#include <stdbool.h>


typedef struct bitmap_t_ bitmap_t;

bitmap_t *bitmap_create(int size);
void bitmap_free(bitmap_t **bitmap);

bool bitmap_get(bitmap_t *bitmap, int bit);
void bitmap_set(bitmap_t *bitmap, int bit, bool value);
void bitmap_fill(bitmap_t *bitmap, bool value);

#endif
