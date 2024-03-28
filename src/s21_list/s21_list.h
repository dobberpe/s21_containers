#ifndef _S21_LIST_H_
#define _S21_LIST_H_

#define _NO_ERROR 0
#define SUCCESS 1
#define FAILURE 0
#define CONTAINER_EMPTY 1
#define CONTAINER_NOT_EMPTY 0

#include <cstddef>
#include <initializer_list>

namespace s21 {

template <typename T>
class ListIterator;

template <typename T>
class ListConstIterator;

template <typename T>
class list {
 public:
  using value_type = T;
  using reference = value_type &;
  using const_reference = const value_type &;
  using size_type = size_t;
  using iterator = ListIterator<value_type>;
  using const_iterator = ListConstIterator<value_type>;

 public:  // private
  class list_node {
   public:
    value_type data;
    list_node *prev;
    list_node *next;
    explicit list_node(const_reference data_node);
  };

  list_node *head_node;
  list_node *tail_node;
  size_type number;

 public:
  const_reference front();
  const_reference back();
  iterator begin();
  iterator end();
  const_iterator cbegin() const;
  const_iterator cend() const;
  bool empty();
  size_type size();
  size_type max_size();
  reference operator()(const size_type i);
  bool operator==(list<value_type> &list_other);

  void clear();
  iterator insert(iterator pos, const_reference value);
  void erase(iterator pos);
  void push_back(const_reference value);
  void pop_back();
  void push_front(const_reference value);
  void pop_front();

  void swap(list &other);
  void merge(list &other);
  void splice(iterator pos, list &other);  ///////////const inter!!!

  void reverse();
  void unique();
  void sort();

  // iterator insert_many(const iterator pos, ...);
  // Inserts new elements into the container directly before pos.
  // list, Vector.

  // void insert_many_back(Args&&... args);
  // Appends new elements to the end of the container.	list, Vector, Queue.
  // void insert_many_front(Args&&... args);

  list();
  explicit list(size_type count);
  explicit list(std::initializer_list<value_type> const &items);
  list(list<value_type> &copy);  //// const COPY
  list(list<value_type> &&moved);
  list<value_type> &operator=(list<value_type> &&moved);
  ~list();

  friend ListIterator<value_type>;
  friend ListConstIterator<value_type>;
};

template <typename value_type>
class ListIterator {
 private:
  typename list<value_type>::list_node *index_ptr;

 public:
  ListIterator();
  ListIterator(ListIterator &copy);
  ListIterator &operator++();
  ListIterator &operator--();
  typename list<value_type>::reference operator*();
  bool operator==(const ListIterator &pos);
  bool operator!=(const ListIterator &pos);

  ListIterator &operator=(typename list<value_type>::list_node *node);
  ListIterator &operator=(const typename list<value_type>::iterator &pos);
  typename list<value_type>::list_node *get_iter_ptr();
};

template <typename value_type>
class ListConstIterator {
 private:
  typename list<value_type>::list_node *index_ptr;

 public:
  ListConstIterator();
  ListConstIterator &operator++();
  ListConstIterator &operator--();
  const typename list<value_type>::reference operator*() const;
  bool operator==(const ListConstIterator &pos);
  bool operator!=(const ListConstIterator &pos);

  ListConstIterator &operator=(typename list<value_type>::list_node *node);
  ListConstIterator &operator=(typename list<value_type>::iterator &pos);
  typename list<value_type>::list_node *get_iter_ptr();
};

template class list<int>;
template class list<double>;
template class ListIterator<int>;
template class ListIterator<double>;
template class ListConstIterator<int>;
template class ListConstIterator<double>;
// template class list<long double>;
// template class list<short>;
// template class list<char>;
// template class list<unsigned char>;
// template class list<unsigned short>;
// template class list<unsigned int>;
}  // namespace s21
#endif  //_S21_LIST_H_
