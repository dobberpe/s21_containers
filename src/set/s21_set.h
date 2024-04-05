#ifndef S21_SET
#define S21_SET

#include <initializer_list>
#include <iostream>
#include <utility>
#include <vector>

namespace s21 {

template <typename Key>
class SetIterator;

template <typename Key>
class SetConstIterator;

template <typename Key>
class set {
 public:
  using key_type = Key;
  using value_type = Key;
  using reference = value_type &;
  using const_reference = const value_type &;
  using iterator = SetIterator<Key>;
  using const_iterator = SetConstIterator<Key>;
  using size_type = size_t;

 private:
  struct Node {
    Key key;
    Node *left;
    Node *right;
    Node *parent;
    explicit Node(const_reference k)
        : key(k), left(nullptr), right(nullptr), parent(nullptr) {}
  };
  Node *root;
  size_t num_elements;

  void transplant(Node *u, Node *v);
  Node *min_node(Node *node);
  void destroy(Node *node);
  Node *copy_nodes(Node *other, Node *parent);
  Node *find_node(const_reference key) const;

 public:
  set();
  explicit set(std::initializer_list<Key> const &items);
  set(const set &s);
  set(set &&s) noexcept;
  ~set();

  set &operator=(set &&s) noexcept;
  std::pair<iterator, bool> insert(const_reference key);
  size_t size() const;
  bool empty() const;
  size_type max_size() const;
  void clear();

  iterator begin();
  iterator end();
  const_iterator begin() const;
  const_iterator end() const;

  iterator find(const Key &key);
  bool contains(const Key &key) const;

  void erase(iterator pos);
  void swap(set &other);
  void merge(set &other);

  template <typename... Args>
  std::vector<std::pair<typename set<Key>::iterator, bool>> insert_many(
      Args &&...args) {
    std::vector<std::pair<typename set<Key>::iterator, bool>> results;
    ((void)results.emplace_back(this->insert(std::forward<Args>(args))), ...);
    return results;
  }

  friend class SetIterator<Key>;
  friend class SetConstIterator<Key>;
};

template <typename Key>
class SetIterator {
 public:
  typename set<Key>::Node *current;
  explicit SetIterator(typename set<Key>::Node *node);
  SetIterator &operator++();
  Key &operator*() const;
  bool operator!=(const SetIterator &other) const;

 private:
  typename set<Key>::Node *successor(typename set<Key>::Node *x);
};

template <typename Key>
class SetConstIterator {
 public:
  typename set<Key>::Node *current;
  explicit SetConstIterator(typename set<Key>::Node *node);
  SetConstIterator &operator++();
  const Key &operator*() const;
  bool operator!=(const SetConstIterator &other) const;

 private:
  typename set<Key>::Node *successor(typename set<Key>::Node *x);
};

template class set<int>;
template class SetIterator<int>;
template class SetConstIterator<int>;

}  // namespace s21

#include "s21_set.tpp"

#endif
