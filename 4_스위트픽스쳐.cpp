// 4_스위트픽스쳐.cpp
#include <iostream>
#include <string>

#include <unistd.h>

// 가정: Connect() / Disconnect() 느립니다.

class Terminal {
public:
    void Connect() { sleep(2); }
    void Disconnect() { sleep(1); }

    void LogIn(const std::string& id, const std::string& password) { }
    void LogOut() { }

    bool IsLogin() { return false; }
};

#include <gtest/gtest.h>

// 아래의 코드를 암묵적 설치/해체의 코드로 변경해보세요.
#if 0
TEST(TerminalTest, LogIn)
{
    Terminal* ts = new Terminal;
    ts->Connect();

    ts->LogIn("test_id", "test_password");

    ASSERT_TRUE(ts->IsLogin()) << "로그인 하였을 때";

    ts->Disconnect();
    delete ts;
}

TEST(TerminalTest, LogOut)
{
    Terminal* ts = new Terminal;
    ts->Connect();

    ts->LogIn("test_id", "test_password");
    ts->LogOut();

    ASSERT_FALSE(ts->IsLogin()) << "로그아웃 하였을 때";

    ts->Disconnect();
    delete ts;
}
#endif

// 문제점
// - SetUp/TearDown이 느려서(픽스쳐 설치/해체가 느려서)
//   테스트케이스가 추가될 때마다 전체적인 테스트의 수행 시간이 늘어납니다.
//  "Slow Test"
//  * 테스트가 너무 느려서, 테스트를 수행하는 개발자의 생산성을 떨어뜨립니다.
//  * 테스트가 너무 느려서, 코드가 변경되어도 아무도 테스트를 수행하지 않습니다.

// 해결 방법
// - xUnit Test Framework이 제공하는 스위트 픽스쳐 설치/해체를 제공합니다.
// => 정적 메소드를 통해 제공됩니다.
// => 정적 메소드 기반의 스위트 픽스쳐 설치/해체를 사용하면,
//    더 이상 신선한 픽스쳐 전략이 아닌 "공유 픽스쳐" 전략 입니다.
//   : 테스트 스위트 안의 모든 테스트 케이스가 동일한 픽스쳐를 공유해서 사용합니다.
//     공유 픽스쳐의 전략은 테스트를 빠르게 수행할 수 있지만,
//     이전의 테스트가 픽스쳐를 망가뜨리면, 이후의 테스트의 결과를 신뢰할 수 없는
//     "변덕스러운 테스트" 문제의 가능성이 있습니다.
//     => 신뢰성

class TerminalTest : public testing::Test {
protected:
    static Terminal* ts;

    // 테스트 스위트 픽스쳐
    static void SetUpTestSuite() // 1.10 이전 - SetUpTestCase
    {
        std::cout << "SetUpTestSuite()" << std::endl;
        Terminal* ts = new Terminal;
        ts->Connect();
    }

    static void TearDownTestSuite() // 1.10 이전 - TearDownTestCase
    {
        std::cout << "TearDownTestSuite()" << std::endl;
        ts->Disconnect();
        delete ts;
    }

    // 테스트(테스트 케이스) 픽스쳐
    void SetUp() override
    {
        // Terminal* ts = new Terminal;
        // ts->Connect();
    }

    void TearDown() override
    {
        // ts->Disconnect();
        // delete ts;
    }
};

// C++ 에서는 정적 멤버는 외부 정의가 필요합니다.
Terminal* TerminalTest::ts = nullptr;

TEST_F(TerminalTest, LogIn)
{
    ts->LogIn("test_id", "test_password");

    ASSERT_TRUE(ts->IsLogin()) << "로그인 하였을 때";
}

TEST_F(TerminalTest, LogOut)
{
    ts->LogIn("test_id", "test_password");
    ts->LogOut();

    ASSERT_FALSE(ts->IsLogin()) << "로그아웃 하였을 때";
}

TEST_F(TerminalTest, foo) { }
