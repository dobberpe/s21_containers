using namespace s21;

template <typename Key>
stack<Key>::stack(std::initializer_list<Key> const& items) {
  for (const auto& item : items) {
    push(item);
  }
}

template <typename Key>
void stack<Key>::push(const_reference value) {
  data.push_back(value);
}

template <typename Key>
void stack<Key>::pop() {
  if (!empty()) {
    data.pop_back();
  }
}

template <typename Key>
typename stack<Key>::const_reference stack<Key>::top() const {
  return data.back();
}

template <typename Key>
bool stack<Key>::empty() const {
  return data.empty();
}

template <typename Key>
typename stack<Key>::size_type stack<Key>::size() const {
  return data.size();
}

template <typename Key>
void stack<Key>::swap(stack& other) {
  data.swap(other.data);
}

template <typename Key>
template <typename... Args>
void stack<Key>::insert_many_front(Args&&... args) {
  (data.push_back(std::forward<Args>(args)), ...);
}