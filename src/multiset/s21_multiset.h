#ifndef S21_MULTISET
#define S21_MULTISET

#include <initializer_list>
#include <iostream>
#include <utility>

namespace s21 {

template <typename Key>
class MultisetIterator;

template <typename Key>
class MultisetConstIterator;

template <typename Key>
class multiset {
 public:
  using key_type = Key;
  using value_type = Key;
  using reference = value_type&;
  using const_reference = const value_type&;
  using iterator = MultisetIterator<Key>;
  using const_iterator = MultisetConstIterator<Key>;
  using size_type = size_t;

 private:
  struct Node {
    Key key;
    Node* left;
    Node* right;
    Node* parent;
    explicit Node(const_reference k)
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
  multiset();
  explicit multiset(std::initializer_list<Key> const& items);
  multiset(const multiset& s);
  multiset(multiset&& s) noexcept;
  ~multiset();

  multiset& operator=(multiset&& s) noexcept;
  iterator insert(const_reference key);
  size_t size() const;
  bool empty() const;
  size_type max_size() const;
  void clear();

  iterator begin();
  iterator end();
  const_iterator begin() const;
  const_iterator end() const;

  size_type count(const Key& key);
  iterator find(const Key& key);
  bool contains(const Key& key) const;

  void erase(iterator pos);
  void swap(multiset& other);
  void merge(multiset& other);

  iterator lower_bound(const Key& key);
  iterator upper_bound(const Key& key);
  std::pair<iterator, iterator> equal_range(const Key& key);
  const_iterator lower_bound(const Key& key) const;
  const_iterator upper_bound(const Key& key) const;
  std::pair<const_iterator, const_iterator> equal_range(const Key& key) const;

  friend class MultisetIterator<Key>;
  friend class MultisetConstIterator<Key>;
};

template <typename Key>
class MultisetIterator {
 public:
  typename multiset<Key>::Node* current;
  explicit MultisetIterator(typename multiset<Key>::Node* node);
  MultisetIterator& operator++();
  Key& operator*() const;
  bool operator!=(const MultisetIterator& other) const;

 private:
  typename multiset<Key>::Node* successor(typename multiset<Key>::Node* x);
};

template <typename Key>
class MultisetConstIterator {
 public:
  typename multiset<Key>::Node* current;
  explicit MultisetConstIterator(typename multiset<Key>::Node* node);
  MultisetConstIterator& operator++();
  const Key& operator*() const;
  bool operator!=(const MultisetConstIterator& other) const;

 private:
  typename multiset<Key>::Node* successor(typename multiset<Key>::Node* x);
};

template class multiset<int>;
template class MultisetIterator<int>;
template class MultisetConstIterator<int>;

}  // namespace s21

#include "s21_multiset.tpp"

#endif
