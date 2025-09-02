#include "Solution.h"
#include <iostream>
#include <sstream>

using namespace std;

constexpr int MAX_INT = 0x7FFFFFFF;

Solution::Solution()
: Error(ErrorCode::OK)
{
    
}

int Solution::rangeBitwiseAnd(int left, int right) {
    int result = left;

    if(left > right) {
        result = 0;
        Error = ErrorCode::RANGE_OUT_OF_SEQUENCE;
    }

    int shifted = GetShiftedSignificance(left, 0);
    left = left >> shifted;
    right = right >> shifted;
    result = left;
    
    int current = left;
    int rightHighestSignificant = GetHighestSignificantValue(left);
    int rightMin = min(right, rightHighestSignificant);
    result = result & right;

    while (current < MAX_INT && ++current <= rightMin && Error == ErrorCode::OK)
    {
        result = result & current;

        int newShifted = GetShiftedSignificance(result, shifted);
        if(newShifted > 0) {
            result = result >> newShifted;
            rightMin = rightMin >> newShifted;
            current = current >> newShifted;
            shifted += newShifted;
        }

        // ANDing 0 with any number will always be 0
        if (result == 0) {
            break;
        }
    }

    result = result << shifted;

    return result;
}

// Get how many rightward shifts can be done, i.e. 0x1000 can be right shifted 4 places
int Solution::GetShiftedSignificance(int value, int currentShift) {
    uint bitIndex = 0;
    uint highestNonZeroBitIndex = 0;

    while (bitIndex <= (31 - currentShift) && value > 0 && (value & 0x1) == 0) {
        value = value >> 1;
        bitIndex++;
    }

    return bitIndex;
}

int Solution::GetHighestSignificantValue(int left)
{
    uint bitIndex = 0;
    uint highestNonZeroBitIndex = 0;

    while (bitIndex <= 31 & left > 0) {
        if (left & 0x1 > 0) {
            highestNonZeroBitIndex = bitIndex;
        }
        left = left >> 1;
        bitIndex++;
    }

    // if left is 11, then highest significant value is is 111
    uint highestMask = (1 << (highestNonZeroBitIndex + 1));
    highestMask -= 1;
    highestMask = (highestMask << 1) + 1;

    return highestNonZeroBitIndex == 30 
        ? MAX_INT
        : (int)highestMask;
}