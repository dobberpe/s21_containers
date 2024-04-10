#include "test_s21_containers.h"

#ifndef _SPCE_
#include <array>
#define _SPCE_ std
#define _SPCE_ORIG_
#endif

class test_array : public testing::Test {
 public:
};

// тест конструкторов
TEST_F(test_array, test_array_create) {
  _SPCE_::array<int, 0> arr1;
  EXPECT_EQ(arr1.empty(), CONTAINER_EMPTY);

  _SPCE_::array<int, 6> arr2;
  EXPECT_EQ(arr2.empty(), CONTAINER_NOT_EMPTY);
#ifndef _SPCE_ORIG_
  try {
    arr2.at(6);
  } catch (int erorr) {
    EXPECT_EQ(erorr, ERROR_OUT_OF_RANGE);
  }
#endif

  arr2[0] = 15;
  arr2[1] = 150;
  arr2[2] = 1500;
  arr2[3] = 15000;

  EXPECT_EQ(arr2.size(), 6);

  _SPCE_::array a3(std::move(arr2));

  EXPECT_EQ(arr2.empty(), CONTAINER_NOT_EMPTY);
  EXPECT_EQ(a3.empty(), CONTAINER_NOT_EMPTY);
  a3[4] = 1000;
  EXPECT_EQ(a3[0], 15);
  EXPECT_EQ(a3.size(), 6);

  _SPCE_::array<double, 9> a5{1.1, 4, 2, 5, 7, 13, 56, 11, 5914.09};
  EXPECT_EQ(a5.empty(), CONTAINER_NOT_EMPTY);
  EXPECT_EQ(a5.size(), 9);
  EXPECT_DOUBLE_EQ(a5.front(), 1.1);
  EXPECT_DOUBLE_EQ(a5[8], 5914.09);

  _SPCE_::array a6 = std::move(a5);
  EXPECT_EQ(a5.empty(), CONTAINER_NOT_EMPTY);
  EXPECT_DOUBLE_EQ(a5.front(), 1.1);
  EXPECT_EQ(a5.size(), 9);
  EXPECT_EQ(a6.size(), 9);
  EXPECT_DOUBLE_EQ(a6[0], 1.1);
  EXPECT_DOUBLE_EQ(a6[8], 5914.09);

  _SPCE_::array a7 = std::move(a6);
  EXPECT_EQ(a6.empty(), CONTAINER_NOT_EMPTY);
  EXPECT_EQ(a7.size(), 9);
  EXPECT_DOUBLE_EQ(a7[0], 1.1);
  EXPECT_DOUBLE_EQ(a7[8], 5914.09);

  _SPCE_::array a8 = std::move(a6);  // std::move empty-list

  EXPECT_EQ(a8.empty(), CONTAINER_NOT_EMPTY);

  _SPCE_::array a9(a7);  // copy

  EXPECT_EQ(a9.empty(), CONTAINER_NOT_EMPTY);
  EXPECT_EQ(a9.size(), 9);
  EXPECT_DOUBLE_EQ(a9[0], 1.1);

  // тест конструктор перемещения и параметризированного конструктора
  // конструктор "со списком" и опрератором присваивания

  _SPCE_::array<int, 4> a2;
  _SPCE_::array listcpy = std::move(a2);
  EXPECT_EQ(listcpy.size(), 4);
  EXPECT_EQ(a2.size(), 4);

  _SPCE_::array<int, 9> list3{1, 4, 2, 5, 7, 13, 56, 11, 5914};
  EXPECT_EQ(list3.size(), 9);
}

// empty(), size(), доступ по индексу[]
TEST_F(test_array, test_array_empty_size) {
  _SPCE_::array<double, 0> a0;
  EXPECT_EQ(a0.empty(), CONTAINER_EMPTY);

  _SPCE_::array<int, 1> a00;
  EXPECT_EQ(a00.empty(), CONTAINER_NOT_EMPTY);
  EXPECT_EQ(a00.size(), 1);

  _SPCE_::array<int, 10000> a1;
  for (int i = 0; i < 10000; i++) a1[i] = i;
  EXPECT_EQ(a1.empty(), CONTAINER_NOT_EMPTY);
  EXPECT_EQ(a1.size(), 10000);
  for (int i = 0; i < 10000; i++) EXPECT_EQ(a1[i], i);

#ifndef _SPCE_ORIG_
  EXPECT_EQ(a1.at(0), 0);
  EXPECT_EQ(a1.at(9999), 9999);
  try {
    a1.at(10000);
  } catch (int erorr) {
    EXPECT_EQ(erorr, ERROR_OUT_OF_RANGE);
  }
#endif
}

// begin(), end(), front(), back()
TEST_F(test_array, test_array_begin_end_front_back) {
  _SPCE_::array<double, 3> a1{0};
  a1[0] = 1.1;
  a1[1] = -0.1;
  a1[2] = 25.1;
  EXPECT_EQ(a1.front(), 1.1);
  EXPECT_EQ(a1.back(), 25.1);

  _SPCE_::array<double>::iterator pos = a1.begin();
  pos = a1.begin();
  EXPECT_EQ(a1.front(), *pos);
  pos = a1.end();
  --pos;
  EXPECT_EQ(a1.back(), *pos);

  _SPCE_::array<int, 4> a2{0, 0, 0, 0};
  EXPECT_EQ(a2.front(), 0);
  EXPECT_EQ(a2.back(), 0);

  _SPCE_::array<double, 9> list3{1.1, 4, 2, 5, 7, 13, 56, 11, 5914.09};
  EXPECT_DOUBLE_EQ(list3.front(), 1.1);
  EXPECT_DOUBLE_EQ(list3.back(), 5914.09);

  _SPCE_::array<double, 9> a4;

  EXPECT_DOUBLE_EQ(a4.back(), 0);
}

// тест итераторa
TEST_F(test_array, test_array_iterator) {
  _SPCE_::array<int, 4> a2;
  _SPCE_::array<int, 0>::iterator iter = a2.begin();
  _SPCE_::array<int, 0>::const_iterator iter1 = a2.end();
  EXPECT_EQ(iter == iter1, FAILURE);
  EXPECT_EQ(iter != iter1, SUCCESS);

  *iter = -111;
  a2[1] = 101;
  a2[2] = 102;
  a2[3] = 103;
  EXPECT_EQ(*iter, -111);
  EXPECT_EQ(*(++iter), 101);
  EXPECT_EQ(*(++iter), 102);
  EXPECT_EQ(*(++iter), 103);

  EXPECT_EQ(*iter, 103);
  EXPECT_EQ(*(--iter), 102);
  EXPECT_EQ(*(--iter), 101);
  EXPECT_EQ(*(--iter), -111);

  EXPECT_EQ(a2.size(), 4);
}

// тест CONST итераторa
TEST_F(test_array, test_array_const_iterator) {
  _SPCE_::array<int, 4> a2;
  _SPCE_::array<int, 0>::const_iterator iter = a2.begin();
  _SPCE_::array<int, 0>::const_iterator iter1 = a2.end();
  EXPECT_EQ(iter == iter1, FAILURE);
  EXPECT_EQ(iter != iter1, SUCCESS);

  a2[0] = -111;
  a2[1] = 101;
  a2[2] = 102;
  a2[3] = 103;

  EXPECT_EQ(*iter, -111);
  EXPECT_EQ(*(++iter), 101);
  EXPECT_EQ(*(++iter), 102);
  EXPECT_EQ(*(++iter), 103);

  EXPECT_EQ(*iter, 103);
  EXPECT_EQ(*(--iter), 102);
  EXPECT_EQ(*(--iter), 101);
  EXPECT_EQ(*(--iter), -111);

  EXPECT_EQ(a2.size(), 4);
}

// swap()
TEST_F(test_array, test_array_swap) {
  _SPCE_::array<int, 9> a1{1, 4, 2, 5, 7, 13, 56, 11, 5914};
  _SPCE_::array<int, 9> a2{1, 2, 3, 4, 5, 6, 7, 8, 9};

  _SPCE_::array answ1(a1);
  _SPCE_::array answ2(a2);
  a1.swap(a2);
  EXPECT_EQ(a1 == answ2, SUCCESS);
  EXPECT_EQ(a2 == answ1, SUCCESS);
  a2.swap(a1);
  EXPECT_EQ(a1 == answ1, SUCCESS);
  EXPECT_EQ(a2 == answ2, SUCCESS);
}

// fill()
TEST_F(test_array, test_array_fill) {
  _SPCE_::array<int, 9> a1{1, 4, 2, 5, 7, 13, 56, 11, 5914};
  _SPCE_::array<double, 3> a2{1, 2, 3};

  _SPCE_::array answ1(a1);
  _SPCE_::array answ2(a2);
  a1.fill(10);
  for (std::size_t i = 0; i < a1.size(); i++) EXPECT_EQ(a1[i], 10);

  a1.fill(100);
  for (std::size_t i = 0; i < a1.size(); i++) EXPECT_EQ(a1[i], 100);

  a2.fill(-3.14);
  for (std::size_t i = 0; i < a2.size(); i++) EXPECT_DOUBLE_EQ(a2[i], -3.14);
}
