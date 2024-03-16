#include "s21_list.h"

template <typename T>
T &list<T>::operator()(const int i) {
  short result = SUCCESS;
  list_node *node = begin();
  int index = 0;
  for (; index < i && result; index++) {
    node = node->next;
    result = (node != nullptr);
  }

  return node->data;
}
