#include "s21_list.h"

template <typename Type>
list<Type>::list() {
  first_node = nullptr;
}

template <typename Type>
list<Type>::list(Type data_init) {
  first_node = nullptr;
  add_elem(data_init);
}

template <typename Type>
list<Type>::list(list<Type> &other) {
  first_node = nullptr;

  if (other.list_empty() == CONTAINER_NOT_EMPTY) {
    list<Type>::iterator iter, iter_end;
    iter_end = other.end();
    for (iter = other.begin(); iter != iter_end; ++iter) add_elem(*iter);
  }
}

template <typename Type>
list<Type>::list(list<Type> &&other) {
  if (other.list_empty() == CONTAINER_NOT_EMPTY) {
    first_node = other.first_node;

    other.first_node = nullptr;
  } else {
    first_node = nullptr;
  }
}

template <typename Type>
list<Type>::~list() {
  list_clean();
}

template <typename Type>
list<Type>::list_node::list_node(Type data_node) {
  data = data_node;
  next = nullptr;
}