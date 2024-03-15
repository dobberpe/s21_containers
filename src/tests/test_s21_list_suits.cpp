#include "test_s21_list.h"

class test_s21_list : public testing::Test {
 public:
};

TEST_F(test_s21_list, test_s21_list_first_1) {
  list list1{-20};

  ASSERT_EQ(list1.list_empty(), CONTAINER_NOT_EMPTY);

  list1.add_elem(15);
  list1.add_elem(19);
  list1.add_elem(4);
  list1.add_elem(50.7);
  list1.add_elem(-4);

  ASSERT_EQ(list1.list_count(), 6);

  list list2(list1);
  ASSERT_EQ(list2.list_empty(), CONTAINER_NOT_EMPTY);

  list list3(move(list2));
  ASSERT_EQ(list3.list_empty(), CONTAINER_NOT_EMPTY);
  ASSERT_EQ(list3.list_count(), 6);

}

TEST_F(test_s21_list, test_s21_list_first_2) {
  list<int> list2;
  ASSERT_EQ(list2.list_empty(), CONTAINER_EMPTY);
  list2.add_elem(100);
  ASSERT_EQ(list2.list_count(), 1);

  list2.remove_elem();
  ASSERT_EQ(list2.list_empty(), CONTAINER_EMPTY);
}


TEST_F(test_s21_list, test_s21_list_first_3) {
  list list1{-20.4};
  ASSERT_EQ(list1.list_count(), 1);

  list<double>::iterator iter;
  iter = list1.begin();

  list1.add_elem(1.5);
  list1.add_elem(13514.9);
  ASSERT_EQ(list1.list_count(), 3);
  ASSERT_DOUBLE_EQ(list1(0), -20.4);
  ASSERT_DOUBLE_EQ(list1(1), 1.5);
  ASSERT_DOUBLE_EQ(list1(2), 13514.9);

  list1.add_elem(4);
  list1.add_elem(50.7);
  list1.add_elem(-4);
  ASSERT_EQ(list1.list_count(), 6);
  ASSERT_DOUBLE_EQ(list1(5), -4);

  list1.remove_elem();
  ASSERT_EQ(list1.list_count(), 5);
  ASSERT_DOUBLE_EQ(list1(3), 4);
  ASSERT_DOUBLE_EQ(list1(4), 50.7);
}
