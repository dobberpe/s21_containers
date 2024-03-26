#include "s21_list.h"
using namespace s21;

template <typename T>
typename list<T>::iterator list<T>::insert(iterator pos, const T &value) {
  int exit_code = _NO_ERROR;
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

template <typename T>
void list<T>::erase(list<T>::iterator pos) {
  if (empty() == CONTAINER_NOT_EMPTY && pos != end()) {
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

template <typename T>
void list<T>::push_back(const T &value) {
  insert(end(), value);
}

template <typename T>
void list<T>::pop_back() {
  iterator iter = end();
  --iter;
  erase(iter);
}

template <typename T>
void list<T>::push_front(const T &value) {
  insert(begin(), value);
}

template <typename T>
void list<T>::pop_front() {
  erase(begin());
}

// template <typename T>
// typename list<T>::iterator list<T>::insert_many(const
// list<T>::iterator pos,
//                                                ...) {
//   va_list args;
//   va_start(args, pos);

//   // for (int i = 0; i < 10; i++) {
//   //   va_arg(args, type);
//   //   args.
//   // }

//   va_end(va_list);
// }

// template <typename T>
// void list<T>::insert_many_back(Args &&...args) {}

// template <typename T>
// void list<T>::insert_many_front(Args &&...args) {}
