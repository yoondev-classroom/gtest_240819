// 2_3A.cpp
// SUT(System Under Test, 테스트 대상 시스템)
// - CUT(Class Under Test / Code Under Test)
class Calc {
public:
    double Display() { return 0.0; }

    void Enter(double n) { }
    void PressPlus() { }
    void PressMinus() { }
    void PressEquals() { }
};

//----
#include <gtest/gtest.h>

// 1. TestCase를 만드는 방법
//  : TEST 매크로를 이용해서 테스트케이스를 만들 수 있습니다.

// - 테스트 스위트는 테스트 대상 클래스(모듈)의 이름의 마지막에
//   Test / Spec 접미를 사용하는 것이 일반적입니다.

// TEST(테스트 스위트 이름, 테스트 케이스 이름)
TEST(CalcTest, PressPlus)
{
    // 아래 매크로 함수를 통해서 테스트를 명시적으로 실패할 수 있습니다.
    // => 실패의 원인을 함께 작성해주어야 합니다.
    // FAIL();
    FAIL() << "작성 중입니다.";
}

// 2. TestCase를 구성하는 방법 - 3A
// 1) Arrange/Given: 테스트 대상 코드를 초기화하고, 필요한 경우 설정하고 준비합니다.
// 2) Act/When: 테스트 대상 코드에서 작용을 가합니다.
// 3) Assert/Then: 기대하는 바를 단언합니다.

// => TDD(Test Driven Development) / BDD(Behavior Driven Development)
//  1. 가독성
//  => 자연어와 가깝게 테스트 코드를 표현하는 것을 중요하게 생각합니다.
//  2. 행위 검증

// 3. 좋은 단위 테스트
//  1) 가독성
//   - 테스트 코드의 구성
//   - 테스트 케이스가 어떤 동작을 검증하는가
//    => 테스트 케이스의 이름을 통해 드러납니다.
//   - 테스트 케이스가 실패하였을 때, 실패의 원인을 코드를 들여다보지 않아도 파악할 수 있어야 합니다.

//  2) 유지보수성
//   - 테스트 코드는 유지보수의 비용이 최소화될 수 있도록 작성되어야 합니다.
//   - 테스트 코드에 오류 가능성이 있는 제어 구문(조건문, 반복문, 예외 처리)의 발생을 최소화해야 합니다.

//  3) 신뢰성
//   - 테스트 결과를 신뢰할 수 있는가?

#define SPEC(msg) printf("[SPEC] %s\n", msg)

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

#if 0
    if (calc->Display() == 4) {
        SUCCEED();
    } else {
        FAIL();
    }
#endif
    // xUnit Test Framework은 다양한 단언문을 제공하고 있습니다.
    // => Google Test는 매크로의 형태로 제공하고 있습니다.
    // ASSERT_EQ/NE/LT/LE/GT/GE ...
    ASSERT_EQ(calc->Display(), 4) << "2 + 2 하였을 때";
}
