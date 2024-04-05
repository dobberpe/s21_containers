using namespace s21;

template <typename T>
void qiucksort(list<T> &data, typename list<T>::iterator start,
               typename list<T>::iterator finish);  // qiuck sort

template <typename T>
void list<T>::clear() {
  while (empty() == CONTAINER_NOT_EMPTY) pop_back();
}

template <typename T>
bool list<T>::operator==(list<T> &list_other) {
  int size1 = size();
  int size2 = list_other.size();
  short result = SUCCESS;
  if (size1 == size2) {
    for (int i = 0; i < size1 && result; i++) {
      if ((*this)(i) != list_other(i)) result = FAILURE;
    }
  } else
    result = FAILURE;

  return result;
}

template <typename T>
void list<T>::swap(list &other) {
  if (this != &other) {
    list_node *save_head = other.head_node;
    list_node *save_tail = other.tail_node;
    size_type save_num = number;
    number = other.number;
    other.number = save_num;
    other.head_node = head_node;
    other.tail_node = tail_node;
    head_node = save_head;
    tail_node = save_tail;
  }
}

template <typename T>
void list<T>::merge(list &other) {
  if (this != &other && other.empty() == CONTAINER_NOT_EMPTY &&
      (number + other.number) <= max_size()) {
    number += other.number;
    other.sort();
    this->sort();
    push_front(0);
    list_node *last_node = tail_node->prev;
    last_node->next = other.head_node;
    other.head_node->prev = last_node;

    tail_node->prev = other.tail_node->prev;
    tail_node->prev->next = tail_node;

    other.head_node = other.tail_node;
    other.tail_node->prev = other.head_node;
    other.number = 0;
    pop_front();
  }
}

// transfers elements from list other starting from pos
template <typename T>
void list<T>::splice(const iterator pos, list &other) {
  if (this != &other && other.empty() == CONTAINER_NOT_EMPTY) {
    // &&    (pos + 1 + other.number) <= max_size()) {
    // number = pos + 1;
    push_front(0);

    while (other.empty() == CONTAINER_NOT_EMPTY) {
      iterator pos_other = other.begin();
      insert(pos, *pos_other);
      other.pop_front();
    }
    pop_front();
  }
}

template <typename T>
void list<T>::reverse() {
  if (empty() == CONTAINER_NOT_EMPTY) {
    iterator pos = begin();
    iterator pos_1 = pos;
    list_node *node = pos.get_iter_ptr();
    list_node *node_1 = pos_1.get_iter_ptr();
    while (pos != end()) {
      ++pos;

      list_node *node_save = node->next;
      node->next = node->prev;
      node->prev = node_save;

      node = pos.get_iter_ptr();
    }
    head_node = tail_node->prev;
    head_node->prev = head_node;
    tail_node->prev = node_1;
    node_1->next = tail_node;
  }
}

template <typename T>
void list<T>::unique() {
  if (empty() == CONTAINER_NOT_EMPTY) {
    iterator iter = begin();
    T elem = *iter;
    ++iter;

    while (iter != end()) {
      if (elem == *iter) {
        iterator iter_del = iter;
        ++iter;
        erase(iter_del);
      } else {
        elem = *iter;
        ++iter;
      }
    }
  }
}

template <typename T>
void list<T>::sort() {
  if (size() > 1) {
    iterator iter = end();
    qiucksort(*this, begin(), --iter);
  }
}

template <typename T>
void qiucksort(list<T> &data, typename list<T>::iterator start,
               typename list<T>::iterator finish) {  // qiuck sort
  typename list<T>::iterator base_pos = finish;
  typename list<T>::iterator curr_pos = start;
  while (curr_pos != base_pos) {
    if (*curr_pos >= *base_pos) {
      typename list<T>::iterator shift = base_pos;
      --shift;
      T save = *shift;
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
  typename list<T>::iterator save = base_pos;
  if (base_pos != start && --base_pos != start)
    qiucksort(data, start, base_pos);

  if (save != finish && ++save != finish) qiucksort(data, save, finish);
}
