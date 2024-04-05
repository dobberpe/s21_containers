#include "s21_list.h"
using namespace s21;

template <typename value_type>
void list<value_type>::create_empty_list() {
  tail_node = new list<value_type>::list_node(0);
  head_node = tail_node;
  number = 0;
  tail_node->prev = head_node;
  tail_node->next = nullptr;

}


template <typename value_type>
list<value_type>::list() {
  create_empty_list();
}

template <typename value_type>
list<value_type>::list(const size_type count) {
  create_empty_list();
  if (count < max_size())
    for (size_type i = 0; i < count; i++) push_back(0);
}

template <typename value_type>
list<value_type>::list(const list<value_type> &copy) {
  create_empty_list();

  if (copy.empty() == CONTAINER_NOT_EMPTY) {
    const_iterator iter = copy.begin();
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
  create_empty_list();
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
  create_empty_list();
  for (value_type data : items) push_back(data);
}

template <typename value_type>
list<value_type>::~list() {
  clear();
  if (tail_node) delete tail_node;
}

template <typename value_type>
list<value_type>::list_node::list_node(value_type data_node) {
  data = data_node;
}
