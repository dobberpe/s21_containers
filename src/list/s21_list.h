#ifndef _S21_LIST_H_
#define _S21_LIST_H_

#include <stdio.h>

#include <initializer_list>

#include "../s21_containers.h"

template <typename T>
class list {
 private:
  class list_node {
   public:
    T data;
    list_node *prev;
    list_node *next;
    list_node(const T data_node);
  };

  list_node *head_node;
  list_node *tail_node;

 public:
  class iterator {
   private:
    list_node *index_ptr;

   public:
    iterator();
    T &operator*();
    void operator++();
    void operator--();
    bool operator==(const list<T>::iterator &iter2);
    bool operator!=(const list<T>::iterator &iter2);

    void operator=(const list<T>::iterator &iter2);
    void operator=(list_node *node);
    bool operator!=(const list_node *node);
  };

  // void print_list();

  const T &front();
  const T &back();
  list_node *begin();
  list_node *end();
  bool push_back(T new_elem);
  bool pop_back();
  void clear();
  int size();
  bool empty();
  T &operator()(const int i);

  // iterator insert(iterator pos, const_reference value);
  // void erase(iterator pos);
  // void push_front(const_reference value);
  // void pop_front();

  // void swap(list &other);
  // void merge(list &other);
  // void splice(const_iterator pos, list &other);

  // void reverse();
  // void unique();
  // void sort();

  /*
  iterator insert_many(const_iterator pos, Args&&... args)	Inserts new
  elements into the container directly before pos.	List, Vector.

  void insert_many_back(Args&&... args)	Appends new elements to the end of the
  container.	List, Vector, Queue.
  void insert_many_front(Args&&... args)
  */

  list();
  list(list<T> &other);
  list(const int count);
  list<T> &operator=(list<T> &&other);
  list(std::initializer_list<T> const &items);
  list(list<T> &&other);
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
