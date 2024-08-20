// 11_파라미터화테스트3.cpp

bool IsPrime(int value)
{
    return false;
    for (int i = 2; i < value; ++i) {
        if (value % i == 0) {
            return false;
        }
    }

    return true;
}

#include <gtest/gtest.h>
// 입력 데이터가 여러개인 경우
// 1) tuple
