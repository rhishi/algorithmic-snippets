#include "sorting.h"

// -----------------------------------------------------------------------------
// Utility functions related to sorting

bool IsSorted(int array[], int size) {
    for (int i = 1; i < size; i++) {
        if (array[i - 1] > array[i]) {
            return false;
        }
    }
    return true;
}

void Swap(int array[], int i, int j) {
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
// QuickSort from the K&R book (2nd edition).  Uses Lomuto partition.
// K&R says: Our version of quicksort is not the fastest possible, but it's one
// of the simplest.

void QuickSortLomutoKRMiddle(int array[], int left, int right);
int PartitionLomutoKR(int array[], int left, int pivot, int right);

void QuickSortLomutoKRMiddle(int array[], int size) {
    QuickSortLomutoKRMiddle(array, 0, size - 1);
}

void QuickSortLomutoKRMiddle(int array[], int left, int right) {
    if (left >= right) return;

    int pivot = left + (right - left) / 2;
    pivot = PartitionLomutoKR(array, left, pivot, right);

    QuickSortLomutoKRMiddle(array, left, pivot - 1);
    QuickSortLomutoKRMiddle(array, pivot + 1, right);
}

// K&R Lomuto Partition swaps the pivot to the left, and partitions left+1..right.
// CLRS Lomuto Partition swaps the pivot to the right, and partitions left..right-1.
int PartitionLomutoKR(int array[], int left, int pivot, int right) {
    Swap(array, left, pivot);

    int pivot_element = array[left];
    int i = left;

    for (int j = left + 1; j <= right; j++) {
        if (array[j] < pivot_element) {
            Swap(array, ++i, j);
        }
    }
    // Always: before, during, and after the loop:
    // left+1..i are all elements smaller than the pivot element
    // i+1..j-1 are all elements bigger than or equal to the pivot element
    // j..right are the unprocessed elements

    // Put the pivot in the middle, and return the pivot position
    Swap(array, left, i);
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

// -----------------------------------------------------------------------------

void InsertionSort(int array[], int size) {
    // Insert ith element in sorted range 0..(i-1),
    // for successively increasing i from 1 to size-1.
    for (int i = 1; i < size; i++) {
        int element = array[i];
        int j = i - 1;
        while (j >= 0 && array[j] > element) {
            array[j + 1] = array[j];
            j--;
        }
        array[j + 1] = element;
    }
}

void SelectionSort(int array[], int size) {
    // find a minimum element of range i..(size-1) and swap it with ith element,
    // for successively increasing i from 0 to (size-2).
    for (int i = 0; i < size - 1; i++) {
        int min_index = i;
        for(int j = i + 1; j < size; j++) {
            if (array[j] < array[min_index]) {
                min_index = j;
            }
        }
        Swap(array, i, min_index);
    }
}

void BubbleSortUp(int array[], int size) {
    // bubble up a maximum element of range 0..(i-1) i.e. sub-array of size i
    // for successively decreasing sizes i = size to 2.
    for (int i = size; i > 1; i--) {
        for (int j = 1; j < i; j++) {
            if (array[j - 1] > array[j]) {
                Swap(array, j - 1, j);
            }
        }
    }
}

void BubbleSortDown(int array[], int size) {
    // bubble down a minimum element of range i..(size-1) i.e. sub-array of size (size-i)
    // for successively increasing start index i = 0 to (size-2).
    for (int i = 0; i < size - 1; i++) {
        for (int j = size - 1; j > i; j--) {
            if (array[j - 1] > array[j]) {
                Swap(array, j - 1, j);
            }
        }
    }
}

void BubbleSortUpJumpDownToLastSwap(int array[], int size) {
    // data-dependent optimization to bubble up
    // becomes O(n) for already-sorted input (like InsertionSort)
    int nexti;
    for (int i = size; i > 1; i = nexti) {
        nexti = 0;
        for (int j = 1; j < i; j++) {
            if (array[j - 1] > array[j]) {
                Swap(array, j - 1, j);
                nexti = j;
            }
        }
    }
}

void BubbleSortDownJumpUpToLastSwap(int array[], int size) {
    // data-dependent optimization to bubble down
    // becomes O(n) for already-sorted input (like InsertionSort)
    int nexti;
    for (int i = 0; i < size - 1; i = nexti) {
        nexti = size;
        for (int j = size - 1; j > i; j--) {
            if (array[j - 1] > array[j]) {
                Swap(array, j - 1, j);
                nexti = j;
            }
        }
    }
}
