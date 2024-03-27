#include "test_s21_containers.h"

using namespace s21;

class test_s21_list : public testing::Test {
 public:
};

// max_size
TEST_F(test_s21_list, test_s21_list_max_size) {
  // printf("%ld\n",list_orig.max_size());
}

TEST_F(test_s21_list, test_s21_list_create) {
  s21::List<int> list1;
  ASSERT_EQ(list1.empty(), CONTAINER_EMPTY);
  s21::List list11(std::move(list1));
  ASSERT_EQ(list11.empty(), CONTAINER_EMPTY);
  ASSERT_EQ(list1.empty(), CONTAINER_EMPTY);

  s21::List<int> list2(1);
  ASSERT_EQ(list2.empty(), CONTAINER_NOT_EMPTY);
  list2.push_back(15);
  list2.push_back(19);
  list2.push_back(4);
  list2.push_back(50);
  list2.push_back(-4);
  ASSERT_EQ(list2.empty(), CONTAINER_NOT_EMPTY);
  ASSERT_EQ(list2.size(), 6);

  s21::List list3(list2);
  ASSERT_EQ(list3.empty(), CONTAINER_NOT_EMPTY);
  ASSERT_EQ(list3.size(), 6);

  s21::List list4(std::move(list3));
  ASSERT_EQ(list4.empty(), CONTAINER_NOT_EMPTY);
  list4.push_back(1000);
  ASSERT_EQ(list4.size(), 7);

  s21::List<double> list5{1.1, 4, 2, 5, 7, 13, 56, 11, 5914.09};
  ASSERT_EQ(list5.empty(), CONTAINER_NOT_EMPTY);
  ASSERT_EQ(list5.size(), 9);
  ASSERT_EQ(list5(0), 1.1);
  ASSERT_EQ(list5(8), 5914.09);

  s21::List list6 = std::move(list5);
  ASSERT_EQ(list5.empty(), CONTAINER_EMPTY);
  ASSERT_EQ(list6.size(), 9);
  ASSERT_EQ(list6(0), 1.1);
  ASSERT_EQ(list6(8), 5914.09);

  s21::List<double> list7;
  list7 = std::move(list6);
  ASSERT_EQ(list6.empty(), CONTAINER_EMPTY);
  ASSERT_EQ(list7.size(), 9);
  ASSERT_EQ(list7(0), 1.1);
  ASSERT_EQ(list7(8), 5914.09);

  s21::List list8 = std::move(list11);  // move empty-List
  ASSERT_EQ(list8.empty(), CONTAINER_EMPTY);

  list8.push_back(5);
  ASSERT_EQ(list8.empty(), CONTAINER_NOT_EMPTY);
  ASSERT_EQ(list8(0), 5);

  ASSERT_EQ(list11.empty(), CONTAINER_EMPTY);
  s21::List list9(std::move(list11));  // move empty-List
  ASSERT_EQ(list9.empty(), CONTAINER_EMPTY);
  ASSERT_EQ(list11.empty(), CONTAINER_EMPTY);

  list9.push_back(10);
  ASSERT_EQ(list9.size(), 1);
}

// empty(), size(), clear();
TEST_F(test_s21_list, test_s21_list_empty_size) {
  List<double> list0;
  ASSERT_EQ(list0.empty(), CONTAINER_EMPTY);

  List<int> list1(1);
  ASSERT_EQ(list1.empty(), CONTAINER_NOT_EMPTY);

  for (size_t i = 0; i < 100; i++) list1(i) = i;
  list1.pop_back();
  ASSERT_EQ(list1.empty(), CONTAINER_EMPTY);
  ASSERT_EQ(list1.size(), 0);

  // 384307168202282325
  // for (int i = 0; i < 38430716820228232; i++) list1.push_back(i);
  // ASSERT_EQ(list1.empty(), CONTAINER_NOT_EMPTY);
  // ASSERT_EQ(list1.size(), 10000);
  // List<int> list_my(100000000);
  // ASSERT_EQ(list_my.size(), 100000000);

  // List<int> list_origin(100000000);
  // ASSERT_EQ(list_origin.size(), 100000000);

  list1.clear();
  ASSERT_EQ(list1.empty(), CONTAINER_EMPTY);
  list1.clear();  // clear empty-List
  ASSERT_EQ(list1.empty(), CONTAINER_EMPTY);

  list1.pop_back();  // del from empty-List
  ASSERT_EQ(list1.empty(), CONTAINER_EMPTY);
}

// begin(), end(), front(), back()
TEST_F(test_s21_list, test_s21_list_begin_end_front_back) {
  List<double> list1;
  list1.push_back(1.1);
  list1.push_back(-0.1);
  list1.push_back(25.1);
  List<double>::iterator pos = list1.begin();
  ASSERT_EQ(list1.front(), *pos);
  pos = list1.end();
  --pos;
  ASSERT_EQ(list1.back(), *pos);
  list1.clear();
  pos = list1.begin();
  ASSERT_EQ(list1.front(), *pos);
  ASSERT_EQ(list1.front(), list1.back());

  List<int> list2(4);
  ASSERT_EQ(list2.front(), 0);
  ASSERT_EQ(list2.back(), 0);

  List<double> list3{1.1, 4, 2, 5, 7, 13, 56, 11, 5914.09};
  ASSERT_EQ(list3.front(), 1.1);
  ASSERT_EQ(list3.back(), 5914.09);
}

// insert(), erase(), push's, pop's
TEST_F(test_s21_list, test_s21_list_insert_erase) {
  List<double> answer{1.1, 2024, 25.1, 9.6};
  List<double> answer1{1.1, 2024, 25.1};
  List<double> answer2{123.4, 1.1, 2024, 25.1};

  List<double> list1{1.1, 25.1};
  List<double>::iterator pos = list1.begin();
  List<double>::iterator pos1;
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
  List<int> list2;
  ASSERT_EQ(list2.empty(), CONTAINER_EMPTY);
  list2.push_back(100);
  ASSERT_EQ(list2.size(), 1);
  ASSERT_EQ(list2.empty(), CONTAINER_NOT_EMPTY);

  list2.pop_back();
  ASSERT_EQ(list2.empty(), CONTAINER_EMPTY);
}

// тест push_back/pop_back, доступ по индексу()
TEST_F(test_s21_list, test_s21_list_3) {
  List<double> list1;
  list1.push_back(-20.4);
  ASSERT_EQ(list1.size(), 1);

  List<double>::iterator iter;
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
  List<int> list2;
  list2.push_back(-111);
  list2.push_back(101);
  list2.push_back(102);
  list2.push_back(103);
  List<int>::iterator iter = list2.begin();
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
  List<int> list2(4);
  ASSERT_EQ(list2.size(), 4);
  List listcpy = std::move(list2);
  ASSERT_EQ(listcpy.size(), 4);
  ASSERT_EQ(list2.empty(), CONTAINER_EMPTY);

  List<int> list3{1, 4, 2, 5, 7, 13, 56, 11, 5914};
  ASSERT_EQ(list3.size(), 9);
}

// swap()
TEST_F(test_s21_list, test_s21_list_swap) {
  List<int> list1{1, 4, 2, 5, 7, 13, 56, 11, 5914};
  List<int> list2{1};

  List<int> answ1(list1);
  List<int> answ2(list2);
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
  List<int> list1{1, 4, 2, 5, 7, 13, 56, 11, 5914};
  List<int> list2{100};

  List<int> answ1{1, 2, 4, 5, 7, 11, 13, 56, 5914, 100};

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

  List<double> list3;
  List<double> list4;
  list3.merge(list4);  // merge both empty-List
  ASSERT_EQ(list3 == list4, SUCCESS);
  ASSERT_EQ(list3.empty(), CONTAINER_EMPTY);
  ASSERT_EQ(list4.empty(), CONTAINER_EMPTY);
}

// splice()
TEST_F(test_s21_list, test_s21_list_splice) {
  List<int> answ1{1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11};
  List<int> list1{5, 6, 7, 8, 11};
  List<int> list2{1, 2, 3};
  List<int> list3{9, 10};
  List<int>::iterator iter;
  iter = list1.begin();

  list1.splice(iter, list2);
  list1.insert(iter, 4);

  iter = list1.end();
  list1.splice(--iter, list3);

  ASSERT_EQ(list1 == answ1, SUCCESS);
  ASSERT_EQ(list2.empty(), CONTAINER_EMPTY);

  iter = list2.end();
  list2.splice(iter, list1);  // splice to empty-List
  ASSERT_EQ(list2 == answ1, SUCCESS);

  list2.splice(iter = list2.begin(), list1);  // splice empty-List
  ASSERT_EQ(list2 == answ1, SUCCESS);
}

// insert()
TEST_F(test_s21_list, test_s21_list_insert) {
  List<int> answ1{11, 12, 13, 10, 1, 4, 2, 5, 7, 13, 56, 11, 5914};
  List<int> list1{4, 2, 5, 7, 13, 56, 11, 5914};

  List<int>::iterator iter = list1.begin();
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
  List<int> answ1{1, 2, 3, 4, 5};
  List<int> list1{1, 1, 1, 2, 2, 2, 3, 4, 5, 5, 5, 5, 5, 5};

  list1.unique();
  ASSERT_EQ(list1 == answ1, SUCCESS);

  List<int> list2;
  list2.unique();
  ASSERT_EQ(list2.empty(), CONTAINER_EMPTY);

  list2.push_back(150);
  list2.unique();
  List<int> answ2{150};

  ASSERT_EQ(list2.empty(), CONTAINER_NOT_EMPTY);
  ASSERT_EQ(list2 == answ2, SUCCESS);
}

// reverse()
TEST_F(test_s21_list, test_s21_list_reverse) {
  List<int> answ1{1, 2, 3, 4, 5};
  List<int> answ2;
  List<int> answ3{777};
  List<int> list1{5, 4, 3, 2, 1};

  list1.reverse();
  ASSERT_EQ(list1 == answ1, SUCCESS);

  List<int> list2;
  list2.reverse();
  ASSERT_EQ(list2 == answ2, SUCCESS);
  list2.push_back(777);
  list2.reverse();
  ASSERT_EQ(list2 == answ3, SUCCESS);
}

// sort()
TEST_F(test_s21_list, test_s21_list_sort) {
  List<int> answ1{1, 2, 3, 4, 5};
  List<int> list1{4, 3, 2, 1, 5};
  List<int> answ2{1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
  List<int> list2{5, 9, 4, 3, 6, 10, 2, 7, 1, 8};
  List<int> list3;
  List<int> list4{4};
  List<int> list5{3, 7, 8, 5, 2, 1, 9, 5, 4};
  List<int> answ5{1, 2, 3, 4, 5, 5, 7, 8, 9};
  List<int> list6{3, 7};
  List<int> answ6{3, 7};
  List<int> list7{1, 0};
  List<int> answ7{0, 1};

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
