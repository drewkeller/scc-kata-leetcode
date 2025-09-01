#include "Solution.h"
#include <gtest/gtest.h>
#include <gmock/gmock.h>

using namespace testing;
using namespace std;

typedef struct BinaryStringTestObj {
    string Input1;
    string Input2;
    string Result;
    ErrorCode Error;
} BinaryStringTestObj;

typedef struct InvalidTestObj {
    string Input;
    ErrorCode Error;
} InvalidTestObj;

initializer_list<BinaryStringTestObj> ValidTestValues = {
    { "0", "0", "0", ErrorCode::OK },
    { "1", "0", "1", ErrorCode::OK },
    { "0", "1", "1", ErrorCode::OK },
    { "1", "1", "10", ErrorCode::OK },
    { "11", "11", "110", ErrorCode::OK },
    { "10", "10", "100", ErrorCode::OK },
    { "111", "111", "1110", ErrorCode::OK },
    { "101", "101", "1010", ErrorCode::OK },
};

initializer_list<InvalidTestObj> InValidTestValues = {
    { "", ErrorCode::INPUT_EMPTY },
    { "12", ErrorCode::INVALID_BIT_VALUE },
    { string(100001, '1'), ErrorCode::INPUT_TOO_LONG },
    //{ nullptr, ErrorCode::INPUT_IS_NULL }, can't construct string from nullptr
};

void PrintTo(const BinaryStringTestObj& obj, ostream *os)
{
    *os << "{ ";
    *os << "\"" << obj.Input1 << "\" + ";
    *os << "\"" << obj.Input1 << "\"";
    *os << " }";
}

void PrintTo(const InvalidTestObj& obj, ostream *os)
{
    *os << "{ \"" << obj.Input << "\" }";
}

void PrintTo(const ErrorCode errorCode, ostream *os)
{
    *os << static_cast<int>(errorCode);
}

class SolutionTest : public Test {
public:
    Solution solution;
};

 class BinaryStringParsingTest : public SolutionTest, public testing::WithParamInterface<BinaryStringTestObj> {};
 class InvalidBinaryStringParsingTest : public SolutionTest, public testing::WithParamInterface<InvalidTestObj> {};

 INSTANTIATE_TEST_SUITE_P(Valid, BinaryStringParsingTest, ValuesIn(ValidTestValues));
 INSTANTIATE_TEST_SUITE_P(Invalid, InvalidBinaryStringParsingTest, ValuesIn(InValidTestValues));

TEST_P(BinaryStringParsingTest, GIVEN_BinaryString_WHEN_Parsed_THEN_ReturnsCorrectInteger)
{
    auto testObj = GetParam();
    auto result = solution.addBinary(testObj.Input1, testObj.Input2);
    EXPECT_THAT(testObj.Result, result);
    EXPECT_THAT(testObj.Error, solution.Error);
}

TEST_P(InvalidBinaryStringParsingTest, GIVEN_InvalidBinaryString_WHEN_Param1Invalid_THEN_HasCorrectErrorCode)
{
    auto testObj = GetParam();
    auto result = solution.addBinary(testObj.Input, "0");
    EXPECT_THAT(testObj.Error, solution.Error);
}

TEST_P(InvalidBinaryStringParsingTest, GIVEN_InvalidBinaryString_WHEN_Param2Invalid_THEN_HasCorrectErrorCode)
{
    auto testObj = GetParam();
    auto result = solution.addBinary("0", testObj.Input);
    EXPECT_THAT(testObj.Error, solution.Error);
}

TEST_F(SolutionTest, GIVEN_MaxSizePluasMaxSize_THEN_ResultIsCorrect)
{   
    constexpr uint length = 10000;
    string value1(length, '1');
    string result(length + 1, '1');
    result[length] = '0';

    EXPECT_THAT(result, solution.addBinary(value1, value1));
    EXPECT_THAT(ErrorCode::OK, solution.Error);
}

// for debugging
TEST_F(SolutionTest, GIVEN_SpecificValue_THEN_ResultIsCorrect)
{
    string value1 = "11";
    string value2 = "11";
    string result = "110";
    EXPECT_THAT(result, solution.addBinary(value1, value1));
    EXPECT_THAT(ErrorCode::OK, solution.Error);
}