#ifndef _S21_List_H_
#define _S21_List_H_

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
class List {
 public:
  using value_type = T;
  using reference = value_type &;
  using const_reference = const value_type &;
  using size_type = size_t;
  using iterator = ListIterator<value_type>;
  using const_iterator = ListConstIterator<value_type>;

 private:
  class List_node {
   public:
    value_type data;
    List_node *prev;
    List_node *next;
    // List_node();
    explicit List_node(value_type data_node);
  };
  List_node *head_node;
  List_node *tail_node;
  size_type number;
  void create_empty_list();

 public:
  reference front();
  reference back();
  const_reference back() const;
  const_reference front() const;
  iterator begin();
  iterator end();
  const_iterator begin() const;
  const_iterator end() const;
  bool empty() const;
  size_type size() const;
  size_type max_size() const;
  reference operator()(size_type i);
  const_reference operator()(size_type i) const;
  bool operator==(const List<value_type> &List_other) const;

  void clear();
  iterator insert(iterator pos, const_reference value);
  void erase(iterator pos);
  void push_back(const_reference value);
  void pop_back();
  void push_front(const_reference value);
  void pop_front();

  void swap(List &other);
  void merge(List &merge);
  void splice(const_iterator pos, List &other);

  void reverse();
  void unique();
  void sort();
  

  // iterator insert_many(const iterator pos, ...);
  // Inserts new elements into the container directly before pos.
  // List, Vector.

  // void insert_many_back(Args&&... args);
  // Appends new elements to the end of the container.	List, Vector, Queue.
  // void insert_many_front(Args&&... args);

  List();
  explicit List(const size_type count);
  explicit List(std::initializer_list<value_type> const &items);
  List(const List<value_type> &copy);
  List(List<value_type> &&moved);
  List<value_type> &operator=(List<value_type> &&moved);
  ~List();

  friend ListIterator<value_type>;
  friend ListConstIterator<value_type>;
};  // List<T>

template <typename T>
class ListConstIterator {
 public:
  typename List<T>::List_node *index_ptr;

 public:
  ListConstIterator();
  ListConstIterator(typename List<T>::List_node *copy);
  ListConstIterator(const ListConstIterator &copy);
  ListConstIterator &operator++();
  ListConstIterator &operator--();
  typename List<T>::const_reference operator*() const;
  bool operator==(const ListConstIterator &pos);
  bool operator!=(const ListConstIterator &pos);
  ListConstIterator &operator=(ListConstIterator &pos);
  ListConstIterator &operator=(const ListIterator<T> &pos);
  typename List<T>::List_node *get_iter_ptr();
};

template <typename value_type>
class ListIterator {
 public:
  typename List<value_type>::List_node *index_ptr;

 public:
  ListIterator();
  ListIterator(typename List<value_type>::List_node *copy);
  ListIterator(ListConstIterator<value_type> &copy);
  ListIterator(const ListIterator &copy);
  ListIterator &operator++();
  ListIterator &operator--();
  typename List<value_type>::reference operator*();
  bool operator==(const ListIterator &pos);
  bool operator!=(const ListIterator &pos);
  ListIterator &operator=(const ListIterator &pos);
  typename List<value_type>::List_node *get_iter_ptr();
};

template class List<int>;
template class List<double>;
template class ListIterator<int>;
template class ListIterator<double>;
template class ListConstIterator<int>;
template class ListConstIterator<double>;
}  // namespace s21
#endif  //_S21_List_H_
