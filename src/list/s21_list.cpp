#include "s21_list.h"

// template <typename Type>
// void list<Type>::print_list() {
//   if (this->list_empty() == CONTAINER_NOT_EMPTY) {
//     list<Type>::iterator iter;
//     iter = begin();
//     for (; iter != end(); ++iter) cout << *iter << " ";
//     cout << *iter << endl;
//   } else
//     cout << "Container is empty." << endl;
// }

template <typename Type>
bool list<Type>::add_elem(Type new_elem) {
  short result = SUCCESS;
  int exit_code = _NO_ERROR;
  if (list_empty() == CONTAINER_EMPTY) {
    first_node = new list<Type>::list_node(new_elem);
    first_node->prev = nullptr;
    first_node->next = new list<Type>::list_node(0);
    first_node->next->prev = first_node;
  } else {
    list_node *save_end_index = end();
    list_node *new_node = nullptr;
    try {
      new_node = new list<Type>::list_node(new_elem);
    } catch (int error) {
      exit_code = error;
    }
    if (!exit_code) {
      new_node->prev = save_end_index->prev;
      new_node->next = save_end_index;
      save_end_index->prev->next = new_node;
      save_end_index->prev = new_node;
    } else
      result = FAILURE;
  }
  return result;
}

template <typename Type>
bool list<Type>::remove_elem() {
  short result = SUCCESS;
  if (list_empty() == CONTAINER_NOT_EMPTY) {
    list_node *save_end_index = end();
    list_node *removing_elem = save_end_index->prev;

    if (removing_elem != first_node) {
      removing_elem->prev->next = save_end_index;
      save_end_index->prev = removing_elem->prev;
      removing_elem->prev = removing_elem->next = nullptr;
      delete removing_elem;

    } else {  // iter == first
      save_end_index->prev = save_end_index->next = nullptr;
      first_node = nullptr;
      delete removing_elem;
      delete save_end_index;
    }
  } else
    result = FAILURE;

  return result;
}

template <typename Type>
void list<Type>::list_clean() {
  while (list_empty() == CONTAINER_NOT_EMPTY) remove_elem();
}

template <typename Type>
bool list<Type>::list_empty() {
  short result = CONTAINER_NOT_EMPTY;
  if (first_node == nullptr) result = CONTAINER_EMPTY;
  return result;
}

template <typename Type>
int list<Type>::list_count() {
  int count = 0;
  if (this->list_empty() == CONTAINER_NOT_EMPTY) {
    list<Type>::iterator iter;
    iter = begin();
    
    for (; iter != end(); ++iter, count++) ;
  }

  return count;
}
