#include "s21_list.h"

template <typename Type>
Type list<Type>::operator()(const int i) {
  short result = SUCCESS;
  list_node *iter = begin();
  int index = 0;
  for (; index < i && result; index++) {
    iter = iter->next;
    result = (iter != nullptr);
  }

  return iter->data;
}
