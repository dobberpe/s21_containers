#include "test_s21_containers.h"

using namespace s21;

TEST(SetConstructorTest, DefaultConstructor) {
  set<int> s;
  EXPECT_EQ(0, s.size());
  EXPECT_TRUE(s.empty());
}

TEST(SetConstructorTest, InitializerListConstructor) {
  set<int> s{1, 2, 3};
  EXPECT_EQ(3, s.size());
  EXPECT_FALSE(s.empty());
  EXPECT_TRUE(s.contains(1));
  EXPECT_TRUE(s.contains(2));
  EXPECT_TRUE(s.contains(3));
}

TEST(SetConstructorTest, CopyConstructor) {
  set<int> s1{1, 2, 3};
  set<int> s2 = s1;
  EXPECT_EQ(s1.size(), s2.size());
  Tree<int>::Iterator i1 = s1.begin(), i2 = s2.begin();
  for (int i = 0; i < 2; i++) {
    ++i1;
    ++i2;
    EXPECT_EQ(i1.current->key, i2.current->key);
  }
}

TEST(SetConstructorTest, MoveConstructor) {
  set<int> s1{1, 2, 3};
  set<int> s2 = std::move(s1);
  EXPECT_EQ(0, s1.size());
  EXPECT_TRUE(s2.contains(1));
  EXPECT_TRUE(s2.contains(2));
  EXPECT_TRUE(s2.contains(3));
}

TEST(SetMoveAssignmentTest, BasicTest) {
  set<int> s1;
  s1.insert(1);
  s1.insert(2);
  s1.insert(3);

  set<int> s2;
  s2 = std::move(s1);

  EXPECT_EQ(0, s1.size());

  EXPECT_EQ(3, s2.size());
  EXPECT_TRUE(s2.contains(1));
  EXPECT_TRUE(s2.contains(2));
  EXPECT_TRUE(s2.contains(3));
}

TEST(SetMoveAssignmentTest, SelfAssignment) {
  set<int> s;
  s.insert(1);
  s.insert(2);

  s = std::move(s);

  EXPECT_EQ(2, s.size());
  EXPECT_TRUE(s.contains(1));
  EXPECT_TRUE(s.contains(2));
}

TEST(SetInsertTest, BasicTest) {
  set<int> s;

  auto result1 = s.insert(1);
  auto result2 = s.insert(2);
  auto result3 = s.insert(3);

  EXPECT_EQ(3, s.size());
  EXPECT_TRUE(result1.second);
  EXPECT_TRUE(result2.second);
  EXPECT_TRUE(result3.second);
  EXPECT_TRUE(s.contains(1));
  EXPECT_TRUE(s.contains(2));
  EXPECT_TRUE(s.contains(3));
}

TEST(SetInsertTest, DuplicateTest) {
  set<int> s;

  s.insert(1);
  auto result = s.insert(1);

  EXPECT_EQ(1, s.size());
  EXPECT_FALSE(result.second);
  EXPECT_TRUE(s.contains(1));
}

TEST(SetCapacityTest, SizeTest) {
  set<int> s;

  s.insert(1);
  s.insert(2);
  s.insert(3);

  EXPECT_EQ(3, s.size());
}

TEST(SetCapacityTest, EmptyTest) {
  set<int> s;

  EXPECT_TRUE(s.empty());

  s.insert(1);
  EXPECT_FALSE(s.empty());
}

TEST(SetCapacityTest, MaxSizeTest) {
  set<int> s;

  EXPECT_EQ(230584300921369395, s.max_size());
}

TEST(SetModifiersTest, ClearTest) {
  set<int> s;

  s.insert(1);
  s.insert(2);
  s.clear();

  EXPECT_TRUE(s.empty());
  EXPECT_EQ(0, s.size());
}

TEST(SetIteratorTest, BeginEndTest) {
  set<int> s;
  s.insert(1);
  s.insert(2);
  s.insert(3);

  set<int>::iterator begin_iter = s.begin();

  EXPECT_EQ(1, *begin_iter);
}

TEST(SetConstIteratorTest, ConstBeginEndTest) {
  const set<int> s{1, 2, 3};

  set<int>::const_iterator begin_iter = s.begin();

  EXPECT_EQ(1, *begin_iter);
}

TEST(SetFindTest, FindExistingElement) {
  set<int> s{1, 2, 3};

  auto it = s.find(2);

  EXPECT_EQ(2, *it);
}

TEST(SetContainsTest, ContainsExistingElement) {
  set<int> s{1, 2, 3};

  EXPECT_TRUE(s.contains(2));
}

TEST(SetContainsTest, ContainsNonExistingElement) {
  set<int> s{1, 2, 3};

  EXPECT_FALSE(s.contains(4));
}

TEST(SetTest, Erase) {
  set<int> s{1, 2, 3, 4, 5};

  auto it = s.find(3);
  ASSERT_NE(it, s.end());
  s.erase(it);

  EXPECT_EQ(s.size(), 4);
  EXPECT_FALSE(s.contains(3));
}

TEST(SetTest, Swap) {
  set<int> s1{1, 2, 3};
  set<int> s2{4, 5, 6};

  s1.swap(s2);

  EXPECT_EQ(s1.size(), 3);
  EXPECT_EQ(s2.size(), 3);

  EXPECT_TRUE(s1.contains(4));
  EXPECT_TRUE(s2.contains(1));
}

TEST(SetTest, Merge) {
  set<int> s1{1, 2, 3};
  set<int> s2{4, 5, 6};

  s1.merge(s2);

  EXPECT_EQ(s1.size(), 6);
  EXPECT_TRUE(s2.empty());

  EXPECT_TRUE(s1.contains(4));
  EXPECT_TRUE(s1.contains(6));
}

TEST(SetTest, InsertMany) {
  set<int> my_set;

  auto results = my_set.insert_many(1, 2, 3);
  ASSERT_EQ(results.size(), 3);
  EXPECT_EQ(results[0].second, true);
  EXPECT_EQ(results[1].second, true);
  EXPECT_EQ(results[2].second, true);

  results = my_set.insert_many(2, 3, 4);
  ASSERT_EQ(results.size(), 3);
  EXPECT_EQ(results[0].second, false);
  EXPECT_EQ(results[1].second, false);
  EXPECT_EQ(results[2].second, true);
  std::vector<int> expected_values = {1, 2, 3, 4};
  int i = 0;
  for (auto it = my_set.begin(); it != my_set.end(); ++it) {
    EXPECT_EQ(*it, expected_values[i]);
    ++i;
  }
}

TEST(SetIteratorTest, DecrementOperator) {
  set<int> mySet;

  mySet.insert(10);
  mySet.insert(5);
  mySet.insert(15);
  mySet.insert(3);
  mySet.insert(7);

  Tree<int>::Iterator it = mySet.begin();
  Tree<int>::Iterator last = mySet.end();

  --last;
  ASSERT_EQ(*last, 15);

  --last;
  ASSERT_EQ(*last, 10);

  --last;
  ASSERT_EQ(*last, 7);

  --last;
  ASSERT_EQ(*last, 5);

  --last;
  ASSERT_EQ(*last, 3);

  ASSERT_EQ(*last, *it);
}

TEST(IteratorComparisonTest, OperatorEqual) {
  set<int> mySet;
  mySet.insert(10);
  mySet.insert(20);

  Tree<int>::Iterator it1 = mySet.begin();
  Tree<int>::Iterator it2 = mySet.begin();

  ASSERT_TRUE(it1 == it2);

  Tree<int>::Iterator it3 = mySet.begin();
  Tree<int>::Iterator it4 = mySet.begin();
  ++it4;

  ASSERT_FALSE(it3 == it4);
}

TEST(TreeTest, Erase) {
  set<int> tree;
  tree.insert(5);
  tree.insert(3);
  tree.insert(8);
  tree.insert(2);
  tree.insert(4);
  tree.insert(7);
  tree.insert(9);

  auto it = tree.find(5);
  tree.erase(it);

  EXPECT_FALSE(tree.contains(5));

  EXPECT_EQ(tree.size(), 6);

  EXPECT_TRUE(tree.contains(3));
  EXPECT_TRUE(tree.contains(8));
  EXPECT_TRUE(tree.contains(2));
  EXPECT_TRUE(tree.contains(4));
  EXPECT_TRUE(tree.contains(7));
  EXPECT_TRUE(tree.contains(9));
}