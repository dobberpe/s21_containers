#ifndef S21_SET
#define S21_SET

#include "../tree_node/s21_tree.h"

namespace s21 {

template <typename Key>
class set : public Tree<Key> {
 public:
  using key_type = Key;
  using value_type = Key;
  using reference = value_type &;
  using const_reference = const value_type &;
  using iterator = typename Tree<Key>::Iterator;
  using const_iterator = typename Tree<Key>::ConstIterator;
  using size_type = size_t;

  using Tree<Key>::Tree;

  template <typename... Args>
  vector<std::pair<iterator, bool>> insert_many(Args &&...args);
};

}  // namespace s21

#include "s21_set.tpp"

#endif
