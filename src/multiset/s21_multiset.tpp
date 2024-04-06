using namespace s21;

template <typename Key>
multiset<Key>::multiset(std::initializer_list<Key> const &items) {
  Tree<Key>::root = nullptr;
  Tree<Key>::num_elements = 0;
  for (const auto &item : items) insert(item);
}

template <typename Key>
typename multiset<Key>::iterator multiset<Key>::insert(const_reference key) {
  ++Tree<Key>::num_elements;
  typename Tree<Key>::Node *new_node = new typename Tree<Key>::Node(key);
  typename Tree<Key>::Node *parent = nullptr;
  typename Tree<Key>::Node *current = Tree<Key>::root;

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
      return iterator(new_node, Tree<Key>::get_max());
    }
  }
  new_node->parent = parent;
  if (parent == nullptr)
    Tree<Key>::root = new_node;
  else if (key < parent->key)
    parent->left = new_node;
  else
    parent->right = new_node;

  return iterator(new_node, Tree<Key>::get_max());
}

template <typename Key>
typename multiset<Key>::size_type multiset<Key>::count(const Key &key) {
  size_type count = 0;
  for (auto it = Tree<Key>::begin(); it != Tree<Key>::end(); ++it) {
    if (*it == key) {
      ++count;
    }
  }
  return count;
}

template <typename Key>
typename multiset<Key>::iterator multiset<Key>::lower_bound(const Key &key) {
  for (auto it = Tree<Key>::begin(); it != Tree<Key>::end(); ++it) {
    if (*it >= key) {
      return it;
    }
  }
  return Tree<Key>::end();
}

template <typename Key>
typename multiset<Key>::iterator multiset<Key>::upper_bound(const Key &key) {
  for (auto it = Tree<Key>::begin(); it != Tree<Key>::end(); ++it) {
    if (*it > key) {
      return it;
    }
  }
  return Tree<Key>::end();
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
  for (auto it = Tree<Key>::begin(); it != Tree<Key>::end(); ++it) {
    if (*it >= key) {
      return it;
    }
  }
  return Tree<Key>::end();
}

template <typename Key>
typename multiset<Key>::const_iterator multiset<Key>::upper_bound(
    const Key &key) const {
  for (auto it = Tree<Key>::begin(); it != Tree<Key>::end(); ++it) {
    if (*it > key) {
      return it;
    }
  }
  return Tree<Key>::end();
}

template <typename Key>
std::pair<typename multiset<Key>::const_iterator,
          typename multiset<Key>::const_iterator>
multiset<Key>::equal_range(const Key &key) const {
  auto lower = lower_bound(key);
  auto upper = upper_bound(key);
  return std::make_pair(lower, upper);
}

template <typename Key>
template <typename... Args>
std::vector<typename multiset<Key>::iterator> multiset<Key>::insert_many(
    Args &&...args) {
  std::vector<typename set<Key>::iterator> results;
  ((void)results.push_back(insert(std::forward<Args>(args))), ...);
  return results;
}