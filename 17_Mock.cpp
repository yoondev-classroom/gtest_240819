// 17_Mock.cpp
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

// Mock Object Pattern
// 의도: SUT의 함수를 호출하였을 때, 발생하는 부수 효과를 관찰할 수 없어서
//     테스트되지 않은 요구사항이 존재합니다.
// 방법: "행위 기반 검증"을 수행합니다.

// * 상태 검증
// - SUT에 작용을 가한 후, 내부 상태 변화를 단언문을 통해서 확인합니다.
// * 동작 검증
// - SUT에 작용을 가한 후, 내부적으로 발생하는 함수의 호출 여부, 호출 횟수, 호출 인자, 호출 순서 등의 정보를 통해
//   정상 동작 여부를 판단합니다.
//  => Mock Framework을 이용해서, 모의 객체(Mock Object)를 만들 수 있습니다.

// Google Test 1.8 버전 이후로, Google Mock 프로젝트가 Google Test에 흡수되었습니다.

#include <gmock/gmock.h>
// 위의 헤더를 통해 gtest/gtest.h도 포함되기 때문에, 별도로 포함할 필요가 없습니다.

// Google Mock을 이용해서 모의 객체를 만듭니다. => Mocking
class MockDLoggerTarget : public DLoggerTarget {
public:
    // void Write(Level level, const std::string& message)
    // => 행위 기반 검증을 수행하고자 하는 메소드에 대해서, MOCK_METHOD를 해야 합니다.

    // MOCK_METHOD{인자개수}(메소드 이름, 메소드 타입)
    MOCK_METHOD2(Write, void(Level level, const std::string& message));
};

TEST(DLoggerTest, Write)
{
    DLogger logger;
    MockDLoggerTarget t1, t2;
    logger.AddTarget(&t1);
    logger.AddTarget(&t2);

    logger.Write(INFO, "test_message1");
    logger.Write(WARN, "test_message2");

    // 행위 기반 검증 단언문
    EXPECT_CALL(t1, Write(INFO, "test_message1"));
    EXPECT_CALL(t1, Write(WARN, "test_message2"));
    EXPECT_CALL(t2, Write(INFO, "test_message1"));
    EXPECT_CALL(t2, Write(WARN, "test_message2"));
}
