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
}
