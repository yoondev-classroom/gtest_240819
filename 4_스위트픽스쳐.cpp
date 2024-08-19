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

class TerminalTest : public testing::Test {
protected:
    Terminal* ts;
    void SetUp() override
    {
        Terminal* ts = new Terminal;
        ts->Connect();
    }

    void TearDown() override
    {
        ts->Disconnect();
        delete ts;
    }
};

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
