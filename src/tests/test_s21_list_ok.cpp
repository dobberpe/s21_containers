#include <list>

#include "test_s21_containers.h"
#define _SPCE_ s21
// using namespace _SPCE_;

class test_s21_list : public testing::Test {
 public:
};

TEST_F(test_s21_list, test_s21_list_origin) {
  // const std::list<int> l{1, 2, 3};
  // // l.front() = 10;
  // std::iterator lv = l.end();
  // std::iterator<int> lv = l.end();
  // std::list<int>::const_iterator lv = l.end();

  // const s21::list<int> l1{1, 2, 3};
  // // l1.front() = 10;
  // s21::iterator l1v  = l1.end();;
  // s21::iterator<int> l2v = l1.begin();
  //   s21::list<int>::const_iterator lv = l1.cend();
}

TEST_F(test_s21_list, test_s21_list_const) {
  // _SPCE_::list<int> list1{1, 2, 3, 4, 5, 6, 7};
  // _SPCE_::list<int>::const_iterator citer = list1.end();
  // *citer = 9;

  // std::list<int> list2{1, 2, 3, 4, 5, 6, 7};
  // std::list<int>::const_iterator iter = list2.end();

  // printf("%d ", *(citer));
  // printf("%d ", *iter);
  // // *citer = 10;
  // *iter = 0;
  // printf("%d ", *citer);
  // printf("%d ", *iter);
}

TEST_F(test_s21_list, test_s21_list_create) {
  _SPCE_::list<int> list1;
  ASSERT_EQ(list1.empty(), CONTAINER_EMPTY);
  _SPCE_::list list11(std::move(list1));
  ASSERT_EQ(list11.empty(), CONTAINER_EMPTY);
  ASSERT_EQ(list1.empty(), CONTAINER_EMPTY);

  _SPCE_::list<int> list2(1);
  ASSERT_EQ(list2.empty(), CONTAINER_NOT_EMPTY);
  list2.push_back(15);
  list2.push_back(19);
  list2.push_back(4);
  list2.push_back(50);
  list2.push_back(-4);
  ASSERT_EQ(list2.empty(), CONTAINER_NOT_EMPTY);
  ASSERT_EQ(list2.size(), 6);

  _SPCE_::list list3(list2);
  ASSERT_EQ(list3.empty(), CONTAINER_NOT_EMPTY);
  ASSERT_EQ(list3.size(), 6);

  _SPCE_::list list4(std::move(list3));
  ASSERT_EQ(list4.empty(), CONTAINER_NOT_EMPTY);
  list4.push_back(1000);
  ASSERT_EQ(list4.size(), 7);

  _SPCE_::list<double> list5{1.1, 4, 2, 5, 7, 13, 56, 11, 5914.09};
  ASSERT_EQ(list5.empty(), CONTAINER_NOT_EMPTY);
  ASSERT_EQ(list5.size(), 9);
  // ASSERT_EQ(list5(0), 1.1);
  // ASSERT_EQ(list5(8), 5914.09);

  _SPCE_::list list6 = std::move(list5);
  ASSERT_EQ(list5.empty(), CONTAINER_EMPTY);
  ASSERT_EQ(list6.size(), 9);
  // ASSERT_EQ(list6(0), 1.1);
  // ASSERT_EQ(list6(8), 5914.09);

  _SPCE_::list<double> list7;
  list7 = std::move(list6);
  ASSERT_EQ(list6.empty(), CONTAINER_EMPTY);
  ASSERT_EQ(list7.size(), 9);
  // ASSERT_EQ(list7(0), 1.1);
  // ASSERT_EQ(list7(8), 5914.09);

  _SPCE_::list list8 = std::move(list11);  // move empty-list
  ASSERT_EQ(list8.empty(), CONTAINER_EMPTY);

  list8.push_back(5);
  ASSERT_EQ(list8.empty(), CONTAINER_NOT_EMPTY);
  // ASSERT_EQ(list8(0), 5);

  ASSERT_EQ(list11.empty(), CONTAINER_EMPTY);
  _SPCE_::list list9(std::move(list11));  // move empty-list
  ASSERT_EQ(list9.empty(), CONTAINER_EMPTY);
  ASSERT_EQ(list11.empty(), CONTAINER_EMPTY);

  list9.push_back(10);
  ASSERT_EQ(list9.size(), 1);
}

// empty(), size(), clear();
TEST_F(test_s21_list, test_s21_list_empty_size) {
  _SPCE_::list<double> list0;
  ASSERT_EQ(list0.empty(), CONTAINER_EMPTY);

  _SPCE_::list<int> list1(1);
  ASSERT_EQ(list1.empty(), CONTAINER_NOT_EMPTY);

  for (size_t i = 0; i < 100; i++) list1.push_back(i);
  list1.pop_back();
  ASSERT_EQ(list1.empty(), CONTAINER_NOT_EMPTY);
  ASSERT_EQ(list1.size(), 100);

  list1.clear();
  ASSERT_EQ(list1.empty(), CONTAINER_EMPTY);
  list1.clear();  // clear empty-list
  ASSERT_EQ(list1.empty(), CONTAINER_EMPTY);

  // list1.pop_back();  // del from empty-list
  ASSERT_EQ(list1.empty(), CONTAINER_EMPTY);
}

// begin(), end(), front(), back()
TEST_F(test_s21_list, test_s21_list_begin_end_front_back) {
  _SPCE_::list<double> list1;
  list1.push_back(1.1);
  list1.push_back(-0.1);
  list1.push_back(25.1);
  _SPCE_::list<double>::iterator pos = list1.begin();
  ASSERT_EQ(list1.front(), *pos);
  pos = list1.end();
  --pos;
  ASSERT_EQ(list1.back(), *pos);
  list1.clear();
  pos = list1.begin();
  ASSERT_EQ(list1.front(), *pos);
  ASSERT_EQ(list1.front(), list1.back());

  _SPCE_::list<int> list2(4);
  ASSERT_EQ(list2.front(), 0);
  ASSERT_EQ(list2.back(), 0);

  _SPCE_::list<double> list3{1.1, 4, 2, 5, 7, 13, 56, 11, 5914.09};
  ASSERT_EQ(list3.front(), 1.1);
  ASSERT_EQ(list3.back(), 5914.09);
}

// insert(), erase(), push's, pop's
TEST_F(test_s21_list, test_s21_list_insert_erase) {
  _SPCE_::list<double> answer{1.1, 2024, 25.1, 9.6};
  _SPCE_::list<double> answer1{1.1, 2024, 25.1};
  _SPCE_::list<double> answer2{123.4, 1.1, 2024, 25.1};

  _SPCE_::list<double> list1{1.1, 25.1};
  _SPCE_::list<double>::iterator pos = list1.begin();
  _SPCE_::list<double>::iterator pos1;
  ++pos;
  pos1 = list1.insert(pos, 2024);
  list1.push_back(9.6);

  ASSERT_EQ(list1 == answer, SUCCESS);

  list1.pop_back();
  ASSERT_EQ(list1 == answer1, SUCCESS);

  list1.push_front(123.4);
  ASSERT_EQ(list1 == answer2, SUCCESS);

  list1.pop_front();
  ASSERT_EQ(list1 == answer1, SUCCESS);
  list1.pop_front();
  list1.pop_back();
  list1.pop_front();
  ASSERT_EQ(list1.empty(), CONTAINER_EMPTY);
  list1.push_back(9.6);
  list1.pop_back();
  ASSERT_EQ(list1.empty(), CONTAINER_EMPTY);
}

// тест конструктора по умолчанию, empty(), push_back/pop_back
TEST_F(test_s21_list, test_s21_list_2) {
  _SPCE_::list<int> list2;
  ASSERT_EQ(list2.empty(), CONTAINER_EMPTY);
  list2.push_back(100);
  ASSERT_EQ(list2.size(), 1);
  ASSERT_EQ(list2.empty(), CONTAINER_NOT_EMPTY);

  list2.pop_back();
  ASSERT_EQ(list2.empty(), CONTAINER_EMPTY);
}

// тест push_back/pop_back, доступ по индексу()
TEST_F(test_s21_list, test_s21_list_3) {
  _SPCE_::list<double> list1;
  list1.push_back(-20.4);
  ASSERT_EQ(list1.size(), 1);

  _SPCE_::list<double>::iterator iter;
  iter = list1.begin();

  list1.push_back(1.5);
  list1.push_back(13514.9);
  ASSERT_EQ(list1.size(), 3);
  *(list1.begin()) = 20.4;
  // ASSERT_DOUBLE_EQ(list1(0), 20.4);
  // ASSERT_DOUBLE_EQ(list1(1), 1.5);
  // ASSERT_DOUBLE_EQ(list1(2), 13514.9);

  list1.push_back(4);
  list1.push_back(50.7);
  list1.push_back(-4);
  ASSERT_EQ(list1.size(), 6);
  // ASSERT_DOUBLE_EQ(list1(5), -4);

  list1.pop_back();
  ASSERT_EQ(list1.size(), 5);
  // ASSERT_DOUBLE_EQ(list1(3), 4);
  // ASSERT_DOUBLE_EQ(list1(4), 50.7);
}

// тест итераторов, push_back/pop_back
TEST_F(test_s21_list, test_s21_list_4) {
  _SPCE_::list<int> list2;
  list2.push_back(-111);
  list2.push_back(101);
  list2.push_back(102);
  list2.push_back(103);
  _SPCE_::list<int>::iterator iter = list2.begin();
  ASSERT_EQ(*iter, -111);

  ASSERT_EQ(*(++iter), 101);
  ASSERT_EQ(*(++iter), 102);
  ASSERT_EQ(*(++iter), 103);
  ++iter;
  ASSERT_EQ(*(--iter), 103);
  ASSERT_EQ(*(--iter), 102);
  ASSERT_EQ(*(--iter), 101);
  ASSERT_EQ(*(--iter), -111);

  for (int i = 0; i < 4; i++) list2.pop_front();
  // for (int i = 0; i < 4; i++) list2.pop_back();

  ASSERT_EQ(list2.empty(), CONTAINER_EMPTY);
}

// тест конструктор перемещения и параметризированного конструктора
// конструктор "со списком" и опрератором присваивания
TEST_F(test_s21_list, test_s21_list_5) {
  _SPCE_::list<int> list2(4);
  ASSERT_EQ(list2.size(), 4);
  _SPCE_::list listcpy = std::move(list2);
  ASSERT_EQ(listcpy.size(), 4);
  ASSERT_EQ(list2.empty(), CONTAINER_EMPTY);

  _SPCE_::list<int> list3{1, 4, 2, 5, 7, 13, 56, 11, 5914};
  ASSERT_EQ(list3.size(), 9);
}

// swap()
TEST_F(test_s21_list, test_s21_list_swap) {
  _SPCE_::list<int> list1{1, 4, 2, 5, 7, 13, 56, 11, 5914};
  _SPCE_::list<int> list2{1};

  _SPCE_::list<int> answ1(list1);
  _SPCE_::list<int> answ2(list2);
  list1.swap(list2);
  ASSERT_EQ(list1 == answ2, SUCCESS);
  ASSERT_EQ(list2 == answ1, SUCCESS);
  list2.swap(list1);
  ASSERT_EQ(list1 == answ1, SUCCESS);
  ASSERT_EQ(list2 == answ2, SUCCESS);
  list1.clear();
  list2.clear();
  list1.swap(list2);
  ASSERT_EQ(list2 == list1, SUCCESS);
}

// merge()
TEST_F(test_s21_list, test_s21_list_merge) {
  _SPCE_::list<int> list1{1, 4, 2, 3, 7, 101, 13, 56, 11, 5914};
  _SPCE_::list<int> list2{4, 1, 100, 56, 102, 57, 6000, 3, 2};

  _SPCE_::list<int> answ1{1,  4,  2,  3,   4,  1,    7,    100, 56, 101,
                          13, 56, 11, 102, 57, 5914, 6000, 3,   2};

  list1.merge(list2);

  ASSERT_EQ(list1.size(), answ1.size());
  ASSERT_EQ(list1 == answ1, SUCCESS);

  ASSERT_EQ(list2.size(), 0);
  ASSERT_EQ(list2.empty(), CONTAINER_EMPTY);
  list1.merge(list2);  // merge with empty-list2
  ASSERT_EQ(list1 == answ1, SUCCESS);
  ASSERT_EQ(list1.size(), 19);
  ASSERT_EQ(list2.empty(), CONTAINER_EMPTY);

  answ1.pop_back();
  list1.pop_back();

  list2.merge(list1);  // merge to empty-list2
  ASSERT_EQ(list2 == answ1, SUCCESS);
  ASSERT_EQ(list1.empty(), CONTAINER_EMPTY);

  _SPCE_::list<double> list3;
  _SPCE_::list<double> list4;
  list3.merge(list4);  // merge both empty-list
  ASSERT_EQ(list3 == list4, SUCCESS);
  ASSERT_EQ(list3.empty(), CONTAINER_EMPTY);
  ASSERT_EQ(list4.empty(), CONTAINER_EMPTY);
}

// splice()
TEST_F(test_s21_list, test_s21_list_splice) {
  _SPCE_::list<int> answ1{1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11};
  _SPCE_::list<int> list1{5, 6, 7, 8, 11};
  _SPCE_::list<int> list2{1, 2, 3};
  _SPCE_::list<int> list3{9, 10};
  _SPCE_::list<int>::iterator iter = list1.begin();

  list1.splice(iter, list2);
  list1.insert(iter, 4);

  iter = list1.end();
  list1.splice(--iter, list3);

  ASSERT_EQ(list1 == answ1, SUCCESS);
  ASSERT_EQ(list2.empty(), CONTAINER_EMPTY);

  iter = list2.end();
  list2.splice(iter, list1);  // splice to empty-list
  ASSERT_EQ(list2 == answ1, SUCCESS);

  list2.splice(iter = list2.begin(), list1);  // splice empty-list
  ASSERT_EQ(list2 == answ1, SUCCESS);
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

  ASSERT_EQ(list1 == answ1, SUCCESS);
}

// unique()
TEST_F(test_s21_list, test_s21_list_unique) {
  _SPCE_::list<int> answ1{1, 2, 3, 4, 5};
  _SPCE_::list<int> list1{1, 1, 1, 2, 2, 2, 3, 4, 5, 5, 5, 5, 5, 5};

  list1.unique();
  ASSERT_EQ(list1 == answ1, SUCCESS);

  _SPCE_::list<int> list2;
  list2.unique();
  ASSERT_EQ(list2.empty(), CONTAINER_EMPTY);

  list2.push_back(1);
  list2.push_back(1);
  list2.unique();
  _SPCE_::list<int> answ2{1};

  ASSERT_EQ(list2.empty(), CONTAINER_NOT_EMPTY);
  ASSERT_EQ(list2 == answ2, SUCCESS);
}

// reverse()
TEST_F(test_s21_list, test_s21_list_reverse) {
  _SPCE_::list<int> answ1{1, 2, 3, 4, 5};
  _SPCE_::list<int> answ2;
  _SPCE_::list<int> answ3{777, 3};
  _SPCE_::list<int> list1{5, 4, 3, 2, 1};

  list1.reverse();
  ASSERT_EQ(list1 == answ1, SUCCESS);

  _SPCE_::list<int> list2;
  list2.reverse();
  ASSERT_EQ(list2 == answ2, SUCCESS);
  list2.push_back(3);
  list2.push_back(777);
  list2.reverse();
  ASSERT_EQ(list2 == answ3, SUCCESS);
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
  ASSERT_EQ(list1 == answ1, SUCCESS);
  ASSERT_EQ(list2 == answ2, SUCCESS);
  ASSERT_EQ(list3.empty(), CONTAINER_EMPTY);
  ASSERT_EQ(list4.size(), 1);
  ASSERT_EQ(list4.front(), 4);
  ASSERT_EQ(list5 == answ5, SUCCESS);
  ASSERT_EQ(list6 == answ6, SUCCESS);
  ASSERT_EQ(list7 == answ7, SUCCESS);
}
