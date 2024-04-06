#include "s21_set.h"

namespace s21 {

template <typename Key>
template <typename... Args>
std::vector<std::pair<typename set<Key>::iterator, bool>> set<Key>::insert_many(
    Args &&...args) {
  std::vector<std::pair<typename Tree<Key>::iterator, bool>> results;
  ((void)results.emplace_back(this->insert(std::forward<Args>(args))), ...);
  return results;
}
}  // namespace s21