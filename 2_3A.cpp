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
// 1) Arrange: 테스트 대상 코드를 초기화하고, 필요한 경우 설정하고 준비합니다.
// 2) Act: 테스트 대상 코드에서 작용을 가합니다.
// 3) Assert: 기대하는 바를 단언합니다.

TEST(CalcTest, PressPlus2)
{
    // Arrange
    Calc* calc = new Calc;

    // Act
    calc->Enter(2);
    calc->PressPlus();
    calc->Enter(2);
    calc->PressEquals();

    // Assert
    if (calc->Display() == 4) {
        SUCCEED();
    } else {
        FAIL();
    }
}
