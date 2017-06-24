#include <iostream>
#include "sorting.h"

void QuickSortTest1();
void QuickSortTest2();

int main(int argc, const char *argv[]) {
    QuickSortTest1();
    QuickSortTest2();
    return 0;
}

void QuickSortTest1() {
    int array1[] = { };
    int size1 = 0;
    QuickSort(array1, size1);
    std::cout << IsSorted(array1, size1) << std::endl;

    int array2[] = { 1 };
    int size2 = 1;
    QuickSort(array2, size2);
    std::cout << IsSorted(array2, size2) << std::endl;

    int array3[] = { 1, 3 };
    int size3 = 2;
    QuickSort(array3, size3);
    std::cout << IsSorted(array3, size3) << std::endl;

    int array4[] = { 2, 1, 3 };
    int size4 = 3;
    QuickSort(array4, size4);
    std::cout << IsSorted(array4, size4) << std::endl;

    int array5[] = { 3, 2, 1 };
    int size5 = 3;
    QuickSort(array5, size5);
    std::cout << IsSorted(array5, size5) << std::endl;
}

void QuickSortTest2() {
    int** arrays = new int*[8] {
        new int[0] { },
        new int[1] { 1 },
        new int[2] { 1, 2},
        new int[2] { 2, 1},
        new int[3] { 1, 2, 3},
        new int[3] { 1, 3, 2},
        new int[3] { 3, 2, 1},
        new int[10] { 7, 2, 3, 2, 4, 9, 7, 8, 9, 10 }
    };
    int sizes[] = { 0, 1, 2, 2, 3, 3, 3, 10 };
    int count = 8;

    for (int i = 0; i < count; i++) {
        QuickSort(arrays[i], sizes[i]);
        std::cout << IsSorted(arrays[i], sizes[i]) << std::endl;
    }

    for (int i = 0; i < count; i++) {
        delete arrays[i];
        arrays[i] = NULL;
    }
    delete arrays;
    arrays = NULL;
}
