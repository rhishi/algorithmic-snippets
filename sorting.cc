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
// QuickSort my first version

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

// -----------------------------------------------------------------------------
// QuickSort as described in CLRS book (2nd edition).  Uses Lomuto partition.

void QuickSortLomutoCLRSMiddle(int array[], int left, int right);
void QuickSortLomutoCLRSLeft(int array[], int left, int right);
void QuickSortLomutoCLRSRight(int array[], int left, int right);
int PartitionLomutoCLRS(int array[], int left, int pivot, int right);

void QuickSortLomutoCLRSMiddle(int array[], int size) {
    QuickSortLomutoCLRSMiddle(array, 0, size - 1);
}

void QuickSortLomutoCLRSMiddle(int array[], int left, int right) {
    if (left >= right) return;

    int pivot = left + (right - left) / 2;
    pivot = PartitionLomutoCLRS(array, left, pivot, right);

    QuickSortLomutoCLRSMiddle(array, left, pivot - 1);
    QuickSortLomutoCLRSMiddle(array, pivot + 1, right);
}

void QuickSortLomutoCLRSLeft(int array[], int size) {
    QuickSortLomutoCLRSLeft(array, 0, size - 1);
}

void QuickSortLomutoCLRSLeft(int array[], int left, int right) {
    if (left >= right) return;

    int pivot = left;
    pivot = PartitionLomutoCLRS(array, left, pivot, right);

    QuickSortLomutoCLRSLeft(array, left, pivot - 1);
    QuickSortLomutoCLRSLeft(array, pivot + 1, right);
}

void QuickSortLomutoCLRSRight(int array[], int size) {
    QuickSortLomutoCLRSRight(array, 0, size - 1);
}

void QuickSortLomutoCLRSRight(int array[], int left, int right) {
    if (left >= right) return;

    int pivot = right;
    pivot = PartitionLomutoCLRS(array, left, pivot, right);

    QuickSortLomutoCLRSRight(array, left, pivot - 1);
    QuickSortLomutoCLRSRight(array, pivot + 1, right);
}

int PartitionLomutoCLRS(int array[], int left, int pivot, int right) {
    Swap(array, pivot, right);

    int pivot_element = array[right];
    int i = left - 1;

    for (int j = left; j <= right - 1; j++) {
        if (array[j] <= pivot_element) {
            Swap(array, ++i, j);
        }
    }
    // Always: before, during, and after the loop:
    // left..i are all elements smaller than or equal to the pivot element
    // i+1..j-1 are all elements bigger than the pivot element
    // j..right-1 are the unprocessed elements

    // Put the pivot in the middle, and return the pivot position
    Swap(array, ++i, right);
    return i;
}
