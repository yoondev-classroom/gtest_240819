// 3_테스트픽스쳐4.cpp
#include <gtest/gtest.h>

class ImageProcessorTest : public testing::Test {
public:
    ImageProcessorTest()
    {
        std::cout << "ImageProcessorTest()" << std::endl;
    }

    ~ImageProcessorTest()
    {
        std::cout << "~ImageProcessorTest()" << std::endl;
    }

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
TEST_F(ImageProcessorTest, foo) { }

// * 신선한 픽스쳐 전략
// => 각 테스트 케이스마다 새로운 픽스쳐 객체를 생성하고 파괴하는 형태로 테스트케이스가 수행됩니다.

// Test Runner
//  -- 스위트 픽스쳐 설치 --
// - ImageProcessorTest 객체 생성
// - ImageProcessorTest.ResizeImage
//   ImageProcessorTest.SetUp()
//   ...
//   ImageProcessorTest.TearDown()
// - ImageProcessorTest 객체 파괴

// - ImageProcessorTest 객체 생성
// - ImageProcessorTest.BlurImage
//   ImageProcessorTest.SetUp()
//   ...
//   ImageProcessorTest.TearDown()
// - ImageProcessorTest 객체 파괴
//  -- 스위트 픽스쳐 해체 --
