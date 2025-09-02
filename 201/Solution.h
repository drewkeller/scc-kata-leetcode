#pragma once

#include <string>
#include <iostream>
#include <cstdint>

typedef unsigned int uint;
typedef unsigned long ulong;

enum class ErrorCode {
    OK = 0,
    RANGE_OUT_OF_SEQUENCE,
};

class Solution {
public:
    ErrorCode Error;
    Solution();
    int rangeBitwiseAnd(int left, int right);
    int GetShiftedSignificance(int value, int currentShift);
    int GetHighestSignificantValue(int left);
};
