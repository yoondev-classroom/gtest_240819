// 3_테스트픽스쳐2.cpp
class Calc {
public:
    // Calc(double n) { } // !

    double Display() { return 0.0; }

    void Enter(double n) { }
    void PressPlus() { }
    void PressMinus() { }
    void PressEquals() { }
};

#include <gtest/gtest.h>

#if 0
#define SPEC(msg) printf("[SPEC] %s\n", msg)

// 2. Test Fixture를 설치하는 방법
//   2) Delegate Set up(위임 설치)
//   > 픽스쳐 설치에 관한 코드를 별도의 테스트 유틸리티 함수를 통해 캡슐화합니다.

TEST(CalcTest, PressPlus_TwoPlusTwo_DisplaysFour)
{
    SPEC("2 더하기 2를 하였을 때, Display의 결과가 4 인지를 검증합니다.");
    // Arrange
    Calc* calc = new Calc;

    // Act
    calc->Enter(2);
    calc->PressPlus();
    calc->Enter(2);
    calc->PressEquals();

    // Assert
    ASSERT_EQ(calc->Display(), 4) << "2 + 2 하였을 때";
}

TEST(CalcTest, PressMinus)
{
    Calc* calc = new Calc;

    calc->Enter(10);
    calc->PressMinus();
    calc->Enter(10);
    calc->PressEquals();

    ASSERT_EQ(calc->Display(), 0) << "10 - 10 하였을 때";
}
#endif

// * 암묵적인 테스트 스위트 클래스
//           ::testing::Test
//                  |
//    -----------------------------------
//    |                                  |
//  CalcTest_PressPlus_Test      CalcTest_PressMinus_Test
#if 0
TEST(CalcTest, PressPlus) { }
// class CalcTest_PressPlus_Test : public ::testing::Test

TEST(CalcTest, PressMinus) { }
// class CalcTest_PressMinus_Test : public ::testing::Test
#endif

// * 명시적인 테스트 스위트 클래스를 제공해서, 테스트 케이스를 만드는 방법.
// => 테스트 유틸리티 메소드를 제공하기 위해서

// 1) 명시적인 테스트 스위트 클래스
class CalcTest : public testing::Test { };

//           ::testing::Test
//                  |
//               CalcTest
//                  |
//    -----------------------------------
//    |                                  |
//  CalcTest_PressPlus_Test      CalcTest_PressMinus_Test

// 2) 테스트 케이스
TEST_F(CalcTest, PressPlus) { }
// class CalcTest_PressPlus_Test : public CalcTest

TEST_F(CalcTest, PressMinus) { }
// class CalcTest_PressMinus_Test : public CalcTest
