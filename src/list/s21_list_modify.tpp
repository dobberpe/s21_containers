#include "s21_list.h"
using namespace s21;

template <typename value_type>
void qiucksort(list<value_type> &data,
               typename list<value_type>::iterator start,
               typename list<value_type>::iterator finish);  // qiuck sort

template <typename value_type>
void list<value_type>::clear() {
  while (empty() == CONTAINER_NOT_EMPTY) pop_back();
}

template <typename value_type>
bool list<value_type>::operator==(const list<value_type> &list_other) const {
  size_type size1 = size();
  size_type size2 = list_other.size();
  short result = SUCCESS;
  if (size1 == size2) {
    for (size_type i = 0; (i < size1) && result; ++i) {
      if (operator()(i) != list_other(i)) result = FAILURE;
    }
  } else
    result = FAILURE;

  return result;
}

template <typename value_type>
void list<value_type>::swap(list &other) {
  if (this != &other) {
    list_node *save_head = other.head_node;
    list_node *save_tail = other.tail_node;
    size_type save_num = other.number;
    other.number = number;
    other.head_node = head_node;
    other.tail_node = tail_node;
    number = save_num;
    head_node = save_head;
    tail_node = save_tail;
  }
}

template <typename value_type>
void list<value_type>::merge(list &merge) {
  if (this != &merge && merge.empty() == CONTAINER_NOT_EMPTY &&
      (number + merge.number) <= max_size()) {
    push_front(0);
    iterator iter_this = begin();
    iterator iter_merge = merge.begin();
    while (merge.empty() == CONTAINER_NOT_EMPTY) {
      if (*iter_merge < *iter_this || iter_this == end()) {
        insert(iter_this, *iter_merge);
        merge.pop_front();
        iter_merge = merge.begin();
      } else {
        ++iter_this;
      }
    }
    pop_front();
  }
}

template <typename value_type>
void list<value_type>::splice(const_iterator pos, list &other) {
  if (this != &other && other.empty() == CONTAINER_NOT_EMPTY) {
    push_front(0);

    while (other.empty() == CONTAINER_NOT_EMPTY) {
      insert(pos, *other.begin());
      other.pop_front();
    }
    pop_front();
  }
}

template <typename value_type>
void list<value_type>::reverse() {
  if (size() > 1) {
    size_type back_list = size() - 1;
    size_type half = size() / 2;
    for (size_type i = 0; i < half; ++i) {
      value_type save = operator()(i);
      operator()(i) = operator()(back_list);
      operator()(back_list--) = save;
    }
  }
}

template <typename value_type>
void list<value_type>::unique() {
  if (size() > 1) {
    iterator iter_prev = begin();
    iterator iter = iter_prev;
    ++iter;

    while (iter != end()) {
      if (*iter_prev == *iter) erase(iter_prev);
      iter_prev = iter;
      ++iter;
    }
  }
}

template <typename value_type>
void list<value_type>::sort() {
  if (size() > 1) qiucksort(*this, begin(), --end());
}

template <typename value_type>  // qiuck sort
void qiucksort(list<value_type> &data,
               typename list<value_type>::iterator start,
               typename list<value_type>::iterator finish) {
  typename list<value_type>::iterator base_pos = finish;
  typename list<value_type>::iterator curr_pos = start;
  while (curr_pos != base_pos) {
    if (*curr_pos >= *base_pos) {
      typename list<value_type>::iterator shift = base_pos;
      --shift;
      value_type save = *shift;
      *shift = *base_pos;
      if (curr_pos != shift) {
        *base_pos = *curr_pos;
        *curr_pos = save;
      } else
        *base_pos = save;
      --base_pos;
    } else {
      ++curr_pos;
    }
  }
  typename list<value_type>::iterator save = base_pos;
  if (base_pos != start && --base_pos != start)
    qiucksort(data, start, base_pos);

  if (save != finish && ++save != finish) qiucksort(data, save, finish);
}
