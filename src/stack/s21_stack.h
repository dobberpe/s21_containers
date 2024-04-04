#ifndef _STACK_H_
#define _STACK_H_

#include "../list/s21_list.h"

namespace s21 {

template <typename Key>
class stack {
 private:
  list<Key> data;

 public:
  using value_type = Key;
  using reference = Key&;
  using const_reference = const Key&;
  using size_type = size_t;

  stack() = default;
  stack(stack& other) = default;
  stack(stack&& other) = default;
  explicit stack(std::initializer_list<Key> const& items);
  ~stack() = default;

  stack& operator=(stack& other) = default;
  stack& operator=(stack&& other) = default;

  void push(const_reference value);
  void pop();
  void swap(stack& other);

  const_reference top() const;

  bool empty() const;
  size_type size() const;
};

template class stack<int>;
}  // namespace s21

#endif