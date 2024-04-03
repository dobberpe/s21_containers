#include "test_s21_containers.h"

// #define _SPCE_ s21

#ifndef _SPCE_
#include <vector>
#define _SPCE_ std
#endif

class test_vector : public testing::Test {
 public:
};

TEST_F(test_vector, test_vector_origin) {
  //  std::vector<int> vect1{1};
  // std::vector<int>::const_iterator iter1 = vect1.begin();
  // *iter1 = 9;

  //  _SPCE_::vector<int> vect2{1};
  // _SPCE_::vector<int>::const_iterator iter2;
  // iter2 = vect2.begin();
  // *iter2 = 9;

  // printf("size=%d=cap=%d\n", *iter, vect1.back());
  // vect1.push_back(3);
  // vect1.push_back(3);
  // vect1.push_back(3);
  // vect1.push_back(3);
  // vect1.push_back(3);
  // vect1.pop_back();
  // printf("size=%d=cap=%d\n", vect1.front(), vect1.back());

  // for (int i = 0; i < 50; i++) {vect1.push_back(i);
  // printf("size=%d=cap=%d\n", vect1.size(), vect1.capacity());
  // }
  /* std::vector<int> vect1;
   std::vector<int>::iterator iter;
   printf("%ld=base=\n", iter.base());
   ++iter;
   vect1.push_back(3);
       printf("%d=empty=\n", vect1.empty());

     // printf("%d=[0]=\n", vect1[0]);
     printf("%d=siz=\n", vect1.size());
   printf("%d=base=\n", iter.base());
   vect1.pop_back();
     printf("%d=base=\n", iter.base());

     printf("%d=[0]=\n", vect1[0]);
     printf("%d=empty=\n", vect1.empty());
 */
}

// тест конструкторов
TEST_F(test_vector, test_vector_create) {
  _SPCE_::vector<int> vect1;
  ASSERT_EQ(vect1.empty(), CONTAINER_EMPTY);

  _SPCE_::vector<int> vect2(6);
  ASSERT_EQ(vect2.empty(), CONTAINER_NOT_EMPTY);
  ASSERT_EQ(vect2.size(), 6);
  ASSERT_EQ(vect2.capacity(), 6);
  try {
    vect2.at(1);
  } catch (int erorr) {
    ASSERT_EQ(erorr, ERROR_OUT_OF_RANGE);
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
  ASSERT_EQ(v5[0], 1.1);
  ASSERT_EQ(v5[8], 5914.09);

  _SPCE_::vector v6 = std::move(v5);
  ASSERT_EQ(v5.empty(), CONTAINER_EMPTY);
  ASSERT_EQ(v6.size(), 9);
  ASSERT_EQ(v6[0], 1.1);
  ASSERT_EQ(v6[8], 5914.09);

  _SPCE_::vector<double> v7;
  v7 = std::move(v6);
  ASSERT_EQ(v6.empty(), CONTAINER_EMPTY);
  ASSERT_EQ(v7.size(), 9);
  ASSERT_EQ(v7[0], 1.1);
  ASSERT_EQ(v7[8], 5914.09);

  _SPCE_::vector v8 = std::move(v6);  // std::move empty-list
  ASSERT_EQ(v8.empty(), CONTAINER_EMPTY);

  v8.push_back(5);
  ASSERT_EQ(v8.empty(), CONTAINER_NOT_EMPTY);
  ASSERT_EQ(v8[0], 5);
  v8[0] = 30;

  _SPCE_::vector v9(v8);  // copy

  v9.push_back(15);
  ASSERT_EQ(v9.empty(), CONTAINER_NOT_EMPTY);
  ASSERT_EQ(v9.size(), 2);
  ASSERT_EQ(v9[0], 30);
}

// // empty(), size(), clear();
TEST_F(test_vector, test_vector_empty_size) {
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
  v1.clear();  // clear empty-list, but capacity >0
  ASSERT_EQ(v1.empty(), CONTAINER_EMPTY);
}

// begin(), end(), front(), back()
TEST_F(test_vector, test_vector_begin_end_front_back) {
  _SPCE_::vector<double> v1;
  v1.push_back(1.1);
  v1.push_back(-0.1);
  v1.push_back(25.1);
  _SPCE_::vector<double>::iterator pos = v1.begin();
  ASSERT_EQ(v1.front(), 1.1);
  pos = v1.end();
  --pos;
  ASSERT_EQ(v1.back(), 25.1);
  v1.clear();
  pos = v1.begin();
  ASSERT_EQ(v1.front(), *pos);

  _SPCE_::vector<int> v2(4);
  ASSERT_EQ(v2.front(), 0);
  ASSERT_EQ(v2.back(), 0);

  _SPCE_::vector<double> list3{1.1, 4, 2, 5, 7, 13, 56, 11, 5914.09};
  ASSERT_EQ(list3.front(), 1.1);
  ASSERT_EQ(list3.back(), 5914.09);
}

// insert(), erase(), push's, pop's
TEST_F(test_vector, test_vector_insert_erase) {
  _SPCE_::vector<double> answer{1.1, 2024, 25.1, 9.6};
  _SPCE_::vector<double> answer1{1.1, 2024, 25.1};
  _SPCE_::vector<double> answer2{123.4, 1.1, 2024, 25.1};

  _SPCE_::vector<double> v1{1.1, 25.1};
  _SPCE_::vector<double>::iterator pos = v1.begin();
  _SPCE_::vector<double>::iterator pos1;
  ++pos;
  pos1 = v1.insert(pos, 2024);
  ASSERT_EQ(v1[0], 1.1);
  ASSERT_EQ(v1[1], 2024);
  ASSERT_EQ(v1[2], 25.1);

  v1.push_back(9.6);

  ASSERT_EQ(v1 == answer, SUCCESS);
  ASSERT_EQ(v1[2], 25.1);

  v1.pop_back();
  ASSERT_EQ(v1 == answer1, SUCCESS);

  v1.erase(++(v1.begin()));
  ASSERT_EQ(v1[0], 1.1);
  ASSERT_EQ(v1[1], 25.1);
  v1.erase(v1.begin());
  ASSERT_EQ(v1[0], 25.1);
  ASSERT_EQ(v1.size(), 1);

  v1.pop_back();
  ASSERT_EQ(v1.size(), 0);
  v1.push_back(9.6);
  v1.pop_back();
  ASSERT_EQ(v1.size(), 0);
}

// тест конструктора по умолчанию, empty(), push_back/pop_back
TEST_F(test_vector, test_vector_2) {
  _SPCE_::vector<int> v2;
  ASSERT_EQ(v2.empty(), CONTAINER_EMPTY);
  v2.push_back(100);
  ASSERT_EQ(v2.size(), 1);
  ASSERT_EQ(v2.empty(), CONTAINER_NOT_EMPTY);

  v2.pop_back();
  ASSERT_EQ(v2.size(), 0);
}

// тест push_back/pop_back, доступ по индексу()
TEST_F(test_vector, test_vector_3) {
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
TEST_F(test_vector, test_vector_4) {
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

// тест конструктор перемещения и параметризированного конструктора
// конструктор "со списком" и опрератором присваивания
TEST_F(test_vector, test_vector_5) {
  _SPCE_::vector<int> v2(4);
  ASSERT_EQ(v2.capacity(), 4);
  _SPCE_::vector listcpy = std::move(v2);
  ASSERT_EQ(listcpy.capacity(), 4);
  ASSERT_EQ(v2.empty(), CONTAINER_EMPTY);

  _SPCE_::vector<int> list3{1, 4, 2, 5, 7, 13, 56, 11, 5914};
  ASSERT_EQ(list3.size(), 9);
}

// swap()
TEST_F(test_vector, test_vector_swap) {
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
TEST_F(test_vector, test_vector_insert) {
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
TEST_F(test_vector, test_vector_shrink_to_fit) {
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
  v1.shrink_to_fit(); // shrink empty-list
  ASSERT_EQ(v1.size(), 0);
  ASSERT_EQ(v1.capacity(), 0);
  ASSERT_EQ(v1.data(), nullptr);
  v1.shrink_to_fit(); // shrink empty-list one more
  ASSERT_EQ(v1.size(), 0);
  ASSERT_EQ(v1.capacity(), 0);
  ASSERT_EQ(v1.data(), nullptr);

  v1.push_back(4);
  ASSERT_EQ(v1.size(), 1);
  ASSERT_EQ(v1.capacity(), 1);
}
