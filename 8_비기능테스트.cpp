// 8_비기능테스트.cpp
#include <string>
#include <unistd.h>

// 아래 함수는 1초 이내로 수행되어야 합니다.
void Connect(const std::string& host)
{
    // ...
    sleep(2);
}

// 비기능 테스트
// - 정의: 기능적으로 잘 동작할 뿐 아니라, 성능이나 메모리 등의 비기능적인 부분을 검증합니다.

#include <gtest/gtest.h>

// Connect 함수가 1초 이내로 수행되는지 여부를 검증하고 싶습니다.
// 문제점: 아래 코드는 일반적인 테스트의 구성과 다릅니다.
//      => 가독성
// 해결 방법
//     : 사용자 정의 단언문
//      => Google Test는 단언문을 매크로의 형태로 제공하고 있습니다.
#define EXPECT_TIMEOUT(fn, limit)                                                \
    do {                                                                         \
        time_t startTime = time(nullptr);                                        \
        fn;                                                                      \
        time_t duration = time(nullptr) - startTime;                             \
        EXPECT_LE(duration, limit) << "Timeout: " << limit << " second(s) 초과"; \
    } while (0)

#define ASSERT_TIMEOUT(fn, limit)                                                \
    do {                                                                         \
        time_t startTime = time(nullptr);                                        \
        fn;                                                                      \
        time_t duration = time(nullptr) - startTime;                             \
        ASSERT_LE(duration, limit) << "Timeout: " << limit << " second(s) 초과"; \
    } while (0)

TEST(ConnectTest, Connect2)
{
    EXPECT_TIMEOUT(Connect("https://server.com"), 1);
}

TEST(ConnectTest, Connect1)
{
    time_t limit = 1;

    //---
    time_t startTime = time(nullptr);
    Connect("https://server.com");
    time_t duration = time(nullptr) - startTime;
    //---

    EXPECT_LE(duration, limit) << "Timeout: " << limit << " second(s) 초과";
}
