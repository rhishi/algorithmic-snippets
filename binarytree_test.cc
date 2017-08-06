#include <string>
#include <sstream>
#include <unordered_map>
#include "gtest/gtest.h"
#include "binarytree.h"
#include "binarytreeexamples.h"

#if GTEST_HAS_PARAM_TEST

typedef BinaryTreeNode* (*BinaryTreeExample)();

class BinaryTreeTestWithExamples : public ::testing::TestWithParam<std::string> {
  public:

    static void SetUpTestCase() {
        example_.insert({
            { "SimpleThree"    , SimpleThreeBinaryTree },
            { "SimpleFour"     , SimpleFourBinaryTree },
            { "SimpleFive"     , SimpleFiveBinaryTree },
            { "SimpleSix"      , SimpleSixBinaryTree },
            { "SimpleFull"     , SimpleFullBinaryTree },
            { "SimpleComplete" , SimpleCompleteBinaryTree },
            { "SimpleTen"      , SimpleTenBinaryTree }
        });
        expected_preorder_.insert({
            { "SimpleThree"   , "1 2 3 " },
            { "SimpleFour"    , "1 2 3 4 " },
            { "SimpleFive"    , "1 2 4 5 3 " },
            { "SimpleSix"     , "1 2 4 3 5 6 " },
            { "SimpleFull"    , "3 2 1 4 1 5 4 " },
            { "SimpleComplete", "5 3 3 5 2 4 4 5 6 " },
            { "SimpleTen"     , "8 5 9 7 1 6 2 4 5 3 " }
        });
        expected_inorder_.insert({
            { "SimpleThree"   , "2 1 3 " },
            { "SimpleFour"    , "2 1 4 3 " },
            { "SimpleFive"    , "4 2 5 1 3 " },
            { "SimpleSix"     , "4 2 1 5 3 6 " },
            { "SimpleFull"    , "1 2 1 4 5 3 4 " },
            { "SimpleComplete", "5 3 2 3 4 5 5 4 6 " },
            { "SimpleTen"     , "9 5 1 7 2 6 8 4 3 5 " }
        });
        expected_postorder_.insert({
            { "SimpleThree"   , "2 3 1 " },
            { "SimpleFour"    , "2 4 3 1 " },
            { "SimpleFive"    , "4 5 2 3 1 " },
            { "SimpleSix"     , "4 2 5 6 3 1 " },
            { "SimpleFull"    , "1 1 5 4 2 4 3 " },
            { "SimpleComplete", "5 2 3 4 3 5 6 4 5 " },
            { "SimpleTen"     , "9 1 2 6 7 5 3 5 4 8 " }
        });
    }

    static void TearDownTestCase() {
        example_.clear();
        expected_preorder_.clear();
        expected_inorder_.clear();
        expected_postorder_.clear();
    }

  protected:

    virtual void SetUp() {
        auto param = GetParam();
        auto example = example_[param];
        root_ = (*example)();
    }

    virtual void TearDown() {
        BinaryTreeDelete(root_);
    }

    BinaryTreeNode* root_;

    static std::unordered_map<std::string, BinaryTreeExample> example_;

    static std::unordered_map<std::string, std::string> expected_preorder_;
    static std::unordered_map<std::string, std::string> expected_inorder_;
    static std::unordered_map<std::string, std::string> expected_postorder_;
};

std::unordered_map<std::string, BinaryTreeExample> BinaryTreeTestWithExamples::example_;

std::unordered_map<std::string, std::string> BinaryTreeTestWithExamples::expected_preorder_;
std::unordered_map<std::string, std::string> BinaryTreeTestWithExamples::expected_inorder_;
std::unordered_map<std::string, std::string> BinaryTreeTestWithExamples::expected_postorder_;


TEST_P(BinaryTreeTestWithExamples, PreOrderRecursive) {
    std::ostringstream os;
    BinaryTreePrintPreOrderRecursive(root_, os);
    auto expected = expected_preorder_[GetParam()];
    auto actual = os.str();
    EXPECT_EQ(expected, actual);
}

TEST_P(BinaryTreeTestWithExamples, InOrderRecursive) {
    std::ostringstream os;
    BinaryTreePrintInOrderRecursive(root_, os);
    auto expected = expected_inorder_[GetParam()];
    auto actual = os.str();
    EXPECT_EQ(expected, actual);
}

TEST_P(BinaryTreeTestWithExamples, PostOrderRecursive) {
    std::ostringstream os;
    BinaryTreePrintPostOrderRecursive(root_, os);
    auto expected = expected_postorder_[GetParam()];
    auto actual = os.str();
    EXPECT_EQ(expected, actual);
}

TEST_P(BinaryTreeTestWithExamples, PreOrderNonRecursive) {
    std::ostringstream os;
    BinaryTreePrintPreOrderNonRecursive(root_, os);
    auto expected = expected_preorder_[GetParam()];
    auto actual = os.str();
    EXPECT_EQ(expected, actual);
}

INSTANTIATE_TEST_CASE_P(Values, BinaryTreeTestWithExamples,
    ::testing::Values("SimpleThree", "SimpleFour", "SimpleFive",
        "SimpleSix", "SimpleFull", "SimpleComplete", "SimpleTen"));

#else

// Google Test may not support value-parameterized tests with some
// compilers. If we use conditional compilation to compile out all
// code referring to the gtest_main library, MSVC linker will not link
// that library at all and consequently complain about missing entry
// point defined in that library (fatal error LNK1561: entry point
// must be defined). This dummy test keeps gtest_main linked in.
TEST(DummyTest, ValueParameterizedTestsAreNotSupportedOnThisPlatform) {}

#endif  // GTEST_HAS_PARAM_TEST
