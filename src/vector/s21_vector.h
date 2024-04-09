#ifndef _S21_VECTOR_H_
#define _S21_VECTOR_H_

#include "../list/s21_list.h"

#define ERROR_MEM 128
#define ERROR_OUT_OF_RANGE 5

namespace s21 {

template <typename T>
class VectorIterator;

template <typename T>
class VectorConstIterator;

template <typename T>
class vector {
 public:
  typedef T value_type;
  typedef value_type &reference;
  typedef const value_type &const_reference;
  typedef size_t size_type;
  typedef VectorIterator<value_type> iterator;
  typedef VectorConstIterator<value_type> const_iterator;

 private:
  size_type max_number;
  size_type number;
  value_type *head_node;

 public:
  bool operator==(const vector<value_type> &list_other) const noexcept;

  // *Vector Element access*
  reference at(size_type pos);
  reference operator[](size_type pos);
  const_reference operator[](size_type pos) const;
  reference front();
  reference back();
  value_type *data();

  // *Vector Iterators*
  iterator begin();
  iterator end();
  const_iterator begin() const;
  const_iterator end() const;

  // *Vector Capacity*
  bool empty() const noexcept;
  size_type size() const noexcept;
  size_type max_size() const noexcept;
  void reserve(size_type new_size);
  size_type capacity() const noexcept;
  void shrink_to_fit() noexcept;

  // *Vector Modifiers*
  void clear();
  iterator insert(iterator pos, const_reference value);
  void erase(iterator pos);
  void push_back(const_reference value);
  void pop_back();
  void swap(vector &other);

  template <typename... Args>
  iterator insert_many(const_iterator pos, Args &&...args);

  template <typename... Args>
  void insert_many_back(Args &&...args);

  vector();
  vector(const size_type n);
  vector(std::initializer_list<value_type> const &items);
  vector(const vector<value_type> &v);
  vector(vector<value_type> &&v);
  vector<value_type> &operator=(vector<value_type> &&v);
  ~vector();

  friend VectorIterator<value_type>;
  friend VectorConstIterator<value_type>;
};

template <typename T>
class VectorIterator {
 private:
  T *index_ptr;

 public:
  VectorIterator();
  VectorIterator(T *node);
  VectorIterator(const VectorIterator &copy);
  VectorIterator &operator++();
  VectorIterator &operator--();
  VectorIterator &operator=(const VectorIterator &iter);
  typename vector<T>::reference operator*() const;
  bool operator!=(const VectorIterator &pos) const;
};

template <typename T>
class VectorConstIterator : public VectorIterator<T> {
 public:
  using VectorIterator<T>::VectorIterator;
  VectorConstIterator(const VectorIterator<T> &copy);
  typename vector<T>::const_reference operator*() const;
};

}  // namespace s21

#include "s21_vector_access.tpp"
#include "s21_vector_begin_end.tpp"
#include "s21_vector_capacity.tpp"
#include "s21_vector_const_iterator.tpp"
#include "s21_vector_constructor.tpp"
#include "s21_vector_iterator.tpp"
#include "s21_vector_modify.tpp"

#endif  //_S21_VECTOR_H_
