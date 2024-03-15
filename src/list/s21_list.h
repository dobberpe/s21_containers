#ifndef _S21_LIST_H_
#define _S21_LIST_H_

using namespace std;

#include <iostream>

#include "../s21_containers.h"

template <typename Type>
class list {
 private:
  class list_node {
   public:
    Type data;
    list_node *prev;
    list_node *next;
    list_node(Type data_node);
  };

  list_node *first_node;

 public:
  class iterator {
   private:
    list_node *index_ptr;

   public:
    iterator();
    Type &operator*();
    void operator++();
    void operator--();
    bool operator==(const list<Type>::iterator &iter2);
    bool operator!=(const list<Type>::iterator &iter2);

    void operator=(const list<Type>::iterator &iter2);
    void operator=(list_node *node);
    bool operator!=(const list_node *node);
  };

  list_node *begin();
  list_node *end();
  // void print_list();
  bool add_elem(Type new_elem);
  bool remove_elem();
  void list_clean();
  int list_count();
  bool list_empty();
  Type operator()(const int i);

  /*
  iterator insert_many(const_iterator pos, Args&&... args)	Inserts new
  elements into the container directly before pos.	List, Vector.

  void insert_many_back(Args&&... args)	Appends new elements to the end of the
  container.	List, Vector, Queue.
  void insert_many_front(Args&&... args)
  */

  list();
  list(Type data_init);
  list(list<Type> &other);
  list(list<Type> &&other);
  ~list();
};

template class list<int>;
template class list<double>;
// template class list<long double>;
// template class list<short>;
// template class list<char>;
// template class list<unsigned char>;
// template class list<unsigned short>;
// template class list<unsigned int>;

#endif  //_S21_LIST_H_
