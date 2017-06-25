#include "sorting.h"
#include "gtest/gtest.h"

// -----------------------------------------------------------------
// QuickSort tests

TEST(QuickSortTest, Empty) {
    int array[] = { };
    int size = 0;
    QuickSort(array, size);
    EXPECT_TRUE(IsSorted(array, size));
}

TEST(QuickSortTest, OneElement) {
    int array[] = { 3 };
    int size = 1;
    QuickSort(array, size);
    EXPECT_TRUE(IsSorted(array, size));
}

TEST(QuickSortTest, TwoElementsAscending) {
    int array[] = { 7, 10 };
    int size = 2;
    QuickSort(array, size);
    EXPECT_TRUE(IsSorted(array, size));
}

TEST(QuickSortTest, TwoElementsDescending) {
    int array[] = { 33, 16 };
    int size = 2;
    QuickSort(array, size);
    EXPECT_TRUE(IsSorted(array, size));
}

TEST(QuickSortTest, SmallExample) {
    int array[] = { 3, 4, 1, 4, 7, 6, 7, 8, 5 };
    int size = 9;
    QuickSort(array, size);
    EXPECT_TRUE(IsSorted(array, size));
}

// -----------------------------------------------------------------
