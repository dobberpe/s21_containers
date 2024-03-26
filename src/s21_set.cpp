#include "s21_set.h"

// namespace s21 {
using namespace s21;

template <typename Key>
void Set<Key>::transplant(Node *u, Node *v) {
  if (u->parent == nullptr)
    root = v;
  else if (u == u->parent->left)
    u->parent->left = v;
  else
    u->parent->right = v;
  if (v != nullptr) v->parent = u->parent;
}

template <typename Key>
typename Set<Key>::Node *Set<Key>::min_node(Node *node) {
  while (node->left != nullptr) node = node->left;
  return node;
}

template <typename Key>
void Set<Key>::destroy(Node *node) {
  if (node != nullptr) {
    destroy(node->left);
    destroy(node->right);
    delete node;
  }
}

template <typename Key>
typename Set<Key>::Node *Set<Key>::copy_nodes(Node *other, Node *parent) {
  if (other == nullptr) return nullptr;
  Node *new_node = new Node(other->key);
  new_node->parent = parent;
  new_node->left = copy_nodes(other->left, new_node);
  new_node->right = copy_nodes(other->right, new_node);
  return new_node;
}

template <typename Key>
typename Set<Key>::Node *Set<Key>::find_node(const_reference key) const {
  Node *current = root;
  while (current != nullptr) {
    if (key == current->key)
      return current;
    else if (key < current->key)
      current = current->left;
    else
      current = current->right;
  }
  return nullptr;
}

template <typename Key>
Set<Key>::Set() : root(nullptr), num_elements(0) {}

template <typename Key>
Set<Key>::Set(std::initializer_list<Key> const &items)
    : root(nullptr), num_elements(0) {
  for (const auto &item : items) insert(item);
}

template <typename Key>
Set<Key>::Set(const Set &s) : root(nullptr), num_elements(0) {
  root = copy_nodes(s.root, nullptr);
  num_elements = s.num_elements;
}

template <typename Key>
Set<Key>::Set(Set &&s) noexcept : root(s.root), num_elements(s.num_elements) {
  s.root = nullptr;
  s.num_elements = 0;
}

template <typename Key>
Set<Key>::~Set() {
  clear();
}

template <typename Key>
typename Set<Key>::Set &Set<Key>::operator=(Set &&s) noexcept {
  if (this != &s) {
    clear();
    root = s.root;
    num_elements = s.num_elements;
    s.root = nullptr;
    s.num_elements = 0;
  }
  return *this;
}

template <typename Key>
std::pair<typename Set<Key>::iterator, bool> Set<Key>::insert(
    const_reference key) {
  Node *new_node = new Node(key);
  Node *parent = nullptr;
  Node *current = root;

  while (current != nullptr) {
    parent = current;
    if (key < current->key)
      current = current->left;
    else if (key > current->key)
      current = current->right;
    else {
      delete new_node;
      return std::make_pair(iterator(current), false);
    }
  }
  new_node->parent = parent;
  if (parent == nullptr)
    root = new_node;
  else if (key < parent->key)
    parent->left = new_node;
  else
    parent->right = new_node;

  ++num_elements;
  return std::make_pair(iterator(new_node), true);
}

template <typename Key>
size_t Set<Key>::size() const {
  return num_elements;
}

template <typename Key>
bool Set<Key>::empty() const {
  return num_elements == 0;
}

template <typename Key>
typename Set<Key>::size_type Set<Key>::max_size() const {
  size_type res = 230584300921369395;
  return res;
}

template <typename Key>
void Set<Key>::clear() {
  destroy(root);
  root = nullptr;
  num_elements = 0;
}

template <typename Key>
typename Set<Key>::iterator Set<Key>::begin() {
  Node *current = root;
  while (current != nullptr && current->left != nullptr)
    current = current->left;
  return iterator(current);
}

template <typename Key>
typename Set<Key>::iterator Set<Key>::end() {
  return iterator(nullptr);
}

template <typename Key>
typename Set<Key>::const_iterator Set<Key>::begin() const {
  Node *current = root;
  while (current != nullptr && current->left != nullptr)
    current = current->left;
  return const_iterator(current);
}

template <typename Key>
typename Set<Key>::const_iterator Set<Key>::end() const {
  return const_iterator(nullptr);
}

template <typename Key>
typename Set<Key>::iterator Set<Key>::find(const Key &key) {
  Node *node = find_node(key);
  return iterator(node);
}

template <typename Key>
bool Set<Key>::contains(const Key &key) const {
  return find_node(key) != nullptr;
}

template <typename Key>
SetIterator<Key>::SetIterator(typename Set<Key>::Node *node) : current(node) {}

template <typename Key>
typename SetIterator<Key>::SetIterator &SetIterator<Key>::operator++() {
  if (current == nullptr)
    throw std::out_of_range("Iterator cannot be incremented beyond the end");
  current = successor(current);
  return *this;
}

template <typename Key>
Key &SetIterator<Key>::operator*() const {
  return current->key;
}

template <typename Key>
bool SetIterator<Key>::operator!=(const SetIterator &other) const {
  return current != other.current;
}

template <typename Key>
typename Set<Key>::Node *SetIterator<Key>::successor(
    typename Set<Key>::Node *x) {
  if (x->right != nullptr) {
    x = x->right;
    while (x->left != nullptr) x = x->left;
    return x;
  }
  typename Set<Key>::Node *y = x->parent;
  while (y != nullptr && x == y->right) {
    x = y;
    y = y->parent;
  }
  return y;
}

template <typename Key>
SetConstIterator<Key>::SetConstIterator(typename Set<Key>::Node *node)
    : current(node) {}

template <typename Key>
typename SetConstIterator<Key>::SetConstIterator &
SetConstIterator<Key>::operator++() {
  if (current == nullptr)
    throw std::out_of_range("Iterator cannot be incremented beyond the end");
  current = successor(current);
  return *this;
}

template <typename Key>
const Key &SetConstIterator<Key>::operator*() const {
  return current->key;
}

template <typename Key>
bool SetConstIterator<Key>::operator!=(const SetConstIterator &other) const {
  return current != other.current;
}

template <typename Key>
typename Set<Key>::Node *SetConstIterator<Key>::successor(
    typename Set<Key>::Node *x) {
  if (x->right != nullptr) {
    x = x->right;
    while (x->left != nullptr) x = x->left;
    return x;
  }
  typename Set<Key>::Node *y = x->parent;
  while (y != nullptr && x == y->right) {
    x = y;
    y = y->parent;
  }
  return y;
}








// #include <gtest/gtest.h>

// // Тест для конструктора по умолчанию
// TEST(SetConstructorTest, DefaultConstructor) {
//     Set<int> s;
//     EXPECT_EQ(0, s.size());
//     EXPECT_TRUE(s.empty());
// }

// // Тест для конструктора с инициализационным списком
// TEST(SetConstructorTest, InitializerListConstructor) {
//     Set<int> s = {1, 2, 3};
//     EXPECT_EQ(3, s.size());
//     EXPECT_FALSE(s.empty());
//     // Проверьте, что все элементы из списка были вставлены в множество
//     EXPECT_TRUE(s.contains(1));
//     EXPECT_TRUE(s.contains(2));
//     EXPECT_TRUE(s.contains(3));
// }

// // Тест для конструктора копирования
// TEST(SetConstructorTest, CopyConstructor) {
//     Set<int> s1 = {1, 2, 3};
//     Set<int> s2 = s1; // Копируем s1 в s2
//     EXPECT_EQ(s1.size(), s2.size());
//     // Проверяем, что s2 содержит те же элементы, что и s1
//     SetIterator<int> i1 = s1.begin(), i2 = s2.begin();
//     for (int i = 0; i < 2; i++)
//     {
//         ++i1;
//         ++i2;
//         EXPECT_EQ(i1.current->key, i2.current->key);
//     }
// }

// // Тест для конструктора перемещения
// TEST(SetConstructorTest, MoveConstructor) {
//     Set<int> s1 = {1, 2, 3};
//     Set<int> s2 = std::move(s1); // Перемещаем s1 в s2
//     EXPECT_EQ(0, s1.size()); // Проверяем, что s1 теперь пустой
//     // Проверяем, что s2 содержит те же элементы, что и s1 перед перемещением
//     EXPECT_TRUE(s2.contains(1));
//     EXPECT_TRUE(s2.contains(2));
//     EXPECT_TRUE(s2.contains(3));
// }


// TEST(SetMoveAssignmentTest, BasicTest) {
//     // Создаем первое множество и добавляем в него элементы
//     Set<int> s1;
//     s1.insert(1);
//     s1.insert(2);
//     s1.insert(3);

//     // Создаем второе множество и перемещаем в него содержимое первого
//     Set<int> s2;
//     s2 = std::move(s1);

//     // Проверяем, что первое множество теперь пусто
//     EXPECT_EQ(0, s1.size());

//     // Проверяем, что второе множество содержит все элементы из первого
//     EXPECT_EQ(3, s2.size());
//     EXPECT_TRUE(s2.contains(1));
//     EXPECT_TRUE(s2.contains(2));
//     EXPECT_TRUE(s2.contains(3));
// }

// TEST(SetMoveAssignmentTest, SelfAssignment) {
//     Set<int> s;
//     s.insert(1);
//     s.insert(2);

//     // Присваивание самому себе не должно приводить к изменениям
//     s = std::move(s);

//     EXPECT_EQ(2, s.size());
//     EXPECT_TRUE(s.contains(1));
//     EXPECT_TRUE(s.contains(2));
// }

// TEST(SetInsertTest, BasicTest) {
//     Set<int> s;
    
//     // Вставляем элементы в множество
//     auto result1 = s.insert(1);
//     auto result2 = s.insert(2);
//     auto result3 = s.insert(3);
    
//     // Проверяем, что вставка прошла успешно и множество содержит правильные элементы
//     EXPECT_EQ(3, s.size());
//     EXPECT_TRUE(result1.second);
//     EXPECT_TRUE(result2.second);
//     EXPECT_TRUE(result3.second);
//     EXPECT_TRUE(s.contains(1));
//     EXPECT_TRUE(s.contains(2));
//     EXPECT_TRUE(s.contains(3));
// }

// TEST(SetInsertTest, DuplicateTest) {
//     Set<int> s;
    
//     // Вставляем один и тот же элемент дважды
//     s.insert(1);
//     auto result = s.insert(1);
    
//     // Проверяем, что вторая вставка не произошла
//     EXPECT_EQ(1, s.size());
//     EXPECT_FALSE(result.second);
//     EXPECT_TRUE(s.contains(1));
// }


// TEST(SetCapacityTest, SizeTest) {
//     Set<int> s;
    
//     // Тестирование размера после вставки элементов
//     s.insert(1);
//     s.insert(2);
//     s.insert(3);
    
//     EXPECT_EQ(3, s.size());
// }

// TEST(SetCapacityTest, EmptyTest) {
//     Set<int> s;
    
//     // Проверка пустого множества
//     EXPECT_TRUE(s.empty());
    
//     // Вставка элемента и проверка, что множество больше не пустое
//     s.insert(1);
//     EXPECT_FALSE(s.empty());
// }

// TEST(SetCapacityTest, MaxSizeTest) {
//     Set<int> s;
    
//     // Проверка максимального размера множества
//     EXPECT_EQ(230584300921369395, s.max_size());
// }

// TEST(SetModifiersTest, ClearTest) {
//     Set<int> s;
    
//     // Вставка элементов и очистка множества
//     s.insert(1);
//     s.insert(2);
//     s.clear();
    
//     // Проверка, что множество пустое после очистки
//     EXPECT_TRUE(s.empty());
//     EXPECT_EQ(0, s.size());
// }

// TEST(SetIteratorTest, BeginEndTest) {
//     Set<int> s;
//     s.insert(1);
//     s.insert(2);
//     s.insert(3);
    
//     // Получение итераторов на начало и конец множества
//     Set<int>::iterator begin_iter = s.begin();
    
//     // Проверка значения первого элемента
//     EXPECT_EQ(1, *begin_iter);
// }

// TEST(SetConstIteratorTest, ConstBeginEndTest) {
//     const Set<int> s = {1, 2, 3};
    
//     // Получение константных итераторов на начало и конец множества
//     Set<int>::const_iterator begin_iter = s.begin();
    
//     // Проверка значения первого элемента
//     EXPECT_EQ(1, *begin_iter);
// }

// TEST(SetFindTest, FindExistingElement) {
//     Set<int> s = {1, 2, 3};

//     // Поиск существующего элемента
//     auto it = s.find(2);

//     // Проверка, что элемент найден и итератор указывает на него
//     EXPECT_EQ(2, *it);
// }

// TEST(SetContainsTest, ContainsExistingElement) {
//     Set<int> s = {1, 2, 3};

//     // Проверка наличия существующего элемента
//     EXPECT_TRUE(s.contains(2));
// }

// TEST(SetContainsTest, ContainsNonExistingElement) {
//     Set<int> s = {1, 2, 3};

//     // Проверка отсутствия несуществующего элемента
//     EXPECT_FALSE(s.contains(4));
// }

// int main(int argc, char **argv) {
//     ::testing::InitGoogleTest(&argc, argv);
//     return RUN_ALL_TESTS();
// }
