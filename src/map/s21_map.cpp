#include "s21_Map.h"

using namespace s21;

template <typename Key, typename T>
typename Map<Key, T>::iterator Map<Key, T>::Map<Key, T>::find_node(Node *node, const Key &key) const {
    while (node && key != node->value.first) node = key < node->value.first ? node->left : node->right;

    return iterator(node);
}

//template <typename Key, typename T>
//void Map<Key, T>::insert_node(Node *node, value_type v) {
//    if (v.first > node->value.first) {
//        if (node->right) insert_node(node->right, v);
//        else node->right = new Node(v);
//    } else if (v.first < node->value.first) {
//        if (node->left) insert_node(node->left, v);
//        else node->left = new Node(v);
//    }
//}

template <typename Key, typename T>
typename Map<Key, T>::iterator Map<Key, T>::insert_node(Node *node, value_type v) {
    while (!(v.first > node->value.first && !node->right) && !(v.first < node->value.first && !node->left)) {
        node = v.first > node->value.first ? node->right : node->left;
    }

    if (v.first > node->value.first) {
        node->right = new Node(v);
        node->right->parent = node;
    } else {
        node->left = new Node(v);
        node->left->parent = node;
    }

    ++num_of_elems;

    return iterator(v.first > node->value.first ? node->right : node->left);
}

template <typename Key, typename T>
void Map<Key, T>::copy_tree(Node* node) {
    if (node) {
        insert(node->value);
        copy_tree(node->left);
        copy_tree(node->right);
    }
}

template <typename Key, typename T>
void Map<Key, T>::clear_tree(Node* node) {
    if (node) {
        clear_tree(node->left);
        clear_tree(node->right);
        delete node;
    }
}

template <typename Key, typename T>
Map<Key, T>::Map() : root(nullptr), num_of_elems(0) {}

template <typename Key, typename T>
Map<Key, T>::Map(std::initializer_list<value_type> const &items)
        : root(nullptr), num_of_elems(0) {
    for (const auto &item : items) insert(item);
}

template <typename Key, typename T>
Map<Key, T>::Map(const Map& m) { copy_tree(m.root); }

template <typename Key, typename T>
Map<Key, T>::Map(Map&& m) noexcept {
    if (this != &m) {
        clear();
        root = s.root;
        num_of_elems = s.num_of_elems;
        s.root = nullptr;
        s.num_of_elems = 0;
    }
}

template <typename Key, typename T>
Map<Key, T>::~Map() {
    clear();
}

template <typename Key, typename T>
typename Map<Key, T>::Map &Map<Key, T>::operator=(Map &&m) noexcept {
    if (this != &m) {
        clear();
        root = s.root;
        num_of_elems = s.num_of_elems;
        s.root = nullptr;
        s.num_of_elems = 0;
    }
    return *this;
}

template <typename Key, typename T>
T& Map<Key, T>::at(const Key& key) {
    auto it = find_node(root, key);

    if (it == nullptr) throw std::out_of_range;
    else return it->value.second;
}

template <typename Key, typename T>
T& Map<Key, T>::operator[](const Key& key) {
    auto [it, inserted] = insert({key, 0});

    return it->value.second;
}

template <typename Key, typename T>
typename Map<Key, T>::iterator Map<Key, T>::begin() {
    Node* node = root;

    while (node && node->left) node = node->left;

    return iterator(node);
}

template <typename Key, typename T>
typename Map<Key, T>::iterator Map<Key, T>::end() {
    Node* node = root;

    while (node && node->right) node = node->right;

    return iterator(node);
}

template <typename Key, typename T>
typename Map<Key, T>::const_iterator Map<Key, T>::begin() const {
    Node* node = root;

    while (node && node->left) node = node->left;

    return const_iterator(node);
}

template <typename Key, typename T>
typename Map<Key, T>::const_iterator Map<Key, T>::end() const {
    Node* node = root;

    while (node && node->right) node = node->right;

    return const_iterator(node);
}

template <typename Key, typename T>
bool Map<Key, T>::empty() const { return !num_of_elems; }

template <typename Key, typename T>
size_type Map<Key, T>::size() const { return num_of_elems; }

template <typename Key, typename T>
size_type Map<Key, T>::max_size() const { return 230584300921369395; }

template <typename Key, typename T>
void Map<Key, T>::clear() {
    clear_tree(root);
    root = nullptr;
    num_of_elems = 0;
}

template <typename Key, typename T>
std::pair<typename Map<Key, T>::iterator, bool> Map<Key, T>::insert(const_reference value) {
    bool inserted = false;
    auto it = find_node(root, value.first);

    if (!it) {
        it = insert_node(root, value);
        inserted = true;
    }

    return std::make_pair(it, inserted);
}

template <typename Key, typename T>
std::pair<typename Map<Key, T>::iterator, bool> Map<Key, T>::insert(const K& key, const T& obj) {
    bool inserted = false;
    auto it = find_node(root, key);

    if (!it) {
        it = insert_node(root, {key, obj});
        inserted = true;
    }

    return std::make_pair(it, inserted);
}

template <typename Key, typename T>
std::pair<typename Map<Key, T>::iterator, bool> Map<Key, T>::insert_or_assign(const Key& key, const T& obj) {
    auto it = find_node(root, key);

    if (it) node->value.second = obj;
    else it = insert_node(root, {key, obj});

    return std::make_pair(it, true);
}

template <typename Key, typename T>
void Map<Key, T>::erase(iterator pos) {
    pos->parent->right = pos->right;
    pos->parent->left = pos->left;
    delete pos;
    --num_of_elems;
}

template <typename Key, typename T>
void Map<Key, T>::swap(map& other) {
    Node* tmp_root = root;
    size_t tmp_num = num_of_elems;

    root = other.root;
    other.root = tmp_root;

    num_of_elems = other.num_of_elems;
    other.num_of_elems = tmp_num;
}

template <typename Key, typename T>
void Map<Key, T>::merge(map& other) {
    for (auto i : other) {
        const auto [it, inserted] = insert(*i);
        if (inserted) other.erase(i);
    }
}

template <typename Key, typename T>
bool Map<Key, T>::contains(const Key& key) { return find_node(root, key) != nullptr; }

template <typename Key, typename T>
Map<Key, T>::iterator::Iterator(Node* node) : current(node) {}

template <typename Key, typename T>
reference Map<Key, T>::iterator::operator*() { return current->value; }

template <typename Key, typename T>
typename Map<Key, T>::iterator::Iterator &Map<Key, T>::iterator::operator++() {
    if (current->right) {
        current = current->right;
        while (current->left) current = current->left;
    } else if (current->parent) {
        Node* tmp = current;
        do {
            current = current->parent;
        } while (tmp->parent && tmp == tmp->parent->right);

        if (tmp) current = tmp;
        else throw std::out_of_range;
    } else throw std::out_of_range;

    return *this;
}

template <typename Key, typename T>
typename Map<Key, T>::iterator::Iterator &Map<Key, T>::iterator::operator--() {
    if (current->left) {
        current = current->left;
        while (current->right) current = current->right;
    } else if (current->parent) {
        Node* tmp = current;
        do {
            current = current->parent;
        } while (tmp->parent && tmp == tmp->parent->left);

        if (tmp) current = tmp;
        else throw std::out_of_range;
    } else throw std::out_of_range;

    return *this;
}

template <typename Key, typename T>
bool Map<Key, T>::iterator::operator==(Iterator& other) { return current == other.current; }

template <typename Key, typename T>
bool Map<Key, T>::iterator::operator!=(Iterator& other) { return current != other.current; }

template <typename Key, typename T>
const_reference Map<Key, T>::iterator::operator*() const { return current->value; }