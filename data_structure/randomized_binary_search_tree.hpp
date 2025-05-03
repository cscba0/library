#pragma once
#include <memory>

template <typename K, typename V>
struct RandomizedBinarySearchTree {
    struct node;
    using nptr = std::unique_ptr<node>;
    struct node {
        K key;
        V v;
        int size{0};
    };
};
