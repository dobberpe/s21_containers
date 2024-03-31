#include "test_s21_containers.h"

using namespace s21;

TEST(StackTest, PushAndTop) {
  Stack<int> s;
  s.push(1);
  s.push(2);
  s.push(3);
  EXPECT_EQ(s.top(), 3);
}

TEST(StackTest, Pop) {
  Stack<int> s;
  s.push(1);
  s.push(2);
  s.push(3);
  s.pop();
  EXPECT_EQ(s.top(), 2);
  s.pop();
  EXPECT_EQ(s.top(), 1);
}

TEST(StackTest, Empty) {
  Stack<int> s;
  EXPECT_TRUE(s.empty());
  s.push(1);
  EXPECT_FALSE(s.empty());
  s.pop();
  EXPECT_TRUE(s.empty());
}

TEST(StackTest, Size) {
  Stack<int> s;
  EXPECT_EQ(s.size(), 0);
  s.push(1);
  s.push(2);
  s.push(3);
  EXPECT_EQ(s.size(), 3);
  s.pop();
  EXPECT_EQ(s.size(), 2);
}
