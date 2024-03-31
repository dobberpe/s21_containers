#include "s21_stack.h"

using namespace s21;

template <typename Key>
Stack<Key>::Stack(std::initializer_list<Key> const& items) {
  for (const auto& item : items) {
    push(item);
  }
}

template <typename Key>
void Stack<Key>::push(const_reference value) {
  list.push_back(value);
}

template <typename Key>
void Stack<Key>::pop() {
  if (!empty()) {
    list.pop_back();
  }
}

template <typename Key>
typename Stack<Key>::const_reference Stack<Key>::top() const {
  return list.back();
}

template <typename Key>
bool Stack<Key>::empty() const {
  return list.empty();
}

template <typename Key>
typename Stack<Key>::size_type Stack<Key>::size() const {
  return list.size();
}

template <typename Key>
void Stack<Key>::swap(Stack& other) {
  list.swap(other.list);
}