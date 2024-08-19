// 6_Assertions.cpp
#include <gtest/gtest.h>

int foo() { return 420; }
int goo() { return 1000; }

// 1. ASSERT_
//  => 단언문이 실패할 경우, 이후의 테스트 코드를 수행하지 않습니다.
//  => 하나의 테스트 케이스 안에서 여러개의 단언문을 사용할 경우,
//     "죽은 단언문" 문제가 발생합니다.
//  : xUnit Test Pattern에서는 하나의 테스트케이스 안에서 여러 개의 단언문을
//    사용하는 것은 지양해야 합니다.
//    - 관리해야 하는 테스트 케이스가 늘어나고, 테스트 코드 중복의 문제가 발생합니다.

#if 0
TEST(SampleTest, Sample1_foo)
{
    // ...
    ASSERT_EQ(foo(), 420);
}

TEST(SampleTest, Sample1_goo)
{
    // ...
    ASSERT_EQ(foo(), 420);
}
#endif

TEST(SampleTest, Sample_ASSERT)
{
    // ...
    ASSERT_EQ(foo(), 42);
    ASSERT_EQ(goo(), 100);
}

// 2. EXPECT_ 단언문
//  : Google Test 고유의 기능입니다.
//  EQ/NE/LE/LT/GE/GT/TRUE/FALSE ..
//  - 단언문이 실패할 경우, 테스트의 결과는 실패이지만, 이후의 코드를 계속 수행합니다.
// "죽은 단언문" 문제가 발생하지 않습니다.
TEST(SampleTest, Sample_EXPECT)
{
    // ...
    EXPECT_EQ(foo(), 42);
    EXPECT_EQ(goo(), 100);
}

class User {
    std::string name = "Tom";

public:
    std::string GetName() const { return name; }
};

// User* GetUser() { return new User; }
User* GetUser() { return nullptr; }

TEST(UserTest, GetName)
{
    User* user = GetUser();

    // EXPECT_NE(user, nullptr);
    ASSERT_NE(user, nullptr); // 왜 ASSERT로 작성되어야 하는지를 이해해야 합니다.
    EXPECT_EQ(user->GetName(), "Tom"); // !!
}

// 3. C 문자열 비교 단언문
//  C 문자열: '\0' 문자로 종료되는 char 배열
//   - EXPECT_STREQ/STRNE
//   - EXPECT_STRCASEQ/STRCASENE
TEST(SampleTest2, Sample1)
{
    std::string s1 = "hello";
    std::string s2 = "hello";

    // ...
    EXPECT_EQ(s1, s2); // s1 == s2

    const char* s3 = "HELLO";
    const char* s4 = s2.c_str();
    // EXPECT_EQ(s3, s4);
    // EXPECT_STREQ(s3, s4); // C 문자열
    EXPECT_STRCASEEQ(s3, s4);
}
