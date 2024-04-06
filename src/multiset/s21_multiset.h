#ifndef S21_MULTISET
#define S21_MULTISET

#include "../tree_node/s21_tree.h"

namespace s21 {

template <typename Key>
class multiset : public Tree<Key> {
 public:
  using key_type = Key;
  using value_type = Key;
  using reference = value_type&;
  using const_reference = const value_type&;
  using iterator = typename Tree<Key>::Iterator;
  using const_iterator = typename Tree<Key>::ConstIterator;
  using size_type = size_t;

  using Tree<Key>::Tree;

  explicit multiset(std::initializer_list<Key> const& items);

  iterator insert(const_reference key);

  size_type count(const Key& key);
  iterator lower_bound(const Key& key);
  iterator upper_bound(const Key& key);
  std::pair<iterator, iterator> equal_range(const Key& key);
  const_iterator lower_bound(const Key& key) const;
  const_iterator upper_bound(const Key& key) const;
  std::pair<const_iterator, const_iterator> equal_range(const Key& key) const;

  template <typename... Args>
  std::vector<iterator> insert_many(Args&&... args);
};

}  // namespace s21

#include "s21_multiset.tpp"

#endif
