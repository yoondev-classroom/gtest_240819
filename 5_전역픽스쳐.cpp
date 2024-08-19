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

class MyEnvironment2 : public testing::Environment {
public:
    void SetUp() override
    {
        std::cout << "MyEnvironment2.SetUp()" << std::endl;
    }

    void TearDown() override
    {
        std::cout << "MyEnvironment2.TearDown()" << std::endl;
    }
};

// 2) 설치하는 방법 2가지
//     => main 함수를 통해 직접 정의하는 것이 안전합니다.

//      - main을 직접 정의한 경우
//      : 정적 라이브러리에서 main을 제거해주어야 합니다.
//        이전 컴파일러에서는 링크 오류가 발생할 수 있습니다.
#if 1
int main(int argc, char** argv)
{
    testing::InitGoogleTest(&argc, argv);

    testing::AddGlobalTestEnvironment(new MyEnvironment);
    testing::AddGlobalTestEnvironment(new MyEnvironment2);

    return RUN_ALL_TESTS();
}
#endif

//   - main을 직접 제공하지 않는 경우
// => 전역 변수의 초기화가 main 이전에 수행되는 원리를 이용합니다.
//  C++ 표준에서는 전역 변수의 초기화가 각 파일의 단위에서 어떤 순서로 수행될지 정의되어 있지 않습니다.

#if 0
// test1.cpp
testing::Environment* my_env1 = testing::AddGlobalTestEnvironment(new MyEnvironment);
// test2.cpp
testing::Environment* my_env2 = testing::AddGlobalTestEnvironment(new MyEnvironment);
#endif
