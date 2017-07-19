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
// QuickSort from the CLRS book (2nd and 3rd editions).  Uses Lomuto partition.

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

// --------------------------------------
// Exercise 7.1-2: Modify Partition to return the middle when all elements are equal.

void QuickSortLomutoCLRSEqualityFixMiddle(int array[], int left, int right);
int PartitionLomutoCLRSEqualityFix(int array[], int left, int pivot, int right);

void QuickSortLomutoCLRSEqualityFixMiddle(int array[], int size) {
    QuickSortLomutoCLRSEqualityFixMiddle(array, 0, size - 1);
}

void QuickSortLomutoCLRSEqualityFixMiddle(int array[], int left, int right) {
    if (left >= right) return;

    int pivot = left + (right - left) / 2;
    pivot = PartitionLomutoCLRSEqualityFix(array, left, pivot, right);

    QuickSortLomutoCLRSEqualityFixMiddle(array, left, pivot - 1);
    QuickSortLomutoCLRSEqualityFixMiddle(array, pivot + 1, right);
}

int PartitionLomutoCLRSEqualityFix(int array[], int left, int pivot, int right) {
    Swap(array, pivot, right);

    int pivot_element = array[right];
    int i = left - 1;

    for (int j = left; j <= right - 1; j++)  {
        if (array[j] <= pivot_element) {
            Swap(array, ++i, j);
        }
        if (++j > right - 1) break;
        if (array[j] < pivot_element) {
            Swap(array, ++i, j);
        }
    }
    // Always: before, during, and after the loop:
    // left..i are all elements smaller than or equal to the pivot element
    // i+1..j-1 are all elements bigger than or equal to the pivot element
    // j..right-1 are the unprocessed elements

    // Put the pivot in the middle, and return the pivot position
    Swap(array, ++i, right);
    return i;
}

// -----------------------------------------------------------------------------
// Hoare Partition.  The original, much efficient, harder to understand, but
// beautiful method of partitioning.

void QuickSortHoareMiddle(int array[], int left, int right);
void QuickSortHoareLeft(int array[], int left, int right);
void QuickSortHoareRight(int array[], int left, int right);
int PartitionHoare(int array[], int left, int pivot, int right);

void QuickSortHoareMiddle(int array[], int size) {
    QuickSortHoareMiddle(array, 0, size - 1);
}

void QuickSortHoareMiddle(int array[], int left, int right) {
    if (left >= right) return;

    int pivot = left + (right - left) / 2;
    int partition = PartitionHoare(array, left, pivot, right);

    QuickSortHoareMiddle(array, left, partition);
    QuickSortHoareMiddle(array, partition + 1, right);
}

void QuickSortHoareLeft(int array[], int size) {
    QuickSortHoareLeft(array, 0, size - 1);
}

void QuickSortHoareLeft(int array[], int left, int right) {
    if (left >= right) return;

    int pivot = left;
    int partition = PartitionHoare(array, left, pivot, right);

    QuickSortHoareLeft(array, left, partition);
    QuickSortHoareLeft(array, partition + 1, right);
}

void QuickSortHoareRight(int array[], int size) {
    QuickSortHoareRight(array, 0, size - 1);
}

void QuickSortHoareRight(int array[], int left, int right) {
    if (left >= right) return;

    int pivot = right;
    int partition = PartitionHoare(array, left, pivot, right);

    QuickSortHoareRight(array, left, partition);
    QuickSortHoareRight(array, partition + 1, right);
}

int PartitionHoare(int array[], int left, int pivot, int right) {
    Swap(array, pivot, left);

    int pivot_element = array[left];
    int i = left - 1;
    int j = right + 1;

    // at the start of every iteration:
    // left..i are less than or equal to the pivot element
    // j..right are greater than or equal to the pivot element
    // (i+1)..(j-1) are elements yet to be scanned.
    // intential that the pivot element is included in the scan.

    while(1) {
        // no need for bounds check on i and j as they advance, because
        // 1) in the first iteration, unscanned part contains the pivot element.
        // 2) in the later iterations, i (j) cannot go past the old value of j (i).
        do {
            i++;
        } while (array[i] < pivot_element);
        do {
            j--;
        } while (array[j] > pivot_element);

        // array[i] >= pivot element
        // left..(i-1) are less than or equal to the pivot element.
        // array[j] <= pivot element
        // (j+1)..right are greater than or equal to the pivot element.

        if (i >= j) break;

        Swap(array, i, j);
    }

    // when the loop exits, exactly two possibilities:
    // i == j or
    // j + 1 == i

    // In both the cases,
    //   left..(i-1) and (j+1)..right are the two partitions to sort next.
    // Turns out, we can partition as:
    //   left..j and (j+1)..right
    // with guarantee that none of the two partitions is empty (which otherwise
    // would cause infinite recursion).
    return j;
}

// --------------------------------------
// Hoare Partition that returns two indices as partition dividers.

// Sorts the elements at the three indices bringing the median at the middle index.
void MedianInMiddle(int array[], int i, int j, int k) {
    if (array[i] > array[j]) {
        Swap(array, i, j);
    }
    if (array[j] > array[k]) {
        Swap(array, j, k);
        if (array[i] > array[j]) {
            Swap(array, i, j);
        }
    }
}

// Finds the index of the median of three elements.
// Does an insertion sort, with pretend-swaps.
int MedianIndex(int array[], int i, int j, int k) {
    // i, j, k
    if (array[i] > array[j]) {
        // j, i, k;
        if (array[i] > array[k]) {
            // j, k, i
            if (array[j] > array[k]) {
                // k, j, i
                return j;
            }
            else {
                // j, k, i
                return k;
            }
        } else {
            // j, i, k
            return i;
        }
    } else {
        // i, j, k
        if (array[j] > array[k]) {
            // i, k, j
            if (array[i] > array[k]) {
                // k, i, j
                return i;
            } else {
                // i, k, j
                return k;
            }
        } else {
            // i, j, k
            return j;
        }
    }
}

void QuickSortHoareTwoMedianThreeInMiddle(int array[], int left, int right);
void QuickSortHoareTwoMedianThree(int array[], int left, int right);
void QuickSortHoareTwoMiddle(int array[], int left, int right);
void PartitionHoareTwo(int array[], int left, int pivot, int right, int& partleft, int& partright);

void QuickSortHoareTwoMedianThreeInMiddle(int array[], int size) {
    QuickSortHoareTwoMedianThreeInMiddle(array, 0, size - 1);
}

void QuickSortHoareTwoMedianThreeInMiddle(int array[], int left, int right) {
    if (left >= right) return;

    int middle = left + (right - left) / 2;
    MedianInMiddle(array, left, middle, right);
    int pivot = middle;
    int partleft, partright;
    PartitionHoareTwo(array, left, pivot, right, partleft, partright);

    QuickSortHoareTwoMedianThreeInMiddle(array, left, partleft);
    QuickSortHoareTwoMedianThreeInMiddle(array, partright, right);
}

void QuickSortHoareTwoMedianThree(int array[], int size) {
    QuickSortHoareTwoMedianThree(array, 0, size - 1);
}

void QuickSortHoareTwoMedianThree(int array[], int left, int right) {
    if (left >= right) return;

    int middle = left + (right - left) / 2;
    int pivot = MedianIndex(array, left, middle, right);
    int partleft, partright;
    PartitionHoareTwo(array, left, pivot, right, partleft, partright);

    QuickSortHoareTwoMedianThree(array, left, partleft);
    QuickSortHoareTwoMedianThree(array, partright, right);
}

void QuickSortHoareTwoMiddle(int array[], int size) {
    QuickSortHoareTwoMiddle(array, 0, size - 1);
}

void QuickSortHoareTwoMiddle(int array[], int left, int right) {
    if (left >= right) return;

    int pivot = left + (right - left) / 2;
    int partleft, partright;
    PartitionHoareTwo(array, left, pivot, right, partleft, partright);

    QuickSortHoareTwoMiddle(array, left, partleft);
    QuickSortHoareTwoMiddle(array, partright, right);
}

void PartitionHoareTwo(int array[], int left, int pivot, int right, int& partleft, int& partright) {

    int pivot_element = array[pivot];
    int i = left - 1;
    int j = right + 1;

    // at the start of every iteration:
    // left..i are less than or equal to the pivot element
    // j..right are greater than or equal to the pivot element
    // (i+1)..(j-1) are elements yet to be scanned.
    // intential that the pivot element is included in the scan.

    while(1) {
        // no need for bounds check on i and j as they advance, because
        // 1) in the first iteration, unscanned part contains the pivot element.
        // 2) i (or j) cannot go past the old value of j (or i)
        do {
            i++;
        } while (array[i] < pivot_element);
        do {
            j--;
        } while (array[j] > pivot_element);

        // array[i] >= pivot element
        // left..(i-1) are less than or equal to the pivot element.
        // array[j] <= pivot element
        // (j+1)..right are greater than or equal to the pivot element.

        if (i >= j) break;

        Swap(array, i, j);
    }

    // when the loop exits, exactly two possibilities:
    // i == j or
    // j + 1 == i

    // In both the cases,
    //   left..(i-1) and (j+1)..right are the two partitions to sort next.
    partleft = i - 1;
    partright = j + 1;
}
