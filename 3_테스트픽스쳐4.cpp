// 3_테스트픽스쳐4.cpp
#include <gtest/gtest.h>

class ImageProcessorTest : public testing::Test {
public:
    void SetUp() override
    {
        std::cout << "ImageProcessorTest.SetUp()" << std::endl;
    }

    void TearDown() override
    {
        std::cout << "ImageProcessorTest.TearDown()" << std::endl;
    }
};

// * 암묵적 설치/해체를 이용하기 위해서는 반드시 명시적인 테스트 스위트 클래스와 TEST_F 테스트 케이스가 필요합니다.
TEST_F(ImageProcessorTest, ResizeImage) { }
TEST_F(ImageProcessorTest, BlurImage) { }
