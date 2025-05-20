#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include "sorting.hpp"

TEST(SortingTest, BubbleSortWorksCorrectly) {
    const int size = 6;
    int arr[size] = {5, 3, 6, 1, 2, 4};
    int expected[size] = {1, 2, 3, 4, 5, 6};

    Sorting::BubbleSort(arr, size);

    for (int i = 0; i < size; ++i) {
        ASSERT_EQ(arr[i], expected[i])
            << "Ошибка в элементе с индексом " << i
            << ": ожидалось " << expected[i]
            << ", получено " << arr[i];
    }
}

TEST(SortingTest, BubbleSortAlreadySorted) {
    const int size = 5;
    int arr[size] = {1, 2, 3, 4, 5};
    int expected[size] = {1, 2, 3, 4, 5};

    Sorting::BubbleSort(arr, size);

    for (int i = 0; i < size; ++i) {
        ASSERT_EQ(arr[i], expected[i])
            << "Не совпадает отсортированный элемент на позиции " << i;
    }
}

TEST(SortingTest, BubbleSortWithDuplicates) {
    const int size = 7;
    int arr[size] = {4, 2, 5, 2, 3, 1, 4};
    int expected[size] = {1, 2, 2, 3, 4, 4, 5};

    Sorting::BubbleSort(arr, size);

    for (int i = 0; i < size; ++i) {
        ASSERT_EQ(arr[i], expected[i])
            << "Несовпадение в элементе с индексом " << i
            << ": ожидалось " << expected[i]
            << ", получено " << arr[i];
    }
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
