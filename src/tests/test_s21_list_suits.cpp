#include "test_s21_list.h"

class test_s21_list : public testing::Test {
 public:
};

// тест конструктора по умолчанию, empty(), size(), push_back/pop_back
// тест конструктора move, доступ по индексу()
TEST_F(test_s21_list, test_s21_list_first_1) {
  list<int> list1(1);
  list1(0) = -20;

  ASSERT_EQ(list1.empty(), CONTAINER_NOT_EMPTY);

  list1.push_back(15);
  list1.push_back(19);
  list1.push_back(4);
  list1.push_back(50.7);
  list1.push_back(-4);

  ASSERT_EQ(list1.size(), 6);

  list list2(list1);
  ASSERT_EQ(list2.empty(), CONTAINER_NOT_EMPTY);
  ASSERT_EQ(list2.size(), 6);

  list list3(move(list2));

  ASSERT_EQ(list3.empty(), CONTAINER_NOT_EMPTY);
  ASSERT_EQ(list3.size(), 6);
}

// тест конструктора по умолчанию, empty(), push_back/pop_back
TEST_F(test_s21_list, test_s21_list_first_2) {
  list<int> list2;
  ASSERT_EQ(list2.empty(), CONTAINER_EMPTY);
  list2.push_back(100);
  ASSERT_EQ(list2.size(), 1);
  ASSERT_EQ(list2.empty(), CONTAINER_NOT_EMPTY);

  list2.pop_back();
  ASSERT_EQ(list2.empty(), CONTAINER_EMPTY);
}

// тест push_back/pop_back, доступ по индексу()
TEST_F(test_s21_list, test_s21_list_first_3) {
  list<double> list1;
  list1.push_back(-20.4);
  ASSERT_EQ(list1.size(), 1);

  list<double>::iterator iter;
  iter = list1.begin();

  list1.push_back(1.5);
  list1.push_back(13514.9);
  ASSERT_EQ(list1.size(), 3);
  list1(0) = 20.4;
  ASSERT_DOUBLE_EQ(list1(0), 20.4);
  ASSERT_DOUBLE_EQ(list1(1), 1.5);
  ASSERT_DOUBLE_EQ(list1(2), 13514.9);

  list1.push_back(4);
  list1.push_back(50.7);
  list1.push_back(-4);
  ASSERT_EQ(list1.size(), 6);
  ASSERT_DOUBLE_EQ(list1(5), -4);

  list1.pop_back();
  ASSERT_EQ(list1.size(), 5);
  ASSERT_DOUBLE_EQ(list1(3), 4);
  ASSERT_DOUBLE_EQ(list1(4), 50.7);
}

// тест итераторов, push_back/pop_back
TEST_F(test_s21_list, test_s21_list_first_4) {
  list<int> list2;
  list2.push_back(-111);
  list2.push_back(101);
  list2.push_back(102);
  list2.push_back(103);
  list<int>::iterator iter;
  iter = list2.begin();
  ASSERT_EQ(*iter, -111);

  ++iter;
  ASSERT_EQ(*iter, 101);
  ++iter;
  ASSERT_EQ(*iter, 102);
  ++iter;
  ASSERT_EQ(*iter, 103);
  ++iter;
  ASSERT_EQ(*iter, 0);

  --iter;
  ASSERT_EQ(*iter, 103);
  --iter;
  ASSERT_EQ(*iter, 102);
  --iter;
  ASSERT_EQ(*iter, 101);
  --iter;
  ASSERT_EQ(*iter, -111);

  for (int i = 0; i < 4; i++) list2.pop_back();

  ASSERT_EQ(list2.empty(), CONTAINER_EMPTY);
}

// тест конструктор перемещения и параметризированного конструктора
// конструктор "со списком" и опрератором присваивания
TEST_F(test_s21_list, test_s21_list_first_5) {
  list<int> list2(4);
  ASSERT_EQ(list2.size(), 4);
  list listcpy = move(list2);
  ASSERT_EQ(listcpy.size(), 4);
  ASSERT_EQ(list2.empty(), CONTAINER_EMPTY);

  list<int> list3{1, 4, 2, 5, 7, 13, 56, 11, 5914};
  ASSERT_EQ(list3.size(), 9);
}

// test ... front() and back()
TEST_F(test_s21_list, test_s21_list_first_6) {
  list<int> list2(4);
  ASSERT_EQ(list2.front(), 0);
  ASSERT_EQ(list2.back(), 0);

  list<double> list3{1.1, 4, 2, 5, 7, 13, 56, 11, 5914.09};
  ASSERT_EQ(list3.front(), 1.1);
  ASSERT_EQ(list3.back(), 5914.09);
}
