#include <iostream>
#include <stdexcept>
#include <initializer_list>
#include <utility>
#include <set>
#include <iterator>

template<typename Key>
class SetIterator;

template<typename Key>
class SetConstIterator;

template<typename Key>
class Set {
public:
using key_type = Key;
using value_type = Key;
using reference = value_type&;
using const_reference = const value_type&;
using iterator = SetIterator<Key>;
using const_iterator = SetConstIterator<Key>;
using size_type = size_t;

private:
    struct Node {
        Key key;
        Node* left;
        Node* right;
        Node* parent;

        Node(const_reference k) : key(k), left(nullptr), right(nullptr), parent(nullptr) {}
    };

    Node* root;
    size_t num_elements;

    void transplant(Node* u, Node* v) {
        if (u->parent == nullptr)
            root = v;
        else if (u == u->parent->left)
            u->parent->left = v;
        else
            u->parent->right = v;
        if (v != nullptr)
            v->parent = u->parent;
    }

    Node* min_node(Node* node) {
        while (node->left != nullptr)
            node = node->left;
        return node;
    }

    void destroy(Node* node) {
        if (node != nullptr) {
            destroy(node->left);
            destroy(node->right);
            delete node;
        }
    }

    Node* copy_nodes(Node* other, Node* parent) {
        if (other == nullptr)
            return nullptr;
        Node* new_node = new Node(other->key);
        new_node->parent = parent;
        new_node->left = copy_nodes(other->left, new_node);
        new_node->right = copy_nodes(other->right, new_node);
        return new_node;
    }

    Node* find_node(const_reference key) const {
        Node* current = root;
        while (current != nullptr) {
            if (key == current->key)
                return current;
            else if (key < current->key)
                current = current->left;
            else
                current = current->right;
        }
        return nullptr;
    }

public:
    Set() : root(nullptr), num_elements(0) {}

    Set(std::initializer_list<Key> const &items) : root(nullptr), num_elements(0) {
        for (const auto& item : items)
            insert(item);
    }

    Set(const Set& s) : root(nullptr), num_elements(0) {
        root = copy_nodes(s.root, nullptr);
        num_elements = s.num_elements;
    }

    Set(Set&& s) noexcept : root(s.root), num_elements(s.num_elements) {
        s.root = nullptr;
        s.num_elements = 0;
    }

    ~Set() {
        clear();
    }

    Set& operator=(Set&& s) noexcept {
        if (this != &s) {
            clear();
            root = s.root;
            num_elements = s.num_elements;
            s.root = nullptr;
            s.num_elements = 0;
        }
        return *this;
    }


    std::pair<iterator, bool> insert(const_reference key) {
        Node* new_node = new Node(key);
        Node* parent = nullptr;
        Node* current = root;

        while (current != nullptr) {
            parent = current;
            if (key < current->key)
                current = current->left;
            else if (key > current->key)
                current = current->right;
            else {
                delete new_node;
                return std::make_pair(iterator(current), false);
            }
        }
        new_node->parent = parent;
        if (parent == nullptr)
            root = new_node;
        else if (key < parent->key)
            parent->left = new_node;
        else
            parent->right = new_node;

        ++num_elements;
        return std::make_pair(iterator(new_node), true);
    }

    size_t size() const {
        return num_elements;
    }

    bool empty() const {
        return num_elements == 0;
    }

    size_type max_size() const {
        size_type res = 230584300921369395;
        return res;
    }

    void clear() {
        destroy(root);
        root = nullptr;
        num_elements = 0;
    }

    iterator begin() {
        Node* current = root;
        while (current != nullptr && current->left != nullptr)
            current = current->left;
        return iterator(current);
    }

    iterator end() {
        return iterator(nullptr);
    }

    iterator find(const Key& key) {
        Node* node = find_node(key);
        return iterator(node);
    }

    bool contains(const Key& key) const {
        return find_node(key) != nullptr;
    }

    void erase(iterator pos) {
        Node* node = pos.current;
        if (node == nullptr)
            return;
        if (node->left == nullptr) {
            transplant(node, node->right);
        } else if (node->right == nullptr) {
            transplant(node, node->left);
        } else {
            Node* successor_node = min_node(node->right);
            if (successor_node->parent != node) {
                transplant(successor_node, successor_node->right);
                successor_node->right = node->right;
                successor_node->right->parent = successor_node;
            }
            transplant(node, successor_node);
            successor_node->left = node->left;
            successor_node->left->parent = successor_node;
        }
        delete node;
        --num_elements;
    }

    void swap(Set& other) {
        std::swap(root, other.root);
        std::swap(num_elements, other.num_elements);
    }

    void merge(Set& other) {
        for (auto it = other.begin(); it != other.end(); ++it)
            insert(*it);
        other.clear();
    }

    friend class SetIterator<Key>;

private:

};





template<typename Key>
class SetIterator {
public:
    typename Set<Key>::Node* current;
    SetIterator(typename Set<Key>::Node* node) : current(node) {}

    SetIterator& operator++() {
        if (current == nullptr)
            throw std::out_of_range("Iterator cannot be incremented beyond the end");
        current = successor(current);
        return *this;
    }

    const Key& operator*() const {
        return current->key;
    }

    bool operator!=(const SetIterator& other) const {
        return current != other.current;
    }

private:
    typename Set<Key>::Node* successor(typename Set<Key>::Node* x) {
        if (x->right != nullptr) {
            x = x->right;
            while (x->left != nullptr)
                x = x->left;
            return x;
        }
        typename Set<Key>::Node* y = x->parent;
        while (y != nullptr && x == y->right) {
            x = y;
            y = y->parent;
        }
        return y;
    }
};

int main() {
    std::set<int> std_set{1, 2, 3, 4, 10, 5};
    Set<int> my_set{1, 2, 3, 4, 5, 10};

    if (std_set.size() == my_set.size()) {
        std::cout << "Размеры множеств совпадают." << std::endl;
    } else {
        std::cout << "Размеры множеств не совпадают." << std::endl;
    }

    bool sets_equal = true;
    for (int element : std_set) {
        if (!my_set.contains(element)) {
            sets_equal = false;
            break;
        }
    }
    if (sets_equal) {
        std::cout << "Множества содержат одинаковые элементы." << std::endl;
    } else {
        std::cout << "Множества не содержат одинаковые элементы." << std::endl;
    }

    for (int i = 6; i <= 10; ++i) {
        auto std_result = std_set.insert(i);
        auto my_result = my_set.insert(i);
        
        std::cout << i << ' ' << std_result.second << std::endl;
        std::cout << i << ' ' << my_result.second << std::endl;
    }

    std::cout << std_set.max_size() << std::endl;

    return 0;
}
