// 5_전역픽스쳐.cpp
// => Test Fixture / Test Suite Fixture
//  : xUnit Test Framework의 공통적인 기능입니다.

// => Global Test Fixture
//  : Google Test 고유의 기능입니다.
//   프로그램의 시작/끝에서 픽스쳐를 설치하거나 해체할 수 있는 기능을 제공합니다.

#include <gtest/gtest.h>

TEST(ImageProcessorTest, ResizeImage) { } // !!
TEST(SampleTest, foo) { }

// 전역 픽스쳐를 사용하는 방법.
// 1) testing::Environment의 자식 클래스를 정의합니다.
class MyEnvironment : public testing::Environment {
public:
    void SetUp() override
    {
        std::cout << "MyEnvironment.SetUp()" << std::endl;
    }

    void TearDown() override
    {
        std::cout << "MyEnvironment.TearDown()" << std::endl;
    }
};

// 2) 설치하는 방법 2가지
//    - main을 직접 정의한 경우
int main(int argc, char** argv)
{
    testing::InitGoogleTest(&argc, argv);

    testing::AddGlobalTestEnvironment(new MyEnvironment); // !!!

    return RUN_ALL_TESTS();
}
