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
class list {
 public:
  // typedef value_type = T;
  // typedef reference = T &;
  // typedef const_reference = const & T;
  using size_type = size_t;

 private:
  class list_node {
   public:
    T data;
    list_node *prev;
    list_node *next;
    explicit list_node(const T data_node);
  };

  list_node *head_node;
  list_node *tail_node;
  size_type number;

 public:
  class ListIterator {
   private:
    list_node *index_ptr;

   public:
    ListIterator();
    T &operator*();
    ListIterator &operator++();
    ListIterator &operator--();
    bool operator==(const ListIterator &pos);
    bool operator!=(const ListIterator &pos);

    ListIterator &operator=(list_node *node);
    list_node *get_iter_ptr();
  };

  class ListConstIterator {
   private:
    list_node *index_ptr;

   public:
    ListConstIterator();
    explicit ListConstIterator(list_node *node);
    const T &operator*() const;
    ListConstIterator &operator++();
    ListConstIterator &operator--();
    bool operator==(const ListConstIterator &pos);
    bool operator!=(const ListConstIterator &pos);

    ListConstIterator &operator=(list_node *node);
    list_node *get_iter_ptr();
  };

  using iterator = ListIterator;
  using const_iterator = ListConstIterator;

 private:
  iterator iter_head;
  iterator iter_tail;

 public:
  T &front();
  const T &front() const;
  T &back();
  const T &back() const;
  iterator &begin();
  iterator &end();
  const_iterator begin() const;
  const_iterator end() const;
  bool empty() const;
  size_type size() const;
  size_type max_size() const;
  T &operator()(const size_type i);
  bool operator==(list<T> &list_other);

  void clear();
  iterator insert(iterator pos, const T &value);
  void erase(iterator pos);
  void push_back(const T &value);
  void pop_back();
  void push_front(const T &value);
  void pop_front();

  void swap(list &other);
  void merge(list &other);
  void splice(const iterator pos, list &other);

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
  explicit list(std::initializer_list<T> const &items);
  list(list<T> &copy);
  list(list<T> &&moved);
  ~list();
  list<T> &operator=(list<T> &&moved);
};

template class list<int>;
template class list<double>;
// template class list<long double>;
// template class list<short>;
// template class list<char>;
// template class list<unsigned char>;
// template class list<unsigned short>;
// template class list<unsigned int>;
}  // namespace s21
#endif  //_S21_LIST_H_
