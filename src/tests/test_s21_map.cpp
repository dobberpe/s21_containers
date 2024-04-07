#include "test_s21_containers.h"

using namespace s21;

TEST(MapMemberFunctionsTest, DefaultConstructor) {
    map<int, int> m;
    EXPECT_EQ(0, m.size());
    EXPECT_TRUE(m.empty());
}

TEST(MapMemberFunctionsTest, InitializerListConstructor) {
map<int, int> m{{1, 1}, {1, 2}, {2, 1}, {3, 3}};
EXPECT_EQ(3, m.size());
EXPECT_TRUE(m.contains(1));
EXPECT_TRUE(m.contains(2));
EXPECT_TRUE(m.contains(3));
EXPECT_EQ(1, m[1]);
EXPECT_EQ(1, m[2]);
EXPECT_EQ(3, m[3]);
}

TEST(MapMemberFunctionsTest, CopyConstructor) {
map<int, int> m1{{1, 1}, {1, 2}, {2, 1}, {3, 3}};
map<int, int> m = m1;
EXPECT_EQ(3, m.size());
EXPECT_TRUE(m.contains(1));
EXPECT_TRUE(m.contains(2));
EXPECT_TRUE(m.contains(3));
EXPECT_EQ(1, m[1]);
EXPECT_EQ(1, m[2]);
EXPECT_EQ(3, m[3]);
}

TEST(MapMemberFunctionsTest, MoveConstructor) {
map<int, int> m1{{1, 1}, {1, 2}, {2, 1}, {3, 3}};
map<int, int> m = std::move(m1);
EXPECT_EQ(0, m1.size());
EXPECT_TRUE(m1.empty());
EXPECT_EQ(3, m.size());
EXPECT_TRUE(m.contains(1));
EXPECT_TRUE(m.contains(2));
EXPECT_TRUE(m.contains(3));
EXPECT_EQ(1, m[1]);
EXPECT_EQ(1, m[2]);
EXPECT_EQ(3, m[3]);
}

TEST(MapMemberFunctionsTest, MoveAssignment) {
map<int, int> m1{{1, 1}, {1, 2}, {2, 1}, {3, 3}};
map<int, int> m;
m = std::move(m1);
EXPECT_EQ(0, m1.size());
EXPECT_TRUE(m1.empty());
EXPECT_EQ(3, m.size());
EXPECT_TRUE(m.contains(1));
EXPECT_TRUE(m.contains(2));
EXPECT_TRUE(m.contains(3));
EXPECT_EQ(1, m[1]);
EXPECT_EQ(1, m[2]);
EXPECT_EQ(3, m[3]);
}

TEST(MapElementAccessTest, At) {
map<int, int> m{{1, 1}, {1, 2}, {2, 1}, {3, 3}};
EXPECT_EQ(1, m.at(1));
EXPECT_EQ(1, m.at(2));
EXPECT_EQ(3, m.at(3));
m.at(1) = 2;
EXPECT_EQ(2, m.at(1));
EXPECT_THROW(m.at(4), std::out_of_range);
}

TEST(MapElementAccessTest, Op) {
map<int, int> m{{1, 1}, {1, 2}, {2, 1}, {3, 3}};
EXPECT_EQ(1, m[1]);
EXPECT_EQ(1, m[2]);
EXPECT_EQ(3, m[3]);
m[1] = 2;
EXPECT_EQ(2, m[1]);
EXPECT_EQ(0, m[4]);
}

TEST(MapIteratorsTest, Begin) {
map<int, int> m{{1, 1}, {1, 2}, {2, 1}, {3, 3}};
auto it = m.begin();
EXPECT_EQ(1, it->first);
EXPECT_EQ(1, it->second);
it->second = 2;
EXPECT_EQ(2, it->second);
}

TEST(MapIteratorsTest, End) {
map<int, int> m{{1, 1},
                {1, 2},
                {2, 1},
                {3, 5}};
auto it = m.end();
EXPECT_EQ(3, it->first);
EXPECT_EQ(5, it->second);
it->second = 4;
EXPECT_EQ(4, it->second);
}

TEST(MapIteratorsTest, CBegin) {
const map<int, int> m{{1, 1}, {1, 2}, {2, 1}, {3, 3}};
auto it = m.begin();
EXPECT_EQ(1, it->first);
EXPECT_EQ(1, it->second);
--it;
EXPECT_EQ(1, it->first);
EXPECT_EQ(1, it->second);
++it;
EXPECT_EQ(2, it->first);
EXPECT_EQ(1, it->second);
++it;
EXPECT_FALSE(it == m.end());
EXPECT_EQ(3, it->first);
EXPECT_EQ(3, it->second);
++it;
EXPECT_TRUE(it == m.end());
EXPECT_EQ(3, it->first);
EXPECT_EQ(3, it->second);
++it;
EXPECT_TRUE(it == m.end());
}

TEST(MapIteratorsTest, CEnd) {
const map<int, int> m{{1, 1}, {1, 2}, {2, 1}, {3, 5}};
auto it = m.end();
EXPECT_EQ(3, it->first);
EXPECT_EQ(5, it->second);
++it;
EXPECT_TRUE(it == m.end());
--it;
EXPECT_FALSE(it == m.end());
EXPECT_EQ(3, it->first);
EXPECT_EQ(5, it->second);
--it;
EXPECT_EQ(2, it->first);
EXPECT_EQ(1, it->second);
}

TEST(MapIteratorsTest, IterationForward) {
const map<int, int> m{{8, 64}, {4, 16}, {12, 144}, {2, 4}, {6, 36}, {10, 100}, {14, 196}, {1, 1}, {3, 9}, {5, 25}, {7, 49}, {9, 81}, {11, 121}, {13, 169}, {15, 225}};
auto it = m.begin();
for (int i = 1; i <= 15; ++i) {
EXPECT_EQ(i, it->first);
EXPECT_EQ(i*i, it->second);
++it;
}
}

TEST(MapIteratorsTest, IterationBackward) {
const map<int, int> m{{8, 64}, {4, 16}, {12, 144}, {2, 4}, {6, 36}, {10, 100}, {14, 196}, {1, 1}, {3, 9}, {5, 25}, {7, 49}, {9, 81}, {11, 121}, {13, 169}, {15, 225}};
auto it = m.end();
--it;
for (int i = 15; i >= 1; --i) {
EXPECT_EQ(i, it->first);
EXPECT_EQ(i*i, it->second);
--it;
}
}

TEST(MapIteratorsTest, RangeBasedFor) {
const map<int, int> m{{8, 64}, {4, 16}, {12, 144}, {2, 4}, {6, 36}, {10, 100}, {14, 196}, {1, 1}, {3, 9}, {5, 25}, {7, 49}, {9, 81}, {11, 121}, {13, 169}, {15, 225}};

int i = 1;
for (auto it : m) {
EXPECT_EQ(i, it.first);
EXPECT_EQ(i*i, it.second);
++i;
}
}

TEST(MapCapacityTest, MaxSize) {
map<int, int> m{{1, 1}, {1, 2}, {2, 1}, {3, 3}};

EXPECT_EQ(size_t(230584300921369395), m.max_size());
}

TEST(MapModifiersTest, Clear) {
map<int, int> m{{1, 1}, {1, 2}, {2, 1}, {3, 3}};
EXPECT_EQ(3, m.size());
EXPECT_TRUE(m.contains(1));
EXPECT_TRUE(m.contains(2));
EXPECT_TRUE(m.contains(3));
EXPECT_EQ(1, m[1]);
EXPECT_EQ(1, m[2]);
EXPECT_EQ(3, m[3]);
m.clear();
EXPECT_EQ(0, m.size());
EXPECT_TRUE(m.empty());
}

TEST(MapModifiersTest, InsertPair) {
map<int, int> m{{1, 1}, {1, 2}, {2, 1}, {3, 5}};
EXPECT_EQ(3, m.size());
auto [it, inserted] = m.insert({4, 16});
EXPECT_EQ(4, m.size());
EXPECT_TRUE(inserted);
EXPECT_EQ(4, it->first);
EXPECT_EQ(16, it->second);
std::tie(it, inserted) = m.insert({3, 9});
EXPECT_EQ(4, m.size());
EXPECT_FALSE(inserted);
EXPECT_EQ(3, it->first);
EXPECT_EQ(5, it->second);
}

TEST(MapModifiersTest, InsertSeparately) {
map<int, int> m{{1, 1}, {1, 2}, {2, 1}, {3, 5}};
EXPECT_EQ(3, m.size());
auto [it, inserted] = m.insert(4, 16);
EXPECT_EQ(4, m.size());
EXPECT_TRUE(inserted);
EXPECT_EQ(4, it->first);
EXPECT_EQ(16, it->second);
std::tie(it, inserted) = m.insert(3, 9);
EXPECT_EQ(4, m.size());
EXPECT_FALSE(inserted);
EXPECT_EQ(3, it->first);
EXPECT_EQ(5, it->second);
}

TEST(MapModifiersTest, InsertMany) {
map<int, int> m;
auto res = m.insert_many(std::make_pair(1, 1), std::make_pair(1, 2), std::make_pair(2, 1), std::make_pair(3, 5));
EXPECT_EQ(3, m.size());
auto it = res.begin();
EXPECT_TRUE(it->second);
EXPECT_EQ(1, it->first->first);
EXPECT_EQ(1, it->first->second);
++it;
EXPECT_FALSE(it->second);
EXPECT_EQ(1, it->first->first);
EXPECT_EQ(1, it->first->second);
++it;
EXPECT_TRUE(it->second);
EXPECT_EQ(2, it->first->first);
EXPECT_EQ(1, it->first->second);
++it;
EXPECT_TRUE(it->second);
EXPECT_EQ(3, it->first->first);
EXPECT_EQ(5, it->first->second);
}

TEST(MapModifiersTest, InsertOrAssign) {
map<int, int> m{{1, 1}, {1, 2}, {2, 1}, {3, 5}};
EXPECT_EQ(3, m.size());
m.insert_or_assign(4, 16);
EXPECT_EQ(4, m.size());
EXPECT_TRUE(m.contains(4));
EXPECT_EQ(16, m[4]);
m.insert_or_assign(3, 9);
EXPECT_EQ(4, m.size());
EXPECT_EQ(9, m[3]);
}

TEST(MapModifiersTest, EraseBegin) {
map<int, int> m{{1, 1}, {1, 2}, {2, 1}, {3, 5}};
EXPECT_EQ(3, m.size());
EXPECT_TRUE(m.contains(1));
EXPECT_EQ(1, m[1]);
m.erase(m.begin());
EXPECT_EQ(2, m.size());
EXPECT_FALSE(m.contains(1));
EXPECT_EQ(2, m.begin()->first);
EXPECT_EQ(1, m.begin()->second);
}

TEST(MapModifiersTest, EraseEnd) {
map<int, int> m{{1, 1}, {1, 2}, {2, 1}, {3, 5}};
EXPECT_EQ(3, m.size());
EXPECT_TRUE(m.contains(3));
EXPECT_EQ(5, m[3]);
m.erase(m.end());
EXPECT_EQ(2, m.size());
EXPECT_FALSE(m.contains(3));
EXPECT_EQ(2, m.end()->first);
EXPECT_EQ(1, m.end()->second);
}

TEST(MapModifiersTest, EraseRoot) {
map<int, int> m{{8, 64}, {4, 16}, {12, 144}, {2, 4}, {6, 36}, {10, 100}, {14, 196}, {1, 1}, {3, 9}, {5, 25}, {7, 49}, {9, 81}, {11, 121}, {13, 169}, {15, 225}};
EXPECT_EQ(15, m.size());
EXPECT_TRUE(m.contains(8));
EXPECT_EQ(64, m[8]);
auto it = m.begin();
for (int i = 0; i < 7; ++i) ++it;
m.erase(it);
EXPECT_EQ(14, m.size());
EXPECT_FALSE(m.contains(8));
int i = 1;
for (auto item : m) {
    if (i == 8) ++i;
EXPECT_EQ(i, item.first);
EXPECT_EQ(i*i, item.second);
    ++i;
}
}

TEST(MapModifiersTest, EraseMiddle) {
map<int, int> m{{8, 64}, {4, 16}, {12, 144}, {2, 4}, {6, 36}, {10, 100}, {14, 196}, {1, 1}, {3, 9}, {5, 25}, {7, 49}, {9, 81}, {11, 121}, {13, 169}, {15, 225}};
EXPECT_EQ(15, m.size());
EXPECT_TRUE(m.contains(4));
EXPECT_EQ(16, m[4]);
auto it = m.begin();
for (int i = 0; i < 3; ++i) ++it;
m.erase(it);
EXPECT_EQ(14, m.size());
EXPECT_FALSE(m.contains(4));
int i = 1;
for (auto item : m) {
if (i == 4) ++i;
EXPECT_EQ(i, item.first);
EXPECT_EQ(i*i, item.second);
++i;
}
}

TEST(MapModifiersTest, Swap) {
map<int, int> m1{{1, 1}, {1, 2}, {2, 1}, {3, 5}};
map<int, int> m2{{8, 4}, {12, 7}, {5, 0}, {6, 1}};
EXPECT_EQ(3, m1.size());
EXPECT_EQ(4, m2.size());
EXPECT_TRUE(m1.contains(1));
EXPECT_TRUE(m1.contains(2));
EXPECT_TRUE(m1.contains(3));
EXPECT_TRUE(m2.contains(5));
EXPECT_TRUE(m2.contains(6));
EXPECT_TRUE(m2.contains(8));
EXPECT_TRUE(m2.contains(12));
EXPECT_EQ(1, m1[1]);
EXPECT_EQ(1, m1[2]);
EXPECT_EQ(5, m1[3]);
EXPECT_EQ(0, m2[5]);
EXPECT_EQ(1, m2[6]);
EXPECT_EQ(4, m2[8]);
EXPECT_EQ(7, m2[12]);
m1.swap(m2);
EXPECT_EQ(3, m2.size());
EXPECT_EQ(4, m1.size());
EXPECT_TRUE(m2.contains(1));
EXPECT_TRUE(m2.contains(2));
EXPECT_TRUE(m2.contains(3));
EXPECT_TRUE(m1.contains(5));
EXPECT_TRUE(m1.contains(6));
EXPECT_TRUE(m1.contains(8));
EXPECT_TRUE(m1.contains(12));
EXPECT_EQ(1, m2[1]);
EXPECT_EQ(1, m2[2]);
EXPECT_EQ(5, m2[3]);
EXPECT_EQ(0, m1[5]);
EXPECT_EQ(1, m1[6]);
EXPECT_EQ(4, m1[8]);
EXPECT_EQ(7, m1[12]);
}

TEST(MapModifiersTest, Merge) {
map<int, int> m1{{8, 4}, {12, 7}, {5, 0}, {6, 1}};
map<int, int> m2{{1, 1}, {15, 2}, {5, 1}, {8, 5}};
EXPECT_EQ(4, m1.size());
EXPECT_EQ(4, m2.size());
EXPECT_TRUE(m1.contains(5));
EXPECT_TRUE(m1.contains(6));
EXPECT_TRUE(m1.contains(8));
EXPECT_TRUE(m1.contains(12));
EXPECT_TRUE(m2.contains(1));
EXPECT_TRUE(m2.contains(5));
EXPECT_TRUE(m2.contains(8));
EXPECT_TRUE(m2.contains(15));
EXPECT_EQ(0, m1[5]);
EXPECT_EQ(1, m1[6]);
EXPECT_EQ(4, m1[8]);
EXPECT_EQ(7, m1[12]);
EXPECT_EQ(1, m2[1]);
EXPECT_EQ(1, m2[5]);
EXPECT_EQ(5, m2[8]);
EXPECT_EQ(2, m2[15]);
m1.merge(m2);
EXPECT_EQ(6, m1.size());
EXPECT_EQ(2, m2.size());
EXPECT_TRUE(m1.contains(1));
EXPECT_TRUE(m1.contains(5));
EXPECT_TRUE(m1.contains(6));
EXPECT_TRUE(m1.contains(8));
EXPECT_TRUE(m1.contains(12));
EXPECT_TRUE(m1.contains(15));
EXPECT_TRUE(m2.contains(5));
EXPECT_TRUE(m2.contains(8));
EXPECT_EQ(1, m1[1]);
EXPECT_EQ(0, m1[5]);
EXPECT_EQ(1, m1[6]);
EXPECT_EQ(4, m1[8]);
EXPECT_EQ(7, m1[12]);
EXPECT_EQ(2, m1[15]);
EXPECT_EQ(1, m2[5]);
EXPECT_EQ(5, m2[8]);
}