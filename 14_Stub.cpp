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

TEST(SchedulerTest, Alarm_00_00)
{
    Clock clock;
    Scheduler scheduler { &clock };

    int result = scheduler.Alarm();

    EXPECT_EQ(result, 42) << "00:00 일때";
};

TEST(SchedulerTest, Alarm_10_00)
{
    Clock clock;
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
