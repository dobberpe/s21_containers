#include "s21_list.h"
using namespace s21;

template <typename value_type>
typename List<value_type>::iterator List<value_type>::insert(
    iterator pos, const_reference value) {
  int exit_code = _NO_ERROR;
  List_node *save_pos = pos.get_iter_ptr();
  List_node *new_node = nullptr;
  try {
    new_node = new List_node(value);
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
void List<value_type>::erase(List<value_type>::iterator pos) {
  if (empty() == CONTAINER_NOT_EMPTY && pos != end()) {
    List_node *removing_elem = pos.get_iter_ptr();
    List_node *before = removing_elem->prev;
    List_node *after = removing_elem->next;
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
void List<value_type>::push_back(const_reference value) {
  insert(end(), value);
}

template <typename value_type>
void List<value_type>::pop_back() {
  iterator iter = end();
  --iter;
  erase(iter);
}

template <typename value_type>
void List<value_type>::push_front(const_reference value) {
  insert(begin(), value);
}

template <typename value_type>
void List<value_type>::pop_front() {
  erase(begin());
}

// template <typename value_type>
// typename List<value_type>::iterator List<value_type>::insert_many(const
// List<value_type>::iterator pos,
//                                                ...) {
//   va_List args;
//   va_start(args, pos);

//   // for (int i = 0; i < 10; i++) {
//   //   va_arg(args, type);
//   //   args.
//   // }

//   va_end(va_List);
// }

// template <typename value_type>
// void List<value_type>::insert_many_back(Args &&...args) {}

// template <typename value_type>
// void List<value_type>::insert_many_front(Args &&...args) {}
