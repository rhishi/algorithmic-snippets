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
class SortTestWithExamples : public ::testing::TestWithParam<int> {
    // You can implement all the usual fixture class members here.
    // To access the test parameter, call GetParam() from class
    // TestWithParam<T>.

  public:
    // the static functions, SetUpTestCase and TearDownTestCase, must be public.

    // per-test-case set-up, called before the first test in the test case
    static void SetUpTestCase() {
        arrays_ = new int*[8] {
            new int[0] { },
            new int[1] { 1 },
            new int[2] { 1, 2},
            new int[2] { 2, 1},
            new int[3] { 1, 2, 3},
            new int[3] { 1, 3, 2},
            new int[3] { 3, 2, 1},
            new int[10] { 7, 2, 3, 2, 4, 9, 7, 8, 9, 10 }
        };
        sizes_ = new int[8] { 0, 1, 2, 2, 3, 3, 3, 10 };
        count_ = 8;
    }

    // per-test-case tear-down, called after the last test in the test case
    static void TearDownTestCase() {
        for (int i = 0; i < count_; i++) {
            delete[] arrays_[i];
            arrays_[i] = NULL;
        }
        delete[] arrays_;
        arrays_ = NULL;

        delete[] sizes_;
        sizes_ = NULL;

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
int** SortTestWithExamples::arrays_ = NULL;
int* SortTestWithExamples::sizes_ = NULL;
int SortTestWithExamples::count_ = 0;

TEST_P(SortTestWithExamples, QuickSortWorksOnExample) {
    int* array;
    int size;
    GetArrayAndSize(&array, &size);
    QuickSort(array, size);
    EXPECT_TRUE(IsSorted(array, size));
}

INSTANTIATE_TEST_CASE_P(Instance, SortTestWithExamples, ::testing::Range(0, 8));

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
