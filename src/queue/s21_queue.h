#ifndef _QUEUE_H_
#define _QUEUE_H_

#include "../list/s21_list.h"

namespace s21 {

template <typename Key>
class queue {
 private:
  list<Key> data;

 public:
  using value_type = Key;
  using reference = Key&;
  using const_reference = const Key&;
  using size_type = size_t;

  queue() = default;
  queue(queue& other) = default;
  queue(queue&& other) = default;
  explicit queue(std::initializer_list<Key> const& items);
  ~queue() = default;

  queue& operator=(queue& other) = default;
  queue& operator=(queue&& other) = default;

  void push(const_reference value);
  void pop();
  const_reference front() const;
  const_reference back() const;
  bool empty() const;
  size_type size() const;
  void swap(queue& other);
};

template class queue<int>;
}  // namespace s21

#endif