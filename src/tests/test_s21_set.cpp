#include "test_s21_containers.h"

using namespace s21;

// Тест для конструктора по умолчанию
TEST(SetConstructorTest, DefaultConstructor) {
  set<int> s;
  EXPECT_EQ(0, s.size());
  EXPECT_TRUE(s.empty());
}

// Тест для конструктора с инициализационным списком
TEST(SetConstructorTest, InitializerListConstructor) {
  set<int> s{1, 2, 3};
  EXPECT_EQ(3, s.size());
  EXPECT_FALSE(s.empty());
  // Проверьте, что все элементы из списка были вставлены в множество
  EXPECT_TRUE(s.contains(1));
  EXPECT_TRUE(s.contains(2));
  EXPECT_TRUE(s.contains(3));
}

// Тест для конструктора копирования
TEST(SetConstructorTest, CopyConstructor) {
  set<int> s1{1, 2, 3};
  set<int> s2 = s1;  // Копируем s1 в s2
  EXPECT_EQ(s1.size(), s2.size());
  // Проверяем, что s2 содержит те же элементы, что и s1
  Tree<int>::Iterator i1 = s1.begin(), i2 = s2.begin();
  for (int i = 0; i < 2; i++) {
    ++i1;
    ++i2;
    EXPECT_EQ(i1.current->key, i2.current->key);
  }
}

// Тест для конструктора перемещения
TEST(SetConstructorTest, MoveConstructor) {
  set<int> s1{1, 2, 3};
  set<int> s2 = std::move(s1);  // Перемещаем s1 в s2
  EXPECT_EQ(0, s1.size());  // Проверяем, что s1 теперь пустой
  // Проверяем, что s2 содержит те же элементы, что и s1 перед перемещением
  EXPECT_TRUE(s2.contains(1));
  EXPECT_TRUE(s2.contains(2));
  EXPECT_TRUE(s2.contains(3));
}

TEST(SetMoveAssignmentTest, BasicTest) {
  // Создаем первое множество и добавляем в него элементы
  set<int> s1;
  s1.insert(1);
  s1.insert(2);
  s1.insert(3);

  // Создаем второе множество и перемещаем в него содержимое первого
  set<int> s2;
  s2 = std::move(s1);

  // Проверяем, что первое множество теперь пусто
  EXPECT_EQ(0, s1.size());

  // Проверяем, что второе множество содержит все элементы из первого
  EXPECT_EQ(3, s2.size());
  EXPECT_TRUE(s2.contains(1));
  EXPECT_TRUE(s2.contains(2));
  EXPECT_TRUE(s2.contains(3));
}

TEST(SetMoveAssignmentTest, SelfAssignment) {
  set<int> s;
  s.insert(1);
  s.insert(2);

  // Присваивание самому себе не должно приводить к изменениям
  s = std::move(s);

  EXPECT_EQ(2, s.size());
  EXPECT_TRUE(s.contains(1));
  EXPECT_TRUE(s.contains(2));
}

TEST(SetInsertTest, BasicTest) {
  set<int> s;

  // Вставляем элементы в множество
  auto result1 = s.insert(1);
  auto result2 = s.insert(2);
  auto result3 = s.insert(3);

  // Проверяем, что вставка прошла успешно и множество содержит правильные
  // элементы
  EXPECT_EQ(3, s.size());
  EXPECT_TRUE(result1.second);
  EXPECT_TRUE(result2.second);
  EXPECT_TRUE(result3.second);
  EXPECT_TRUE(s.contains(1));
  EXPECT_TRUE(s.contains(2));
  EXPECT_TRUE(s.contains(3));
}

TEST(SetInsertTest, DuplicateTest) {
  set<int> s;

  // Вставляем один и тот же элемент дважды
  s.insert(1);
  auto result = s.insert(1);

  // Проверяем, что вторая вставка не произошла
  EXPECT_EQ(1, s.size());
  EXPECT_FALSE(result.second);
  EXPECT_TRUE(s.contains(1));
}

TEST(SetCapacityTest, SizeTest) {
  set<int> s;

  // Тестирование размера после вставки элементов
  s.insert(1);
  s.insert(2);
  s.insert(3);

  EXPECT_EQ(3, s.size());
}

TEST(SetCapacityTest, EmptyTest) {
  set<int> s;

  // Проверка пустого множества
  EXPECT_TRUE(s.empty());

  // Вставка элемента и проверка, что множество больше не пустое
  s.insert(1);
  EXPECT_FALSE(s.empty());
}

TEST(SetCapacityTest, MaxSizeTest) {
  set<int> s;

  // Проверка максимального размера множества
  EXPECT_EQ(230584300921369395, s.max_size());
}

TEST(SetModifiersTest, ClearTest) {
  set<int> s;

  // Вставка элементов и очистка множества
  s.insert(1);
  s.insert(2);
  s.clear();

  // Проверка, что множество пустое после очистки
  EXPECT_TRUE(s.empty());
  EXPECT_EQ(0, s.size());
}

TEST(SetIteratorTest, BeginEndTest) {
  set<int> s;
  s.insert(1);
  s.insert(2);
  s.insert(3);

  // Получение итераторов на начало и конец множества
  set<int>::iterator begin_iter = s.begin();

  // Проверка значения первого элемента
  EXPECT_EQ(1, *begin_iter);
}

TEST(SetConstIteratorTest, ConstBeginEndTest) {
  const set<int> s{1, 2, 3};

  // Получение константных итераторов на начало и конец множества
  set<int>::const_iterator begin_iter = s.begin();

  // Проверка значения первого элемента
  EXPECT_EQ(1, *begin_iter);
}

TEST(SetFindTest, FindExistingElement) {
  set<int> s{1, 2, 3};

  // Поиск существующего элемента
  auto it = s.find(2);

  // Проверка, что элемент найден и итератор указывает на него
  EXPECT_EQ(2, *it);
}

TEST(SetContainsTest, ContainsExistingElement) {
  set<int> s{1, 2, 3};

  // Проверка наличия существующего элемента
  EXPECT_TRUE(s.contains(2));
}

TEST(SetContainsTest, ContainsNonExistingElement) {
  set<int> s{1, 2, 3};

  // Проверка отсутствия несуществующего элемента
  EXPECT_FALSE(s.contains(4));
}

TEST(SetTest, Erase) {
  set<int> s{1, 2, 3, 4, 5};

  // Erase element 3
  auto it = s.find(3);
  ASSERT_NE(it, s.end());
  s.erase(it);

  EXPECT_EQ(s.size(), 4);
  EXPECT_FALSE(s.contains(3));
}

// Test case for swap function
TEST(SetTest, Swap) {
  set<int> s1{1, 2, 3};
  set<int> s2{4, 5, 6};

  s1.swap(s2);

  EXPECT_EQ(s1.size(), 3);
  EXPECT_EQ(s2.size(), 3);

  EXPECT_TRUE(s1.contains(4));
  EXPECT_TRUE(s2.contains(1));
}

// Test case for merge function
TEST(SetTest, Merge) {
  set<int> s1{1, 2, 3};
  set<int> s2{4, 5, 6};

  s1.merge(s2);

  EXPECT_EQ(s1.size(), 6);
  EXPECT_TRUE(s2.empty());

  EXPECT_TRUE(s1.contains(4));
  EXPECT_TRUE(s1.contains(6));
}

TEST(SetTest, InsertMany) {
  // Создание пустого множества
  set<int> my_set;

  // Вставка элементов и проверка результата
  auto results = my_set.insert_many(1, 2, 3);
  ASSERT_EQ(results.size(), 3);
  EXPECT_EQ(results[0].second,
            true);  // Должно быть true, так как элемент вставлен успешно
  EXPECT_EQ(results[1].second, true);
  EXPECT_EQ(results[2].second, true);

  // Попытка вставить элементы, которые уже присутствуют в множестве
  results = my_set.insert_many(2, 3, 4);
  ASSERT_EQ(results.size(), 3);
  EXPECT_EQ(
      results[0].second,
      false);  // Должно быть false, так как элемент уже существует в множестве
  EXPECT_EQ(results[1].second, false);
  EXPECT_EQ(results[2].second,
            true);  // Должно быть true, так как элемент успешно вставлен

  // Проверка содержимого множества
  std::vector<int> expected_values = {1, 2, 3, 4};
  int i = 0;
  for (auto it = my_set.begin(); it != my_set.end(); ++it) {
    EXPECT_EQ(*it, expected_values[i]);
    ++i;
  }
}

TEST(SetIteratorTest, DecrementOperator) {
  // Создаем пустое множество
  set<int> mySet;

  // Вставляем элементы в множество
  mySet.insert(10);
  mySet.insert(5);
  mySet.insert(15);
  mySet.insert(3);
  mySet.insert(7);

  // Создаем итераторы для множества
  Tree<int>::Iterator it = mySet.begin();
  Tree<int>::Iterator last = mySet.end();

  // Тестируем метод operator--
  --last;
  ASSERT_EQ(*last, 15);

  --last;
  ASSERT_EQ(*last, 10);

  --last;
  ASSERT_EQ(*last, 7);

  --last;
  ASSERT_EQ(*last, 5);

  --last;
  ASSERT_EQ(*last, 3);

  ASSERT_EQ(*last, *it);  // Должно быть равно начальному итератору
}

TEST(IteratorComparisonTest, OperatorEqual) {
  // Создаем множество и вставляем в него несколько элементов
  set<int> mySet;
  mySet.insert(10);
  mySet.insert(20);

  // Создаем два итератора, указывающих на одинаковый элемент в множестве
  Tree<int>::Iterator it1 = mySet.begin();
  Tree<int>::Iterator it2 = mySet.begin();

  // Проверяем, что они равны
  ASSERT_TRUE(it1 == it2);

  // Создаем два итератора, указывающих на разные элементы в множестве
  Tree<int>::Iterator it3 = mySet.begin();
  Tree<int>::Iterator it4 = mySet.begin();
  ++it4;

  // Проверяем, что они не равны
  ASSERT_FALSE(it3 == it4);
}

TEST(TreeTest, Erase) {
  set<int> tree;
  tree.insert(5);
  tree.insert(3);
  tree.insert(8);
  tree.insert(2);
  tree.insert(4);
  tree.insert(7);
  tree.insert(9);

  // Удаляем узел со значением 5
  auto it = tree.find(5);
  tree.erase(it);

  // Проверяем, что значение 5 больше нет в дереве
  EXPECT_FALSE(tree.contains(5));

  // Проверяем размер дерева после удаления
  EXPECT_EQ(tree.size(), 6);

  // Проверяем, что другие значения остаются в дереве
  EXPECT_TRUE(tree.contains(3));
  EXPECT_TRUE(tree.contains(8));
  EXPECT_TRUE(tree.contains(2));
  EXPECT_TRUE(tree.contains(4));
  EXPECT_TRUE(tree.contains(7));
  EXPECT_TRUE(tree.contains(9));
}