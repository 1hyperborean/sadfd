#include "collections/hash_table.h"
#include <iostream>
#include <cassert>
#include <chrono>

void testBasicOperations() {
    std::cout << "Testing basic operations..." << std::endl;
    
    HashTable table;
    
    // Test insert and get
    table.insert("name", "John");
    assert(table.get("name") == "John");
    
    // Test contains
    assert(table.contains("name") == true);
    assert(table.contains("age") == false);
    
    // Test remove
    table.insert("age", "25");
    assert(table.remove("age") == true);
    assert(table.contains("age") == false);
    
    std::cout << "✓ Basic operations passed" << std::endl;
}

void testCollisionScenarios() {
    std::cout << "Testing collision scenarios..." << std::endl;
    
    HashTable table;
    
    // Force collisions by using keys that hash to same bucket
    // This is tricky to predict, so we'll insert many items
    for (int i = 0; i < 50; i++) {
        std::string key = "key" + std::to_string(i);
        std::string value = "value" + std::to_string(i);
        table.insert(key, value);
    }
    
    // Verify all items can still be retrieved
    for (int i = 0; i < 50; i++) {
        std::string key = "key" + std::to_string(i);
        std::string expected = "value" + std::to_string(i);
        assert(table.get(key) == expected);
    }
    
    std::cout << "✓ Collision scenarios passed" << std::endl;
}

void testResizeBehavior() {
    std::cout << "Testing resize behavior..." << std::endl;
    
    HashTable table;
    
    // Insert enough items to trigger resize (more than 75% of 16 buckets)
    for (int i = 0; i < 20; i++) {
        std::string key = "resize_key" + std::to_string(i);
        std::string value = "resize_value" + std::to_string(i);
        table.insert(key, value);
    }
    
    // Verify all items are still accessible after resize
    for (int i = 0; i < 20; i++) {
        std::string key = "resize_key" + std::to_string(i);
        std::string expected = "resize_value" + std::to_string(i);
        assert(table.get(key) == expected);
    }
    
    std::cout << "✓ Resize behavior passed" << std::endl;
}

void testEdgeCases() {
    std::cout << "Testing edge cases..." << std::endl;
    
    HashTable table;
    
    // Test empty table
    assert(table.contains("anything") == false);
    
    // Test single item
    table.insert("single", "item");
    assert(table.get("single") == "item");
    
    // Test duplicate keys (should update value)
    table.insert("duplicate", "first");
    table.insert("duplicate", "second");
    assert(table.get("duplicate") == "second");
    
    // Test removing non-existent key
    assert(table.remove("nonexistent") == false);
    
    std::cout << "✓ Edge cases passed" << std::endl;
}

void testCopyAndAssignment() {
    std::cout << "Testing copy constructor and assignment..." << std::endl;
    
    HashTable original;
    original.insert("key1", "value1");
    original.insert("key2", "value2");
    
    // Test copy constructor
    HashTable copy = original;
    assert(copy.get("key1") == "value1");
    assert(copy.get("key2") == "value2");
    
    // Test assignment operator
    HashTable assigned;
    assigned = original;
    assert(assigned.get("key1") == "value1");
    assert(assigned.get("key2") == "value2");
    
    // Test self-assignment
    original = original;
    assert(original.get("key1") == "value1");
    
    std::cout << "✓ Copy and assignment passed" << std::endl;
}

void performanceTest() {
    std::cout << "Testing performance..." << std::endl;
    
    HashTable table;
    
    // Measure insert time
    auto start = std::chrono::high_resolution_clock::now();
    
    for (int i = 0; i < 10000; i++) {
        std::string key = "perf_key" + std::to_string(i);
        std::string value = "perf_value" + std::to_string(i);
        table.insert(key, value);
    }
    
    auto insert_end = std::chrono::high_resolution_clock::now();
    auto insert_time = std::chrono::duration_cast<std::chrono::microseconds>(insert_end - start);
    
    // Measure get time
    start = std::chrono::high_resolution_clock::now();
    
    for (int i = 0; i < 10000; i++) {
        std::string key = "perf_key" + std::to_string(i);
        table.get(key);
    }
    
    auto get_end = std::chrono::high_resolution_clock::now();
    auto get_time = std::chrono::duration_cast<std::chrono::microseconds>(get_end - start);
    
    std::cout << "Inserted 10,000 items in: " << insert_time.count() << " μs" << std::endl;
    std::cout << "Retrieved 10,000 items in: " << get_time.count() << " μs" << std::endl;
    std::cout << "✓ Performance test completed" << std::endl;
}

int main() {
    std::cout << "Starting HashTable tests..." << std::endl;
    std::cout << "================================" << std::endl;
    
    try {
        testBasicOperations();
        testCollisionScenarios();
        testResizeBehavior();
        testEdgeCases();
        testCopyAndAssignment();
        performanceTest();
        
        std::cout << "================================" << std::endl;
        std::cout << "All tests passed successfully! 🎉" << std::endl;
        
    } catch (const std::exception& e) {
        std::cerr << "Test failed with exception: " << e.what() << std::endl;
        return 1;
    }
    
    return 0;
}