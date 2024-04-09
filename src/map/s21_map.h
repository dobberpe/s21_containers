#pragma once

#include <initializer_list>
#include <iostream>
#include <utility>

#include "../vector/s21_vector.h"
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
  vector<std::pair<iterator, bool>> insert_many(Args&&... args);
  std::pair<iterator, bool> insert_or_assign(const Key& key, const T& obj);
  void erase(iterator pos);
  void swap(map& other);
  void merge(map& other);

  bool contains(const Key& key);

  class Iterator {
   protected:
    Node<Key, T>* current;
    Node<Key, T>* last;

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
  };

  class ConstIterator : public Iterator {
   public:
    using Iterator::Iterator;
    const_reference operator*() const {
      return this->current ? this->current->value : this->last->value;
    }
    const value_type* operator->() const {
      return this->current ? &(this->current->value) : &(this->last->value);
    }
  };
};

}  // namespace s21

#include "s21_map.tpp"
