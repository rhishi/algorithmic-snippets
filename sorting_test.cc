#include <iostream>
#include <vector>
#include <string>
#include "sorting.h"
#include "gtest/gtest.h"

// -----------------------------------------------------------------------------
// QuickSort tests

TEST(QuickSortTest, Empty) {
    int array[] = { };
    int size = 0;
    QuickSort(array, size);
    EXPECT_TRUE(IsSorted(array, size));
}

TEST(QuickSortTest, OneElement) {
    int array[] = { 3 };
    int size = 1;
    QuickSort(array, size);
    EXPECT_TRUE(IsSorted(array, size));
}

TEST(QuickSortTest, TwoElementsAscending) {
    int array[] = { 7, 10 };
    int size = 2;
    QuickSort(array, size);
    EXPECT_TRUE(IsSorted(array, size));
}

TEST(QuickSortTest, TwoElementsDescending) {
    int array[] = { 33, 16 };
    int size = 2;
    QuickSort(array, size);
    EXPECT_TRUE(IsSorted(array, size));
}

TEST(QuickSortTest, SmallExample) {
    int array[] = { 3, 4, 1, 4, 7, 6, 7, 8, 5 };
    int size = 9;
    QuickSort(array, size);
    EXPECT_TRUE(IsSorted(array, size));
}

// -----------------------------------------------------------------------------
// Data-driven tests of QuickSort, using Google Test's value-parameterized tests

#if GTEST_HAS_PARAM_TEST

// Derive from ::testing::TestWithParam<T>, which in turn derives from
// ::testing::Test and ::testing::WithParamInterface<T>.
class SortTestWithStaticExamples : public ::testing::TestWithParam<int> {
    // You can implement all the usual fixture class members here.
    // To access the test parameter, call GetParam() from class TestWithParam<T>.

  public:
    // the static functions, SetUpTestCase and TearDownTestCase, must be public.

    // per-test-case set-up, called before the first test in the test case
    static void SetUpTestCase() {
        std::cout << "Running SetUpTestCase" << std::endl;
        arrays_ = new int*[9] {
            new int[0] { },
            new int[1] { 1 },
            new int[2] { 1, 2 },
            new int[2] { 2, 1 },
            new int[3] { 1, 2, 3 },
            new int[3] { 1, 3, 2 },
            new int[3] { 3, 2, 1 },
            new int[10] { 7, 2, 3, 2, 4, 9, 7, 8, 9, 10 },
            new int[12] { 3, 4, 1, 0, 6, 7, 8, -1, 10, 8, 1, -2 }
        };
        sizes_ = new int[9] { 0, 1, 2, 2, 3, 3, 3, 10, 12 };
        count_ = 9;
    }

    // per-test-case tear-down, called after the last test in the test case
    static void TearDownTestCase() {
        std::cout << "Running TearDownTestCase" << std::endl;
        for (int i = 0; i < count_; i++) {
            delete[] arrays_[i];
            arrays_[i] = nullptr;
        }
        delete[] arrays_;
        arrays_ = nullptr;

        delete[] sizes_;
        sizes_ = nullptr;

        count_ = 0;
    }

  protected:
    // protected members are accessible in bodies of individual tests that use
    // this test fixture (or any derived sub-fixtures).

    void GetArrayAndSize(int** array, int* size) {
        int index = GetParam();
        *array = arrays_[index];
        *size = sizes_[index];
    }

  private:
    // data members could be private to keep them away from derived fixtures,
    // or implementations of individual tests using this fixture.
    static int** arrays_;
    static int* sizes_;
    static int count_;
};

// Remember how C++ works: static members need to be brought into existence
// by declaring them outside the class declaration.  Else, the linker complains.
int** SortTestWithStaticExamples::arrays_ = nullptr;
int* SortTestWithStaticExamples::sizes_ = nullptr;
int SortTestWithStaticExamples::count_ = 0;

// ------------------------------------
// QuickSort tests using examples

class QuickSortTest : public SortTestWithStaticExamples {
    // Nothing here; everything is in the base class.
    // Defined in order to trigger fresh invocations of SetUpTestCase, TearDownTestCase.
};

TEST_P(QuickSortTest, WorksOnExample) {
    int* array;
    int size;
    GetArrayAndSize(&array, &size);
    QuickSort(array, size);
    EXPECT_TRUE(IsSorted(array, size));
}

INSTANTIATE_TEST_CASE_P(InstantiateOnRange, QuickSortTest, ::testing::Range(0, 9));

// ------------------------------------
// QuickSortMiddle tests using examples

class QuickSortMiddleTest : public SortTestWithStaticExamples {
    // Nothing here; everything is in the base class.
    // Defined in order to trigger fresh invocations of SetUpTestCase, TearDownTestCase.
};

TEST_P(QuickSortMiddleTest, WorksOnExample) {
    int* array;
    int size;
    GetArrayAndSize(&array, &size);
    QuickSortMiddle(array, size);
    EXPECT_TRUE(IsSorted(array, size));
}

INSTANTIATE_TEST_CASE_P(InstantiateOnRange, QuickSortMiddleTest, ::testing::Range(0, 9));

// ------------------------------------
// QuickSortLeft tests using examples

class QuickSortLeftTest : public SortTestWithStaticExamples {
    // Nothing here; everything is in the base class.
    // Defined in order to trigger fresh invocations of SetUpTestCase, TearDownTestCase.
};

TEST_P(QuickSortLeftTest, WorksOnExample) {
    int* array;
    int size;
    GetArrayAndSize(&array, &size);
    QuickSortLeft(array, size);
    EXPECT_TRUE(IsSorted(array, size));
}

INSTANTIATE_TEST_CASE_P(InstantiateOnRange, QuickSortLeftTest, ::testing::Range(0, 9));

// ------------------------------------
// QuickSortRight tests using examples

class QuickSortRightTest : public SortTestWithStaticExamples {
    // Nothing here; everything is in the base class.
    // Defined in order to trigger fresh invocations of SetUpTestCase, TearDownTestCase.
};

TEST_P(QuickSortRightTest, WorksOnExample) {
    int* array;
    int size;
    GetArrayAndSize(&array, &size);
    QuickSortRight(array, size);
    EXPECT_TRUE(IsSorted(array, size));
}

INSTANTIATE_TEST_CASE_P(InstantiateOnRange, QuickSortRightTest, ::testing::Range(0, 9));

//------------------------------------------------------------------------------

// SortTestWithStaticExamples is a parameterized test fixture, as exhibited above.
// But it has a problem: one can't write multiple TEST_P tests using the test
// fixture.  That's because the example arrays are static, and tests access them
// directly.  So if one test sorts the array, the second test would get that
// sorted array and not the original version.
//
// The workaround as done above is:
// 1. derive an empty sub-fixture from the base fixture,
// 2. have exactly one TEST_P defined for that sub-fixture, and then
// 3. instantiate the test for a range of indices.
//
// But a better solution is to give each test a fresh copy of the static example.
// This parameterized test fixture achieves that.
//
// Derive from ::testing::TestWithParam<T>, which in turn derives from
// ::testing::Test and ::testing::WithParamInterface<T>.
class SortTestWithExamples : public ::testing::TestWithParam<int> {
    // You can implement all the usual fixture class members here.
    // To access the test parameter, call GetParam() from class TestWithParam<T>.

  public:
    // the static functions, SetUpTestCase and TearDownTestCase, must be public.

    // per-test-case set-up, called before the first test in the test case
    static void SetUpTestCase() {
        std::cout << "Running SetUpTestCase" << std::endl;
        examples_ = std::vector<std::vector<int>> {
            std::vector<int> { },
            std::vector<int> { 1 },
            std::vector<int> { 1, 2 },
            std::vector<int> { 2, 1 },
            std::vector<int> { 2, 2 },
            std::vector<int> { 1, 2, 3 },
            std::vector<int> { 1, 3, 2 },
            std::vector<int> { 2, 1, 3 },
            std::vector<int> { 2, 3, 1 },
            std::vector<int> { 3, 2, 1 },
            std::vector<int> { 3, 1, 2 },
            std::vector<int> { 7, 2, 3, 2, 4, 9, 7, 8, 9, 10 },
            std::vector<int> { 3, 4, 1, 0, 6, 7, 8, -1, 10, 8, 1, -2 }
        };
    }

    // per-test-case tear-down, called after the last test in the test case
    static void TearDownTestCase() {
        std::cout << "Running TearDownTestCase" << std::endl;
        examples_.clear();
    }

  protected:
    // protected members are accessible in bodies of individual tests that use
    // this test fixture (or any derived sub-fixtures).

    // virtual void SetUp() will be called before each test is run.
    virtual void SetUp() {
        int index = GetParam();
        example_ = std::vector<int>{examples_[index]};

        array_ = example_.data();
        size_ = example_.size();
    }

    // virtual void TearDown() will be called after each test is run.
    virtual void TearDown() {
        example_.clear();
        array_ = nullptr;
        size_ = 0;
    }

    std::vector<int> example_;
    int* array_;
    int size_;

  private:
    // data members could be private to keep them away from derived fixtures,
    // or bodies of individual tests that use this fixture.
    static std::vector<std::vector<int>> examples_;
};

// Remember how C++ works: static members need to be brought into existence
// by declaring them outside the class declaration.  Else, the linker complains.
std::vector<std::vector<int>> SortTestWithExamples::examples_;

TEST_P(SortTestWithExamples, QuickSort) {
    QuickSort(array_, size_);
    EXPECT_TRUE(IsSorted(array_, size_));
}

TEST_P(SortTestWithExamples, QuickSortMiddle) {
    QuickSortMiddle(array_, size_);
    EXPECT_TRUE(IsSorted(array_, size_));
}

TEST_P(SortTestWithExamples, QuickSortLeft) {
    QuickSortLeft(array_, size_);
    EXPECT_TRUE(IsSorted(array_, size_));
}

TEST_P(SortTestWithExamples, QuickSortRight) {
    QuickSortRight(array_, size_);
    EXPECT_TRUE(IsSorted(array_, size_));
}

TEST_P(SortTestWithExamples, QuickSortLomutoCLRSMiddle) {
    QuickSortLomutoCLRSMiddle(array_, size_);
    EXPECT_TRUE(IsSorted(array_, size_));
}

TEST_P(SortTestWithExamples, QuickSortLomutoCLRSLeft) {
    QuickSortLomutoCLRSLeft(array_, size_);
    EXPECT_TRUE(IsSorted(array_, size_));
}

TEST_P(SortTestWithExamples, QuickSortLomutoCLRSRight) {
    QuickSortLomutoCLRSRight(array_, size_);
    EXPECT_TRUE(IsSorted(array_, size_));
}

TEST_P(SortTestWithExamples, QuickSortLomutoCLRSEqualityFixMiddle) {
    QuickSortLomutoCLRSEqualityFixMiddle(array_, size_);
    EXPECT_TRUE(IsSorted(array_, size_));
}

TEST_P(SortTestWithExamples, QuickSortHoareMiddle) {
    QuickSortHoareMiddle(array_, size_);
    EXPECT_TRUE(IsSorted(array_, size_));
}

TEST_P(SortTestWithExamples, QuickSortHoareLeft) {
    QuickSortHoareLeft(array_, size_);
    EXPECT_TRUE(IsSorted(array_, size_));
}

TEST_P(SortTestWithExamples, QuickSortHoareRight) {
    QuickSortHoareRight(array_, size_);
    EXPECT_TRUE(IsSorted(array_, size_));
}

TEST_P(SortTestWithExamples, QuickSortHoareTwoMiddle) {
    QuickSortHoareTwoMiddle(array_, size_);
    EXPECT_TRUE(IsSorted(array_, size_));
}

TEST_P(SortTestWithExamples, QuickSortHoareTwoMedianThree) {
    QuickSortHoareTwoMedianThree(array_, size_);
    EXPECT_TRUE(IsSorted(array_, size_));
}

TEST_P(SortTestWithExamples, QuickSortHoareTwoMedianThreeInMiddle) {
    QuickSortHoareTwoMedianThreeInMiddle(array_, size_);
    EXPECT_TRUE(IsSorted(array_, size_));
}

// ------------------------------------------

TEST_P(SortTestWithExamples, InsertionSort) {
    InsertionSort(array_, size_);
    EXPECT_TRUE(IsSorted(array_, size_));
}

TEST_P(SortTestWithExamples, SelectionSort) {
    SelectionSort(array_, size_);
    EXPECT_TRUE(IsSorted(array_, size_));
}

TEST_P(SortTestWithExamples, BubbleSortUp) {
    BubbleSortUp(array_, size_);
    EXPECT_TRUE(IsSorted(array_, size_));
}

TEST_P(SortTestWithExamples, BubbleSortDown) {
    BubbleSortDown(array_, size_);
    EXPECT_TRUE(IsSorted(array_, size_));
}

TEST_P(SortTestWithExamples, BubbleSortUpJumpDownToLastSwap) {
    BubbleSortUpJumpDownToLastSwap(array_, size_);
    EXPECT_TRUE(IsSorted(array_, size_));
}

TEST_P(SortTestWithExamples, BubbleSortDownJumpUpToLastSwap) {
    BubbleSortDownJumpUpToLastSwap(array_, size_);
    EXPECT_TRUE(IsSorted(array_, size_));
}

INSTANTIATE_TEST_CASE_P(InstantiateOnRange, SortTestWithExamples, ::testing::Range(0, 13));

// -----------------------------------------------------------------------------

#if GTEST_HAS_COMBINE

typedef ::testing::tuple<std::string, int> Pattern;

class SortTestWithPatterns : public ::testing::TestWithParam<Pattern> {
  protected:

    virtual void SetUp() {
        std::string name;
        int size;
        std::tie(name, size) = GetParam();

        example_ = std::vector<int>(size);

        if (name == "ascending") {
            for (int i = 0; i < size; i++) {
                example_[i] = i;
            }
        } else if (name == "descending") {
            for (int i = 0; i < size; i++) {
                example_[i] = size - 1 - i;
            }
        } else if (name == "constant") {
            for (int i = 0; i < size; i++) {
                example_[i] = size;
            }
        } else if (name == "uptriangle") {
            for (int i = 0; i < size; i++) {
                example_[i] = (i < size / 2) ? i : size - 1 - i;
            }
        } else if (name == "downtriangle") {
            for (int i = 0; i < size; i++) {
                example_[i] = (i < size / 2) ? size - 1 - i : i;
            }
        }

        array_ = example_.data();
        size_ = example_.size();
    }

    virtual void TearDown() {
        example_.clear();
        array_ = nullptr;
        size_ = 0;
    }

    std::vector<int> example_;
    int* array_;
    int size_;
};

TEST_P(SortTestWithPatterns, QuickSort) {
    QuickSort(array_, size_);
    EXPECT_TRUE(IsSorted(array_, size_));
}

TEST_P(SortTestWithPatterns, QuickSortMiddle) {
    QuickSortMiddle(array_, size_);
    EXPECT_TRUE(IsSorted(array_, size_));
}

TEST_P(SortTestWithPatterns, QuickSortLeft) {
    QuickSortLeft(array_, size_);
    EXPECT_TRUE(IsSorted(array_, size_));
}

TEST_P(SortTestWithPatterns, QuickSortRight) {
    QuickSortRight(array_, size_);
    EXPECT_TRUE(IsSorted(array_, size_));
}

TEST_P(SortTestWithPatterns, QuickSortLomutoCLRSMiddle) {
    QuickSortLomutoCLRSMiddle(array_, size_);
    EXPECT_TRUE(IsSorted(array_, size_));
}

TEST_P(SortTestWithPatterns, QuickSortLomutoCLRSLeft) {
    QuickSortLomutoCLRSLeft(array_, size_);
    EXPECT_TRUE(IsSorted(array_, size_));
}

TEST_P(SortTestWithPatterns, QuickSortLomutoCLRSRight) {
    QuickSortLomutoCLRSRight(array_, size_);
    EXPECT_TRUE(IsSorted(array_, size_));
}

TEST_P(SortTestWithPatterns, QuickSortLomutoCLRSEqualityFixMiddle) {
    QuickSortLomutoCLRSEqualityFixMiddle(array_, size_);
    EXPECT_TRUE(IsSorted(array_, size_));
}

TEST_P(SortTestWithPatterns, QuickSortHoareMiddle) {
    QuickSortHoareMiddle(array_, size_);
    EXPECT_TRUE(IsSorted(array_, size_));
}

TEST_P(SortTestWithPatterns, QuickSortHoareLeft) {
    QuickSortHoareLeft(array_, size_);
    EXPECT_TRUE(IsSorted(array_, size_));
}

TEST_P(SortTestWithPatterns, QuickSortHoareRight) {
    QuickSortHoareRight(array_, size_);
    EXPECT_TRUE(IsSorted(array_, size_));
}

TEST_P(SortTestWithPatterns, QuickSortHoareTwoMiddle) {
    QuickSortHoareTwoMiddle(array_, size_);
    EXPECT_TRUE(IsSorted(array_, size_));
}

TEST_P(SortTestWithPatterns, QuickSortHoareTwoMedianThree) {
    QuickSortHoareTwoMedianThree(array_, size_);
    EXPECT_TRUE(IsSorted(array_, size_));
}

TEST_P(SortTestWithPatterns, QuickSortHoareTwoMedianThreeInMiddle) {
    QuickSortHoareTwoMedianThreeInMiddle(array_, size_);
    EXPECT_TRUE(IsSorted(array_, size_));
}

// ------------------------------------------

TEST_P(SortTestWithPatterns, InsertionSort) {
    InsertionSort(array_, size_);
    EXPECT_TRUE(IsSorted(array_, size_));
}

TEST_P(SortTestWithPatterns, SelectionSort) {
    SelectionSort(array_, size_);
    EXPECT_TRUE(IsSorted(array_, size_));
}

TEST_P(SortTestWithPatterns, BubbleSortUp) {
    BubbleSortUp(array_, size_);
    EXPECT_TRUE(IsSorted(array_, size_));
}

TEST_P(SortTestWithPatterns, BubbleSortDown) {
    BubbleSortDown(array_, size_);
    EXPECT_TRUE(IsSorted(array_, size_));
}

TEST_P(SortTestWithPatterns, BubbleSortUpJumpDownToLastSwap) {
    BubbleSortUpJumpDownToLastSwap(array_, size_);
    EXPECT_TRUE(IsSorted(array_, size_));
}

TEST_P(SortTestWithPatterns, BubbleSortDownJumpUpToLastSwap) {
    BubbleSortDownJumpUpToLastSwap(array_, size_);
    EXPECT_TRUE(IsSorted(array_, size_));
}

const int sizes[] = { 100, 1000, 10000, 20000, 30000, 40000, 50000 };

// One instantiation by combining an array of pattern names and an array of sizes
// is the compact, extendable option.  But then the standard output does not
// display the pattern names.  If we do separate instantiation for each pattern
// name, the displayed test names contain the pattern name, e.g.
// Constant/SortTestWithPatterns.QuickSort/0.
// Note: the XML output generated by --gtest_output=xml does show full parameter
// tuple values in addition to the test names.  So, that's recommended if using
// one instantiation approach.
#if 1
INSTANTIATE_TEST_CASE_P(Constant, SortTestWithPatterns,
    ::testing::Combine(::testing::Values("constant"), ::testing::ValuesIn(sizes)));
INSTANTIATE_TEST_CASE_P(Ascending, SortTestWithPatterns,
    ::testing::Combine(::testing::Values("ascending"), ::testing::ValuesIn(sizes)));
INSTANTIATE_TEST_CASE_P(Descending, SortTestWithPatterns,
    ::testing::Combine(::testing::Values("descending"), ::testing::ValuesIn(sizes)));
INSTANTIATE_TEST_CASE_P(Uptriangle, SortTestWithPatterns,
    ::testing::Combine(::testing::Values("uptriangle"), ::testing::ValuesIn(sizes)));
INSTANTIATE_TEST_CASE_P(Downtriangle, SortTestWithPatterns,
    ::testing::Combine(::testing::Values("downtriangle"), ::testing::ValuesIn(sizes)));
#else
const std::string names[] = { "constant", "ascending", "descending", "uptriangle", "downtriangle" };
INSTANTIATE_TEST_CASE_P(Combine, SortTestWithPatterns,
    ::testing::Combine(::testing::ValuesIn(names), ::testing::ValuesIn(sizes)));
#endif

#else

// Google Test may not support Combine() with some compilers. If we
// use conditional compilation to compile out all code referring to
// the gtest_main library, MSVC linker will not link that library at
// all and consequently complain about missing entry point defined in
// that library (fatal error LNK1561: entry point must be
// defined). This dummy test keeps gtest_main linked in.
TEST(DummyTest, CombineIsNotSupportedOnThisPlatform) {}

#endif  // GTEST_HAS_COMBINE

// -----------------------------------------------------------------------------
// Tests for the small functions MedianInMiddle and MedianIndex

TEST(MedianTest, MedianInMiddle) {
    int examples[][3] = {
        { 1, 2, 3 },
        { 2, 1, 3 },
        { 2, 3, 1 },
        { 3, 2, 1 },
        { 3, 1, 2 },
        { 1, 3, 2 },

        { 1, 1, 3 },
        { 2, 1, 2 },
        { 2, 3, 3 },

        { 3, 3, 1 },
        { 1, 2, 1 },
        { 3, 2, 2 },

        { 1, 1, 1 }
    };
    int medians[] = {
        2, 2, 2, 2, 2, 2,
        1, 2, 3,
        3, 1, 2,
        1
    };
    for (int i = 0; i < 13; i++) {
        MedianInMiddle(examples[i], 0, 1, 2);
        EXPECT_EQ(medians[i], examples[i][1]);
    }
}

TEST(MedianTest, MedianIndex) {
    int examples[][3] = {
        { 1, 2, 3 },
        { 2, 1, 3 },
        { 2, 3, 1 },
        { 3, 2, 1 },
        { 3, 1, 2 },
        { 1, 3, 2 },

        { 1, 1, 3 },
        { 2, 1, 2 },
        { 2, 3, 3 },

        { 3, 3, 1 },
        { 1, 2, 1 },
        { 3, 2, 2 },

        { 1, 1, 1 }
    };
    int median_indices[] = {
        1, 0, 0, 1, 2, 2,
        1, 0, 1,
        0, 2, 2,
        1
    };
    for (int i = 0; i < 13; i++) {
        int index = MedianIndex(examples[i], 0, 1, 2);
        EXPECT_EQ(median_indices[i], index);
    }
}

#else

// Google Test may not support value-parameterized tests with some
// compilers. If we use conditional compilation to compile out all
// code referring to the gtest_main library, MSVC linker will not link
// that library at all and consequently complain about missing entry
// point defined in that library (fatal error LNK1561: entry point
// must be defined). This dummy test keeps gtest_main linked in.
TEST(DummyTest, ValueParameterizedTestsAreNotSupportedOnThisPlatform) {}

#endif  // GTEST_HAS_PARAM_TEST

// -----------------------------------------------------------------------------
