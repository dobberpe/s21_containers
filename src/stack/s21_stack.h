#ifndef _STACK_H_
#define _STACK_H_

#include "../list/s21_list.h"

namespace s21 {

template <typename Key>
class Stack {
 private:
  List<Key> list;

 public:
  using value_type = Key;
  using reference = Key&;
  using const_reference = const Key&;
  using size_type = size_t;

  Stack() = default;
  Stack(Stack& other) = default;
  Stack(Stack&& other) = default;
  Stack(std::initializer_list<Key> const& items);
  ~Stack() = default;

  Stack& operator=(Stack& other) = default;
  Stack& operator=(Stack&& other) = default;

  void push(const_reference value);
  void pop();
  void swap(Stack& other);

  const_reference top() const;

  bool empty() const;
  size_type size() const;
};

template class Stack<int>;
}  // namespace s21

#endif