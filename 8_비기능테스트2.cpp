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

TEST(ImageTest, DrawImage)
{
    std::string url = "https://a.com/a.jpg";
    EXPECT_TRUE(DrawImage(url));
}
