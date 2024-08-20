// 11_파라미터화테스트3.cpp

bool IsPrime(int value)
{

    for (int i = 2; i < value; ++i) {
        if (value % i == 0) {
            // return false;
            return true;
        }
    }

    // return true;
    return false;
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
// => Google Test에서 사용자 정의 타입이 표현될 때,
//    원하는 형태로 표현될 수 있도록 연산자 재정의를 제공해주어야 합니다.

struct InputType {
    int good;
    int bad;
};

// 연산자 재정의 함수
std::ostream& operator<<(std::ostream& os, const InputType& data)
{
    return os << "{" << "good: " << data.good << ", bad: " << data.bad << "}";
}

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
