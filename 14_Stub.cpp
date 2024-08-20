// 14_Stub.cpp
#include <iostream>
#include <string>

class Time {
public:
    virtual ~Time() { }

    virtual std::string GetCurrentTime() const = 0;
};

class Clock : public Time {
public:
    std::string GetCurrentTime() const override
    {
        time_t rawTime;
        tm* timeInfo;
        char buffer[128];

        time(&rawTime);
        timeInfo = localtime(&rawTime);

        strftime(buffer, sizeof(buffer), "%H:%M", timeInfo);

        return std::string { buffer };
    }
};

class Scheduler {
    Time* time;

public:
    Scheduler(Time* p)
        : time { p }
    {
    }

    int Alarm()
    {
        std::string current = time->GetCurrentTime();
        if (current == "00:00") {
            return 42;
        } else if (current == "10:00") {
            return 100;
        }

        return 0;
    }
};

#include <gtest/gtest.h>

// Test Stub Pattern
//  의도: 다른 컴포넌트로부터의 간접 입력에 의존하는 로직을 독립적으로 검증하고 싶습니다.
//  방법: 실제 의존하는 객체를 테스트 대역으로 교체해서,
//       SUT가 테스트하는데 필요한 결과를 보내도록 제어합니다.
class StubTime : public Time {
    std::string result;

public:
    StubTime(const std::string& r)
        : result { r }
    {
    }

    std::string GetCurrentTime() const override
    {
        return result;
    }
};

TEST(SchedulerTest, Alarm_00_00)
{
    // Clock clock;
    StubTime clock { "00:00" };
    Scheduler scheduler { &clock };

    int result = scheduler.Alarm();

    EXPECT_EQ(result, 42) << "00:00 일때";
};

TEST(SchedulerTest, Alarm_10_00)
{
    // Clock clock;
    StubTime clock { "10:00" };
    Scheduler scheduler { &clock };

    int result = scheduler.Alarm();

    EXPECT_EQ(result, 100) << "10:00 일때";
};

#if 0
int main()
{
    Clock clock;
    std::cout << clock.GetCurrentTime() << std::endl;
}
#endif
