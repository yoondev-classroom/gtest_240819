// 9_FriendTest.cpp
#include <gtest/gtest_prod.h>

class User {
    int age = 42;

    int GetAge() const { return age; }

    void process1() { }
    void process2() { }

public:
    void foo() { age = 100; }

    void goo()
    {
        process1();
        process2();
    }

    FRIEND_TEST(UserTest, foo);
};
//----

#include <gtest/gtest.h>
// * 문제점
// : 테스트 코드에서 상태를 확인하는 메소드가
//   private 영역에 존재해서, 외부에서 접근이 불가능합니다.
//   (테스트케이스에서 호출이 불가능해서, 단언문을 작성할 수 없습니다.)
// * 해결방법
//  - xUnit Test Pattern에서는 테스트를 통해서 상태를 확인해야 하는 메소드는
//    private 영역에 두지 말아야 한다.
//   "검증되지 않은 private 메소드가 검증된 public 메소드보다 위험하다."
//  - private 메소드의 용도를 public 메소드의 가독성을 높이는 목적으로 사용해야 한다.

//  - Google Test는 FRIEND_TEST 기능을 제공합니다.
//   => 제품코드에 Google Test 의존성이 발생합니다.

TEST(UserTest, foo)
{
    User user;

    user.foo();

    EXPECT_EQ(user.GetAge(), 100); // !!
}
