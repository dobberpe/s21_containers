#ifndef S21_Map
#define S21_Map

#include <initializer_list>
#include <iostream>
#include <utility>

namespace s21 {

    template <typename Key, typename T>
    class Map {
    public:
        template <typename Key, typename T>
        class Iterator;

        template <typename Key, typename T>
        class ConstIterator;

        using key_type = Key;
        using mapped_type = T;
        using value_type = std::pair<const key_type, mapped_type>;
        using reference = value_type&;
        using const_reference = const value_type&;
        using iterator = Iterator<Key, T>;
        using const_iterator = ConstIterator<Key, T>;
        using size_type = size_t;

    private:
        struct Node {
            value_type value;
            Node* left;
            Node* right;
            Node* parent;

            Node(const_reference v)
                    : value(v), left(nullptr), right(nullptr), parent(nullptr) {}
        };

        Node* root;
        size_t num_of_elems;

        iterator find_node(Node *node, const Key &key) const;
        iterator insert_node(Node* node, value_type v);
        void copy_tree(Node* tree);
        void clear_tree(Node* node);

    public:
        Map();
        Map(std::initializer_list<value_type> const& items);
        Map(const Map& m);
        Map(Map&& m) noexcept;
        ~Map();

        Map& operator=(Map&& m) noexcept;

        T& at(const Key& key);
        T& operator[](const Key& key);

        iterator begin();
        iterator end();
        const_iterator begin() const;
        const_iterator end() const;

        bool empty() const;
        size_type size() const;
        size_type max_size() const;

        void clear();
        std::pair<iterator, bool> insert(const_reference& value);
        std::pair<iterator, bool> insert(const Key& key, const T& obj);
        std::pair<iterator, bool> insert_or_assign(const Key& key, const T& obj);
        void erase(iterator pos);
        void swap(map& other);
        void merge(map& other);

        bool contains(const Key& key);

        template <typename Key, typename T>
        class Iterator {
        private:
            Node* current;

        public:
            Iterator(Node* node);

            reference operator*();
            Iterator& operator++();
            Iterator& operator--();
            bool operator==(const Iterator& other);
            bool operator!=(const Iterator& other);
        };

        template <typename Key, typename T>
        class ConstIterator {};
    };

//    template class Map<int>;
//    template class MapIterator<int>;
//    template class MapConstIterator<int>;

}  // namespace s21

#endif
