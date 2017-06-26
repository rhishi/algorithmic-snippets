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

// -----------------------------------------------------------------------------
// QuickSort variants

void QuickSortMiddle(int array[], int left, int right);
void QuickSortLeft(int array[], int left, int right);
void QuickSortRight(int array[], int left, int right);
int Partition(int array[], int left, int pivot, int right);

void QuickSort(int array[], int size) {
    QuickSortMiddle(array, 0, size - 1);
}

void QuickSortMiddle(int array[], int size) {
    QuickSortMiddle(array, 0, size - 1);
}

void QuickSortMiddle(int array[], int left, int right) {
    if (left >= right) return;

    int pivot = left + (right - left) / 2;
    pivot = Partition(array, left, pivot, right);

    QuickSortMiddle(array, left, pivot - 1);
    QuickSortMiddle(array, pivot + 1, right);
}

void QuickSortLeft(int array[], int size) {
    QuickSortLeft(array, 0, size - 1);
}

void QuickSortLeft(int array[], int left, int right) {
    if (left >= right) return;

    int pivot = left;
    pivot = Partition(array, left, pivot, right);

    QuickSortLeft(array, left, pivot - 1);
    QuickSortLeft(array, pivot + 1, right);
}

void QuickSortRight(int array[], int size) {
    QuickSortRight(array, 0, size - 1);
}

void QuickSortRight(int array[], int left, int right) {
    if (left >= right) return;

    int pivot = right;
    pivot = Partition(array, left, pivot, right);

    QuickSortRight(array, left, pivot - 1);
    QuickSortRight(array, pivot + 1, right);
}

int Partition(int array[], int left, int pivot, int right) {
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

    // Put the pivot in the middle, and return the pivot position
    Swap(array, i, right);
    return i;
}
