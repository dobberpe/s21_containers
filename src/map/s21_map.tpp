using namespace s21;

// template <typename Key, typename T>
// typename map<Key, T>::iterator map<Key, T>::find_node(Node *node, const Key
// &key) const {
//     while (node && key != node->value.first) node = key < node->value.first ?
//     node->left : node->right;
//
//     return iterator(node);
// }
//
////template <typename Key, typename T>
////void map<Key, T>::insert_node(Node *node, value_type v) {
////    if (v.first > node->value.first) {
////        if (node->right) insert_node(node->right, v);
////        else node->right = new Node(v);
////    } else if (v.first < node->value.first) {
////        if (node->left) insert_node(node->left, v);
////        else node->left = new Node(v);
////    }
////}
//
// template <typename Key, typename T>
// typename map<Key, T>::iterator map<Key, T>::insert_node(Node *node,
// value_type v) {
//    while (!(v.first > node->value.first && !node->right) && !(v.first <
//    node->value.first && !node->left)) {
//        node = v.first > node->value.first ? node->right : node->left;
//    }
//
//    if (v.first > node->value.first) {
//        node->right = new Node(v);
//        node->right->parent = node;
//    } else {
//        node->left = new Node(v);
//        node->left->parent = node;
//    }
//
//    ++num_of_elems;
//
//    return iterator(v.first > node->value.first ? node->right : node->left);
//}
//
// template <typename Key, typename T>
// void map<Key, T>::copy_tree(Node* node) {
//    if (node) {
//        insert(node->value);
//        copy_tree(node->left);
//        copy_tree(node->right);
//    }
//}
//
// template <typename Key, typename T>
// void map<Key, T>::clear_tree(Node* node) {
//    if (node) {
//        clear_tree(node->left);
//        clear_tree(node->right);
//        delete node;
//    }
//}

template <typename Key, typename T>
map<Key, T>::map() : tree() {}

template <typename Key, typename T>
map<Key, T>::map(std::initializer_list<value_type> const& items) : tree() {
  for (const auto& item : items) insert(item);
}

template <typename Key, typename T>
map<Key, T>::map(const map& m) : tree(m.tree) {}

template <typename Key, typename T>
map<Key, T>::map(map&& m) noexcept : tree(m.tree) {
  m.tree.clear();
}

template <typename Key, typename T>
map<Key, T>::~map() {
  clear();
}

template <typename Key, typename T>
typename map<Key, T>::map& map<Key, T>::operator=(map&& m) noexcept {
  if (this != &m) {
    clear();
    tree = m.tree;
    m.clear();
  }
  return *this;
}

template <typename Key, typename T>
T& map<Key, T>::at(const Key& key) {
  Node<Key, T>* node = tree.find_node(key);

  if (!node)
    throw std::out_of_range("map::at");
  else
    return node->value.second;
}

template <typename Key, typename T>
T& map<Key, T>::operator[](const Key& key) {
  auto [it, inserted] = insert({key, 0});

  return it->second;
}

template <typename Key, typename T>
typename map<Key, T>::iterator map<Key, T>::begin() {
  return iterator(tree.first(), tree.last());
}

template <typename Key, typename T>
typename map<Key, T>::iterator map<Key, T>::end() {
  return iterator(nullptr, tree.last());
}

template <typename Key, typename T>
typename map<Key, T>::const_iterator map<Key, T>::begin() const {
  return const_iterator(tree.first(), tree.last());
}

template <typename Key, typename T>
typename map<Key, T>::const_iterator map<Key, T>::end() const {
  return const_iterator(nullptr, tree.last());
}

template <typename Key, typename T>
bool map<Key, T>::empty() const {
  return !tree.get_size();
}

template <typename Key, typename T>
size_t map<Key, T>::size() const {
  return tree.get_size();
}

template <typename Key, typename T>
size_t map<Key, T>::max_size() const {
  return size_t(230584300921369395);
}

template <typename Key, typename T>
void map<Key, T>::clear() {
  tree.clear();
}

template <typename Key, typename T>
std::pair<typename map<Key, T>::iterator, bool> map<Key, T>::insert(
    const_reference value) {
  bool inserted = false;
  Node<Key, T>* node = tree.find_node(value.first);

  if (!node) {
    node = tree.insert_node(value);
    inserted = true;
  }

  return std::make_pair(iterator(node, tree.last()), inserted);
}

template <typename Key, typename T>
std::pair<typename map<Key, T>::iterator, bool> map<Key, T>::insert(
    const Key& key, const T& obj) {
  bool inserted = false;
  Node<Key, T>* node = tree.find_node(key);

  if (!node) {
    node = tree.insert_node(std::make_pair(key, obj));
    inserted = true;
  }

  return std::make_pair(iterator(node, tree.last()), inserted);
}

template <typename Key, typename T>
template <typename... Args>
vector<std::pair<typename map<Key, T>::iterator, bool>>
map<Key, T>::insert_many(Args&&... args) {
  vector<std::pair<typename map<Key, T>::iterator, bool>> res;

  (res.push_back(insert(std::forward<Args>(args))), ...);

  return res;
}

template <typename Key, typename T>
std::pair<typename map<Key, T>::iterator, bool> map<Key, T>::insert_or_assign(
    const Key& key, const T& obj) {
  Node<Key, T>* node = tree.find_node(key);

  if (node)
    node->value.second = obj;
  else
    node = tree.insert_node(std::make_pair(key, obj));

  return std::make_pair(iterator(node, tree.last()), true);
}

template <typename Key, typename T>
void map<Key, T>::erase(iterator pos) {
  tree.remove_node(tree.find_node(pos->first));
}

template <typename Key, typename T>
void map<Key, T>::swap(map& other) {
  b_tree tmp = tree;
  tree = other.tree;
  other.tree = tmp;
}

template <typename Key, typename T>
void map<Key, T>::merge(map& other) {
  auto iter = other.begin();

  while (iter != other.end()) {
    const auto [it, inserted] = insert(*iter);
    if (inserted) {
      other.erase(iter);
      iter = other.begin();
    } else
      ++iter;
  }
}

template <typename Key, typename T>
bool map<Key, T>::contains(const Key& key) {
  return tree.find_node(key) != nullptr;
}

// template <typename Key, typename T>
// typename map<Key, T>::Node* map<Key, T>::iterator::get_current() { return
// current; }

template <typename Key, typename T>
map<Key, T>::iterator::Iterator(Node<Key, T>* curr, Node<Key, T>* lst)
    : current(curr), last(lst) {}

template <typename Key, typename T>
map<Key, T>::iterator::Iterator(const Iterator& other)
    : current(other.current), last(other.last) {}

template <typename Key, typename T>
std::pair<const Key, T>& map<Key, T>::iterator::operator*() {
  return current ? current->value : last->value;
}

template <typename Key, typename T>
std::pair<const Key, T>* map<Key, T>::iterator::operator->() {
  return current ? &(current->value) : &(last->value);
}

template <typename Key, typename T>
typename map<Key, T>::iterator::Iterator& map<Key, T>::iterator::operator++() {
  if (current == last)
    current = nullptr;
  else if (current && current->right) {
    current = current->right;
    while (current->left) current = current->left;
  } else if (current && current->parent) {
    Node<Key, T>* tmp = current;
    while (tmp->parent && tmp == tmp->parent->right) tmp = tmp->parent;
    tmp = tmp->parent;

    if (tmp) current = tmp;
  }

  return *this;
}

template <typename Key, typename T>
typename map<Key, T>::iterator::Iterator& map<Key, T>::iterator::operator--() {
  if (!current)
    current = last;
  else if (current->left) {
    current = current->left;
    while (current->right) current = current->right;
  } else if (current->parent) {
    Node<Key, T>* tmp = current;
    while (tmp->parent && tmp == tmp->parent->left) tmp = tmp->parent;
    tmp = tmp->parent;

    if (tmp) current = tmp;
  }

  return *this;
}

template <typename Key, typename T>
typename map<Key, T>::iterator::Iterator& map<Key, T>::iterator::operator=(
    const Iterator& other) {
  current = other.current;
  last = other.last;

  return *this;
}

template <typename Key, typename T>
bool map<Key, T>::iterator::operator==(const Iterator& other) {
  return current == other.current;
}

template <typename Key, typename T>
bool map<Key, T>::iterator::operator!=(const Iterator& other) {
  return current != other.current;
}

// template <typename Key, typename T>
// void map<Key, T>::iterator::copy(const Iterator &other) {
//     current = other.current;
//     last = other.last;
// }