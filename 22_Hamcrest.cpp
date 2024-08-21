// 22_Hamcrest.cpp
// => Hamcrest Matcher
//  : 비교 표현의 확장 라이브러리
//   - Google Mock을 통해서 제공되고 있습니다.
//   1) Matcher를 이용해서, 행위 기반 검증에서 인자를 검증할 때 사용합니다.
//   2) Matcher를 상태 기반 검증에서 사용할 수 있는 단언문을 제공합니다.
//     => ASSERT_THAT / EXPECT_THAT

#include <gmock/gmock.h>

class User {
    std::string name = "Tom";

public:
    std::string GetName() const { return name; }
};

using namespace testing;

using testing::StartsWith;

// https://google.github.io/googletest/reference/matchers.html

TEST(UserTest, Sample)
{
    User user;

    // ...

    // ASSERT_EQ(user.GetName(), "Tom");
    EXPECT_EQ(user.GetName(), "Tom") << "error!";
    EXPECT_THAT(user.GetName(), Eq("Tom"));

    // GetName()의 결과가 "Tom"으로 시작하는지 검증
    EXPECT_THAT(user.GetName(), StartsWith("Tom")) << "error!";
    EXPECT_THAT(user.GetName(), StrCaseEq("TOM"));
}
