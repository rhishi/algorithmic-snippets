#ifndef SORTING_H_
#define SORTING_H_

bool IsSorted(int array[], int size);

void QuickSort(int array[], int size);
void QuickSortMiddle(int array[], int size);
void QuickSortLeft(int array[], int size);
void QuickSortRight(int array[], int size);

void QuickSortLomutoCLRSMiddle(int array[], int size);
void QuickSortLomutoCLRSLeft(int array[], int size);
void QuickSortLomutoCLRSRight(int array[], int size);

void QuickSortLomutoCLRSEqualityFixMiddle(int array[], int size);

void QuickSortHoareMiddle(int array[], int size);
void QuickSortHoareLeft(int array[], int size);
void QuickSortHoareRight(int array[], int size);

void QuickSortHoareTwoMedianThreeInMiddle(int array[], int size);
void QuickSortHoareTwoMedianThree(int array[], int size);
void QuickSortHoareTwoMiddle(int array[], int size);

void MedianInMiddle(int array[], int i, int j, int k);
int MedianIndex(int array[], int i, int j, int k);

void InsertionSort(int array[], int size);
void SelectionSort(int array[], int size);
void BubbleSortUp(int array[], int size);
void BubbleSortDown(int array[], int size);
void BubbleSortUpJumpDownToLastSwap(int array[], int size);
void BubbleSortDownJumpUpToLastSwap(int array[], int size);

#endif // #ifndef SORTING_H_
