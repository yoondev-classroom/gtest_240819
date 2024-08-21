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

    virtual std::pair<bool, int> GetPair() const = 0;

    // 아래 함수를 MOCK_METHOD 해보세요.
    virtual bool CheckMap(std::map<std::string, int> a, bool b) const = 0;
};

// 협력 객체의 인터페이스를 구현하는 형태로 만들어야 합니다.
class MockMP3 : public MP3 {
public:
    // MOCK_METHOD(반환타입, 메소드이름, (인자 정보), (한정자 정보))

    // void Play() override
    MOCK_METHOD(void, Play, (), (override));

    // bool Stop(int n) override
    MOCK_METHOD(bool, Stop, (int n), (override));

    // std::string GetTitle() const override
    MOCK_METHOD(std::string, GetTitle, (), (const, override));

    // void Go() const noexcept override
    MOCK_METHOD(void, Go, (), (const, noexcept, override));

    // std::pair<bool, int> GetPair() const override
    // 주의사항: 템플릿의 타입 인자가 2개 이상인 경우,
    //         괄호로 감싸주어야 한다.
    MOCK_METHOD((std::pair<bool, int>), GetPair, (), (const, override));

    // bool CheckMap(std::map<std::string, int> a, bool b) const override
    MOCK_METHOD(bool, CheckMap, ((std::map<std::string, int> a), bool b), (const, override));
};

TEST(SampleTest, Sample)
{
    MockMP3 mock; // !!
}
