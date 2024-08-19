// 3_테스트픽스쳐3.cpp
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

#define SPEC(msg) printf("[SPEC] %s\n", msg)

// 2. Test Fixture를 설치하는 방법
// 3) Implicit Set up(암묵적 설치)
// => xUnit Test Framework이 제공하는 기능입니다.
// 방법: 여러 테스트케이스에서 같은 테스트 픽스쳐 설치에 코드를 암묵적으로 호출되는 약속된 함수를 통해서 처리합니다.
//    - 반드시 명시적인 테스트 스위트 클래스를 제공해야 합니다.

class CalcTest : public testing::Test {
protected:
    Calc* calc;

    void SetUp()
    {
        std::cout << "SetUp()" << std::endl;
        calc = new Calc;
    }
};

TEST_F(CalcTest, PressPlus_TwoPlusTwo_DisplaysFour)
{
    SPEC("2 더하기 2를 하였을 때, Display의 결과가 4 인지를 검증합니다.");
    // Act
    calc->Enter(2);
    calc->PressPlus();
    calc->Enter(2);
    calc->PressEquals();

    // Assert
    ASSERT_EQ(calc->Display(), 4) << "2 + 2 하였을 때";
}

TEST_F(CalcTest, PressMinus)
{
    calc->Enter(10);
    calc->PressMinus();
    calc->Enter(10);
    calc->PressEquals();

    ASSERT_EQ(calc->Display(), 0) << "10 - 10 하였을 때";
}
