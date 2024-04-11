#include "test_s21_containers.h"

#ifndef _SPCE_
#include <list>
#define _SPCE_ std
#define _SPCE_ORIG_
#endif

class test_s21_list : public testing::Test {
 public:
};

TEST_F(test_s21_list, test_s21_list_create) {
  _SPCE_::list<int> list1;
  EXPECT_EQ(list1.empty(), CONTAINER_EMPTY);

  _SPCE_::list list11(std::move(list1));
  EXPECT_EQ(list11.empty(), CONTAINER_EMPTY);
  EXPECT_EQ(list1.empty(), CONTAINER_EMPTY);

  _SPCE_::list<int> list2(1);
  EXPECT_EQ(list2.empty(), CONTAINER_NOT_EMPTY);
  list2.push_back(15);
  list2.push_back(19);
  list2.push_back(4);
  list2.push_back(50);
  list2.push_back(-4);
  EXPECT_EQ(list2.empty(), CONTAINER_NOT_EMPTY);
  EXPECT_EQ(list2.size(), 6);

  _SPCE_::list list3(list2);
  EXPECT_EQ(list3.empty(), CONTAINER_NOT_EMPTY);
  EXPECT_EQ(list3.size(), 6);

  _SPCE_::list list4(std::move(list3));
  EXPECT_EQ(list4.empty(), CONTAINER_NOT_EMPTY);
  list4.push_back(1000);
  EXPECT_EQ(list4.size(), 7);

  _SPCE_::list<double> list5{1.1, 4, 2, 5, 7, 13, 56, 11, 5914.09};
  EXPECT_EQ(list5.empty(), CONTAINER_NOT_EMPTY);
  EXPECT_EQ(list5.size(), 9);

#ifndef _SPCE_ORIG_
  EXPECT_DOUBLE_EQ(list5(0), 1.1);
  EXPECT_DOUBLE_EQ(list5(8), 5914.09);
#endif

  _SPCE_::list list6 = std::move(list5);
  EXPECT_EQ(list5.empty(), CONTAINER_EMPTY);
  EXPECT_EQ(list6.size(), 9);
#ifndef _SPCE_ORIG_
  EXPECT_DOUBLE_EQ(list6(0), 1.1);
  EXPECT_DOUBLE_EQ(list6(8), 5914.09);
#endif

  _SPCE_::list<double> list7;
  list7 = std::move(list6);
  EXPECT_EQ(list6.empty(), CONTAINER_EMPTY);
  EXPECT_EQ(list7.size(), 9);
#ifndef _SPCE_ORIG_
  EXPECT_DOUBLE_EQ(list7(0), 1.1);
  EXPECT_DOUBLE_EQ(list7(8), 5914.09);
#endif

  _SPCE_::list list8 = std::move(list11);  // move empty-list
  EXPECT_EQ(list8.empty(), CONTAINER_EMPTY);

  list8.push_back(5);
  EXPECT_EQ(list8.empty(), CONTAINER_NOT_EMPTY);
#ifndef _SPCE_ORIG_
  EXPECT_DOUBLE_EQ(list8(0), 5);
#endif

  EXPECT_EQ(list11.empty(), CONTAINER_EMPTY);
  _SPCE_::list list9(std::move(list11));  // move empty-list
  EXPECT_EQ(list9.empty(), CONTAINER_EMPTY);
  EXPECT_EQ(list11.empty(), CONTAINER_EMPTY);

  list9.push_back(10);
  EXPECT_EQ(list9.size(), 1);

  // тест конструктор перемещения и параметризированного конструктора
  // конструктор "со списком" и опрератором присваивания
  _SPCE_::list<int> list10(4);
  EXPECT_EQ(list10.size(), 4);
  _SPCE_::list listcpy = std::move(list10);
  EXPECT_EQ(listcpy.size(), 4);
  EXPECT_EQ(list10.empty(), CONTAINER_EMPTY);
}

// empty(), size(), clear();
TEST_F(test_s21_list, test_s21_list_empty_size) {
  _SPCE_::list<double> list0;
  EXPECT_EQ(list0.empty(), CONTAINER_EMPTY);

  _SPCE_::list<int> list1(1);
  EXPECT_EQ(list1.empty(), CONTAINER_NOT_EMPTY);

  for (size_t i = 0; i < 100; i++) list1.push_back(i);
  list1.pop_back();
  EXPECT_EQ(list1.empty(), CONTAINER_NOT_EMPTY);
  EXPECT_EQ(list1.size(), 100);

  list1.clear();
  EXPECT_EQ(list1.empty(), CONTAINER_EMPTY);
  list1.clear();  // clear empty-list
  EXPECT_EQ(list1.empty(), CONTAINER_EMPTY);

  EXPECT_DEATH((list1.pop_back(), exit(0)),
               ".*");  // del from empty-list ... ERROR
  EXPECT_EQ(list1.empty(), CONTAINER_EMPTY);
}

// begin(), end(), front(), back()
TEST_F(test_s21_list, test_s21_list_begin_end_front_back) {
  _SPCE_::list<double> list1;
  list1.push_back(1.1);
  list1.push_back(-0.1);
  list1.push_back(25.1);
  _SPCE_::list<double>::iterator pos = list1.begin();
  EXPECT_EQ(list1.front(), *pos);
  pos = list1.end();
  --pos;
  EXPECT_EQ(list1.back(), *pos);
  list1.clear();
  pos = list1.begin();
  EXPECT_EQ(list1.front(), *pos);
  EXPECT_EQ(list1.front(), list1.back());

  _SPCE_::list<int> list2(4);
  EXPECT_EQ(list2.front(), 0);
  EXPECT_EQ(list2.back(), 0);

  _SPCE_::list<double> list3{1.1, 4, 2, 5, 7, 13, 56, 11, 5914.09};
  EXPECT_EQ(list3.front(), 1.1);
  EXPECT_EQ(list3.back(), 5914.09);
}

// insert(), erase(), push's, pop's
TEST_F(test_s21_list, test_s21_list_insert_erase) {
  _SPCE_::list<double> answer{1.1, 2024, 25.1, 9.6};
  _SPCE_::list<double> answer1{1.1, 2024, 25.1};
  _SPCE_::list<double> answer2{123.4, 1.1, 2024, 25.1};

  _SPCE_::list<double> list1{1.1, 25.1};
  _SPCE_::list<double>::iterator pos = list1.begin();
  _SPCE_::list<double>::iterator pos1 = pos;
  EXPECT_EQ(pos == pos1, SUCCESS);

  ++pos;
  pos1 = list1.insert(pos, 2024);
  list1.push_back(9.6);

  EXPECT_EQ(list1 == answer, SUCCESS);

  list1.pop_back();
  EXPECT_EQ(list1 == answer1, SUCCESS);

  list1.push_front(123.4);
  EXPECT_EQ(list1 == answer2, SUCCESS);

  list1.pop_front();
  EXPECT_EQ(list1 == answer1, SUCCESS);
  list1.pop_front();
  list1.pop_back();
  list1.pop_front();
  EXPECT_EQ(list1.empty(), CONTAINER_EMPTY);
  list1.push_back(9.6);
  list1.pop_back();
  EXPECT_EQ(list1.empty(), CONTAINER_EMPTY);
}

// push_back/pop_back
TEST_F(test_s21_list, test_s21_list_pushback_popback) {
  _SPCE_::list<int> list2;
  EXPECT_EQ(list2.empty(), CONTAINER_EMPTY);
  list2.push_back(100);
  EXPECT_EQ(list2.size(), 1);
  EXPECT_EQ(list2.empty(), CONTAINER_NOT_EMPTY);

  list2.pop_back();
  EXPECT_EQ(list2.empty(), CONTAINER_EMPTY);
}

// тест push_back/pop_back, доступ по индексу()
TEST_F(test_s21_list, test_s21_list_index) {
  _SPCE_::list<double> list1;
  list1.push_back(-20.4);
  EXPECT_EQ(list1.size(), 1);

  _SPCE_::list<double>::iterator iter;
  iter = list1.begin();

  list1.push_back(1.5);
  list1.push_back(13514.9);
  EXPECT_EQ(list1.size(), 3);
  *(list1.begin()) = 20.4;
#ifndef _SPCE_ORIG_
  EXPECT_DOUBLE_EQ(list1(0), 20.4);
  EXPECT_DOUBLE_EQ(list1(1), 1.5);
  EXPECT_DOUBLE_EQ(list1(2), 13514.9);
#endif

  list1.push_back(4);
  list1.push_back(50.7);
  list1.push_back(-4);
  EXPECT_EQ(list1.size(), 6);
#ifndef _SPCE_ORIG_
  EXPECT_DOUBLE_EQ(list1(5), -4);
#endif

  list1.pop_back();
  EXPECT_EQ(list1.size(), 5);
#ifndef _SPCE_ORIG_
  EXPECT_DOUBLE_EQ(list1(3), 4);
  EXPECT_DOUBLE_EQ(list1(4), 50.7);
#endif
}

// тест итераторов, push_back/pop_back
TEST_F(test_s21_list, test_s21_list_iterator) {
  _SPCE_::list<int> list2;
  list2.push_back(-111);
  list2.push_back(101);
  list2.push_back(102);
  list2.push_back(103);
  _SPCE_::list<int>::iterator iter = list2.begin();
  EXPECT_EQ(*iter, -111);

  EXPECT_EQ(*(++iter), 101);
  EXPECT_EQ(*(++iter), 102);
  EXPECT_EQ(*(++iter), 103);
  ++iter;
  EXPECT_EQ(*(--iter), 103);
  EXPECT_EQ(*(--iter), 102);
  EXPECT_EQ(*(--iter), 101);
  EXPECT_EQ(*(--iter), -111);

  for (int i = 0; i < 4; i++) list2.pop_front();
  EXPECT_EQ(list2.empty(), CONTAINER_EMPTY);

  list2.push_front(-111);
  list2.push_front(101);
  list2.push_front(102);
  list2.push_front(103);
  iter = list2.begin();

  EXPECT_EQ(*iter, 103);
  EXPECT_EQ(*(++iter), 102);
  EXPECT_EQ(*(++iter), 101);
  EXPECT_EQ(*(++iter), -111);

  for (int i = 0; i < 4; i++) list2.pop_back();

  EXPECT_EQ(list2.empty(), CONTAINER_EMPTY);
}

// тест итераторов, push_back/pop_back
TEST_F(test_s21_list, test_s21_list_const_iterator) {
  _SPCE_::list<int> list2;
  list2.push_back(-111);
  list2.push_back(101);
  list2.push_back(102);
  list2.push_back(103);
  _SPCE_::list<int>::const_iterator iter = list2.cbegin();

  int a = *iter;
  EXPECT_EQ(a, -111);
  EXPECT_EQ(*iter, -111);
  EXPECT_EQ(*(++iter), 101);
  EXPECT_EQ(*(++iter), 102);
  EXPECT_EQ(*(++iter), 103);
  ++iter;
  EXPECT_EQ(*(--iter), 103);
  EXPECT_EQ(*(--iter), 102);
  EXPECT_EQ(*(--iter), 101);
  EXPECT_EQ(*(--iter), -111);

  for (int i = 0; i < 4; i++) list2.pop_front();

  EXPECT_EQ(list2.empty(), CONTAINER_EMPTY);
}

// swap()
TEST_F(test_s21_list, test_s21_list_swap) {
  _SPCE_::list<int> list1{1, 4, 2, 5, 7, 13, 56, 11, 5914};
  _SPCE_::list<int> list2{1};

  _SPCE_::list<int> answ1(list1);
  _SPCE_::list<int> answ2(list2);
  list1.swap(list2);
  EXPECT_EQ(list1 == answ2, SUCCESS);
  EXPECT_EQ(list2 == answ1, SUCCESS);
  list2.swap(list1);
  EXPECT_EQ(list1 == answ1, SUCCESS);
  EXPECT_EQ(list2 == answ2, SUCCESS);
  list1.clear();
  list2.clear();
  list1.swap(list2);
  EXPECT_EQ(list2 == list1, SUCCESS);
}

// merge()
TEST_F(test_s21_list, test_s21_list_merge) {
  _SPCE_::list<int> list1{1, 4, 2, 3, 7, 101, 13, 56, 11, 5914};
  _SPCE_::list<int> list2{4, 1, 100, 56, 102, 57, 6000, 3, 2};

  _SPCE_::list<int> answ1{1,  4,  2,  3,   4,  1,    7,    100, 56, 101,
                          13, 56, 11, 102, 57, 5914, 6000, 3,   2};

  list1.merge(list2);

  EXPECT_EQ(list1.size(), answ1.size());
  EXPECT_EQ(list1 == answ1, SUCCESS);

  EXPECT_EQ(list2.size(), 0);
  EXPECT_EQ(list2.empty(), CONTAINER_EMPTY);
  list1.merge(list2);  // merge with empty-list2
  EXPECT_EQ(list1 == answ1, SUCCESS);
  EXPECT_EQ(list1.size(), 19);
  EXPECT_EQ(list2.empty(), CONTAINER_EMPTY);

  answ1.pop_back();
  list1.pop_back();

  list2.merge(list1);  // merge to empty-list2
  EXPECT_EQ(list2 == answ1, SUCCESS);
  EXPECT_EQ(list1.empty(), CONTAINER_EMPTY);

  _SPCE_::list<double> list3;
  _SPCE_::list<double> list4;
  list3.merge(list4);  // merge both empty-list
  EXPECT_EQ(list3 == list4, SUCCESS);
  EXPECT_EQ(list3.empty(), CONTAINER_EMPTY);
  EXPECT_EQ(list4.empty(), CONTAINER_EMPTY);
}

// splice()
TEST_F(test_s21_list, test_s21_list_splice) {
  _SPCE_::list<int> answ1{1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11};
  _SPCE_::list<int> list1{5, 6, 7, 8, 11};
  _SPCE_::list<int> list2{1, 2, 3};
  _SPCE_::list<int> list3{9, 10};
  _SPCE_::list<int>::const_iterator iter{list1.begin()};

  _SPCE_::list<int>::const_iterator iter1;
  iter1 = iter;

  list1.splice(iter1, list2);
  list1.insert(iter, 4);

  iter = list1.end();
  --iter;
  list1.splice(iter, list3);

  EXPECT_EQ(list1 == answ1, SUCCESS);
  EXPECT_EQ(list2.empty(), CONTAINER_EMPTY);

  iter = list2.end();
  list2.splice(iter, list1);  // splice to empty-list
  EXPECT_EQ(list2 == answ1, SUCCESS);

  list2.splice(iter = list2.begin(), list1);  // splice empty-list
  EXPECT_EQ(list2 == answ1, SUCCESS);
}

// insert()
TEST_F(test_s21_list, test_s21_list_insert) {
  _SPCE_::list<int> answ1{11, 12, 13, 10, 1, 4, 2, 5, 7, 13, 56, 11, 5914};
  _SPCE_::list<int> list1{4, 2, 5, 7, 13, 56, 11, 5914};

  _SPCE_::list<int>::iterator iter = list1.begin();
  list1.insert(iter, 1);
  iter = list1.begin();
  list1.insert(iter, 10);
  iter = list1.begin();
  list1.insert(iter, 11);
  iter = list1.begin();
  list1.insert(++iter, 12);
  iter = list1.begin();
  ++iter;
  list1.insert(++iter, 13);

  EXPECT_EQ(list1 == answ1, SUCCESS);
}

// unique()
TEST_F(test_s21_list, test_s21_list_unique) {
  _SPCE_::list<int> answ1{1, 2, 3, 4, 5};
  _SPCE_::list<int> list1{1, 1, 1, 2, 2, 2, 3, 4, 5, 5, 5, 5, 5, 5};

  list1.unique();
  EXPECT_EQ(list1 == answ1, SUCCESS);

  _SPCE_::list<int> list2;
  list2.unique();
  EXPECT_EQ(list2.empty(), CONTAINER_EMPTY);

  list2.push_back(1);
  list2.push_back(1);
  list2.unique();
  _SPCE_::list<int> answ2{1};

  EXPECT_EQ(list2.empty(), CONTAINER_NOT_EMPTY);
  EXPECT_EQ(list2 == answ2, SUCCESS);
}

// reverse()
TEST_F(test_s21_list, test_s21_list_reverse) {
  _SPCE_::list<int> answ1{1, 2, 3, 4, 5};
  _SPCE_::list<int> answ2;
  _SPCE_::list<int> answ3{777, 3};
  _SPCE_::list<int> list1{5, 4, 3, 2, 1};

  list1.reverse();
  EXPECT_EQ(list1 == answ1, SUCCESS);

  _SPCE_::list<int> list2;
  list2.reverse();
  EXPECT_EQ(list2 == answ2, SUCCESS);
  list2.push_back(3);
  list2.push_back(777);
  list2.reverse();
  EXPECT_EQ(list2 == answ3, SUCCESS);
}

// sort()
TEST_F(test_s21_list, test_s21_list_sort) {
  _SPCE_::list<int> answ1{1, 2, 3, 4, 5};
  _SPCE_::list<int> list1{4, 3, 2, 1, 5};
  _SPCE_::list<int> answ2{1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
  _SPCE_::list<int> list2{5, 9, 4, 3, 6, 10, 2, 7, 1, 8};
  _SPCE_::list<int> list3;
  _SPCE_::list<int> list4{4};
  _SPCE_::list<int> list5{3, 7, 8, 5, 2, 1, 9, 5, 4};
  _SPCE_::list<int> answ5{1, 2, 3, 4, 5, 5, 7, 8, 9};
  _SPCE_::list<int> list6{3, 7};
  _SPCE_::list<int> answ6{3, 7};
  _SPCE_::list<int> list7{1, 0};
  _SPCE_::list<int> answ7{0, 1};

  list1.sort();
  list2.sort();
  list3.sort();
  list4.sort();
  list5.sort();
  list6.sort();
  list7.sort();
  EXPECT_EQ(list1 == answ1, SUCCESS);
  EXPECT_EQ(list2 == answ2, SUCCESS);
  EXPECT_EQ(list3.empty(), CONTAINER_EMPTY);
  EXPECT_EQ(list4.size(), 1);
  EXPECT_EQ(list4.front(), 4);
  EXPECT_EQ(list5 == answ5, SUCCESS);
  EXPECT_EQ(list6 == answ6, SUCCESS);
  EXPECT_EQ(list7 == answ7, SUCCESS);
}

#ifndef _SPCE_ORIG_

// insert_many()
TEST_F(test_s21_list, test_s21_list_insert_many) {
  _SPCE_::list<int> answ1{1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12};
  _SPCE_::list<int> list1{5, 6, 7, 8, 11};
  _SPCE_::list<int>::const_iterator iter(list1.begin());

  list1.insert_many(iter, 1, 2, 3, 4);
  iter = list1.end();
  --iter;

  list1.insert_many(iter, 9, 10);
  iter = list1.end();
  list1.insert_many(iter, 12);
  EXPECT_EQ(list1 == answ1, SUCCESS);
}

// insert_many_back()
TEST_F(test_s21_list, test_s21_list_insert_back) {
  _SPCE_::list<double> answ1{1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11.1};
  _SPCE_::list<double> list1{1, 2, 3};

  list1.insert_many_back(4);
  list1.insert_many_back(5, 6, 7, 8);
  list1.insert_many_back(9, 10, 11.1);

  EXPECT_EQ(list1 == answ1, SUCCESS);
}

// insert_many_front()
TEST_F(test_s21_list, test_s21_list_insert_front) {
  _SPCE_::list<int> answ1{1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11};
  _SPCE_::list<int> list1{11};
  list1.insert_many_front(8, 9, 10);
  list1.insert_many_front(2, 3, 4, 5, 6, 7);
  list1.insert_many_front(1);
  EXPECT_EQ(list1 == answ1, SUCCESS);
}

#endif