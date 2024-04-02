#include "s21_vector.h"

using namespace s21;

template <typename value_type>
vector<value_type>::vector() : max_number(0), number(0), head_node(nullptr) {}

template <typename value_type>
vector<value_type>::vector(const size_type n) {
  head_node = nullptr;
  max_number = number = 0;
  if (n > 0 && n < this->max_size()) reserve(n);
}

template <typename value_type>
vector<value_type>::vector(std::initializer_list<value_type> const &items) {
  max_number = number = 0;
  head_node = nullptr;
  for (auto digit : items) vector<value_type>::push_back(digit);
}

template <typename value_type>
vector<value_type>::vector(const vector<value_type> &v) : List<value_type>(v) {
  max_number = v.max_number;
  number = 0;
  head_node = nullptr;

  reserve(max_number);
  for (size_type i = 0; i < v.number; i++) vector<value_type>::push_back(v[i]);
}

template <typename value_type>
vector<value_type>::vector(vector<value_type> &&v) {
  max_number = v.max_number;
  number = v.number;
  head_node = v.head_node;

  v.head_node = nullptr;
  v.number = v.max_number = 0;
}

template <typename value_type>
vector<value_type>::~vector() {
  clear();
  if (head_node) free(head_node);
  head_node = nullptr;
  number = max_number = 0;
}

template <typename value_type>
vector<value_type> &vector<value_type>::operator=(vector &&v) {
  if (&v != this) {
    clear();
    if (head_node) free(head_node);

    max_number = v.max_number;
    number = v.number;
    head_node = v.head_node;

    v.head_node = nullptr;
    v.number = v.max_number = 0;
  }
  return *this;
}

template <typename value_type>
bool vector<value_type>::operator==(const vector<value_type> &vect) const {
  size_type size1 = size();
  size_type size2 = vect.size();
  short result = SUCCESS;
  if (size1 == size2) {
    for (size_type i = 0; i < size1 && result; i++) {
      if (operator[](i) != vect[i]) result = FAILURE;
    }
  } else
    result = FAILURE;

  return result;
}