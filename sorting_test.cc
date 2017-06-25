#include "sorting.h"
#include "gtest/gtest.h"

// -----------------------------------------------------------------
// QuickSort tests

TEST(QuickSortTest, Test1) {
    int array[] = { 3, 4, 1, 4, 7, 6, 7, 8, 5 };
    int size = 9;
    QuickSort(array, size);
    EXPECT_TRUE(IsSorted(array, size));
}

// -----------------------------------------------------------------
