#pragma once

namespace s21 {

    template <typename Key, typename T>
    struct Node {
        using value_type = std::pair<const Key, T>;

        value_type value;
        Node* left;
        Node* right;
        Node* parent;

        Node(const value_type& v)
                : value(v), left(nullptr), right(nullptr), parent(nullptr) {}
        size_t size() { return 1 + (left ? left->size() : 0) + (right ? right->size() : 0); }
    };

    template <typename Key, typename T>
    class b_tree {
    public:
        using value_type = std::pair<const Key, T>;

    private:
        Node<Key, T>* root;
        size_t size;

        void copy(Node<Key, T>* node);
        void destroy(Node<Key, T>* node);

    public:
        b_tree();
        b_tree(const b_tree &other);
        ~b_tree();

        b_tree& operator=(const b_tree &t) noexcept;

        Node<Key, T>* first() const;
        Node<Key, T>* last() const;

        Node<Key, T>* find_node(const Key &key) const;
        Node<Key, T>* insert_node(value_type v);
        void remove_node(Node<Key, T>* node);
        void clear();
        size_t get_size() const;
    };
}

#include "s21_binary_tree.tpp"