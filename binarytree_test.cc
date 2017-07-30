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
            { "SimpleThree", SimpleThreeBinaryTree },
            { "SimpleFour" , SimpleFourBinaryTree },
            { "SimpleFive" , SimpleFiveBinaryTree }
        });
        expected_preorder_.insert({
            { "SimpleThree", "1 2 3 " },
            { "SimpleFour" , "1 2 3 4 " },
            { "SimpleFive" , "1 2 4 5 3 " }
        });
        expected_inorder_.insert({
            { "SimpleThree", "2 1 3 " },
            { "SimpleFour" , "2 1 4 3 " },
            { "SimpleFive" , "4 2 5 1 3 " }
        });
        expected_postorder_.insert({
            { "SimpleThree", "2 3 1 " },
            { "SimpleFour" , "2 4 3 1 " },
            { "SimpleFive" , "4 5 2 3 1 " }
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
    ::testing::Values("SimpleThree", "SimpleFour", "SimpleFive"));

#else

// Google Test may not support value-parameterized tests with some
// compilers. If we use conditional compilation to compile out all
// code referring to the gtest_main library, MSVC linker will not link
// that library at all and consequently complain about missing entry
// point defined in that library (fatal error LNK1561: entry point
// must be defined). This dummy test keeps gtest_main linked in.
TEST(DummyTest, ValueParameterizedTestsAreNotSupportedOnThisPlatform) {}

#endif  // GTEST_HAS_PARAM_TEST
