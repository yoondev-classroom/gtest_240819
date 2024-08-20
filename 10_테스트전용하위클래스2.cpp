// 10_테스트전용하위클래스2.cpp
#include <iostream>

class Engine {
public:
    virtual ~Engine() { }

    virtual void Start() // 가상함수!
    {
        // ...
        std::cout << "Engine Start" << std::endl;
        // ...
    }
};

class Car {
    Engine* engine;

public:
    Car(Engine* p)
        : engine { p }
    {
    }

    void Go() const
    {
        // ...
        engine->Start();

        // ...
    }
};

#include <gtest/gtest.h>

// Car의 Go가 호출되면, Engine이 Start되었을 것이다.
// 문제점
//  : Engine이 Start되었을 때, Engine 객체가 확인할 수 있는 기능을 제공하지 않아서,
//    단언문을 작성할 수 없습니다.
class TestEngine : public Engine {
    bool isStart = false;

public:
    void Start() override
    {
        Engine::Start();
        isStart = true;
    }

    bool IsStart() const
    {
        return isStart;
    }
};

TEST(CarTest, Go)
{
    // Engine engine;
    TestEngine engine;
    Car car { &engine };

    car.Go();

    EXPECT_TRUE(engine.IsStart());
}
