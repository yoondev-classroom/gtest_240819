// 18_Mocking2.cpp
#include <gmock/gmock.h>

struct Element { }; // Dummy

class Calc {
public:
    virtual ~Calc() { }

    virtual int Add(Element x) { return 0; } // 행위 기반 검증 대상 X
    virtual int Add(int times, Element x) { return 0; } // 행위 기반 검증 대상 O
};

class MockCalc : public Calc {
public:
    // 순수 가상 함수가 아닌 경우에는,
    // 부모가 제공하는 기능 중에 행위 기반 검증을 수행하고자 하는 메소드에 대해서만 MOCK_METHOD 하면 됩니다.
    // int Add(int times, Element x) override
    MOCK_METHOD(int, Add, (int times, Element x), (override));

    // 문제: MOCK_METHOD한 메소드와 동일한 이름의 함수가 부모에 존재하면,
    //     MOCK_METHOD에 의해서 가려지는 현상이 발생합니다.
    // 해결방법: 명시적으로 동일한 이름의 함수에 대한 using 선언이 필요합니다.
    using Calc::Add;
};

void foo(Calc* p)
{
    p->Add(Element {});
    p->Add(42, Element {});
}

TEST(SampleTest, Sample)
{
    MockCalc mock;

    mock.Add(Element {});
    mock.Add(42, Element {});

    // foo(&mock);
}
