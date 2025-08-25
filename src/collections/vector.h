#ifndef VECTOR_H
#define VECTOR_H

#include <stddef.h>
#include <stdbool.h>

typedef struct {
  int *data;
  size_t size;
  size_t size_max;
} CVector;

CVector* vector_create(int size_max);
void vector_push(CVector* vec, int value);
int vector_get(CVector* vec, int index);
void vector_remove(CVector* vec, int index);
void vector_free(CVector* vec);
void vector_resize(CVector* vec);
bool vector_check_index_bounds(CVector* vec, int index);
void vector_display(CVector* vec);

#endif