#include <list>

#include "test_s21_containers.h"

using namespace s21;

class test_s21_list : public testing::Test {
 public:
};

TEST_F(test_s21_list, test_s21_list_origin) {
  // printf("%ld\n",list_orig.max_size());
  // s21::list<int> l;
  // s21::vector<int> v;
  // s21::ListIterator lv = l.end();
  // s21::VectorIterator vv = v.begin();

  // std::list<int> l1;
  // std::vector<int> v1;
  // std::iterator l1v;
  // std::iterator v1v = v1.begin();
  // std::list<int>::iterator l2v = l1.begin();
  // std::vector<int>::iterator v2v = v1.begin();
}

TEST_F(test_s21_list, test_s21_list_const) {
  //   const std::list<int> list1{1, 2, 3, 4, 5, 6, 7};
  //   std::list<int>::const_iterator citer = list1.cend();
  // *citer = 9;
  //   s21::list<int> list2{1, 2, 3, 4, 5, 6, 7};
  //   s21::list<int>::iterator iter = list2.begin();

  //   printf("%d ", *(citer));
  //   printf("%d ", *iter);
  //   *citer = 10;
  //   *iter = 0;
  //   printf("%d ", *citer);
  //   printf("%d ", *iter);
}

TEST_F(test_s21_list, test_s21_list_create) {
  s21::list<int> list1;
  ASSERT_EQ(list1.empty(), CONTAINER_EMPTY);
  s21::list list11(std::move(list1));
  ASSERT_EQ(list11.empty(), CONTAINER_EMPTY);
  ASSERT_EQ(list1.empty(), CONTAINER_EMPTY);

  s21::list<int> list2(1);
  ASSERT_EQ(list2.empty(), CONTAINER_NOT_EMPTY);
  list2.push_back(15);
  list2.push_back(19);
  list2.push_back(4);
  list2.push_back(50);
  list2.push_back(-4);
  ASSERT_EQ(list2.empty(), CONTAINER_NOT_EMPTY);
  ASSERT_EQ(list2.size(), 6);

  s21::list list3(list2);
  ASSERT_EQ(list3.empty(), CONTAINER_NOT_EMPTY);
  ASSERT_EQ(list3.size(), 6);

  s21::list list4(std::move(list3));
  ASSERT_EQ(list4.empty(), CONTAINER_NOT_EMPTY);
  list4.push_back(1000);
  ASSERT_EQ(list4.size(), 7);

  s21::list<double> list5{1.1, 4, 2, 5, 7, 13, 56, 11, 5914.09};
  ASSERT_EQ(list5.empty(), CONTAINER_NOT_EMPTY);
  ASSERT_EQ(list5.size(), 9);
  ASSERT_EQ(list5(0), 1.1);
  ASSERT_EQ(list5(8), 5914.09);

  s21::list list6 = std::move(list5);
  ASSERT_EQ(list5.empty(), CONTAINER_EMPTY);
  ASSERT_EQ(list6.size(), 9);
  ASSERT_EQ(list6(0), 1.1);
  ASSERT_EQ(list6(8), 5914.09);

  s21::list<double> list7;
  list7 = std::move(list6);
  ASSERT_EQ(list6.empty(), CONTAINER_EMPTY);
  ASSERT_EQ(list7.size(), 9);
  ASSERT_EQ(list7(0), 1.1);
  ASSERT_EQ(list7(8), 5914.09);

  s21::list list8 = std::move(list11);  // move empty-list
  ASSERT_EQ(list8.empty(), CONTAINER_EMPTY);

  list8.push_back(5);
  ASSERT_EQ(list8.empty(), CONTAINER_NOT_EMPTY);
  ASSERT_EQ(list8(0), 5);

  ASSERT_EQ(list11.empty(), CONTAINER_EMPTY);
  s21::list list9(std::move(list11));  // move empty-list
  ASSERT_EQ(list9.empty(), CONTAINER_EMPTY);
  ASSERT_EQ(list11.empty(), CONTAINER_EMPTY);

  list9.push_back(10);
  ASSERT_EQ(list9.size(), 1);
}

// empty(), size(), clear();
TEST_F(test_s21_list, test_s21_list_empty_size) {
  list<double> list0;
  ASSERT_EQ(list0.empty(), CONTAINER_EMPTY);

  list<int> list1(1);
  ASSERT_EQ(list1.empty(), CONTAINER_NOT_EMPTY);

  for (size_t i = 0; i < 100; i++) list1(i) = i;
  list1.pop_back();
  ASSERT_EQ(list1.empty(), CONTAINER_EMPTY);
  ASSERT_EQ(list1.size(), 0);

  // 384307168202282325
  // for (int i = 0; i < 38430716820228232; i++) list1.push_back(i);
  // ASSERT_EQ(list1.empty(), CONTAINER_NOT_EMPTY);
  // ASSERT_EQ(list1.size(), 10000);
  // list<int> list_my(100000000);
  // ASSERT_EQ(list_my.size(), 100000000);

  // list<int> list_origin(100000000);
  // ASSERT_EQ(list_origin.size(), 100000000);

  list1.clear();
  ASSERT_EQ(list1.empty(), CONTAINER_EMPTY);
  list1.clear();  // clear empty-list
  ASSERT_EQ(list1.empty(), CONTAINER_EMPTY);

  list1.pop_back();  // del from empty-list
  ASSERT_EQ(list1.empty(), CONTAINER_EMPTY);
}

// begin(), end(), front(), back()
TEST_F(test_s21_list, test_s21_list_begin_end_front_back) {
  list<double> list1;
  list1.push_back(1.1);
  list1.push_back(-0.1);
  list1.push_back(25.1);
  list<double>::iterator pos = list1.begin();
  ASSERT_EQ(list1.front(), *pos);
  pos = list1.end();
  --pos;
  ASSERT_EQ(list1.back(), *pos);
  list1.clear();
  pos = list1.begin();
  ASSERT_EQ(list1.front(), *pos);
  ASSERT_EQ(list1.front(), list1.back());

  list<int> list2(4);
  ASSERT_EQ(list2.front(), 0);
  ASSERT_EQ(list2.back(), 0);

  list<double> list3{1.1, 4, 2, 5, 7, 13, 56, 11, 5914.09};
  ASSERT_EQ(list3.front(), 1.1);
  ASSERT_EQ(list3.back(), 5914.09);
}

// insert(), erase(), push's, pop's
TEST_F(test_s21_list, test_s21_list_insert_erase) {
  list<double> answer{1.1, 2024, 25.1, 9.6};
  list<double> answer1{1.1, 2024, 25.1};
  list<double> answer2{123.4, 1.1, 2024, 25.1};

  list<double> list1{1.1, 25.1};
  list<double>::iterator pos = list1.begin();
  list<double>::iterator pos1;
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
  list<int> list2;
  ASSERT_EQ(list2.empty(), CONTAINER_EMPTY);
  list2.push_back(100);
  ASSERT_EQ(list2.size(), 1);
  ASSERT_EQ(list2.empty(), CONTAINER_NOT_EMPTY);

  list2.pop_back();
  ASSERT_EQ(list2.empty(), CONTAINER_EMPTY);
}

// тест push_back/pop_back, доступ по индексу()
TEST_F(test_s21_list, test_s21_list_3) {
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
TEST_F(test_s21_list, test_s21_list_4) {
  list<int> list2;
  list2.push_back(-111);
  list2.push_back(101);
  list2.push_back(102);
  list2.push_back(103);
  list<int>::iterator iter = list2.begin();
  ASSERT_EQ(*iter, -111);

  ASSERT_EQ(*(++iter), 101);
  ASSERT_EQ(*(++iter), 102);
  ASSERT_EQ(*(++iter), 103);
  ASSERT_EQ(*(++iter), 0);

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
  list<int> list2(4);
  ASSERT_EQ(list2.size(), 4);
  list listcpy = std::move(list2);
  ASSERT_EQ(listcpy.size(), 4);
  ASSERT_EQ(list2.empty(), CONTAINER_EMPTY);

  list<int> list3{1, 4, 2, 5, 7, 13, 56, 11, 5914};
  ASSERT_EQ(list3.size(), 9);
}

// swap()
TEST_F(test_s21_list, test_s21_list_swap) {
  list<int> list1{1, 4, 2, 5, 7, 13, 56, 11, 5914};
  list<int> list2{1};

  list<int> answ1(list1);
  list<int> answ2(list2);
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
  list<int> list1{1, 4, 2, 5, 7, 13, 56, 11, 5914};
  list<int> list2{100};

  list<int> answ1{1, 2, 4, 5, 7, 11, 13, 56, 5914, 100};

  list1.merge(list2);

  ASSERT_EQ(list1 == answ1, SUCCESS);
  ASSERT_EQ(list2.size(), 0);
  ASSERT_EQ(list2.empty(), CONTAINER_EMPTY);
  list1.merge(list2);  // merge with empty-list2
  ASSERT_EQ(list1 == answ1, SUCCESS);
  ASSERT_EQ(list1.size(), 10);
  ASSERT_EQ(list2.empty(), CONTAINER_EMPTY);

  answ1.pop_back();
  list1.pop_back();

  list2.merge(list1);  // merge to empty-list2
  ASSERT_EQ(list2 == answ1, SUCCESS);
  ASSERT_EQ(list1.empty(), CONTAINER_EMPTY);

  list<double> list3;
  list<double> list4;
  list3.merge(list4);  // merge both empty-list
  ASSERT_EQ(list3 == list4, SUCCESS);
  ASSERT_EQ(list3.empty(), CONTAINER_EMPTY);
  ASSERT_EQ(list4.empty(), CONTAINER_EMPTY);
}

// splice()
TEST_F(test_s21_list, test_s21_list_splice) {
  list<int> answ1{1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11};
  list<int> list1{5, 6, 7, 8, 11};
  list<int> list2{1, 2, 3};
  list<int> list3{9, 10};
  list<int>::iterator iter;
  iter = list1.begin();

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
  list<int> answ1{11, 12, 13, 10, 1, 4, 2, 5, 7, 13, 56, 11, 5914};
  list<int> list1{4, 2, 5, 7, 13, 56, 11, 5914};

  list<int>::iterator iter = list1.begin();
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
  list<int> answ1{1, 2, 3, 4, 5};
  list<int> list1{1, 1, 1, 2, 2, 2, 3, 4, 5, 5, 5, 5, 5, 5};

  list1.unique();
  ASSERT_EQ(list1 == answ1, SUCCESS);

  list<int> list2;
  list2.unique();
  ASSERT_EQ(list2.empty(), CONTAINER_EMPTY);

  list2.push_back(150);
  list2.unique();
  list<int> answ2{150};

  ASSERT_EQ(list2.empty(), CONTAINER_NOT_EMPTY);
  ASSERT_EQ(list2 == answ2, SUCCESS);
}

// reverse()
TEST_F(test_s21_list, test_s21_list_reverse) {
  list<int> answ1{1, 2, 3, 4, 5};
  list<int> answ2;
  list<int> answ3{777};
  list<int> list1{5, 4, 3, 2, 1};

  list1.reverse();
  ASSERT_EQ(list1 == answ1, SUCCESS);

  list<int> list2;
  list2.reverse();
  ASSERT_EQ(list2 == answ2, SUCCESS);
  list2.push_back(777);
  list2.reverse();
  ASSERT_EQ(list2 == answ3, SUCCESS);
}

// sort()
TEST_F(test_s21_list, test_s21_list_sort) {
  list<int> answ1{1, 2, 3, 4, 5};
  list<int> list1{4, 3, 2, 1, 5};
  list<int> answ2{1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
  list<int> list2{5, 9, 4, 3, 6, 10, 2, 7, 1, 8};
  list<int> list3;
  list<int> list4{4};
  list<int> list5{3, 7, 8, 5, 2, 1, 9, 5, 4};
  list<int> answ5{1, 2, 3, 4, 5, 5, 7, 8, 9};
  list<int> list6{3, 7};
  list<int> answ6{3, 7};
  list<int> list7{1, 0};
  list<int> answ7{0, 1};

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
  ASSERT_EQ(list4(0), 4);
  ASSERT_EQ(list5 == answ5, SUCCESS);
  ASSERT_EQ(list6 == answ6, SUCCESS);
  ASSERT_EQ(list7 == answ7, SUCCESS);
}
