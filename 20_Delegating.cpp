// 20_Delegating.cpp
#include <iostream>
using namespace std;

class Calc {
public:
    virtual ~Calc() { }

    virtual int Add(int a, int b) { return a + b; }
    virtual int Sub(int a, int b) { return a - b; }
};

void Process(Calc* p)
{
    if (p->Add(10, 20) == 30) {
        int result = p->Sub(100, 50);
        std::cout << "result: " << result << std::endl;
    }
}

#include <gmock/gmock.h>

class MockCalc : public Calc {
public:
    MOCK_METHOD(int, Add, (int a, int b), (override));
    MOCK_METHOD(int, Sub, (int a, int b), (override));
};
// - MOCK_METHOD 된 함수의 결과는 기본값을 반환합니다.
// - Google Mock은 MOCK_METHOD를 수행한 메소드에 대해서, 결과를 제어할 수 있는 기능을 제공합니다.
//   => Delegating(위임)
//    ON_CALL

using testing::Return;

TEST(CalcTest, Process)
{
    MockCalc mock;
    ON_CALL(mock, Add(10, 20)).WillByDefault(Return(30));

    EXPECT_CALL(mock, Add(10, 20));
    EXPECT_CALL(mock, Sub(100, 50));

    // std::cout << mock.Add(10, 20) << std::endl;
    // std::cout << mock.Sub(100, 50) << std::endl;

    Process(&mock);
}
