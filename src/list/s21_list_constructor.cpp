#include <stdio.h>

using namespace std;

#include "s21_list.h"

#define CREATE_EMPTY_LIST                \
  tail_node = new list<T>::list_node(0); \
  head_node = tail_node;                 \
  tail_node->prev = head_node;           \
  tail_node->next = nullptr;

template <typename T>
list<T>::list() {
  CREATE_EMPTY_LIST;
}

template <typename T>
list<T>::list(const int count) {
  CREATE_EMPTY_LIST;
  for (int i = 0; i < count; i++) push_back(0);
}

template <typename T>
list<T>::list(list<T> &other) {
  CREATE_EMPTY_LIST;
  if (other.empty() == CONTAINER_NOT_EMPTY) {
    list<T>::iterator iter, iter_end;
    iter_end = other.end();
    for (iter = other.begin(); iter != iter_end; ++iter) push_back(*iter);
  }
}

template <typename T>
list<T>::list(list<T> &&other) {
  if (other.empty() == CONTAINER_NOT_EMPTY) {
    head_node = other.head_node;
    tail_node = other.tail_node;
    head_node->prev = head_node;
    other.head_node = other.tail_node = nullptr;
  } else {
    CREATE_EMPTY_LIST;
  }
}

template <typename T>  // !!!!!!!!!!!!!!!!!!!!!!!!!
list<T> &list<T>::operator=(list<T> &&other) {
  // list<T>::list(move(other));
  if (other.empty() == CONTAINER_NOT_EMPTY) {
    // head_node = other.head_node;
    // other.tail_node->prev->next = tail_node;
    // other.head_node = other.tail_node;
  }
  return *this;
}

template <typename T>
list<T>::list(std::initializer_list<T> const &items) {
  CREATE_EMPTY_LIST;
  for (auto &data : items) push_back(data);
}

template <typename T>
list<T>::~list() {
  clear();
}

template <typename T>
list<T>::list_node::list_node(const T data_node) {
  data = data_node;
}