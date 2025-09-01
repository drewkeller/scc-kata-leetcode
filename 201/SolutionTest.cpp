#include "Solution.h"
#include <gtest/gtest.h>
#include <gmock/gmock.h>

using namespace testing;
using namespace std;

typedef struct TestObj {
    int Left;
    int Right;
    int Result;
} TestObj;

initializer_list<TestObj> TestValues = {
    { 0, 0, 0},
    { 1, 1, 1},
    { 5, 7, 4},
    { 1, 4, 0},
    { 1, 5, 0},
    { 2, 6, 0},
    { 1, 2147483647, 0},
    { 1073741824, 2147483647, 1073741824},
    { 2147483647, 2147483647, 2147483647},
};

void PrintTo(const TestObj& obj, ostream *os)
{
    *os << "{ ";
    *os << obj.Left << ", ";
    *os << obj.Right;
    *os << " }";
}

void PrintTo(const ErrorCode errorCode, ostream *os)
{
    *os << static_cast<int>(errorCode);
}

class SolutionTest : public Test {
public:
    Solution solution;
};

 class TestObjFixture : public SolutionTest, public testing::WithParamInterface<TestObj> {};
 
 INSTANTIATE_TEST_SUITE_P(TestSuite, TestObjFixture, ValuesIn(TestValues));
 
TEST_P(TestObjFixture, GIVEN_Range_WHEN_ANDed_THEN_ReturnsCorrectResult)
{
    auto testObj = GetParam();
    auto result = solution.rangeBitwiseAnd(testObj.Left, testObj.Right);
    EXPECT_THAT(testObj.Result, result);
    EXPECT_THAT(ErrorCode::OK, solution.Error);
}

// for debugging
TEST_F(SolutionTest, GIVEN_SpecificValue_THEN_ResultIsCorrect)
{
    TestObj testObj = { 2, 6, 0};
    EXPECT_THAT(testObj.Result, solution.rangeBitwiseAnd(testObj.Left, testObj.Right));
    EXPECT_THAT(ErrorCode::OK, solution.Error);
}