#include <iterator>

#include "test_s21_containers.h"

using namespace s21;

TEST(msTest, InsertionAndCount) {
  multiset<int> ms;
  ms.insert(1);
  ms.insert(2);
  ms.insert(2);
  ms.insert(3);
  ms.insert(3);
  ms.insert(3);

  EXPECT_EQ(6, ms.size());

  EXPECT_TRUE(ms.contains(1));
  EXPECT_TRUE(ms.contains(2));
  EXPECT_TRUE(ms.contains(3));
}

TEST(msTest, Iteration) {
  multiset<int> ms;
  ms.insert(1);
  ms.insert(2);
  ms.insert(-11);
  ms.insert(-11);
  ms.insert(-11);
  ms.insert(2);
  ms.insert(3);
  ms.insert(3);
  ms.insert(3);
  int count_1 = 0, count_2 = 0, count_3 = 0;
  for (auto it = ms.begin(); it != ms.end(); ++it) {
    if (*it == 1)
      count_1++;
    else if (*it == 2)
      count_2++;
    else if (*it == 3)
      count_3++;
  }

  EXPECT_EQ(1, count_1);
  EXPECT_EQ(2, count_2);
  EXPECT_EQ(3, count_3);
}

TEST(msTest, LowerBound) {
  multiset<int> ms{1, 2, 2, 3, 3, 3, 4, 5};

  // Lower bound of 2 should point to the first occurrence of 2
  auto it = ms.lower_bound(2);
  EXPECT_EQ(*it, 2);

  // Lower bound of 3 should point to the first occurrence of 3
  it = ms.lower_bound(3);
  EXPECT_EQ(*it, 3);
}

TEST(msTest, UpperBound) {
  multiset<int> ms{1, 2, 2, 3, 3, 3, 4, 5};

  // Upper bound of 2 should point to the first element after the last
  // occurrence of 2
  auto it = ms.upper_bound(2);
  EXPECT_EQ(*it, 3);

  // Upper bound of 3 should point to the first element after the last
  // occurrence of 3
  it = ms.upper_bound(3);
  EXPECT_EQ(*it, 4);
}

TEST(msTest, EqualRange) {
  multiset<int> ms{1, 2, 2, 3, 3, 3, 4, 5};

  // Equal range of 2 should cover all occurrences of 2
  auto range = ms.equal_range(2);
  auto it = range.first;
  int count = 0;
  while (it != range.second) {
    ++count;
    EXPECT_EQ(*it, 2);
    ++it;
  }
  EXPECT_EQ(count, 2);

  // Equal range of 3 should cover all occurrences of 3
  range = ms.equal_range(3);
  it = range.first;
  count = 0;
  while (it != range.second) {
    ++count;
    EXPECT_EQ(*it, 3);
    ++it;
  }
  EXPECT_EQ(count, 3);

  // Equal range of 6 should be empty
  // range = ms.equal_range(6);
  // EXPECT_EQ(range.first, ms.end());
  // EXPECT_EQ(range.second, ms.end());
}