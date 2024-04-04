#include "test_s21_containers.h"

using namespace s21;

// Тест для конструктора по умолчанию
TEST(MapConstructorTest, DefaultConstructor) {
    Map<int, int> m;
    EXPECT_EQ(0, m.size());
    EXPECT_TRUE(m.empty());
}
