#include "s21_set.h"

using namespace s21;

template <typename Key>
void Set<Key>::transplant(Node* u, Node* v) {
  if (u->parent == nullptr)
    root = v;
  else if (u == u->parent->left)
    u->parent->left = v;
  else
    u->parent->right = v;
  if (v != nullptr) v->parent = u->parent;
}

template <typename Key>
typename Set<Key>::Node* Set<Key>::min_node(Node* node) {
  while (node->left != nullptr) node = node->left;
  return node;
}

template <typename Key>
void Set<Key>::destroy(Node* node) {
  if (node != nullptr) {
    destroy(node->left);
    destroy(node->right);
    delete node;
  }
}

template <typename Key>
typename Set<Key>::Node* Set<Key>::copy_nodes(Node* other,
                                                        Node* parent) {
  if (other == nullptr) return nullptr;
  Node* new_node = new Node(other->key);
  new_node->parent = parent;
  new_node->left = copy_nodes(other->left, new_node);
  new_node->right = copy_nodes(other->right, new_node);
  return new_node;
}

template <typename Key>
typename Set<Key>::Node* Set<Key>::find_node(
    const_reference key) const {
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

template <typename Key>
Set<Key>::Set() : root(nullptr), num_elements(0) {}

template <typename Key>
Set<Key>::Set(std::initializer_list<Key> const& items)
    : root(nullptr), num_elements(0) {
  for (const auto& item : items) insert(item);
}

template <typename Key>
Set<Key>::Set(const Set& s) : root(nullptr), num_elements(0) {
  root = copy_nodes(s.root, nullptr);
  num_elements = s.num_elements;
}

template <typename Key>
Set<Key>::Set(Set&& s) noexcept
    : root(s.root), num_elements(s.num_elements) {
  s.root = nullptr;
  s.num_elements = 0;
}

template <typename Key>
Set<Key>::~Set() {
  clear();
}

template <typename Key>
typename Set<Key>::Set& Set<Key>::operator=(Set&& s) noexcept {
  if (this != &s) {
    clear();
    root = s.root;
    num_elements = s.num_elements;
    s.root = nullptr;
    s.num_elements = 0;
  }
  return *this;
}

template <typename Key>
std::pair<typename Set<Key>::iterator, bool> Set<Key>::insert(
    const_reference key) {
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

template <typename Key>
size_t Set<Key>::size() const {
  return num_elements;
}

template <typename Key>
bool Set<Key>::empty() const {
  return num_elements == 0;
}

template <typename Key>
typename Set<Key>::size_type Set<Key>::max_size() const {
  size_type res = 230584300921369395;
  return res;
}

template <typename Key>
void Set<Key>::clear() {
  destroy(root);
  root = nullptr;
  num_elements = 0;
}

template <typename Key>
typename Set<Key>::iterator Set<Key>::begin() {
  Node* current = root;
  while (current != nullptr && current->left != nullptr)
    current = current->left;
  return iterator(current);
}

template <typename Key>
typename Set<Key>::iterator Set<Key>::end() {
  return iterator(nullptr);
}

template <typename Key>
typename Set<Key>::const_iterator Set<Key>::begin() const {
  Node* current = root;
  while (current != nullptr && current->left != nullptr)
    current = current->left;
  return const_iterator(current);
}

template <typename Key>
typename Set<Key>::const_iterator Set<Key>::end() const {
  return const_iterator(nullptr);
}

template <typename Key>
typename Set<Key>::iterator Set<Key>::find(const Key& key) {
  Node* node = find_node(key);
  return iterator(node);
}

template <typename Key>
bool Set<Key>::contains(const Key& key) const {
  return find_node(key) != nullptr;
}

template <typename Key>
SetIterator<Key>::SetIterator(typename Set<Key>::Node* node)
    : current(node) {}

template <typename Key>
typename SetIterator<Key>::SetIterator&
SetIterator<Key>::operator++() {
  if (current == nullptr)
    throw std::out_of_range("Iterator cannot be incremented beyond the end");
  current = successor(current);
  return *this;
}

template <typename Key>
Key& SetIterator<Key>::operator*() const {
  return current->key;
}

template <typename Key>
bool SetIterator<Key>::operator!=(const SetIterator& other) const {
  return current != other.current;
}

template <typename Key>
typename Set<Key>::Node* SetIterator<Key>::successor(
    typename Set<Key>::Node* x) {
  if (x->right != nullptr) {
    x = x->right;
    while (x->left != nullptr) x = x->left;
    return x;
  }
  typename Set<Key>::Node* y = x->parent;
  while (y != nullptr && x == y->right) {
    x = y;
    y = y->parent;
  }
  return y;
}

template <typename Key>
SetConstIterator<Key>::SetConstIterator(typename Set<Key>::Node* node)
    : current(node) {}

template <typename Key>
typename SetConstIterator<Key>::SetConstIterator&
SetConstIterator<Key>::operator++() {
  if (current == nullptr)
    throw std::out_of_range("Iterator cannot be incremented beyond the end");
  current = successor(current);
  return *this;
}

template <typename Key>
const Key& SetConstIterator<Key>::operator*() const {
  return current->key;
}

template <typename Key>
bool SetConstIterator<Key>::operator!=(
    const SetConstIterator& other) const {
  return current != other.current;
}

template <typename Key>
typename Set<Key>::Node* SetConstIterator<Key>::successor(
    typename Set<Key>::Node* x) {
  if (x->right != nullptr) {
    x = x->right;
    while (x->left != nullptr) x = x->left;
    return x;
  }
  typename Set<Key>::Node* y = x->parent;
  while (y != nullptr && x == y->right) {
    x = y;
    y = y->parent;
  }
  return y;
}