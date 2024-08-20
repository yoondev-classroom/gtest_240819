// 8_비기능테스트3.cpp
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

// 조건부 컴파일을 통해서, 테스트 코드에서만 사용될 수 있도록 만들어야 합니다.
#ifdef GTEST_LEAK_TEST
    static int allocCount;

    void* operator new(size_t size)
    {
        ++allocCount;
        return malloc(size);
    }

    void operator delete(void* p, size_t)
    {
        free(p);
        --allocCount;
    }
#endif
};

#ifdef GTEST_LEAK_TEST
int Image::allocCount = 0;
#endif

bool DrawImage(const std::string& url)
{
    Image* p = new Image { url };
    Image* p2 = new Image { url };
    Image* p3 = new Image { url };

    p->Draw();

    // ...
    return true;
}

#include <gtest/gtest.h>

// 메모리 누수 여부를, 단위 테스트를 통해서 검증하고 싶습니다.
// - 방법 1. operator new / operator delete를 재정의

// new
// 1) 메모리 할당 - operator new
// 2) 객체라면, 생성자 호출

// delete
// 1) 객체라면, 소멸자 호출
// 2) 메모리 해지 - operator delete
#if 0
TEST(ImageTest, DrawImage)
{
    std::string url = "https://a.com/a.jpg";

    int alloc = Image::allocCount;
    EXPECT_TRUE(DrawImage(url));
    int diff = Image::allocCount - alloc;
    EXPECT_EQ(diff, 0) << "Memory Leak: " << diff << " object(s) 누수";
}
#endif

class ImageTest : public testing::Test {
protected:
    int alloc = 0;

    void SetUp() override
    {
#ifdef GTEST_LEAK_TEST
        alloc = Image::allocCount;
#endif
    }

    void TearDown() override
    {
#ifdef GTEST_LEAK_TEST
        int diff = Image::allocCount - alloc;
        EXPECT_EQ(diff, 0) << "Memory Leak: " << diff << " object(s) 누수";
#endif
    }
};

TEST_F(ImageTest, DrawImage)
{
    std::string url = "https://a.com/a.jpg";
    EXPECT_TRUE(DrawImage(url));
}
