#ifndef _S21_VECTOR_H_
#define _S21_VECTOR_H_

#include <stdlib.h>

#include "../list/s21_list.h"

#define ERROR_MEM 128
#define ERROR_OUT_OF_RANGE 5

namespace s21 {

template <typename T>
class VectorIterator;

template <typename T>
class VectorConstIterator;

template <typename T>
class vector : public list<T> {
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
  bool operator==(const vector<value_type> &list_other) const;

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
  bool empty() const;
  size_type size() const;
  void reserve(size_type size);
  size_type capacity() const;
  void shrink_to_fit(); 

  // *Vector Modifiers*
  void clear();
  iterator insert(iterator pos, const_reference value);
  void erase(iterator pos);
  void push_back(const_reference value);
  void pop_back();
  void swap(vector &other);

    // iterator insert_many(const iterator pos, ...);
  // Inserts new elements into the container directly before pos.
  // list, Vector.

  // void insert_many_back(Args&&... args);
  // Appends new elements to the end of the container.	list, Vector, Queue.
  

  vector();
  vector(const size_type n);
  vector(std::initializer_list<value_type> const &items);
  vector(const vector<value_type> &v);
  vector(vector<value_type> &&v);
  vector<value_type> &operator=(vector &&v);
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
  typename vector<T>::reference operator*();
  bool operator!=(const VectorIterator &pos);
  T *get_iter_ptr() {return index_ptr;};
};

template <typename T>
class VectorConstIterator {
 private:
  T *index_ptr;

 public:
  VectorConstIterator();
  VectorConstIterator(const VectorConstIterator &copy);
  VectorConstIterator(T *node);
  VectorConstIterator &operator++();
  VectorConstIterator &operator--();
  VectorConstIterator &operator=(const VectorConstIterator &iter);
  VectorConstIterator &operator=(VectorIterator<T> iter);
  typename vector<T>::const_reference operator*() const;
  bool operator!=(const VectorConstIterator &pos);
};

template class vector<int>;
template class vector<double>;
template class VectorIterator<int>;
template class VectorIterator<double>;
template class VectorConstIterator<int>;
template class VectorConstIterator<double>;

}  // namespace s21

#endif  //_S21_VECTOR_H_
