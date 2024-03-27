#ifndef S21_SET
#define S21_SET

#include <initializer_list>
#include <iostream>
#include <utility>

namespace s21 {

template <typename Key>
class SetIterator;

template <typename Key>
class SetConstIterator;

template <typename Key>
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
    Node(const_reference k)
        : key(k), left(nullptr), right(nullptr), parent(nullptr) {}
  };
  Node* root;
  size_t num_elements;

  void transplant(Node* u, Node* v);
  Node* min_node(Node* node);
  void destroy(Node* node);
  Node* copy_nodes(Node* other, Node* parent);
  Node* find_node(const_reference key) const;

 public:
  Set();
  Set(std::initializer_list<Key> const& items);
  Set(const Set& s);
  Set(Set&& s) noexcept;
  ~Set();

  Set& operator=(Set&& s) noexcept;
  std::pair<iterator, bool> insert(const_reference key);
  size_t size() const;
  bool empty() const;
  size_type max_size() const;
  void clear();

  iterator begin();
  iterator end();
  const_iterator begin() const;
  const_iterator end() const;

  iterator find(const Key& key);
  bool contains(const Key& key) const;

  void erase(iterator pos);
  void swap(Set& other);
  void merge(Set& other);

  friend class SetIterator<Key>;
  friend class SetConstIterator<Key>;
};


template <typename Key>
class SetIterator {
 public:
  typename Set<Key>::Node* current;
  SetIterator(typename Set<Key>::Node* node);
  SetIterator& operator++();
  Key& operator*() const;
  bool operator!=(const SetIterator& other) const;

 private:
  typename Set<Key>::Node* successor(typename Set<Key>::Node* x);
};

template <typename Key>
class SetConstIterator {
 public:
  typename Set<Key>::Node* current;
  SetConstIterator(typename Set<Key>::Node* node);
  SetConstIterator& operator++();
  const Key& operator*() const;
  bool operator!=(const SetConstIterator& other) const;

 private:
  typename Set<Key>::Node* successor(typename Set<Key>::Node* x);
};

template class Set<int>;
template class SetIterator<int>;
template class SetConstIterator<int>;

}  // namespace s21

#endif
