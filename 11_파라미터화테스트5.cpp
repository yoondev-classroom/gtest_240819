// 11_파라미터화테스트5.cpp
#include <gtest/gtest.h>

// * 파라미터화 테스트에서 데이터셋을 정의하는 함수
// 1) testing::Values(1, 2, 3, 4, 5)
// 2) int data[] = { 1, 2, 3, 4, 5 };
//    testing::ValuesIn(data)
// 3) testing::Range(start, end, step)
//    [start, end)
// 4) testing::Combine(
//       testing::Values(1, 2, 3, 4, 5),
//       testing::ValuesIn(data)
//    )
class SampleTest : public testing::TestWithParam<int> {
protected:
    void SetUp() override
    {
        std::cout << "SetUp()" << std::endl;
    }

    void TearDown() override
    {
        std::cout << "TearDown()" << std::endl;
    }

    static void SetUpTestSuite()
    {
        std::cout << "SetUpTestSuite()" << std::endl;
    }

    static void TearDownTestSuite()
    {
        std::cout << "TearDownTestSuite()" << std::endl;
    }
};

// 1<100 => 1 ~ 99
INSTANTIATE_TEST_SUITE_P(IntValues, SampleTest,
    // testing::Range(1, 100));
    testing::Range(1, 100, 5));

TEST_P(SampleTest, IntTest)
{
    std::cout << GetParam() << std::endl;
}

// * Google Test에서 테스트 케이스를 만드는 3가지 방법
// 1) TEST - 암묵적인 테스트 스위트 클래스
// 2) TEST_F - 명시적인 테스트 스위트 클래스
//             class SampleTest : public testing::Test {};

// 3) TEST_P - 파라미터화 테스트
//             class SampleTest : public testing::TestWithParam<T> {};
