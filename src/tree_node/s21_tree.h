#ifndef _S21_TREE_
#define _S21_TREE_

#include <iostream>
#include <utility>
#include <vector>

namespace s21 {

template <typename Key>
class Tree {
 public:
  class Iterator;
  class ConstIterator;

  using key_type = Key;
  using value_type = Key;
  using reference = value_type &;
  using const_reference = const value_type &;
  using iterator = Iterator;
  using const_iterator = ConstIterator;
  using size_type = size_t;

  struct Node {
    Key key;
    Node *left;
    Node *right;
    Node *parent;
    explicit Node(const Key &k)
        : key(k), left(nullptr), right(nullptr), parent(nullptr) {}
  };
  Node *root;
  size_t num_elements;

  void transplant(Node *u, Node *v);
  Node *min_node(Node *node);
  void destroy(Node *node);
  Node *copy_nodes(Node *other, Node *parent);
  Node *find_node(const_reference key) const;
  Node *get_max() const;

  Tree();
  explicit Tree(std::initializer_list<Key> const &items);
  Tree(const Tree &s);
  Tree(Tree &&s) noexcept;
  ~Tree();

  Tree &operator=(Tree &&s) noexcept;
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
  void swap(Tree &other);
  void merge(Tree &other);

  class Iterator {
   public:
    typename Tree<Key>::Node *current;
    typename Tree<Key>::Node *last;
    explicit Iterator(typename Tree<Key>::Node *node,
                      typename Tree<Key>::Node *back);
    Iterator &operator++();
    Iterator &operator--();
    bool operator==(const Iterator &other) const;
    Key &operator*() const;
    bool operator!=(const Iterator &other) const;

   private:
    typename Tree<Key>::Node *successor(typename Tree<Key>::Node *x);
    typename Tree<Key>::Node *maximum(typename Tree<Key>::Node *x);
  };

  class ConstIterator : public Iterator {
   public:
    using Iterator::Iterator;
    const Key &operator*() const;
  };
};

}  // namespace s21

#include "s21_tree.tpp"
#endif