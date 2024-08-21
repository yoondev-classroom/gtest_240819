// 21_행위기반검증3.cpp
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

using testing::NiceMock;
using testing::Return;

TEST(CalcTest, Process)
{
    MockCalc mock;
    ON_CALL(mock, Add(10, 20)).WillByDefault(Return(30));
    ON_CALL(mock, Sub(100, 50)).WillByDefault(Return(50));

    EXPECT_CALL(mock, Add(10, 20));
    EXPECT_CALL(mock, Sub(100, 50));

    Process(&mock);
}

// EXPECT_CALL과 ON_CALL을 동시에 사용할 경우,
// EXPECT_CALL을 통해서 ON_CALL을 사용하지 않고,
// Delegating을 수행할 수 있습니다.
//  => EXPECT_CALL(...).WillOnce(...)

TEST(CalcTest, Process2)
{
    MockCalc mock;

    EXPECT_CALL(mock, Add(10, 20)).WillOnce(Return(30));
    EXPECT_CALL(mock, Sub(100, 50)).WillOnce(Return(50));

    Process(&mock);
}
