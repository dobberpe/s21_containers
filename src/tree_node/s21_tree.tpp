#include "s21_tree.h"

using namespace s21;

template <typename Key>
void Tree<Key>::transplant(Node *u, Node *v) {
  if (u->parent == nullptr)
    root = v;
  else if (u == u->parent->left)
    u->parent->left = v;
  else
    u->parent->right = v;
  if (v != nullptr) v->parent = u->parent;
}

template <typename Key>
typename Tree<Key>::Node *Tree<Key>::min_node(Node *node) {
  while (node->left != nullptr) node = node->left;
  return node;
}

template <typename Key>
void Tree<Key>::destroy(Node *node) {
  if (node != nullptr) {
    destroy(node->left);
    destroy(node->right);
    delete node;
  }
}

template <typename Key>
typename Tree<Key>::Node *Tree<Key>::copy_nodes(Node *other, Node *parent) {
  if (other == nullptr) return nullptr;
  Node *new_node = new Node(other->key);
  new_node->parent = parent;
  new_node->left = copy_nodes(other->left, new_node);
  new_node->right = copy_nodes(other->right, new_node);
  return new_node;
}

template <typename Key>
typename Tree<Key>::Node *Tree<Key>::find_node(const_reference key) const {
  Node *current = root;
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
Tree<Key>::Tree() : root(nullptr), num_elements(0) {}

template <typename Key>
Tree<Key>::Tree(std::initializer_list<Key> const &items)
    : root(nullptr), num_elements(0) {
  for (const auto &item : items) insert(item);
}

template <typename Key>
Tree<Key>::Tree(const Tree &s) : root(nullptr), num_elements(0) {
  root = copy_nodes(s.root, nullptr);
  num_elements = s.num_elements;
}

template <typename Key>
Tree<Key>::Tree(Tree &&s) noexcept
    : root(s.root), num_elements(s.num_elements) {
  s.root = nullptr;
  s.num_elements = 0;
}

template <typename Key>
Tree<Key>::~Tree() {
  clear();
}

template <typename Key>
typename Tree<Key>::Tree &Tree<Key>::operator=(Tree &&s) noexcept {
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
std::pair<typename Tree<Key>::iterator, bool> Tree<Key>::insert(
    const_reference key) {
  Node *new_node = new Node(key);
  Node *parent = nullptr;
  Node *current = root;

  while (current != nullptr) {
    parent = current;
    if (key < current->key)
      current = current->left;
    else if (key > current->key)
      current = current->right;
    else {
      delete new_node;
      return std::make_pair(iterator(current, get_max()), false);
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
  return std::make_pair(iterator(new_node, get_max()), true);
}

template <typename Key>
size_t Tree<Key>::size() const {
  return num_elements;
}

template <typename Key>
bool Tree<Key>::empty() const {
  return num_elements == 0;
}

template <typename Key>
typename Tree<Key>::size_type Tree<Key>::max_size() const {
  size_type res = 230584300921369395;
  return res;
}

template <typename Key>
void Tree<Key>::clear() {
  destroy(root);
  root = nullptr;
  num_elements = 0;
}

template <typename Key>
typename Tree<Key>::Node *Tree<Key>::get_max() const {
  Node *max = root;
  while (max && max->right) {
    max = max->right;
  }
  return max;
}

template <typename Key>
typename Tree<Key>::iterator Tree<Key>::begin() {
  Node *current = root;
  while (current != nullptr && current->left != nullptr)
    current = current->left;
  return iterator(current, get_max());
}

template <typename Key>
typename Tree<Key>::iterator Tree<Key>::end() {
  return iterator(nullptr, get_max());
}

template <typename Key>
typename Tree<Key>::const_iterator Tree<Key>::begin() const {
  Node *current = root;
  while (current != nullptr && current->left != nullptr)
    current = current->left;
  return const_iterator(current, get_max());
}

template <typename Key>
typename Tree<Key>::const_iterator Tree<Key>::end() const {
  return const_iterator(nullptr, get_max());
}

template <typename Key>
typename Tree<Key>::iterator Tree<Key>::find(const Key &key) {
  Node *node = find_node(key);
  return iterator(node, get_max());
}

template <typename Key>
bool Tree<Key>::contains(const Key &key) const {
  return find_node(key) != nullptr;
}

template <typename Key>
void Tree<Key>::erase(iterator pos) {
  Node *node = pos.current;
  if (node != nullptr) {
    if (node->left == nullptr) {
      transplant(node, node->right);
    } else if (node->right == nullptr) {
      transplant(node, node->left);
    } else {
      Node *successor_node = min_node(node->right);
      if (successor_node->parent != node) {
        transplant(successor_node, successor_node->right);
        successor_node->right = node->right;
        successor_node->right->parent = successor_node;
      }
      transplant(node, successor_node);
      successor_node->left = node->left;
      successor_node->left->parent = successor_node;
    }
    --num_elements;
  }
  delete node;
}

template <typename Key>
void Tree<Key>::swap(Tree &other) {
  std::swap(root, other.root);
  std::swap(num_elements, other.num_elements);
}

template <typename Key>
void Tree<Key>::merge(Tree &other) {
  for (auto it = other.begin(); it != other.end(); ++it) insert(*it);
  other.clear();
}

template <typename Key>
Tree<Key>::Iterator::Iterator(typename Tree<Key>::Node *node,
                              typename Tree<Key>::Node *back)
    : current(node), last(back) {}

template <typename Key>
typename Tree<Key>::Iterator &Tree<Key>::Iterator::operator++() {
  current = successor(current);
  return *this;
}

template <typename Key>
typename Tree<Key>::Iterator &Tree<Key>::Iterator::operator--() {
  if (current == nullptr) {
    current = last;
    return *this;
  }
  if (current->left != nullptr) {
    current = maximum(current->left);
  } else {
    typename Tree<Key>::Node *y = current->parent;
    while (y != nullptr && current == y->left) {
      current = y;
      y = y->parent;
    }
    current = y;
  }
  return *this;
}

template <typename Key>
bool Tree<Key>::Iterator::operator==(const Tree<Key>::Iterator &other) const {
  return current == other.current;
}

template <typename Key>
typename Tree<Key>::Node *Tree<Key>::Iterator::maximum(
    typename Tree<Key>::Node *x) {
  while (x->right != nullptr) x = x->right;
  return x;
}

template <typename Key>
Key &Tree<Key>::Iterator::operator*() const {
  return current->key;
}

template <typename Key>
bool Tree<Key>::Iterator::operator!=(const Tree<Key>::Iterator &other) const {
  return current != other.current;
}

template <typename Key>
typename Tree<Key>::Node *Tree<Key>::Iterator::successor(
    typename Tree<Key>::Node *x) {
  if (x->right != nullptr) {
    x = x->right;
    while (x->left != nullptr) x = x->left;
    return x;
  }
  typename Tree<Key>::Node *y = x->parent;
  while (y != nullptr && x == y->right) {
    x = y;
    y = y->parent;
  }
  return y;
}

template <typename Key>
const Key &Tree<Key>::ConstIterator::operator*() const {
  return this->current->key;
}
