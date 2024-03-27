#include "test_s21_containers.h"

using namespace s21;

TEST(QueueTest, Push)
{
    Queue<int> q;
    q.push(1);
    q.push(2);
    q.push(3);

    EXPECT_EQ(3, q.size());
    EXPECT_EQ(1, q.front());
    EXPECT_EQ(3, q.back());
}

TEST(QueueTest, Pop)
{
    Queue<int> q;
    q.push(1);
    q.push(2);
    q.push(3);

    q.pop();
    q.pop();

    EXPECT_EQ(1, q.size());
    EXPECT_EQ(3, q.front());
    EXPECT_EQ(3, q.back());

    q.pop();

    EXPECT_TRUE(q.empty());
}

TEST(QueueTest, Swap)
{
    Queue<int> q1;
    q1.push(1);
    q1.push(2);
    q1.push(3);

    Queue<int> q2;
    q2.push(4);
    q2.push(5);

    q1.swap(q2);

    EXPECT_EQ(2, q1.size());
    EXPECT_EQ(4, q1.front());
    EXPECT_EQ(5, q1.back());

    EXPECT_EQ(3, q2.size());
    EXPECT_EQ(1, q2.front());
    EXPECT_EQ(3, q2.back());
}