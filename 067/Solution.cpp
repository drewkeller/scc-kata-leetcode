#include "Solution.h"
#include <iostream>
#include <sstream>
#include <iomanip>
#include <algorithm>

using namespace std;

Solution::Solution()
: Error(ErrorCode::OK)
{
    
}

string Solution::addBinary(string a, string b) 
{
    constexpr uint MAX_LENGTH = 100000;
    constexpr uint INVALID_BIT = 0xFFFF;
    string result(MAX_LENGTH, '-');

    ErrorCode error = ErrorCode::OK;

    struct BinaryString {
        ulong Length;
        const char* Ptr;
    };

    ulong lengthA = a.length();
    ulong lengthB = b.length();
    ulong length = 0;

    const char* ptrA = &a[lengthA-1];
    const char* ptrB = &b[lengthB-1];

    uint carry = 0;

    if(lengthA == 0 || lengthB == 0)
    {
        error = ErrorCode::INPUT_EMPTY;
    }

    if(lengthA > MAX_LENGTH || lengthB > MAX_LENGTH) {
        error = ErrorCode::INPUT_TOO_LONG;
    }

    while(error == ErrorCode::OK && (ptrA >= &a[0] || ptrB >= &b[0] || carry > 0))
    {
        uint bitA = 0;
        if(length < lengthA) {
            bitA = *ptrA == '0' ? 0 : *ptrA == '1' ? 1 : INVALID_BIT;
            ptrA--;
        }

        uint bitB = 0;
        if(length < lengthB) {
            bitB = *ptrB == '0' ? 0 : *ptrB == '1' ? 1 : INVALID_BIT;
            ptrB--;
        }

        if(bitA == INVALID_BIT || bitB == INVALID_BIT)
        {
            error = ErrorCode::INVALID_BIT_VALUE;
            break;
        }

        if(bitA == 1 && bitB == 1 && carry > 0) {
            result[length] = '1';
        } else if(bitA == 1 && bitB == 1) {
            result[length] = '0';
            carry++;
        } else if((bitA == 1 || bitB == 1) && carry > 0) {
            result[length] = '0';
        } else if(bitA == 1 || bitB == 1) {
            result[length] = '1';
        } else if(carry > 0) {
            result[length] = '1';
            carry--;
        } else {
            result[length] = '0';
        }

        length++;
    }
    result.resize(length);

    if(error == ErrorCode::OK)
    {
        ReverseString(&result[0], length);
    } else {
        result.resize(0);
    }

    Error = error;
    return result;
}

void Solution::ReverseString(char* str, uint length) 
{
    char* startPtr = str;
    char* endPtr = str + length - 1;
    while(startPtr < endPtr) {
        swap(*startPtr, *endPtr);
        startPtr++;
        endPtr--;
    }
}
