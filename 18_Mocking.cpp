// 18_Mocking.cpp
#include <gmock/gmock.h>

// 협력 객체 인터페이스
class MP3 {
public:
    virtual ~MP3() { }

    virtual void Play() = 0;
    virtual bool Stop(int n) = 0;

    virtual std::string GetTitle() const = 0;
    virtual void Go() const noexcept = 0;
};

// 협력 객체의 인터페이스를 구현하는 형태로 만들어야 합니다.
class MockMP3 : public MP3 {
public:
    // MOCK_METHOD(반환타입, 메소드이름, (인자 정보), (한정자 정보))

    // void Play() override
    MOCK_METHOD(void, Play, (), (override));

    // bool Stop(int n) override
    MOCK_METHOD(bool, Stop, (int n), (override));
};

TEST(SampleTest, Sample)
{
    MockMP3 mock; // !!
}
