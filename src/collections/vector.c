#include "vector.h"
#include "../utility/logger.h"

#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <string.h>

CVector* vector_create(int size_max) {
  CVector* vec = malloc(sizeof(CVector));
  vec->data = malloc(sizeof(int)*size_max);
  vec->size = 0;
  vec->size_max = size_max;
  return vec;
}

void vector_push(CVector* vec, int item) {
  if (vec->size >= vec->size_max * 0.75) {
    vector_resize(vec);
  }
  vec->data[vec->size++] = item;
}

int vector_get(CVector* vec, int index) {
  vector_check_index_bounds(vec, index);
  return vec->data[index];
}

void vector_remove(CVector* vec, int index) {
  vector_check_index_bounds(vec, index);
  vec->data[index] = vec->data[vec->size-1];
  vec->size--;
}

void vector_free(CVector* vec) {
  free(vec->data);
  free(vec);
}

void vector_resize(CVector* vec) {
    void* res = realloc(vec->data, sizeof(int)*vec->size_max*2);
    if (res == NULL) {
      fprintf(stderr, "Failed to reallocate memory\n");
      return;
    }
    vec->data = res;
    vec->size_max *= 2;
}

bool vector_check_index_bounds(CVector* vec, int index) {
  if (index >= vec->size) {

    fprintf(stderr, "Index out of bounds\n");
    return true;
  }
  return false;
}

void vector_display(CVector* vec) {
  printf("%s", "Vector data: [");
  for (int i = 0; i < vec->size; i++) {
    printf("%d", vec->data[i]);
    if (i < vec->size-1) {
      printf(", ");
    }
  }
  printf("]\n");

  char buffer[32];
  snprintf(buffer, sizeof(buffer), "Vector size: %zu", vec->size);
  log(LOG_DEBUG, buffer);
  char bufferSize[32];
  snprintf(bufferSize, sizeof(bufferSize), "Vector max size: %zu", vec->size_max);
  log(LOG_DEBUG, bufferSize);
}