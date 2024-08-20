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
    delete p;

    int* p2 = new int[3];

    // ...
    return true;
}

#include <gtest/gtest.h>

// 메모리 누수 여부를, 단위 테스트를 통해서 검증하고 싶습니다.
// 방법 2. Sanitizer
//   => 대부분의 컴파일러들이 제공하는 도구 입니다.
//     - 메모리 / 스레드 / 미정의 동작
//   => 모든 플랫폼에서 제공되지는 않습니다.
//     - 컴파일 옵션: -fsanitize=address

TEST(ImageTest, DrawImage)
{
    std::string url = "https://a.com/a.jpg";
    EXPECT_TRUE(DrawImage(url));
}
