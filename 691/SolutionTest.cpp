#include "Solution.h"
#include <gtest/gtest.h>
#include <gmock/gmock.h>

using namespace testing;
using namespace std;

typedef struct TestObj {
    int Result;
    string Target;
    vector<string> Stickers;
} TestObj;

initializer_list<TestObj> TestValues = {
    { 3, "thehat", {"with", "example", "science"} },
    { -1, "basicbasic", {"notice", "possible"}},
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
 
TEST_P(TestObjFixture, GIVEN_Inputs_THEN_ReturnsCorrectResult)
{
    TestObj testObj = GetParam();
    EXPECT_THAT(testObject.Result, solution.minStickers(testObject.Stickers, testObject.Target));
}

// for debugging
TEST_F(SolutionTest, GIVEN_SpecificValue_THEN_ResultIsCorrect)
{
    TestObj testObj = { 3, "thehat", {"with", "example", "science"} };
    EXPECT_THAT(testObj.Result, solution.minStickers(testObject.Stickers, testObject.Target));
    EXPECT_THAT(ErrorCode::OK, solution.Error);
}