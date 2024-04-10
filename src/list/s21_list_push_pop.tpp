#include "s21_list.h"
using namespace s21;

template <typename value_type>
typename list<value_type>::iterator list<value_type>::insert(
    iterator pos, const_reference value) {
  int exit_code = _NO_ERROR;
  list_node *save_pos = pos.index_ptr;

  list_node *new_node = nullptr;
  try {
    new_node = new list_node(value);
  } catch (int error) {
    exit_code = error;
  }
  if (!exit_code) {
    new_node->next = save_pos;
    new_node->prev = save_pos->prev;
    save_pos->prev = new_node;

    if (save_pos == head_node) {
      head_node = new_node;
    } else {
      new_node->prev->next = new_node;
    }
    ++number;
  }

  return pos;
}

template <typename value_type>
void list<value_type>::erase(list<value_type>::iterator pos) {
  if (empty() == CONTAINER_NOT_EMPTY && pos != end()) {
    list_node *removing_elem = pos.index_ptr;
    list_node *before = removing_elem->prev;
    list_node *after = removing_elem->next;
    if (removing_elem != head_node) {
      before->next = after;
      after->prev = before;
    } else {
      head_node = after;
      after->prev = head_node;
    }
    removing_elem->data = 0;
    removing_elem->prev = removing_elem->next = nullptr;
    delete removing_elem;
    --number;
  }
}

template <typename value_type>
void list<value_type>::push_back(const_reference value) {
  insert(end(), value);
}

template <typename value_type>
void list<value_type>::pop_back() {
  erase(--end());
}

template <typename value_type>
void list<value_type>::push_front(const_reference value) {
  insert(begin(), value);
}

template <typename value_type>
void list<value_type>::pop_front() {
  erase(begin());
}

template <typename value_type>
template <typename... Args>
typename list<value_type>::iterator list<value_type>::insert_many(
    const_iterator pos, Args &&...args) {
  list tmp{args...};
  this->splice(pos, tmp);
  return pos;
}

template <typename value_type>
template <typename... Args>
void list<value_type>::insert_many_back(Args &&...args) {
  (insert_many(cend(), std::forward<value_type>(args)), ...);
}

template <typename value_type>
template <typename... Args>
void list<value_type>::insert_many_front(Args &&...args) {
  insert_many(cbegin(), args...);
}
