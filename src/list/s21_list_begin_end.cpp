#include "s21_list.h"

template <typename Type>
typename list<Type>::list_node *list<Type>::begin() {
  return first_node;
}

template <typename Type>
typename list<Type>::list_node *list<Type>::end() {
  list_node *result = first_node;
  for (; result->next != nullptr; result = result->next)
    ;

  return result;
}
