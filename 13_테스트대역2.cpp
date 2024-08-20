// 13_테스트대역2.cpp
#include <string>

// * 테스트 대역
//  목적: 테스트 환경을 통제하기 위해서 사용합니다.
//  적용: 테스트 대역을 적용하기 위해서는, 제품 코드가 테스트 대역을 적용할 수 있는 설계가
//       필요합니다.
//   => 약한 결합(느슨한 결합)
//    : 협력 객체를 이용할 때, 추상 타입(추상 클래스/인터페이스)에 의존하는 것

//  <강한 결합>
//   : 협력 객체를 이용할 때, 구체적인 타입에 의존하는 것
// Logger
//   IsValidLogFilename ---> FileSystem

// 1) 협력 객체의 인터페이스(추상 클래스)
class IFileSystem {
public:
    virtual ~IFileSystem() { }

    virtual bool IsValidFilename(const std::string& name) = 0;
};

// 2) 협력 객체의 인터페이스를 구현하는 형태로 만들어져야 합니다.
class FileSystem : public IFileSystem {
public:
    bool IsValidFilename(const std::string& name) override
    {
        // 현재의 파일 시스템에서 적합한 이름인지 확인합니다.
        // return true;
        return false;
    }
};

// 3) 협력 객체를 외부에서 생성해서, 전달해야 합니다.
//    직접 생성하면 강한 결합이 형성됩니다.
//     "의존성 주입(Dependency Injection, DI)"
//   1) 생성자 주입
//      : 협력객체가 필수적일 때
//   2) 메소드 주입
//      : 협력객체가 필수적이지 않을 때

class Logger {
    IFileSystem* fs;

public:
    Logger(IFileSystem* p = nullptr)
        : fs { p }
    {
        // 기존 제품 코드의 생성 방식과 동일하게 만들기 위해 제공합니다.
        if (p == nullptr) {
            fs = new FileSystem;
        }
    }

    // 확장자를 제외한 파일명이 5글자 이상이어야 한다.
    // ex)
    //  file.log => file  => X
    // hello.log => hello => O
    bool IsValidLogFilename(const std::string& filename)
    {
        //--------- 테스트 대상 코드 영역
        size_t index = filename.find_last_of(".");
        std::string name = filename.substr(0, index);
        if (name.size() < 5) {
            return false;
        }
        //--------- 테스트 대상 코드 영역

        // IFileSystem* fs = new FileSystem;
        return fs->IsValidFilename(filename);
    }
};

#include <gtest/gtest.h>

TEST(LoggerTest, IsValidLogFilename_NameLongerThan5Chars_ReturnsTrue)
{
    Logger logger;
    std::string validFilename = "valid.log";

    EXPECT_TRUE(logger.IsValidLogFilename(validFilename))
        << "확장자를 제외한 파일명이 5글자 이상일 때";
}

TEST(LoggerTest, IsValidLogFilename_NAmeShorterThan5Chars_ReturnsFalse)
{
    Logger logger;
    std::string invalidFilename = "bad.log";

    EXPECT_FALSE(logger.IsValidLogFilename(invalidFilename))
        << "확장자를 제외한 파일명이 5글자 미만일 때";
}
