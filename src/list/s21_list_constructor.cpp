#include "s21_list.h"
using namespace s21;
/*
#define CREATE_EMPTY_List                         \
  tail_node = new List<value_type>::List_node(0); \
  head_node = tail_node;                          \
  number = 0;                                     \
  tail_node->prev = head_node;                    \
  tail_node->next = nullptr;

*/

// template <typename value_type>
// List<value_type>::List_node::List_node() {
//   prev = next = nullptr;
//   data = 0;
//   // using List<value_type>;

//   List<value_type>::tail_node = *this;
//   List<value_type>::head_node = List<value_type>::tail_node;
//   List<value_type>::number = 0;
//   List<value_type>::tail_node->prev = List<value_type>::head_node;
//   List<value_type>::tail_node->next = nullptr;
// }

template <typename value_type>
void List<value_type>::create_empty_list() {
  tail_node = new List<value_type>::List_node(0);
  head_node = tail_node;
  number = 0;
  tail_node->prev = head_node;
  tail_node->next = nullptr;

}


template <typename value_type>
List<value_type>::List() {
  // CREATE_EMPTY_List;
  // List_node();
  create_empty_list();
}

template <typename value_type>
List<value_type>::List(const size_type count) {
  // CREATE_EMPTY_List;
    // List_node();
  create_empty_list();
  if (count < max_size())
    for (size_type i = 0; i < count; i++) push_back(0);
}

template <typename value_type>
List<value_type>::List(const List<value_type> &copy) {
  // CREATE_EMPTY_List;
    // List_node();
  create_empty_list();

  if (copy.empty() == CONTAINER_NOT_EMPTY) {
    const_iterator iter = copy.begin();
    for (; iter != copy.end(); ++iter) push_back(*iter);
  }
}

template <typename value_type>
List<value_type>::List(List<value_type> &&moved) {
  if (moved.empty() == CONTAINER_NOT_EMPTY) {
    number = moved.number;
    head_node = moved.head_node;
    tail_node = moved.tail_node;
    head_node->prev = head_node;
    moved.head_node = moved.tail_node = nullptr;
    moved.number = 0;
  } else {
    // CREATE_EMPTY_List;
      // List_node();
  create_empty_list();
  }
}

template <typename value_type>
List<value_type> &List<value_type>::operator=(List<value_type> &&moved) {
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
List<value_type>::List(std::initializer_list<value_type> const &items) {
  // CREATE_EMPTY_List;
    // List_node();
  create_empty_list();
  for (value_type data : items) push_back(data);
}

template <typename value_type>
List<value_type>::~List() {
  clear();
  if (tail_node) delete tail_node;
}

template <typename value_type>
List<value_type>::List_node::List_node(value_type data_node) {
  data = data_node;
}
