// 18_Mocking6.cpp
enum Level {
    INFO,
    WARN
};

class Logger {
public:
    virtual ~Logger() { }

    virtual void Send(Level level,
        const char* dir,
        const char* file,
        const char* message)
        = 0;
};

class Car {
public:
    void Start(Logger* logger)
    {
        // ...
        logger->Send(INFO, "/tmp", "car.log", "car start...");
        // ...
    }
};

// Car 객체가 logger를 사용할 때, /tmp 디렉토리에 로그를 기록하는지 여부를
// 검증하고 싶습니다.
// => 모든 인자에 대해서 검증이 필요한 것이 아니라, 특정한 인자에 대해서만 검증하고 싶습니다.
#include <gmock/gmock.h>

#if 1
class MockLogger : public Logger {
public:
    //  void Send(Level level, const char* dir, const char* file, const char* message) override
    MOCK_METHOD(void, Send, (Level level, const char* dir, const char* file, const char* message), (override));
};

using testing::_;

TEST(CarTest, Start)
{
    MockLogger logger;
    Car car;

    EXPECT_CALL(logger, Send(_, "/tmp", _, _));

    car.Start(&logger);
}
#endif

#if 0
class MockLogger : public Logger {
public:
    void Send(Level level, const char* dir, const char* file, const char* message) override
    {
        // MOCK_METHOD한 메소드를 직접 호출해줍니다.
        Send(dir);
    }

    // void Send(const char* dir)
    // - Mock 간략화의 방법입니다.
    MOCK_METHOD(void, Send, (const char* dir));
};

TEST(CarTest, Start)
{
    MockLogger logger;
    Car car;

    // EXPECT_CALL(logger, Send(INFO, "/tmp", "car.log", "car start..."));
    EXPECT_CALL(logger, Send("/tmp"));

    car.Start(&logger);
}
#endif
