// 21_행위기반검증2.cpp
class Dog {
public:
    virtual ~Dog() { }

    virtual void First() = 0;
    virtual void Second() = 0;
    virtual void Third() = 0;
    virtual void Fourth() = 0;
};

#include <gmock/gmock.h>

class MockDog : public Dog {
public:
    MOCK_METHOD(void, First, (), (override));
    MOCK_METHOD(void, Second, (), (override));
    MOCK_METHOD(void, Third, (), (override));
    MOCK_METHOD(void, Fourth, (), (override));
};

void Process(Dog* p)
{
    p->First();
    p->Second();
    p->Third();
    p->Fourth();
}

// 4. 호출 순서
//  : First -> Second -> Third -> Fourth

// => testing::InSequence 객체
using testing::InSequence;
TEST(DogTest, Sample1)
{
    InSequence seq; // 해당 객체가 존재하면, 순서를 검증합니다.
    MockDog mock;

    EXPECT_CALL(mock, First);
    EXPECT_CALL(mock, Second);
    EXPECT_CALL(mock, Third);
    EXPECT_CALL(mock, Fourth);

    Process(&mock);
}

void Process2(Dog* p)
{
    p->First();

    p->Third();
    p->Fourth();

    p->Second();
}

// First ---> Second            ; seq1
//       |
//       ---> Third -> Fourth   ; seq2

// => EXPECT_CALL().InSequence()
using testing::Sequence;

TEST(DogTest, Sample2)
{
    Sequence seq1, seq2;
    MockDog mock;

    EXPECT_CALL(mock, First).InSequence(seq1, seq2);
    EXPECT_CALL(mock, Second).InSequence(seq1);

    EXPECT_CALL(mock, Third).InSequence(seq2);
    EXPECT_CALL(mock, Fourth).InSequence(seq2);

    Process2(&mock);
}

class Car {
public:
    virtual ~Car() { }

    virtual void f1() { }
    virtual void f2() { }
    virtual void f3() { }
    virtual void f4() { }
    virtual void f5() { }
};

class MockCar : public Car {
public:
    MOCK_METHOD(void, f1, (), (override));
    MOCK_METHOD(void, f2, (), (override));
    MOCK_METHOD(void, f3, (), (override));
    MOCK_METHOD(void, f4, (), (override));
    MOCK_METHOD(void, f5, (), (override));
};

void foo(Car* p)
{
    p->f1();
    p->f2();
    p->f3();
    p->f4();
    p->f5();
}

// f1 ---> f2
//    |
//    ---> f3 --> f5
//    |
//    ---> f4

TEST(CarTest, Sample)
{
    MockCar mock;

    // EXPECT_CALL

    foo(&mock);
}
