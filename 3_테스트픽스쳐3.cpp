// 3_테스트픽스쳐3.cpp
#include <iostream>

class Calc {
public:
    // Calc(double n) { } // !
    ~Calc() { std::cout << "Calc 객체 파괴" << std::endl; }

    double Display() { return 0.0; }

    void Enter(double n) { }
    void PressPlus() { }
    void PressMinus() { }
    void PressEquals() { }
};

#include <gtest/gtest.h>

#define SPEC(msg) printf("[SPEC] %s\n", msg)

// 2. Test Fixture를 설치하는 방법
// 3) Implicit Set up/Tear down(암묵적 설치/해체)
// => xUnit Test Framework이 제공하는 기능입니다.
// 방법: 여러 테스트케이스에서 같은 테스트 픽스쳐 설치/해체에 코드를 암묵적으로 호출되는 약속된 함수를 통해서 처리합니다.
//    - 반드시 명시적인 테스트 스위트 클래스를 제공해야 합니다.
//  장점: 테스트 코드 중복을 제거하고, 불필요한 준비 과정을 테스트 케이스 안에서 제거할 수 있습니다.
//  단점: 픽스쳐 설치의 과정이 테스트 케이스 외부에 존재하기 때문에,
//       테스트케이스만으로 테스트 코드를 분석하기 어려울 수 있습니다.

// 3. Test Suite
// => 동일한 테스트 픽스쳐를 공유하는 테스트 케이스의 집합

class CalcTest : public testing::Test {
protected:
    Calc* calc;

    void SetUp() override
    {
        std::cout << "SetUp()" << std::endl;
        calc = new Calc;
    }

    // 테스트의 성공/실패에 상관없이 암묵적으로 호출되는 것이 보장됩니다.
    void TearDown() override
    {
        std::cout << "TearDown()" << std::endl;
        delete calc;
    }
};

// * xUnit Test Pattern에서 테스트 케이스를 구성하는 방법
//  => 4단계 테스트 패턴(Four Phase Test Pattern)
//  - 1단계: 테스트 픽스쳐를 설치하거나, 실제 결과를 관찰하기 위해 필요한 것을 설정합니다. => SetUp
//  - 2단계: SUT와 상호 작용 합니다. => TestCase
//  - 3단계: 기대 결과를 확인합니다.  => TestCase
//  - 4단계: 테스트 픽스쳐를 해체해서, 테스트 시작 이전의 상태로 돌려 놓습니다. => TearDown

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
    // 단언문이 실패할 경우, 이후의 코드를 수행하지 않고, 테스트는 실패합니다.

    // delete calc;
}

TEST_F(CalcTest, PressMinus)
{
    calc->Enter(10);
    calc->PressMinus();
    calc->Enter(10);
    calc->PressEquals();

    ASSERT_EQ(calc->Display(), 0) << "10 - 10 하였을 때";
}
