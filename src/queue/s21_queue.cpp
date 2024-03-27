#include "s21_queue.h"

using namespace s21;

template <typename Key>
Queue<Key>::Queue(std::initializer_list<Key> const& items) {
  for (const auto& item : items) {
    push(item);
  }
}

template <typename Key>
void Queue<Key>::push(const_reference value) {
  list.push_back(value);
}

template <typename Key>
void Queue<Key>::pop() {
  if (!empty()) {
    list.pop_front();
  }
}

template <typename Key>
typename Queue<Key>::const_reference Queue<Key>::front() const {
  return list.front();
}

template <typename Key>
typename Queue<Key>::const_reference Queue<Key>::back() const {
  return list.back();
}

template <typename Key>
bool Queue<Key>::empty() const {
  return list.empty();
}

template <typename Key>
typename Queue<Key>::size_type Queue<Key>::size() const {
  return list.size();
}

template <typename Key>
void Queue<Key>::swap(Queue& other) {
  list.swap(other.list);
}