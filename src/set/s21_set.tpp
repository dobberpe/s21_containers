using namespace s21;

template <typename Key>
void set<Key>::transplant(Node *u, Node *v) {
  if (u->parent == nullptr)
    root = v;
  else if (u == u->parent->left)
    u->parent->left = v;
  else
    u->parent->right = v;
  if (v != nullptr) v->parent = u->parent;
}

template <typename Key>
typename set<Key>::Node *set<Key>::min_node(Node *node) {
  while (node->left != nullptr) node = node->left;
  return node;
}

template <typename Key>
void set<Key>::destroy(Node *node) {
  if (node != nullptr) {
    destroy(node->left);
    destroy(node->right);
    delete node;
  }
}

template <typename Key>
typename set<Key>::Node *set<Key>::copy_nodes(Node *other, Node *parent) {
  if (other == nullptr) return nullptr;
  Node *new_node = new Node(other->key);
  new_node->parent = parent;
  new_node->left = copy_nodes(other->left, new_node);
  new_node->right = copy_nodes(other->right, new_node);
  return new_node;
}

template <typename Key>
typename set<Key>::Node *set<Key>::find_node(const_reference key) const {
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
set<Key>::set() : root(nullptr), num_elements(0) {}

template <typename Key>
set<Key>::set(std::initializer_list<Key> const &items)
    : root(nullptr), num_elements(0) {
  for (const auto &item : items) insert(item);
}

template <typename Key>
set<Key>::set(const set &s) : root(nullptr), num_elements(0) {
  root = copy_nodes(s.root, nullptr);
  num_elements = s.num_elements;
}

template <typename Key>
set<Key>::set(set &&s) noexcept : root(s.root), num_elements(s.num_elements) {
  s.root = nullptr;
  s.num_elements = 0;
}

template <typename Key>
set<Key>::~set() {
  clear();
}

template <typename Key>
typename set<Key>::set &set<Key>::operator=(set &&s) noexcept {
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
std::pair<typename set<Key>::iterator, bool> set<Key>::insert(
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
size_t set<Key>::size() const {
  return num_elements;
}

template <typename Key>
bool set<Key>::empty() const {
  return num_elements == 0;
}

template <typename Key>
typename set<Key>::size_type set<Key>::max_size() const {
  size_type res = 230584300921369395;
  return res;
}

template <typename Key>
void set<Key>::clear() {
  destroy(root);
  root = nullptr;
  num_elements = 0;
}

template <typename Key>
typename set<Key>::Node *set<Key>::get_max() const {
  Node *max = root;
  while (max && max->right) {
    max = max->right;
  }
  return max;
}

template <typename Key>
typename set<Key>::iterator set<Key>::begin() {
  Node *current = root;
  while (current != nullptr && current->left != nullptr)
    current = current->left;
  return iterator(current, get_max());
}

template <typename Key>
typename set<Key>::iterator set<Key>::end() {
  return iterator(nullptr, get_max());
}

template <typename Key>
typename set<Key>::const_iterator set<Key>::begin() const {
  Node *current = root;
  while (current != nullptr && current->left != nullptr)
    current = current->left;
  return const_iterator(current, get_max());
}

template <typename Key>
typename set<Key>::const_iterator set<Key>::end() const {
  return const_iterator(nullptr, get_max());
}

template <typename Key>
typename set<Key>::iterator set<Key>::find(const Key &key) {
  Node *node = find_node(key);
  return iterator(node, get_max());
}

template <typename Key>
bool set<Key>::contains(const Key &key) const {
  return find_node(key) != nullptr;
}

template <typename Key>
void set<Key>::erase(iterator pos) {
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
void set<Key>::swap(set &other) {
  std::swap(root, other.root);
  std::swap(num_elements, other.num_elements);
}

template <typename Key>
void set<Key>::merge(set &other) {
  for (auto it = other.begin(); it != other.end(); ++it) insert(*it);
  other.clear();
}

template <typename Key>
SetIterator<Key>::SetIterator(typename set<Key>::Node *node,
                              typename set<Key>::Node *back)
    : current(node), last(back) {}

template <typename Key>
typename SetIterator<Key>::SetIterator &SetIterator<Key>::operator++() {
  current = successor(current);
  return *this;
}

template <typename Key>
typename SetIterator<Key>::SetIterator &SetIterator<Key>::operator--() {
  if (current == nullptr) {
    current = last;
    return *this;
  }
  if (current->left != nullptr) {
    current = maximum(current->left);
  } else {
    typename set<Key>::Node *y = current->parent;
    while (y != nullptr && current == y->left) {
      current = y;
      y = y->parent;
    }
    current = y;
  }
  return *this;
}

template <typename Key>
bool SetIterator<Key>::operator==(const SetIterator<Key> &other) const {
  return current == other.current;
}

template <typename Key>
typename set<Key>::Node *SetIterator<Key>::predecessor(
    typename set<Key>::Node *x) {
  if (x->left != nullptr) return maximum(x->left);
  typename set<Key>::Node *y = x->parent;
  while (y != nullptr && x == y->left) {
    x = y;
    y = y->parent;
  }
  return y;
}

template <typename Key>
typename set<Key>::Node *SetIterator<Key>::maximum(typename set<Key>::Node *x) {
  while (x->right != nullptr) x = x->right;
  return x;
}

template <typename Key>
Key &SetIterator<Key>::operator*() const {
  return current->key;
}

template <typename Key>
bool SetIterator<Key>::operator!=(const SetIterator &other) const {
  return current != other.current;
}

template <typename Key>
typename set<Key>::Node *SetIterator<Key>::successor(
    typename set<Key>::Node *x) {
  if (x->right != nullptr) {
    x = x->right;
    while (x->left != nullptr) x = x->left;
    return x;
  }
  typename set<Key>::Node *y = x->parent;
  while (y != nullptr && x == y->right) {
    x = y;
    y = y->parent;
  }
  return y;
}

template <typename Key>
const Key &SetConstIterator<Key>::operator*() const {
  return this->current->key;
}
