using namespace s21;

template <typename Key>
multiset<Key>::multiset() : root(nullptr), num_elements(0) {}

template <typename Key>
multiset<Key>::multiset(std::initializer_list<Key> const &items)
    : root(nullptr), num_elements(0) {
  for (const auto &item : items) insert(item);
}

template <typename Key>
multiset<Key>::multiset(const multiset &s) : root(nullptr), num_elements(0) {
  root = copy_nodes(s.root, nullptr);
  num_elements = s.num_elements;
}

template <typename Key>
multiset<Key>::multiset(multiset &&s) noexcept
    : root(s.root), num_elements(s.num_elements) {
  s.root = nullptr;
  s.num_elements = 0;
}

template <typename Key>
multiset<Key>::~multiset() {
  clear();
}

template <typename Key>
typename multiset<Key>::iterator multiset<Key>::insert(const_reference key) {
  ++num_elements;
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
      new_node->parent = current;
      new_node->right = current->right;
      if (current->right) current->right->parent = new_node;
      current->right = new_node;
      return iterator(new_node);
    }
  }
  new_node->parent = parent;
  if (parent == nullptr)
    root = new_node;
  else if (key < parent->key)
    parent->left = new_node;
  else
    parent->right = new_node;

  return iterator(new_node);
}

template <typename Key>
void multiset<Key>::transplant(Node *u, Node *v) {
  if (u->parent == nullptr)
    root = v;
  else if (u == u->parent->left)
    u->parent->left = v;
  else
    u->parent->right = v;
  if (v != nullptr) v->parent = u->parent;
}

template <typename Key>
typename multiset<Key>::Node *multiset<Key>::min_node(Node *node) {
  while (node->left != nullptr) node = node->left;
  return node;
}

template <typename Key>
void multiset<Key>::destroy(Node *node) {
  if (node != nullptr) {
    destroy(node->left);
    destroy(node->right);
    delete node;
  }
}

template <typename Key>
typename multiset<Key>::Node *multiset<Key>::copy_nodes(Node *other,
                                                        Node *parent) {
  if (other == nullptr) return nullptr;
  Node *new_node = new Node(other->key);
  new_node->parent = parent;
  new_node->left = copy_nodes(other->left, new_node);
  new_node->right = copy_nodes(other->right, new_node);
  return new_node;
}

template <typename Key>
typename multiset<Key>::Node *multiset<Key>::find_node(
    const_reference key) const {
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
typename multiset<Key>::multiset &multiset<Key>::operator=(
    multiset &&s) noexcept {
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
size_t multiset<Key>::size() const {
  return num_elements;
}

template <typename Key>
bool multiset<Key>::empty() const {
  return num_elements == 0;
}

template <typename Key>
typename multiset<Key>::size_type multiset<Key>::max_size() const {
  size_type res = 230584300921369395;
  return res;
}

template <typename Key>
void multiset<Key>::clear() {
  destroy(root);
  root = nullptr;
  num_elements = 0;
}

template <typename Key>
typename multiset<Key>::iterator multiset<Key>::begin() {
  Node *current = root;
  while (current != nullptr && current->left != nullptr)
    current = current->left;
  return iterator(current);
}

template <typename Key>
typename multiset<Key>::iterator multiset<Key>::end() {
  return iterator(nullptr);
}

template <typename Key>
typename multiset<Key>::const_iterator multiset<Key>::begin() const {
  Node *current = root;
  while (current != nullptr && current->left != nullptr)
    current = current->left;
  return const_iterator(current);
}

template <typename Key>
typename multiset<Key>::const_iterator multiset<Key>::end() const {
  return const_iterator(nullptr);
}

template <typename Key>
typename multiset<Key>::size_type multiset<Key>::count(const Key &key) {
  size_type count = 0;
  for (auto it = begin(); it != end(); ++it) {
    if (*it == key) {
      ++count;
    }
  }
  return count;
}

template <typename Key>
typename multiset<Key>::iterator multiset<Key>::find(const Key &key) {
  Node *node = find_node(key);
  return iterator(node);
}

template <typename Key>
bool multiset<Key>::contains(const Key &key) const {
  return find_node(key) != nullptr;
}

template <typename Key>
void multiset<Key>::erase(iterator pos) {
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
void multiset<Key>::swap(multiset &other) {
  std::swap(root, other.root);
  std::swap(num_elements, other.num_elements);
}

template <typename Key>
void multiset<Key>::merge(multiset &other) {
  for (auto it = other.begin(); it != other.end(); ++it) insert(*it);
  other.clear();
}

template <typename Key>
MultisetIterator<Key>::MultisetIterator(typename multiset<Key>::Node *node)
    : current(node) {}

template <typename Key>
typename MultisetIterator<Key>::MultisetIterator &
MultisetIterator<Key>::operator++() {
  current = successor(current);
  return *this;
}

template <typename Key>
Key &MultisetIterator<Key>::operator*() const {
  return current->key;
}

template <typename Key>
bool MultisetIterator<Key>::operator!=(const MultisetIterator &other) const {
  return current != other.current;
}

template <typename Key>
typename multiset<Key>::Node *MultisetIterator<Key>::successor(
    typename multiset<Key>::Node *x) {
  if (x->right != nullptr) {
    x = x->right;
    while (x->left != nullptr) x = x->left;
    return x;
  }
  typename multiset<Key>::Node *y = x->parent;
  while (y != nullptr && x == y->right) {
    x = y;
    y = y->parent;
  }
  return y;
}

template <typename Key>
MultisetConstIterator<Key>::MultisetConstIterator(
    typename multiset<Key>::Node *node)
    : current(node) {}

template <typename Key>
typename MultisetConstIterator<Key>::MultisetConstIterator &
MultisetConstIterator<Key>::operator++() {
  current = successor(current);
  return *this;
}

template <typename Key>
const Key &MultisetConstIterator<Key>::operator*() const {
  return current->key;
}

template <typename Key>
bool MultisetConstIterator<Key>::operator!=(
    const MultisetConstIterator &other) const {
  return current != other.current;
}

template <typename Key>
typename multiset<Key>::Node *MultisetConstIterator<Key>::successor(
    typename multiset<Key>::Node *x) {
  if (x->right != nullptr) {
    x = x->right;
    while (x->left != nullptr) x = x->left;
    return x;
  }
  typename multiset<Key>::Node *y = x->parent;
  while (y != nullptr && x == y->right) {
    x = y;
    y = y->parent;
  }
  return y;
}

template <typename Key>
typename multiset<Key>::iterator multiset<Key>::lower_bound(const Key &key) {
  for (auto it = begin(); it != end(); ++it) {
    if (*it >= key) {
      return it;
    }
  }
  return end();
}

template <typename Key>
typename multiset<Key>::iterator multiset<Key>::upper_bound(const Key &key) {
  for (auto it = begin(); it != end(); ++it) {
    if (*it > key) {
      return it;
    }
  }
  return end();
}

template <typename Key>
std::pair<typename multiset<Key>::iterator, typename multiset<Key>::iterator>
multiset<Key>::equal_range(const Key &key) {
  auto lower = lower_bound(key);
  auto upper = upper_bound(key);
  return std::make_pair(lower, upper);
}

template <typename Key>
typename multiset<Key>::const_iterator multiset<Key>::lower_bound(
    const Key &key) const {
  for (auto it = begin(); it != end(); ++it) {
    if (*it >= key) {
      return it;
    }
  }
  return end();
}

template <typename Key>
typename multiset<Key>::const_iterator multiset<Key>::upper_bound(
    const Key &key) const {
  for (auto it = begin(); it != end(); ++it) {
    if (*it > key) {
      return it;
    }
  }
  return end();
}

template <typename Key>
std::pair<typename multiset<Key>::const_iterator,
          typename multiset<Key>::const_iterator>
multiset<Key>::equal_range(const Key &key) const {
  auto lower = lower_bound(key);
  auto upper = upper_bound(key);
  return std::make_pair(lower, upper);
}