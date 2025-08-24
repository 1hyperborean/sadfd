#include "hash_table.h"

#include <cstddef>
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

HashTable::Node* HashTable::findNode(const std::string& key) {
  size_t index = calculateBucketIndex(key);

  Node* current = bucket[index];
  while (current != nullptr) {
    if (current->key == key) {
      return current;
    }
    current = current->next;
  }

  return nullptr;
}

bool HashTable::remove(const std::string& key) {
  size_t index = calculateBucketIndex(key);

  if (bucket[index] != nullptr && bucket[index]->key == key) {
    Node* temp = bucket[index];
    bucket[index] = bucket[index]->next;
    delete temp;
    size--;
    return true;
  }

  Node* current = bucket[index];
  while (current != nullptr && current->next != nullptr) {
    if (current->next->key == key) {
      Node* temp = current->next;
      current->next = current->next->next;
      delete temp;
      size--;
      return true;
    }
    current = current->next;
  }

  return false;
}

std::string HashTable::pop(size_t bucketIndex) {
  if (bucket[bucketIndex] == nullptr) {
    throw  std::runtime_error("Bucket is empty");
  }

  Node* current = bucket[bucketIndex];
  Node* prev = nullptr;
  while (current->next != nullptr) {
    prev = current;
    current = current->next;
  }

  std::string value = current->value;
  if (prev == nullptr) {
    bucket[bucketIndex] = nullptr;
  } else {
    prev->next = nullptr;
  }
  delete current;
  size--;
  return value;
}