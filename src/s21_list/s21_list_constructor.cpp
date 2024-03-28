#include "s21_list.h"
using namespace s21;

#define CREATE_EMPTY_LIST                \
  tail_node = new list<value_type>::list_node(0); \
  head_node = tail_node;                 \
  number = 0;                            \
  tail_node->prev = head_node;           \
  tail_node->next = nullptr;             

template <typename value_type>
list<value_type>::list() {
  CREATE_EMPTY_LIST;
}

template <typename value_type>
list<value_type>::list(size_type count) {
  CREATE_EMPTY_LIST;
  if (count < max_size())
    for (size_type i = 0; i < count; i++) push_back(0);
}

template <typename value_type>
list<value_type>::list( list<value_type> &copy) {
  CREATE_EMPTY_LIST;
  if (copy.empty() == CONTAINER_NOT_EMPTY) {
    iterator iter = copy.begin();
    for (; iter != copy.end(); ++iter) push_back(*iter);
  }
}

template <typename value_type>
list<value_type>::list(list<value_type> &&moved) {
  if (moved.empty() == CONTAINER_NOT_EMPTY) {
    number = moved.number;
    head_node = moved.head_node;
    tail_node = moved.tail_node;
    head_node->prev = head_node;
    moved.head_node = moved.tail_node = nullptr;
    moved.number = 0;
  } else {
    CREATE_EMPTY_LIST;
  }
}

template <typename value_type>
list<value_type> &list<value_type>::operator=(list<value_type> &&moved) {
  if (&moved != this) {
    clear();
    if (moved.empty() == CONTAINER_NOT_EMPTY) {
      delete tail_node;
      number = moved.number;
      head_node = moved.head_node;
      tail_node = moved.tail_node;
      head_node->prev = head_node;
      moved.head_node = moved.tail_node = nullptr;
      moved.number = 0;
    }
  }
  return *this;
}

template <typename value_type>
list<value_type>::list(std::initializer_list<value_type> const &items) {
  CREATE_EMPTY_LIST;
  for (value_type data : items) push_back(data);
}

template <typename value_type>
list<value_type>::~list() {
  clear();
  if (tail_node) delete tail_node;
}

template <typename value_type>
list<value_type>::list_node::list_node(const_reference data_node) {
  data = data_node;
}
