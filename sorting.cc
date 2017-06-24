
void Swap(int array[], int i, int j) {
    if (i == j) return;

    int temp = array[i];
    array[i] = array[j];
    array[j] = temp;
}

void QuickSort(int array[], int left, int right) {
    if (left >= right) return;

    int pivot = left + (right - left) / 2;
    Swap(array, pivot, right);

    int i = left;
    int j = right - 1;

    while (i <= j) {
        if (array[i] <= array[right]) { i++; }
        else { Swap(array, i, j); j--; }
    }

    // Always: before, during, and after the loop:
    // to the left of i are all elements smaller than or equal to the pivot element
    // to the right of j are all elements bigger than the pivot element
    // i..j are the unprocessed elements
    // When the loop ends, i == j + 1
    // So,
    // left..i-1 are smaller-or-equal elements
    // i..right-1 are greater elements
    // So, put the pivot in the middle, and invoke recursively on the two halves
    Swap(array, i, right);
    QuickSort(array, left, i - 1);
    QuickSort(array, i + 1, right);
}

void QuickSort(int array[], int size) {
    QuickSort(array, 0, size - 1);
}

bool IsSorted(int array[], int size) {
    if (size <= 1) return true;
    for (int i = 0; i < size - 1; i++) {
        if (array[i] > array[i + 1]) return false;
    }
    return true;
}

#include <iostream>

int main(int argc, const char *argv[]) {
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

    return 0;
}
