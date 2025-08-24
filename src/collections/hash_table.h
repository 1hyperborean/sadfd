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

  size_t calculateBucketIndex(const std::string& key) {
    size_t index = std::hash<std::string>{}(key) % bucket.size();
    return index;
  }
  void resize(size_t newBucketCount) {
    std::vector<Node*> oldBuckets = bucket;
    bucket.clear();
    bucket.resize(newBucketCount, nullptr);
    size = 0;

    for (Node* oldNode : oldBuckets) {
      while (oldNode != nullptr) {
        insert(oldNode->key, oldNode->value);
        Node* temp = oldNode;
        oldNode = oldNode->next;
        delete temp;
      }
    }
  }
  void checkAndResize() {
    double loadFactor = static_cast<double>(size) / bucket.size();
    if (loadFactor > LOAD_FACTOR_TRESHOLD) {
      resize(bucket.size() * 2);
    }
  }
public:
  static const size_t DEFAULT_BUCKET_COUNT = 16;
  double LOAD_FACTOR_TRESHOLD = 0.75;

  HashTable() : bucket(DEFAULT_BUCKET_COUNT, nullptr), size(0) {}
  ~HashTable();

  void insert(const std::string& key, const std::string& value);
  std::string get(const std::string& key);
  bool contains(const std::string& key);
  Node* findNode(const std::string& key);
  bool remove(const std::string& key);
  std::string pop(size_t bucketIndex);
};