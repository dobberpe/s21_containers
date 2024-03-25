#include "../s21_set.h" 
#include <gtest/gtest.h>

using namespace s21;


// Тест для конструктора по умолчанию
TEST(SetConstructorTest, DefaultConstructor) {
    Set<int> s;
    EXPECT_EQ(0, s.size());
    EXPECT_TRUE(s.empty());
}

// Тест для конструктора с инициализационным списком
TEST(SetConstructorTest, InitializerListConstructor) {
    Set<int> s = {1, 2, 3};
    EXPECT_EQ(3, s.size());
    EXPECT_FALSE(s.empty());
    // Проверьте, что все элементы из списка были вставлены в множество
    EXPECT_TRUE(s.contains(1));
    EXPECT_TRUE(s.contains(2));
    EXPECT_TRUE(s.contains(3));
}

// Тест для конструктора копирования
TEST(SetConstructorTest, CopyConstructor) {
    Set<int> s1 = {1, 2, 3};
    Set<int> s2 = s1; // Копируем s1 в s2
    EXPECT_EQ(s1.size(), s2.size());
    // Проверяем, что s2 содержит те же элементы, что и s1
    SetIterator<int> i1 = s1.begin(), i2 = s2.begin();
    for (int i = 0; i < 2; i++)
    {
        ++i1;
        ++i2;
        EXPECT_EQ(i1.current->key, i2.current->key);
    }
}

// Тест для конструктора перемещения
TEST(SetConstructorTest, MoveConstructor) {
    Set<int> s1 = {1, 2, 3};
    Set<int> s2 = std::move(s1); // Перемещаем s1 в s2
    EXPECT_EQ(0, s1.size()); // Проверяем, что s1 теперь пустой
    // Проверяем, что s2 содержит те же элементы, что и s1 перед перемещением
    EXPECT_TRUE(s2.contains(1));
    EXPECT_TRUE(s2.contains(2));
    EXPECT_TRUE(s2.contains(3));
}


int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
