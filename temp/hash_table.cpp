#include "hash_table.h"

#include <cstddef>
#include <stdexcept>

HashTable::~HashTable() {
  for (Node* head : bucket) {
      while (head != nullptr) {
          Node* temp = head;
          head = head->next;
          delete temp;
      }
  }
}

HashTable::HashTable(const HashTable& other) : bucket(other.bucket.size(), nullptr), size(0) {
  for (size_t i = 0; i < other.bucket.size(); i++) {
    Node* otherNode = other.bucket[i];
    while (otherNode != nullptr) {
      insert(otherNode->key, otherNode->value);
      otherNode = otherNode->next;
    }
  }
}

HashTable& HashTable::operator=(const HashTable& other) {
  if (this == &other) {
    return *this;
  }

  for (Node* node : bucket) {
    while (node != nullptr) {
      Node* temp = node;
      node = node->next;
      delete temp;
    }
  }

  bucket.clear();
  bucket.resize(other.bucket.size(), nullptr);
  size = 0;

  for (size_t i = 0; i < other.bucket.size(); i++) {
    Node* otherNode = other.bucket[i];
    while (otherNode != nullptr) {
      insert(otherNode->key, otherNode->value);
      otherNode = otherNode->next;
    }
  }

  return *this;
}

void HashTable::insert(const std::string& key, const std::string& value) {
  checkAndResize();
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