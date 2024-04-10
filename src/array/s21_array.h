#ifndef _S21_ARRAY_H_
#define _S21_ARRAY_H_

#include "../vector/s21_vector.h"

namespace s21 {

template <typename T, size_t _MAX = 0>
class array {
 public:
  using value_type = T;
  using reference = value_type &;
  using const_reference = const value_type &;
  using size_type = size_t;
  using iterator = value_type *;
  using const_iterator = const value_type *;

 private:
  size_type number;
  value_type *head_node;
  void allocate_array(size_type n);

 public:
  bool operator==(const array<value_type, _MAX> &arr_other) const;

  // *Array Element access*
  reference at(size_type pos);
  reference operator[](size_type pos);
  const_reference operator[](size_type pos) const;
  reference front();
  reference back();
  iterator data();

  // *Array Iterators*
  iterator begin();
  iterator end();

  // *Array Capacity*
  bool empty() const;
  size_type size() const;
  size_type max_size() const;

  // *Array Modifiers*
  void swap(array<value_type, _MAX> &other);
  void fill(const_reference value);

  array();
  explicit array(std::initializer_list<value_type> const &items);
  array(const array<value_type, _MAX> &a);
  array(array<value_type, _MAX> &&a);
  array<value_type, _MAX> &operator=(array<value_type, _MAX> &&a);
  ~array();
};

}  // namespace s21

#include "s21_array_access.tpp"
#include "s21_array_begin_end.tpp"
#include "s21_array_capacity.tpp"
#include "s21_array_constructor.tpp"
#include "s21_array_modify.tpp"

#endif  //_S21_ARRAY_H_
