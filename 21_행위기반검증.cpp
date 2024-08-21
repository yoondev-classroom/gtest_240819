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

// 3) 함수 호출 인자
//  => Matcher
//    : Hamcrest라는 비교 표현의 확장 라이브러리

using testing::Matcher;

using testing::Eq; // ==
using testing::Ne; // !=

using testing::Ge; // >=
using testing::Gt; // >

using testing::Le; // <=
using testing::Lt; // <

using testing::AllOf; // &&
using testing::AnyOf; // ||

using testing::_; // Anything

void UsePerson4(Person* p)
{
    p->Go(11, -100);
    p->Go(19, 11);
    p->Go(5, 19);
}

TEST(PersonTest3, Sample3)
{
    MockPerson mock;

    // 첫번째 인자: 5 이상입니다.
    // 두번째 인자는 아무거나 상관없습니다.
    EXPECT_CALL(mock, Go(Ge(5), _)).Times(3);

    UsePerson4(&mock);
}

TEST(PersonTest3, Sample2)
{
    MockPerson mock;

    // 첫번째 인자: 5 이상이고 20 미만입니다.   => &&
    Matcher<int> arg0 = AllOf(Ge(5), Lt(20));
    // 두번째 인자: 0 미만이거나, 10 초과입니다. => ||
    Matcher<int> arg1 = AnyOf(Lt(0), Gt(10));
    EXPECT_CALL(mock, Go(arg0, arg1)).Times(3);

    UsePerson4(&mock);
}

void UsePerson3(Person* p)
{
    p->Go(10, 20);
    p->Go(10, 20);
    p->Go(10, 20);
}

TEST(PersonTest3, Sample1)
{
    MockPerson mock;

    // EXPECT_CALL(mock, Go).Times(3);

    // 첫번째 인자는 5 이상이고, 두번째 인자는 20 이어야 합니다.
    Matcher<int> arg0 = Ge(5);
    Matcher<int> arg1 = Eq(20);
    EXPECT_CALL(mock, Go(arg0, arg1)).Times(3);

    UsePerson3(&mock);
}

void UsePerson5(Person* p)
{
    // p->Print({ 1, 2, 3 });
    p->Print({ 3, 2, 1 });
}

using testing::ElementsAre;
using testing::ElementsAreArray;
using testing::UnorderedElementsAre;
using testing::UnorderedElementsAreArray;

TEST(PersonTest4, Sample1)
{
    MockPerson mock;

    // Print로 전달되는 인자
    // [0]: 10보다 작아야 합니다. => Lt(10)
    // [1]: 2 이상입니다.       => Ge(2)
    // [2]: 5 이하입니다.       => Le(5)
    // Matcher<int> args[] = { Lt(10), Ge(2), Le(5) };
    // EXPECT_CALL(mock, Print(ElementsAreArray(args)));
    // EXPECT_CALL(mock, Print(ElementsAre(Lt(10), Ge(2), Le(5))));

    // 순서와 상관없이 검증할 수 있느 기능도 제공됩니다.
    EXPECT_CALL(mock, Print(UnorderedElementsAre(Lt(10), Ge(2), Le(5))));

    UsePerson5(&mock);
}

void UsePerson6(Person* p)
{
    p->SetAddress("XXX Seoul XXX");
}

using testing::ContainsRegex;
using testing::HasSubstr;

TEST(PersonTest5, Sample)
{
    MockPerson mock;

    // EXPECT_CALL(mock, SetAddress("Seoul"));
    // EXPECT_CALL(mock, SetAddress(HasSubstr("Seoul")));
    EXPECT_CALL(mock, SetAddress(ContainsRegex("Seoul")));

    UsePerson6(&mock);
}
