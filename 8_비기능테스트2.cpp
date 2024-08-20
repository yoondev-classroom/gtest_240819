// 8_비기능테스트2.cpp
#include <iostream>
#include <string>

class Image {
    std::string url;

public:
    Image(const std::string& s)
        : url { s }
    {
    }

    void Draw() const
    {
        std::cout << "Draw Image: " << url << std::endl;
    }
};

bool DrawImage(const std::string& url)
{
    Image* p = new Image { url };
    p->Draw();

    // ...
    return true;
}

#include <gtest/gtest.h>

// 메모리 누수 여부를, 단위 테스트를 통해서 검증하고 싶습니다.
TEST(ImageTest, DrawImage)
{
    std::string url = "https://a.com/a.jpg";
    EXPECT_TRUE(DrawImage(url));
}
