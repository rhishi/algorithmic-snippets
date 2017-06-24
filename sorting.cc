#include "sorting.h"

// -----------------------------------------------------------------
// Utility functions related to sorting

bool IsSorted(int array[], int size) {
    if (size <= 1) return true;
    for (int i = 0; i < size - 1; i++) {
        if (array[i] > array[i + 1]) return false;
    }
    return true;
}

void Swap(int array[], int i, int j) {
    if (i == j) return;

    int temp = array[i];
    array[i] = array[j];
    array[j] = temp;
}

// -----------------------------------------------------------------
// QuickSort

void QuickSort(int array[], int left, int right);

void QuickSort(int array[], int size) {
    QuickSort(array, 0, size - 1);
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

    // Put the pivot in the middle, and invoke recursively on the two halves
    Swap(array, i, right);
    QuickSort(array, left, i - 1);
    QuickSort(array, i + 1, right);
}
