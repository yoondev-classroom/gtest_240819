// 18_Mocking3.cpp
#include <gmock/gmock.h>

template <typename T>
class StackInterface {
public:
    virtual ~StackInterface() { }

    virtual int GetSize() const { return 0; }
    virtual void Push(const T& data) = 0;
};

// 템플릿 기반의 인터페이스/추상클래스/부모클래스도 Mocking이 가능합니다.
template <typename TYPE>
class MockStackInterface : public StackInterface<TYPE> {
public:
    // int GetSize() const override
    MOCK_METHOD(int, GetSize, (), (const, override));

    // void Push(const T& data) override
    MOCK_METHOD(void, Push, (const TYPE& data), (override));
};

void foo(StackInterface<int>* p)
{
    // ...
    p->GetSize();
    // ...
    p->Push(42);
}

TEST(StackTest, Sample)
{
    MockStackInterface<int> mock;

    EXPECT_CALL(mock, GetSize());
    EXPECT_CALL(mock, Push(42));

    foo(&mock);
}

template <typename TYPE>
void goo(StackInterface<TYPE>* p)
{
    p->GetSize();
}

TEST(StackTest, Sample2)
{
    MockStackInterface<int> mock;

    EXPECT_CALL(mock, GetSize());

    goo(&mock);
}
