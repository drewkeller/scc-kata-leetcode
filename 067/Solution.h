#pragma once

#include <string>
#include <iostream>
#include <cstdint>

typedef unsigned int uint;
typedef unsigned long ulong;

constexpr uint MAX_LENGTH = 100000;
constexpr char NULL_CHAR = '\0';

enum class ErrorCode {
    OK = 0,
    INPUT_IS_NULL,
    INPUT_EMPTY,
    INPUT_TOO_LONG,
    INVALID_BIT_VALUE,
};

class Solution {
public:
    ErrorCode Error;
    Solution();
    std::string addBinary(std::string a, std::string b);
    void ReverseString(char* str, uint length);
};
