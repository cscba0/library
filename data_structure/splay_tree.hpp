#pragma once
#include <memory>
#include <utility>  // For std::pair

template <typename T, auto op, auto e>
struct SplayTree {
    struct node;
    using nptr = std::unique_ptr<node>;
    struct node {
        T v, p;
        int siz{1};
        bool rev{false};  // Reverse flag
        nptr left{nullptr}, right{nullptr};
        node(T _v) : v(_v), p(_v) {}
    };

    // Propagate reverse flag
    void push(nptr& ptr) {
        if (!ptr || !ptr->rev) return;
        std::swap(ptr->left, ptr->right);
        if (ptr->left) ptr->left->rev = !ptr->left->rev;
        if (ptr->right) ptr->right->rev = !ptr->right->rev;
        ptr->rev = false;
    }

    // Update node size and aggregate value
    void update(nptr& ptr) {
        if (!ptr) return;
        ptr->siz = size(ptr->left) + size(ptr->right) + 1;
        ptr->p = op(op(ptr->left ? ptr->left->p : e(), ptr->v), ptr->right ? ptr->right->p : e());
    }

    // Get size of subtree
    static int size(const nptr& ptr) {
        return !ptr ? 0 : ptr->siz;
    }

    // Rotate left
    nptr rotate_left(nptr x) {
        if (!x || !x->right) return x;
        push(x);
        nptr y = std::move(x->right);
        push(y);
        x->right = std::move(y->left);
        y->left = std::move(x);
        update(x);
        update(y);
        return y;
    }

    // Rotate right
    nptr rotate_right(nptr y) {
        if (!y || !y->left) return y;
        push(y);
        nptr x = std::move(y->left);
        push(x);
        y->left = std::move(x->right);
        x->right = std::move(y);
        update(y);
        update(x);
        return x;
    }

    // Splay operation: brings the node at index k to the root
    nptr splay(nptr ptr, int k) {
        if (!ptr) return nullptr;
        push(ptr);

        // This splay implementation is based on index (0-based)
        // To splay by value, a different approach would be needed

        int left_size = size(ptr->left);

        if (k < left_size) {  // Target is in the left subtree
            // Zig-zig or Zig-zag left
            if (!ptr->left) return std::move(ptr);  // Should not happen if k < left_size and ptr->left is null

            int grand_child_size = size(ptr->left->left);

            if (k < grand_child_size) {  // Zig-zig left
                ptr->left->left = splay(std::move(ptr->left->left), k);
                ptr = rotate_right(std::move(ptr));
            } else if (k > grand_child_size) {  // Zig-zag left
                ptr->left->right = splay(std::move(ptr->left->right), k - grand_child_size - 1);
                if (ptr->left->right) ptr->left = rotate_left(std::move(ptr->left));
            }
            return rotate_right(std::move(ptr));

        } else if (k > left_size) {  // Target is in the right subtree
            // Zig-zig or Zig-zag right
            if (!ptr->right) return std::move(ptr);  // Should not happen if k > left_size and ptr->right is null

            int grand_child_size = size(ptr->right->left);

            if (k < grand_child_size) {  // Zig-zag right
                ptr->right->left = splay(std::move(ptr->right->left), k);
                if (ptr->right->left) ptr->right = rotate_right(std::move(ptr->right));
            } else if (k > grand_child_size) {  // Zig-zig right
                ptr->right->right = splay(std::move(ptr->right->right), k - grand_child_size - 1);
                ptr = rotate_left(std::move(ptr));
            }
            return rotate_left(std::move(ptr));

        } else {  // Target is the root
            return std::move(ptr);
        }
    }

    // Split the tree into two at index k (0-based)
    // Returns {first k nodes, remaining nodes}
    std::pair<nptr, nptr> split(nptr ptr, int k) {
        if (!ptr) return {nullptr, nullptr};
        if (k == 0) return {nullptr, std::move(ptr)};
        if (k == size(ptr)) return {std::move(ptr), nullptr};

        ptr = splay(std::move(ptr), k);
        nptr left_part = std::move(ptr->left);
        ptr->left = nullptr;
        update(ptr);
        return {std::move(left_part), std::move(ptr)};
    }

    // Merge two trees (all elements in l must be less than all elements in r)
    nptr merge(nptr l, nptr r) {
        if (!l || !r) return l ? std::move(l) : std::move(r);
        // Splay the maximum element of the left tree to the root
        l = splay(std::move(l), size(l) - 1);
        l->right = std::move(r);
        update(l);
        return std::move(l);
    }

    // Insert a value v at index k (0-based)
    void insert(nptr& ptr, int k, T v) {
        auto [L, R] = split(std::move(ptr), k);
        nptr new_node = std::make_unique<node>(v);
        ptr = merge(merge(std::move(L), std::move(new_node)), std::move(R));
    }

    // Erase the node at index k (0-based)
    void erase(nptr& ptr, int k) {
        ptr = splay(std::move(ptr), k);
        nptr left_part = std::move(ptr->left);
        nptr right_part = std::move(ptr->right);
        ptr.reset();  // Delete the node
        ptr = merge(std::move(left_part), std::move(right_part));
    }

    // Reverse the nodes in range [l, r) (0-based)
    void reverse(nptr& ptr, int l, int r) {
        auto [L, tmp] = split(std::move(ptr), l);
        auto [M, R] = split(std::move(tmp), r - l);
        if (M) M->rev = !M->rev;
        ptr = merge(merge(std::move(L), std::move(M)), std::move(R));
    }

    // Get the aggregate value in range [l, r) (0-based)
    T operator()(nptr& ptr, int l, int r) {
        auto [L, tmp] = split(std::move(ptr), l);
        auto [M, R] = split(std::move(tmp), r - l);
        T res = M ? M->p : e();
        ptr = merge(merge(std::move(L), std::move(M)), std::move(R));
        return res;
    }
};
