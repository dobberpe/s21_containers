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

 private:
  class list_node {
   public:
    value_type data;
    list_node *prev;
    list_node *next;
    explicit list_node(value_type data_node);
  };
  list_node *head_node;
  list_node *tail_node;
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
  bool operator==(const list<value_type> &list_other) const;

  void clear();
  iterator insert(iterator pos, const_reference value);
  void erase(iterator pos);
  void push_back(const_reference value);
  void pop_back();
  void push_front(const_reference value);
  void pop_front();

  void swap(list &other);
  void merge(list &merge);
  void splice(const_iterator pos, list &other);

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
  explicit list(const size_type count);
  explicit list(std::initializer_list<value_type> const &items);
  list(const list<value_type> &copy);
  list(list<value_type> &&moved);
  list<value_type> &operator=(list<value_type> &&moved);
  ~list();

  friend ListIterator<value_type>;
  friend ListConstIterator<value_type>;
};  // list<T>

template <typename value_type>
class ListConstIterator {
 private:
  typename list<value_type>::list_node *index_ptr;

 public:
  ListConstIterator();
  ListConstIterator(typename list<value_type>::list_node *copy);
  ListConstIterator(const ListConstIterator &copy);
  ListConstIterator(const ListIterator<value_type> &copy);
  ListConstIterator &operator++();
  ListConstIterator &operator--();
  typename list<value_type>::const_reference operator*() const;
  bool operator==(const ListConstIterator &pos);
  bool operator!=(const ListConstIterator &pos);
  ListConstIterator &operator=(ListIterator<value_type> pos);
  typename list<value_type>::list_node *get_iter_ptr() const;
};

template <typename value_type>
class ListIterator {
 private:
  typename list<value_type>::list_node *index_ptr;

 public:
  ListIterator();
  ListIterator(typename list<value_type>::list_node *copy);
  ListIterator(ListConstIterator<value_type> &copy);
  ListIterator(const ListIterator &copy);
  ListIterator &operator++();
  ListIterator &operator--();
  typename list<value_type>::reference operator*();
  bool operator==(const ListIterator &pos);
  bool operator!=(const ListIterator &pos);
  ListIterator &operator=(ListIterator pos);
  typename list<value_type>::list_node *get_iter_ptr() const;
};

template class list<int>;
template class list<double>;
template class ListIterator<int>;
template class ListIterator<double>;
template class ListConstIterator<int>;
template class ListConstIterator<double>;
}  // namespace s21
#endif  //_S21_LIST_H_
