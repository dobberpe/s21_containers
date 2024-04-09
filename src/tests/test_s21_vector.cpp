#include "test_s21_containers.h"

#ifndef _SPCE_
#include <vector>
#define _SPCE_ std
#define _SPCE_ORIG_
#endif

class test_s21_vector : public testing::Test {
 public:
};

// тест конструкторов
TEST_F(test_s21_vector, test_vector_create) {
  _SPCE_::vector<int> vect1;
  ASSERT_EQ(vect1.empty(), CONTAINER_EMPTY);

  _SPCE_::vector<int> vect2(6);
  ASSERT_EQ(vect2.empty(), CONTAINER_NOT_EMPTY);
  ASSERT_EQ(vect2.size(), 6);
  ASSERT_EQ(vect2.capacity(), 6);
  try {
#ifndef _SPCE_ORIG_
    vect2.at(6);
#endif
  } catch (int error) {
    ASSERT_EQ(error, ERROR_OUT_OF_RANGE);
  }

  vect2.push_back(15);
  vect2.push_back(19);
  vect2.push_back(4);
  vect2.push_back(50);
  vect2.push_back(-4);

  ASSERT_EQ(vect2.empty(), CONTAINER_NOT_EMPTY);
  ASSERT_EQ(vect2.size(), 11);

  _SPCE_::vector v3(std::move(vect2));
  ASSERT_EQ(vect2.empty(), CONTAINER_EMPTY);
  ASSERT_EQ(v3.empty(), CONTAINER_NOT_EMPTY);
  v3.push_back(1000);
  ASSERT_EQ(v3.size(), 12);

  _SPCE_::vector<double> v5{1.1, 4, 2, 5, 7, 13, 56, 11, 5914.09};
  ASSERT_EQ(v5.empty(), CONTAINER_NOT_EMPTY);
  ASSERT_EQ(v5.size(), 9);
  ASSERT_DOUBLE_EQ(v5[0], 1.1);
  ASSERT_DOUBLE_EQ(v5[8], 5914.09);

  _SPCE_::vector v6 = std::move(v5);
  ASSERT_EQ(v5.empty(), CONTAINER_EMPTY);
  ASSERT_EQ(v6.size(), 9);
  ASSERT_DOUBLE_EQ(v6[0], 1.1);
  ASSERT_DOUBLE_EQ(v6[8], 5914.09);

  _SPCE_::vector<double> v7;
  v7 = std::move(v6);

  ASSERT_EQ(v6.empty(), CONTAINER_EMPTY);
  ASSERT_EQ(v7.size(), 9);
  ASSERT_DOUBLE_EQ(v7[0], 1.1);
  ASSERT_DOUBLE_EQ(v7[8], 5914.09);

  _SPCE_::vector v8 = std::move(v6);  // std::move empty-vector
  ASSERT_EQ(v8.empty(), CONTAINER_EMPTY);

  v8.push_back(5);
  ASSERT_EQ(v8.empty(), CONTAINER_NOT_EMPTY);
  ASSERT_EQ(v8[0], 5);
  v8[0] = 30;
  ASSERT_EQ(v8[0], 30);
  _SPCE_::vector v9(v8);  // copy

  v9.push_back(15);
  ASSERT_EQ(v9.empty(), CONTAINER_NOT_EMPTY);
  ASSERT_EQ(v9.size(), 2);
  ASSERT_EQ(v9[0], 30);
}

// // empty(), size(), clear();
TEST_F(test_s21_vector, test_vector_empty_size) {
  _SPCE_::vector<double> v0;
  ASSERT_EQ(v0.empty(), CONTAINER_EMPTY);

  _SPCE_::vector<int> v1(1);
  ASSERT_EQ(v1.empty(), CONTAINER_NOT_EMPTY);

  // for (int i = 0; i < 100; i++) v1[i] = i;
  v1.pop_back();
  ASSERT_EQ(v1.size(), 0);
  ASSERT_EQ(v1.capacity(), 1);
  ASSERT_EQ(v1.empty(), CONTAINER_EMPTY);

  for (int i = 0; i < 10000; i++) v1.push_back(i);
  ASSERT_EQ(v1.empty(), CONTAINER_NOT_EMPTY);
  ASSERT_EQ(v1.size(), 10000);

  v1.clear();
  ASSERT_EQ(v1.size(), 0);
  ASSERT_EQ(v1.empty(), CONTAINER_EMPTY);
  v1.clear();  // clear empty-vector, but capacity >0
  ASSERT_EQ(v1.empty(), CONTAINER_EMPTY);
}

// begin(), end(), front(), back()
TEST_F(test_s21_vector, test_vector_begin_end_front_back) {
  _SPCE_::vector<double> v1;
  v1.push_back(1.1);
  v1.push_back(-0.1);
  v1.push_back(25.1);
  ASSERT_DOUBLE_EQ(v1.front(), 1.1);
  _SPCE_::vector<double>::iterator pos = v1.end();
  --pos;
  ASSERT_DOUBLE_EQ(*pos, 25.1);
  ASSERT_DOUBLE_EQ(v1.back(), 25.1);
  v1.clear();
  pos = v1.begin();
  ASSERT_DOUBLE_EQ(v1.front(), *pos);

  _SPCE_::vector<int> v2(4);
  ASSERT_EQ(v2.front(), 0);
  ASSERT_EQ(v2.back(), 0);

  _SPCE_::vector<double> v3{1.1, 4, 2, 5, 7, 13, 56, 11, 5914.09};
  ASSERT_DOUBLE_EQ(v3.front(), 1.1);
  ASSERT_DOUBLE_EQ(v3.back(), 5914.09);
}

// insert(), erase(), push's, pop's
TEST_F(test_s21_vector, test_vector_insert_erase) {
  _SPCE_::vector<double> answer{1.1, 2024, 25.1, 9.6};
  _SPCE_::vector<double> answer1{1.1, 2024, 25.1};
  _SPCE_::vector<double> answer2{123.4, 1.1, 2024, 25.1};

  _SPCE_::vector<double> v1{1.1, 25.1};
  _SPCE_::vector<double>::iterator pos = v1.begin();
  _SPCE_::vector<double>::iterator pos1;
  ++pos;
  pos1 = v1.insert(pos, 2024);
  ASSERT_DOUBLE_EQ(v1[0], 1.1);
  ASSERT_DOUBLE_EQ(v1[1], 2024);
  ASSERT_DOUBLE_EQ(v1[2], 25.1);

  v1.push_back(9.6);

  ASSERT_EQ(v1 == answer, SUCCESS);
  ASSERT_EQ(v1[2], 25.1);

  v1.pop_back();
  ASSERT_EQ(v1 == answer1, SUCCESS);

  v1.erase(++(v1.begin()));
  ASSERT_DOUBLE_EQ(v1[0], 1.1);
  ASSERT_DOUBLE_EQ(v1[1], 25.1);
  v1.erase(v1.begin());
  ASSERT_DOUBLE_EQ(v1[0], 25.1);
  ASSERT_DOUBLE_EQ(v1.size(), 1);

  v1.pop_back();
  ASSERT_EQ(v1.size(), 0);
  v1.push_back(9.6);
  v1.pop_back();
  ASSERT_EQ(v1.size(), 0);
}

// тест конструктора по умолчанию, empty(), push_back/pop_back
TEST_F(test_s21_vector, test_vector_push_pop) {
  _SPCE_::vector<int> v2;
  ASSERT_EQ(v2.empty(), CONTAINER_EMPTY);
  v2.push_back(100);
  ASSERT_EQ(v2.size(), 1);
  ASSERT_EQ(v2.empty(), CONTAINER_NOT_EMPTY);
  ASSERT_EQ(v2[0], 100);

  v2.pop_back();
  ASSERT_EQ(v2.size(), 0);
}

// тест push_back/pop_back, доступ по индексу()
TEST_F(test_s21_vector, test_vector_index) {
  _SPCE_::vector<double> v1;
  v1.push_back(-20.4);
  ASSERT_EQ(v1.size(), 1);

  _SPCE_::vector<double>::iterator iter;
  iter = v1.begin();

  v1.push_back(1.5);
  v1.push_back(13514.9);
  ASSERT_EQ(v1.size(), 3);
  v1[0] = 20.4;
  ASSERT_DOUBLE_EQ(v1[0], 20.4);
  ASSERT_DOUBLE_EQ(v1[1], 1.5);
  ASSERT_DOUBLE_EQ(v1[2], 13514.9);

  v1.push_back(4);
  v1.push_back(50.7);
  v1.push_back(-4);
  ASSERT_EQ(v1.size(), 6);
  ASSERT_DOUBLE_EQ(v1[5], -4);

  v1.pop_back();
  ASSERT_EQ(v1.size(), 5);
  ASSERT_DOUBLE_EQ(v1[3], 4);
  ASSERT_DOUBLE_EQ(v1[4], 50.7);
}

// тест итераторов, push_back/pop_back
TEST_F(test_s21_vector, test_vector_iterator) {
  _SPCE_::vector<int> v2;
  v2.push_back(-111);
  v2.push_back(101);
  v2.push_back(102);
  v2.push_back(103);
  _SPCE_::vector<int>::iterator iter;
  iter = v2.begin();
  ASSERT_EQ(*iter, -111);
  ASSERT_EQ(*(++iter), 101);
  ASSERT_EQ(*(++iter), 102);
  ASSERT_EQ(*(++iter), 103);

  ASSERT_EQ(*iter, 103);
  ASSERT_EQ(*(--iter), 102);
  ASSERT_EQ(*(--iter), 101);
  ASSERT_EQ(*(--iter), -111);

  for (int i = 0; i < 4; i++) v2.pop_back();

  ASSERT_EQ(v2.size(), 0);
}

// постоянный итератор
TEST_F(test_s21_vector, test_vector_const_iterator) {
  _SPCE_::vector<int> v2;
  v2.push_back(-111);
  v2.push_back(101);
  v2.push_back(102);
  v2.push_back(103);
  _SPCE_::vector<int>::const_iterator iter = v2.begin();

  ASSERT_EQ(*iter, -111);
  ASSERT_EQ(*(++iter), 101);
  ASSERT_EQ(*(++iter), 102);
  ASSERT_EQ(*(++iter), 103);

  _SPCE_::vector<int>::const_iterator iter1(v2.end());
  --iter1;
  ASSERT_EQ(*iter1, 103);
  ASSERT_EQ(*(--iter1), 102);
  ASSERT_EQ(*(--iter1), 101);
  ASSERT_EQ(*(--iter1), -111);

  for (int i = 0; i < 4; i++) v2.pop_back();

  ASSERT_EQ(v2.size(), 0);
}

// swap()
TEST_F(test_s21_vector, test_vector_swap) {
  _SPCE_::vector<int> v1{1, 4, 2, 5, 7, 13, 56, 11, 5914};
  _SPCE_::vector<int> v2{1};

  _SPCE_::vector<int> answ1(v1);
  _SPCE_::vector<int> answ2(v2);
  v1.swap(v2);
  ASSERT_EQ(v1 == answ2, SUCCESS);
  ASSERT_EQ(v2 == answ1, SUCCESS);
  v2.swap(v1);
  ASSERT_EQ(v1 == answ1, SUCCESS);
  ASSERT_EQ(v2 == answ2, SUCCESS);
  v1.clear();
  v2.clear();
  v1.swap(v2);
  ASSERT_EQ(v2 == v1, SUCCESS);
}

// insert()
TEST_F(test_s21_vector, test_vector_insert) {
  _SPCE_::vector<int> answ1{11, 12, 13, 10, 1, 4, 2, 5, 7, 13, 56, 11, 5914};
  _SPCE_::vector<int> v1{4, 2, 5, 7, 13, 56, 11, 5914};
  _SPCE_::vector<int>::iterator iter = v1.begin();
  v1.insert(iter, 1);
  iter = v1.begin();
  v1.insert(iter, 10);
  iter = v1.begin();
  v1.insert(iter, 11);
  iter = v1.begin();
  v1.insert(++iter, 12);
  iter = v1.begin();
  ++iter;
  v1.insert(++iter, 13);

  iter = v1.begin();
  ASSERT_EQ(v1 == answ1, SUCCESS);
}

// shrink_to_fit()
TEST_F(test_s21_vector, test_vector_shrink_to_fit) {
  _SPCE_::vector<int> v1{11, 12, 13, 14};
  _SPCE_::vector<int> answ1{11, 12, 13, 14};
  v1.shrink_to_fit();
  ASSERT_EQ(v1 == answ1, SUCCESS);
  ASSERT_EQ(v1.capacity(), 4);
  v1.pop_back();
  v1.pop_back();
  ASSERT_EQ(v1.capacity(), 4);
  v1.shrink_to_fit();
  ASSERT_EQ(v1.capacity(), 2);
  v1.pop_back();
  v1.pop_back();
  ASSERT_EQ(v1.size(), 0);
  ASSERT_EQ(v1.capacity(), 2);
  v1.shrink_to_fit();  // shrink empty-vector
  ASSERT_EQ(v1.size(), 0);
  ASSERT_EQ(v1.capacity(), 0);
  ASSERT_EQ(v1.data(), nullptr);
  v1.shrink_to_fit();  // shrink empty-vector one more
  ASSERT_EQ(v1.size(), 0);
  ASSERT_EQ(v1.capacity(), 0);
  ASSERT_EQ(v1.data(), nullptr);

  v1.push_back(4);
  ASSERT_EQ(v1.size(), 1);
  ASSERT_EQ(v1.capacity(), 1);
}

#ifndef _SPCE_ORIG_

// insert_many()
TEST_F(test_s21_vector, test_s21_vector_insert_many) {
  _SPCE_::vector<int> answ1{1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13};
  _SPCE_::vector<int> vector1{5, 6, 7, 8, 11};
  _SPCE_::vector<int>::const_iterator iter = vector1.begin();

  vector1.insert_many(iter, 1, 2, 3, 4);
  iter = vector1.end();
  --iter;

  vector1.insert_many(iter, 9, 10);
  iter = vector1.end();
  vector1.insert_many(iter, 12, 13);

  vector1.insert_many(iter);  // insert null-elements
  ASSERT_EQ(vector1 == answ1, SUCCESS);
}

// insert_many_back()
TEST_F(test_s21_vector, test_s21_vector_insert_back) {
  _SPCE_::vector<int> answ1{1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11};
  _SPCE_::vector<int> vector1{1, 2};

  vector1.insert_many_back(3);
  vector1.insert_many_back(4, 5, 6, 7, 8);
  vector1.insert_many_back(9, 10, 11);
  vector1.insert_many_back();

  ASSERT_EQ(vector1 == answ1, SUCCESS);
}

#endif