#include "s21_list.h"
using namespace s21;

template <typename value_type>
typename list<value_type>::iterator list<value_type>::insert(
    iterator pos, const_reference value) {
  int exit_code = _NO_ERROR;
  // list_node *save_pos = pos.index_ptr;
  list_node *save_pos = pos.get_iter_ptr();
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
    number++;
  }

  return pos;
}

template <typename value_type>
void list<value_type>::erase(list<value_type>::iterator pos) {
  if (empty() == CONTAINER_NOT_EMPTY && pos != end()) {
    // list_node *removing_elem = pos.index_ptr;
    list_node *removing_elem = pos.get_iter_ptr();
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
    number--;
  }
}

template <typename value_type>
void list<value_type>::push_back(const_reference value) {
  insert(end(), value);
}

template <typename value_type>
void list<value_type>::pop_back() {
  iterator iter = end();
  --iter;
  erase(iter);
}

template <typename value_type>
void list<value_type>::push_front(const_reference value) {
  insert(begin(), value);
}

template <typename value_type>
void list<value_type>::pop_front() {
  erase(begin());
}

// template <typename value_type>
// typename list<value_type>::iterator list<value_type>::insert_many(
//     const list<value_type>::iterator pos, Args &&...args) {
//   va_List args;
//   va_start(args, pos);

//   // for (int i = 0; i < 10; i++) {
//   //   va_arg(args, type);
//   //   args.
//   // }

//   va_end(va_List);
// }

// template <typename value_type>
// void list<value_type>::insert_many_back(Args &&...args) {}

// template <typename value_type>
// void list<value_type>::insert_many_front(Args &&...args) {}
