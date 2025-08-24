#include "hash_table.h"

void HashTable::insert(const std::string& key, const std::string& value) {
  if (bucket.size() == 0) {

  }
  
  size_t index = std::hash<std::string>{}(key) % bucket.size();

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