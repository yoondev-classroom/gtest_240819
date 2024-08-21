// 21_행위기반검증.cpp
// - 정의: SUT 내부에서 협력 객체를 대상으로 함수의 호출을 통해
//        정상 동작 여부를 검증합니다.
//   1) 함수 호출 여부
//   2) 함수 호출 횟수
//   3) 함수 호출 인자
//   4) 함수 호출 순서
#include <string>
#include <vector>

class Person {
public:
    virtual ~Person() { }

    virtual void Go(int x, int y) = 0;
    virtual void Print(const std::vector<int>& numbers) = 0;
    virtual void SetAddress(const std::string& address) = 0;
};

#include <gmock/gmock.h>

class MockPerson : public Person {
public:
    MOCK_METHOD(void, Go, (int x, int y), (override));
    MOCK_METHOD(void, Print, (const std::vector<int>& numbers), (override));
    MOCK_METHOD(void, SetAddress, (const std::string& address), (override));
};
