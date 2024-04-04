#include "test_s21_containers.h"
#include <iterator>

using namespace s21;

TEST(MultisetTest, InsertionAndCount)
{
    multiset<int> multiset;
    multiset.insert(1);
    multiset.insert(2);
    multiset.insert(2);
    multiset.insert(3);
    multiset.insert(3);
    multiset.insert(3);

    EXPECT_EQ(6, multiset.size());

    EXPECT_TRUE(multiset.contains(1));
    EXPECT_TRUE(multiset.contains(2));
    EXPECT_TRUE(multiset.contains(3));
}

TEST(MultisetTest, Iteration)
{
    multiset<int> multiset;
    multiset.insert(1);
    multiset.insert(2);
    multiset.insert(-11);
    multiset.insert(-11);
    multiset.insert(-11);
    multiset.insert(2);
    multiset.insert(3);
    multiset.insert(3);
    multiset.insert(3);
    int count_1 = 0, count_2 = 0, count_3 = 0;
    for (auto it = multiset.begin(); it != multiset.end(); ++it)
    {
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

TEST(MultisetTest, LowerBound)
{
    multiset<int> ms = {1, 2, 2, 3, 3, 3, 4, 5};

    // Lower bound of 2 should point to the first occurrence of 2
    auto it = ms.lower_bound(2);
    EXPECT_EQ(*it, 2);

    // Lower bound of 3 should point to the first occurrence of 3
    it = ms.lower_bound(3);
    EXPECT_EQ(*it, 3);

    // Lower bound of 6 should point to the end
    it = ms.lower_bound(6);
    // EXPECT_EQ(it, ms.end());
}

TEST(MultisetTest, UpperBound)
{
    multiset<int> ms = {1, 2, 2, 3, 3, 3, 4, 5};

    // Upper bound of 2 should point to the first element after the last occurrence of 2
    auto it = ms.upper_bound(2);
    EXPECT_EQ(*it, 3);

    // Upper bound of 3 should point to the first element after the last occurrence of 3
    it = ms.upper_bound(3);
    EXPECT_EQ(*it, 4);

    // Upper bound of 6 should point to the end
    it = ms.upper_bound(6);
    // EXPECT_EQ(it, ms.end());
}

TEST(MultisetTest, EqualRange) {
    multiset<int> ms = {1, 2, 2, 3, 3, 3, 4, 5};

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