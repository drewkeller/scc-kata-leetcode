#include "Solution.h"
#include <gtest/gtest.h>
#include <gmock/gmock.h>

using namespace testing;

class SolutionTest : public testing::Test {
protected:
    void SetUp() {
    }
//public:
};

TEST_F(SolutionTest, WHEN_ValidCoinIsInserted_THEN_CoinIsRecognized)
{
    EXPECT_THAT(true, true);
}
