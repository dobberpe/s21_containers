#include "s21_list.h"

// template <typename T>
// void list<T>::print_list() {
//   if (this->empty() == CONTAINER_NOT_EMPTY) {
//     list<T>::iterator iter;
//     iter = begin();
//     for (; iter != end(); ++iter) cout << *iter << " ";
//     cout << *iter << endl;
//   } else
//     cout << "Container is empty." << endl;
// }

template <typename T>
bool list<T>::push_back(T new_elem) {
  short result = SUCCESS;
  int exit_code = _NO_ERROR;
  list_node *save_end_index = end();
  list_node *new_node = nullptr;
  try {
    new_node = new list<T>::list_node(new_elem);
  } catch (int error) {
    exit_code = error;
  }
  if (!exit_code) {
    new_node->next = save_end_index;
    new_node->prev = save_end_index->prev;
    save_end_index->prev = new_node;
    if (empty() == CONTAINER_EMPTY) {
      head_node = new_node;
    } else {
      new_node->prev->next = new_node;
    }
  } else
    result = FAILURE;
  // }
  return result;
}

template <typename T>
bool list<T>::pop_back() {
  short result = SUCCESS;
  if (empty() == CONTAINER_NOT_EMPTY) {
    list_node *save_end_index = end();
    list_node *removing_elem = save_end_index->prev;

    if (removing_elem != head_node) {
      save_end_index->prev = removing_elem->prev;
      save_end_index->prev->next = save_end_index;
    } else {
      head_node = tail_node;
      save_end_index->prev = head_node;
    }
    removing_elem->data = 0;
    removing_elem->prev = removing_elem->next = nullptr;
    delete removing_elem;
  } else
    result = FAILURE;

  return result;
}

template <typename T>
void list<T>::clear() {
  while (empty() == CONTAINER_NOT_EMPTY) pop_back();

  delete tail_node;
}

template <typename T>
bool list<T>::empty() {
  short result = CONTAINER_NOT_EMPTY;
  if (head_node == tail_node) result = CONTAINER_EMPTY;
  return result;
}

template <typename T>
int list<T>::size() {
  int count = 0;
  if (this->empty() == CONTAINER_NOT_EMPTY) {
    list<T>::iterator iter;
    iter = begin();

    for (; iter != end(); ++iter, count++)
      ;
  }

  return count;
}
