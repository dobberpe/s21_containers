#include "s21_vector.h"

using namespace s21;

template <typename value_type>
void vector<value_type>::swap(vector &other) {
  if (this != &other) {
    value_type *save = head_node;
    head_node = other.head_node;
    other.head_node = save;

    size_type save_mn = max_number;
    max_number = other.max_number;
    other.max_number = save_mn;

    save_mn = number;
    number = other.number;
    other.number = save_mn;
  }
}

template <typename value_type>
typename vector<value_type>::iterator vector<value_type>::insert(
    iterator pos, const_reference value) {
  if (!head_node) reserve(1);

  size_type i = 0;
  value_type last_vect = value;
  if (empty() == CONTAINER_NOT_EMPTY) {
    iterator curr = end();
    iterator prev_iter = --end();
    last_vect = *prev_iter;
    i = number;

    for (; curr != pos; i--) {
      if (curr != end()) *curr = *prev_iter;
      --curr;
      --prev_iter;
    }
  }
  if (i < number)
    *pos = value;
  else
    last_vect = value;

  if (size() + 1 > capacity()) reserve(capacity() * 2);
  *end() = last_vect;
  number += 1;
  return iterator(head_node + i);
}

template <typename value_type>
void vector<value_type>::erase(vector<value_type>::iterator pos) {
  if (empty() == CONTAINER_NOT_EMPTY) {
    iterator curr = pos;
    iterator finish = --end();
    iterator new_iter = curr;

    for (; curr != finish;) {
      *curr = *(++new_iter);
      curr = new_iter;
    }
    number -= 1;
  }
}

template <typename value_type>
void vector<value_type>::clear() {
  while (size() != 0) pop_back();
}

template <typename value_type>
void vector<value_type>::push_back(const_reference value) {
  insert(end(), value);
}

template <typename value_type>
void vector<value_type>::pop_back() {
  if (size() > 0) erase(--end());
}

template <typename value_type>
template <typename... Args>
typename vector<value_type>::iterator vector<value_type>::insert_many(
    const_iterator pos, Args &&...args) {
  vector tmp{args...};
  for (size_type i = 0; i < tmp.size(); i++, ++pos) {
    pos = insert(pos, tmp[i]);
  }
  return pos;
}

template <typename value_type>
template <typename... Args>
void vector<value_type>::insert_many_back(Args &&...args) {
  insert_many(cend(), args...);
}
