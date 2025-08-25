#include "hash_table.h"

#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

hash_table* hash_table_create(void) {
  hash_table* table = malloc(sizeof(hash_table));
  if (table == NULL) {
    return NULL;
  }
  table->length = 0;
  table->capacity = INITIAL_CAPACITY;

  table->nodes = calloc(table->capacity, sizeof(hash_table_node));
  if (table->nodes == NULL) {
    free(table);
    return NULL;
  }
  return table;
}

void hash_table_destroy(hash_table* table) {
  for (size_t i = 0; i < table->capacity; i++) {
    free((void*)table->nodes[i].key);
  }
  free(table->nodes);
  free(table);
}

void* hash_table_get(hash_table* table, const char* key) {
  uint64_t hash = hash_key(key);
  size_t index = (size_t)(hash & (uint64_t)(table->capacity - 1));

  while (table->nodes[index].key != NULL) {
    if (strcmp(key, table->nodes[index].key) == 0) {
      return  table->nodes[index].value;
    }
    index++;
    if (index >= table->capacity) {
      index = 0;
    }
  }
  
  return NULL;
}

const char* hash_table_set(hash_table* table, const char* key, void* value) {
  assert(value != NULL);
  if (value == NULL) {
    return NULL;
  }

  if (table->length >= table->capacity / 2) {
    if (!hash_table_expand(table)) {
      return NULL;
    }
  }

  return hash_table_set_node(table->nodes, table->capacity, key, value, &table->length);
}

size_t hash_table_length(hash_table* table);

hash_table_iter hash_table_iterator(hash_table* table);
bool hash_table_next(hash_table_iter* it);

static uint64_t hash_key(const char* key) {
  uint64_t hash = FNV_OFFSET;
  for (const char* p = key; *p; p++) {
    hash ^= (uint64_t)(unsigned char)(*p);
    hash *= FNV_PRIME;
  }
  return hash;
}

static const char* hash_table_set_node(hash_table_node* entries, size_t capacity,
  const char* key, void* value, size_t* plength) {
    uint64_t hash = hash_key(key);
    size_t index = (size_t)(hash & (uint64_t)(capacity - 1));

    while (entries[index].key != NULL) {
      if (strcmp(key, entries[index].key) == 0) {
        entries[index].value = value;
        return entries[index].key;
      }
      index++;
      if (index >= capacity) {
        index = 0;
      }
    }
    if (plength != NULL) {
      key = strdup(key);
      if (key == NULL) {
          return NULL;
      }
      (*plength)++;
    }
    entries[index].key = (char*)key;
    entries[index].value = value;
    return key;
  }

static bool hash_table_expand(hash_table* table) {
  size_t new_capacity = table->capacity * 2;
  if (new_capacity < table->capacity) {
      return false; 
  }
  hash_table_node* new_entries = calloc(new_capacity, sizeof(hash_table_node));
  if (new_entries == NULL) {
      return false;
  }

  for (size_t i = 0; i < table->capacity; i++) {
      hash_table_node entry = table->nodes[i];
      if (entry.key != NULL) {
        hash_table_set_node(new_entries, new_capacity, entry.key,
                       entry.value, NULL);
      }
  }

  free(table->nodes);
  table->nodes = new_entries;
  table->capacity = new_capacity;
  return true;
}

size_t hash_table_length(hash_table* table) {
  return table->length;
}

hash_table_iter ht_iterator(hash_table* table) {
  hash_table_iter it;
  it._table = table;
  it._index = 0;
  return it;
}

bool ht_next(hash_table_iter* it) {
  hash_table* table = it->_table;
  while (it->_index < table->capacity) {
      size_t i = it->_index;
      it->_index++;
      if (table->nodes[i].key != NULL) {
          hash_table_node node = table->nodes[i];
          it->key = node.key;
          it->value = node.value;
          return true;
      }
  }
  return false;
}