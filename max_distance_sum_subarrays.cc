/*
  Maximum Distance between Sums of non-overlapping Sub-Arrays

  GfG: http://practice.geeksforgeeks.org/problems/max-absolute-difference/0
  My notes: https://docs.google.com/document/d/1ydf8JyLhTQjsoowyG6lq29FhxzvRbOsOmBWTW8tfPaY/

  Given an array of integers, find two non-overlapping, contiguous sub-arrays
  such that the absolute value of the difference between the sums of the
  sub-arrays is maximum.
  p.s. for starters, just find the maximum value, not the sub-arrays.

  For the full program mode, here's sample input and output:

  Input:
    2
    7
    2 -1 -2 1 -4 2 8
    8
    -2 -3 4 -1 -2 1 5 -3
  Output:
    16
    12

  v1 (2017.07): O(n) time, O(n) space. Marked correct by GfG. Full program mode.
*/

#include <iostream>
#include <vector>

struct MinMax {
    int min;
    int max;
};

int min(const int x, const int y) { return x < y ? x : y; }
int max(const int x, const int y) { return x > y ? x : y; }
int max(const int x, const int y, const int z, const int w) { return max(x, max(y, max(z, w))); }
int abs(const int x) { return x < 0 ? -x : x; }

std::vector<MinMax> RowMinMaxes(const std::vector<int>& array) {
    const int size = array.size();
    std::vector<MinMax> rowminmax(size);

    rowminmax[size - 1] = { array[size - 1], array[size - 1] };
    for (int i = size - 2; i >= 0; i--) {
        rowminmax[i] = {
            min(array[i], array[i] + rowminmax[i + 1].min),
            max(array[i], array[i] + rowminmax[i + 1].max)
        };
    }

    return rowminmax;
}

std::vector<MinMax> ColMinMaxes(const std::vector<int>& array) {
    const int size = array.size();
    std::vector<MinMax> colminmax(size);

    colminmax[0] = { array[0], array[0] };
    for (int i = 1; i < size; i++) {
        colminmax[i] = {
            min(array[i], array[i] + colminmax[i - 1].min),
            max(array[i], array[i] + colminmax[i - 1].max)
        };
    }

    return colminmax;
}

std::vector<MinMax> LowerMinMaxes(const std::vector<MinMax>& rowminmax) {
    const int size = rowminmax.size();
    std::vector<MinMax> lowerminmax(size);

    lowerminmax[size - 1] = rowminmax[size - 1];
    for (int i = size - 2; i >= 0; i--) {
        lowerminmax[i] = {
            min(rowminmax[i].min, lowerminmax[i + 1].min),
            max(rowminmax[i].max, lowerminmax[i + 1].max)
        };
    }

    return lowerminmax;
}

std::vector<MinMax> UpperMinMaxes(const std::vector<MinMax>& colminmax) {
    const int size = colminmax.size();
    std::vector<MinMax> upperminmax(size);

    upperminmax[0] = colminmax[0];
    for (int i = 1; i < size; i++) {
        upperminmax[i] = {
            min(colminmax[i].min, upperminmax[i - 1].min),
            max(colminmax[i].max, upperminmax[i - 1].max)
        };
    }

    return upperminmax;
}

int MaxDistanceSumSubArrays(const std::vector<int>& array) {
    auto upperminmax = UpperMinMaxes(ColMinMaxes(array));
    auto lowerminmax = LowerMinMaxes(RowMinMaxes(array));

    const int size = array.size();
    int maxdist = 0;
    for (int i = 0; i < size - 1; i++) {
        auto n1 = upperminmax[i].min;
        auto x1 = upperminmax[i].max;
        auto n2 = lowerminmax[i + 1].min;
        auto x2 = lowerminmax[i + 1].max;
        auto maxdisti = max(
            abs(n1 - n2),
            abs(n1 - x2),
            abs(x1 - n2),
            abs(x1 - x2));
        maxdist = max(maxdist, maxdisti);
    }
    return maxdist;
}

int main() {
    int count;
    std::cin >> count;
    while (count--) {
        int size;
        std::cin >> size;
        std::vector<int> array(size);
        for (int i = 0; i < size; i++) {
            std::cin >> array[i];
        }
        std::cout << MaxDistanceSumSubArrays(array) << std::endl;
    }
    return 0;
}
