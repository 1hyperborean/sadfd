#pragma once

#include <cstddef>
#include <functional>
#include <string>
#include <vector>

class HashTable {
private:
  struct Node {
    std::string key;
    std::string value;
    Node* next;

    Node(std::string k, std::string v, Node* n) 
      : key(k), value(v), next(n) {} 
  };
  std::vector<Node*> bucket;
  size_t size;
public:
  static const size_t DEFAULT_BUCKET_COUNT = 16;
  size_t LOAD_FACTOR_TRESHOLD;

  HashTable() : bucket(DEFAULT_BUCKET_COUNT, nullptr), size(0) {}

  void insert(const std::string& key, const std::string& value);
};