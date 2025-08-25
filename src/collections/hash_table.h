#ifndef HASH_TABLE_H
#define HASH_TABLE_H

#include <stddef.h>
#include <stdbool.h>
#include <stdint.h>

#define INITIAL_CAPACITY 16
#define FNV_OFFSET 14695981039346656037UL
#define FNV_PRIME 1099511628211UL

typedef struct {
  const char* key;
  void* value;
} hash_table_node;

typedef struct {
  hash_table_node* nodes;
  size_t capacity;
  size_t length;
} hash_table;

typedef struct {
  const char* key;
  void* value;

  hash_table* _table;
  size_t _index;
} hash_table_iter;

hash_table* hash_table_create(void);
void hash_table_destroy(hash_table* table);
void* hash_table_get(hash_table* table, const char* key);
const char* hash_table_set(hash_table* table, const char* key, void* value);
size_t hash_table_length(hash_table* table);

hash_table_iter hash_table_iterator(hash_table* table);
bool hash_table_next(hash_table_iter* it);

static uint64_t hash_key(const char* key);

static const char* hash_table_set_node(hash_table_node* entries, size_t capacity,
  const char* key, void* value, size_t* plength);
static bool hash_table_expand(hash_table* table);

#endif