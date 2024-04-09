#pragma once

#include <initializer_list>
#include <iostream>
#include <utility>
// #include <vector>

#include "s21_binary_tree.h"

namespace s21 {

template <typename Key, typename T>
class map {
 public:
  class Iterator;

  class ConstIterator;

  using key_type = Key;
  using mapped_type = T;
  using value_type = std::pair<const key_type, mapped_type>;
  using reference = value_type&;
  using const_reference = const value_type&;
  using iterator = Iterator;
  using const_iterator = ConstIterator;
  using size_type = size_t;

 private:
  b_tree<Key, T> tree;
  //        struct Node {
  //            value_type value;
  //            Node* left;
  //            Node* right;
  //            Node* parent;
  //
  //            Node(const_reference v)
  //                    : value(v), left(nullptr), right(nullptr),
  //                    parent(nullptr) {}
  //        };
  //
  //        Node* root;
  //        size_t num_of_elems;
  //
  //        iterator find_node(Node *node, const Key &key) const;
  //        iterator insert_node(Node* node, value_type v);
  //        void copy_tree(Node* tree);
  //        void clear_tree(Node* node);

 public:
  map();
  explicit map(std::initializer_list<value_type> const& items);
  map(const map& m);
  map(map&& m) noexcept;
  ~map();

  map& operator=(map&& m) noexcept;

  T& at(const Key& key);
  T& operator[](const Key& key);

  iterator begin();
  iterator end();
  const_iterator begin() const;
  const_iterator end() const;

  bool empty() const;
  size_t size() const;
  size_t max_size() const;

  void clear();
  std::pair<iterator, bool> insert(const_reference& value);
  std::pair<iterator, bool> insert(const Key& key, const T& obj);
  template <typename... Args>
  s21::vector<std::pair<iterator, bool>> insert_many(Args&&... args);
  std::pair<iterator, bool> insert_or_assign(const Key& key, const T& obj);
  void erase(iterator pos);
  void swap(map& other);
  void merge(map& other);

  bool contains(const Key& key);

  class Iterator {
   protected:
    Node<Key, T>* current;
    Node<Key, T>* last;

    //        protected:
    //            Node<Key, T>* get_current() const { return current; }

   public:
    Iterator(Node<Key, T>* curr, Node<Key, T>* lst);
    Iterator(const Iterator& other);

    reference operator*();
    value_type* operator->();
    Iterator& operator++();
    Iterator& operator--();
    Iterator& operator=(const Iterator& other);
    bool operator==(const Iterator& other);
    bool operator!=(const Iterator& other);
    //            void copy(const Iterator &other);
  };

  class ConstIterator : public Iterator {
   public:
    using Iterator::Iterator;
    //            ConstIterator(Node<Key, T>* node) : Iterator(node) {};
    const_reference operator*() const {
      return this->current ? this->current->value : this->last->value;
    }
    const value_type* operator->() const {
      return this->current ? &(this->current->value) : &(this->last->value);
    }
    //            Iterator& operator++() {
    //                Iterator::operator++();
    //                return *this;
    //            }
    //            Iterator& operator--() {
    //                Iterator::operator--();
    //                return *this;
    //            }
  };
};

}  // namespace s21

#include "s21_map.tpp"
