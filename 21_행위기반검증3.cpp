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

// 중요: EXPECT_CALL().WillOnce/WillRepeatedly를 사용하면, Times에 영향을 줍니다.

// - EXPECT_CALL(...)
// => EXPECT_CALL(...).Times(1)

// - EXPECT_CALL(...).WillOnce(...)
// => EXPECT_CALL(...).Times(1)

// - EXPECT_CALL(...).WillOnce(...).WillOnce(...)
// => EXPECT_CALL(...).Times(2)

// - EXPECT_CALL(...).WillOnce(...).WillOnce(...).WillOnce(...)
// => EXPECT_CALL(...).Times(3)

// - EXPECT_CALL(...).WillOnce(...).WillOnce(...).WillOnce(...)
// => WillOnce: N
//    WillRepeatedly: AtLeast
//    : EXPECT_CALL(...).Times(AtLeast(N))

// * WillRepeatedly는 한번만 사용 가능합니다.
//   WillOnce 존재한다면 WillOnce 후에 사용이 가능합니다.

TEST(CalcTest, Process3)
{
    MockCalc mock;

    EXPECT_CALL(mock, Add(10, 20))
        .WillOnce(Return(30))
        .WillOnce(Return(300))
        .WillRepeatedly(Return(1000)); // 2번 이상

    std::cout << mock.Add(10, 20) << std::endl; // 30
    std::cout << mock.Add(10, 20) << std::endl; // 300
    std::cout << mock.Add(10, 20) << std::endl; // 1000
    std::cout << mock.Add(10, 20) << std::endl; // 1000
    std::cout << mock.Add(10, 20) << std::endl; // 1000
    std::cout << mock.Add(10, 20) << std::endl; // 1000
}

TEST(CalcTest, Process4)
{
    MockCalc mock;

    EXPECT_CALL(mock, Add(10, 20))
        .WillRepeatedly(Return(1000)); // Times(AtLeast(0)) ; 0번 이상
    // 위의 행위 기반 검증은 실패하지 않습니다.
}
