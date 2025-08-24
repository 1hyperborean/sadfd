#include "hash_table.h"

#include <stdexcept>

void HashTable::insert(const std::string& key, const std::string& value) {
  size_t index = calculateBucketIndex(key);

  Node* current = bucket[index];
  while (current != nullptr) {
    if (current->key == key) {
      current->value = value;
      return;
    }
    current = current->next;
  }

  Node* newNode = new Node(key, value, bucket[index]);
  bucket[index] = newNode;
  size++;
}

std::string HashTable::get(const std::string& key) {
  size_t index = calculateBucketIndex(key);

  Node* current = bucket[index];
  while (current != nullptr) {
    if (current->key == key) {
      return current->value;
    }
    current = current->next;
  }

  throw std::runtime_error("Key not found");
}

bool HashTable::contains(const std::string& key) {
  size_t index = calculateBucketIndex(key);

  Node* current = bucket[index];
  while (current != nullptr) {
    if (current->key == key) {
      return true;
    }
    current = current->next;
  }

  return false;
}