#include "test_s21_containers.h"

using namespace s21;

TEST(MultisetTest, InsertionAndCount) {
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

TEST(MultisetTest, Iteration) {
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
    for (auto it = multiset.begin(); it != multiset.end(); ++it) {
        if (*it == 1) count_1++;
        else if (*it == 2) count_2++;
        else if (*it == 3) count_3++;

    }

    EXPECT_EQ(1, count_1);
    EXPECT_EQ(2, count_2);
    EXPECT_EQ(3, count_3);
}