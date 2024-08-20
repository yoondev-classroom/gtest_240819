// 16_Spy.cpp
#include <string>
#include <vector>

enum Level {
    INFO,
    WARN,
    ERROR
};

class DLoggerTarget {
public:
    virtual ~DLoggerTarget() { }

    virtual void Write(Level level, const std::string& message) = 0;
};

class FileTarget : public DLoggerTarget {
    // 전달된 내용을 파일에 기록합니다.
};
class NetworkTarget : public DLoggerTarget {
    // 전달된 내용을 네트워크로 전송합니다.
};

class DLogger {
    std::vector<DLoggerTarget*> targets;

public:
    void AddTarget(DLoggerTarget* p) { targets.push_back(p); }

    void Write(Level level, const std::string& message)
    {
        for (auto e : targets) {
            e->Write(level, message);
        }
    }
};

#include <gtest/gtest.h>

// 문제점: DLogger의 Write를 수행하였을 때,
//       검증할 수 있는 상태가 존재하지 않습니다.

// Test Spy Pattern
// 의도: SUT의 함수를 호출하였을 때, 발생하는 부수 효과를 관찰할 수 없어서
//     테스트되지 않은 요구사항이 존재합니다.
// 방법: 목격한 일을 기록해두었다가, 나중에 테스트에서 확인할 수 있도록 만들어진 테스트 대역을 이용합니다.
//    => 다른 컴포넌트로부터의 간접 출력을 저장해두었다가, 검증에 활용합니다.
class SpyTarget : public DLoggerTarget {
    std::vector<std::string> history;

    std::string Concat(Level level, const std::string& message) const
    {
        return message + std::to_string(level);
    }

public:
    void Write(Level level, const std::string& message) override
    {
        // 목격한 일을 기록합니다.
        history.push_back(Concat(level, message));
    }

    // 테스트를 통해 결과를 확인할 수 있도록 기능을 제공합니다.
    bool IsReceived(Level level, const std::string& message) const
    {
        return std::find(std::begin(history), std::end(history), Concat(level, message))
            != std::end(history);
    }
};

TEST(DLoggerTest, Write)
{
    DLogger logger;
    SpyTarget t1, t2;
    logger.AddTarget(&t1);
    logger.AddTarget(&t2);

    logger.Write(INFO, "test_message1");
    logger.Write(WARN, "test_message2");

    EXPECT_TRUE(t1.IsReceived(INFO, "test_message1"));
    EXPECT_TRUE(t2.IsReceived(INFO, "test_message1"));
    EXPECT_TRUE(t1.IsReceived(WARN, "test_message2"));
    EXPECT_TRUE(t2.IsReceived(WARN, "test_message2"));
}
