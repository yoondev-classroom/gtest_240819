// 21_행위기반검증.cpp
// - 정의: SUT 내부에서 협력 객체를 대상으로 함수의 호출을 통해
//        정상 동작 여부를 검증합니다.
//   1) 함수 호출 여부
//   2) 함수 호출 횟수
//   3) 함수 호출 인자
//   4) 함수 호출 순서
#include <string>
#include <vector>

class Person {
public:
    virtual ~Person() { }

    virtual void Go(int x, int y) = 0;
    virtual void Print(const std::vector<int>& numbers) = 0;
    virtual void SetAddress(const std::string& address) = 0;
};

#include <gmock/gmock.h>

class MockPerson : public Person {
public:
    MOCK_METHOD(void, Go, (int x, int y), (override));
    MOCK_METHOD(void, Print, (const std::vector<int>& numbers), (override));
    MOCK_METHOD(void, SetAddress, (const std::string& address), (override));
};

void UsePerson(Person* p)
{
    p->Go(100, 20);
}

// EXPECT_CALL
// - 별도의 오류 메세지를 지정할 수 있는 기능을 제공하지 않습니다.
// - 협력 객체를 대상으로 호출이 되기 이전에, EXPECT_CALL을 먼저 작성해야 합니다.
// - mock 객체가 파괴될 때, EXPECT_CALL에 대한 검증이 수행됩니다.

// 1) 함수 호출 여부
TEST(PersonTest, Sample2)
{
    MockPerson* mock = new MockPerson;

    // EXPECT_CALL(mock, Go(10, 20));
    EXPECT_CALL(*mock, Go); // 인자와 상관없이 호출 여부를 판단합니다.

    UsePerson(mock);

    delete mock; // !! 검증이 수행됩니다.
}

TEST(PersonTest, Sample1)
{
    MockPerson mock;

    // EXPECT_CALL(mock, Go(10, 20));
    EXPECT_CALL(mock, Go); // 인자와 상관없이 호출 여부를 판단합니다.

    UsePerson(&mock);
} // 범위를 벗어나면 자동으로 파괴되면서 검증이 수행됩니다.

// 2) 함수 호출 횟수
//   EXPECT_CALL(...).Times(N)
//   EXPECT_CALL(...).Times(Cardinality)

// * Cardinality
// 1) AtLeast(N) => N번 이상
// 2) AtMost(N)  => N번 이하
// 3) Between(A, B) => A ~ B번

void UsePerson2(Person* p)
{
    p->Go(10, 20);
    p->Go(10, 20);
    p->Go(10, 20);
}

using testing::AtLeast;
using testing::AtMost;
using testing::Between;

TEST(PersonTest2, Sample1)
{
    MockPerson mock;

    // EXPECT_CALL(mock, Go(10, 20)); // 1번
    // EXPECT_CALL(mock, Go(10, 20)).Times(3);
    // EXPECT_CALL(mock, Go(10, 20)).Times(AtMost(3));
    EXPECT_CALL(mock, Go(10, 20)).Times(Between(2, 3));

    UsePerson2(&mock);
}
