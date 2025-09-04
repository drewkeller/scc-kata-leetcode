#pragma once

#include <string>
#include <iostream>
#include <vector>

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
    int minStickers(vector<string>& stickers, string target);
};
