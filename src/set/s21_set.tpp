namespace s21 {

template <typename Key>
template <typename... Args>
vector<std::pair<typename set<Key>::iterator, bool>> set<Key>::insert_many(
    Args &&...args) {
  vector<std::pair<typename set<Key>::iterator, bool>> results;
  ((void)results.push_back(Tree<Key>::insert(std::forward<Args>(args))), ...);
  return results;
}
}  // namespace s21