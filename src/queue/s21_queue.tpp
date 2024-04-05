using namespace s21;

template <typename Key>
queue<Key>::queue(std::initializer_list<Key> const& items) {
  for (const auto& item : items) {
    push(item);
  }
}

template <typename Key>
void queue<Key>::push(const_reference value) {
  data.push_back(value);
}

template <typename Key>
void queue<Key>::pop() {
  if (!empty()) {
    data.pop_front();
  }
}

template <typename Key>
typename queue<Key>::const_reference queue<Key>::front() const {
  return data.front();
}

template <typename Key>
typename queue<Key>::const_reference queue<Key>::back() const {
  return data.back();
}

template <typename Key>
bool queue<Key>::empty() const {
  return data.empty();
}

template <typename Key>
typename queue<Key>::size_type queue<Key>::size() const {
  return data.size();
}

template <typename Key>
void queue<Key>::swap(queue& other) {
  data.swap(other.data);
}