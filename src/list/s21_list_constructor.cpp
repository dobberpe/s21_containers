#include "s21_list.h"
using namespace s21;

#define CREATE_EMPTY_LIST                \
  tail_node = new List<T>::list_node(0); \
  head_node = tail_node;                 \
  number = 0;                            \
  tail_node->prev = head_node;           \
  tail_node->next = nullptr;             \
  iter_head = head_node;                 \
  iter_tail = tail_node;

template <typename T>
List<T>::List() {
  CREATE_EMPTY_LIST;
}

template <typename T>
List<T>::List(const size_type count) {
  CREATE_EMPTY_LIST;
  if (count < max_size())
    for (size_type i = 0; i < count; i++) push_back(0);
}

template <typename T>
List<T>::List(List<T> &copy) {
  CREATE_EMPTY_LIST;
  if (copy.empty() == CONTAINER_NOT_EMPTY) {
    iterator iter;
    for (iter = copy.begin(); iter != copy.end(); ++iter) push_back(*iter);
  }
}

template <typename T>
List<T>::List(List<T> &&moved) {
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

template <typename T>
List<T> &List<T>::operator=(List<T> &&moved) {
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

template <typename T>
List<T>::List(std::initializer_list<T> const &items) {
  CREATE_EMPTY_LIST;
  for (T data : items) push_back(data);
}

template <typename T>
List<T>::~List() {
  clear();
  if (tail_node) delete tail_node;
}

template <typename T>
List<T>::list_node::list_node(const T data_node) {
  data = data_node;
}
