// 11_파라미터화테스트3.cpp

bool IsPrime(int value)
{
    // return false;
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
#if 0
using InputType = std::tuple<int, int>;

class PrimeTest : public testing::TestWithParam<InputType> { };

INSTANTIATE_TEST_SUITE_P(PrimeValues, PrimeTest,
    testing::Values(
        InputType { 2, 4 },
        InputType { 3, 6 },
        InputType { 5, 10 },
        InputType { 7, 14 },
        InputType { 11, 22 },
        InputType { 13, 26 }));

TEST_P(PrimeTest, IsPrime_1)
{
    const InputType& data = GetParam();

    EXPECT_TRUE(IsPrime(std::get<0>(data)));
}

TEST_P(PrimeTest, IsPrime_2)
{
    const InputType& data = GetParam();

    EXPECT_FALSE(IsPrime(std::get<1>(data)));
}
#endif

// 2) 사용자 정의 타입
struct InputType {
    int good;
    int bad;
};

class PrimeTest : public testing::TestWithParam<InputType> { };

INSTANTIATE_TEST_SUITE_P(PrimeValues, PrimeTest,
    testing::Values(
        InputType { 2, 4 },
        InputType { 3, 6 },
        InputType { 5, 10 },
        InputType { 7, 14 },
        InputType { 11, 22 },
        InputType { 13, 26 }));

TEST_P(PrimeTest, IsPrime_1)
{
    const InputType& data = GetParam();

    EXPECT_TRUE(IsPrime(data.good));
}

TEST_P(PrimeTest, IsPrime_2)
{
    const InputType& data = GetParam();

    EXPECT_FALSE(IsPrime(data.bad));
}
