// 13_테스트대역.cpp
#include <string>

class FileSystem {
public:
    bool IsValidFilename(const std::string& name)
    {
        // 현재의 파일 시스템에서 적합한 이름인지 확인합니다.
        return true;
    }
};

class Logger {
public:
    // 확장자를 제외한 파일명이 5글자 이상이어야 한다.
    // ex)
    //  file.log => file  => X
    // hello.log => hello => O
    bool IsValidLogFilename(const std::string& filename)
    {
        size_t index = filename.find_last_of(".");
        std::string name = filename.substr(0, index);
        if (name.size() < 5) {
            return false;
        }

        FileSystem fs;
        return fs.IsValidFilename(filename);
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
