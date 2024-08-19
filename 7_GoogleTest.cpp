// 7_GoogleTest.cpp
#include <gtest/gtest.h>

// 1. 테스트 비활성화
// => 테스트를 비활성화하면, 테스트를 수행하지 않고, 결과에 포함되지 않습니다.
//    비활성화된 테스트가 존재한다는 사실을 결과를 통해서 알립니다.
// => Google Test에서 테스트를 비활성화하기 위해서는
//    테스트 스위트 이름 또는 테스트 케이스 이름이 DISABLED_로 시작하면 됩니다.
// => 비활성화된 테스트를 수행할 수 있는 옵션이 존재합니다.
//    $ ./a.out --gtest_also_run_disabled_tests

// * 작성 중인 테스트는 명시적으로 실패해야 합니다.
// * 테스트를 비활성화하기 위해서, 주석 처리하면, "잊혀진 테스트"가 됩니다.

TEST(ImageProcessorTest, DISABLED_ResizeImage)
{
    // 작성중입니다.
    FAIL() << "작성중입니다.";
}

class DISABLED_SampleTest : public testing::Test { };
TEST_F(DISABLED_SampleTest, foo) { }
TEST_F(DISABLED_SampleTest, goo) { }
TEST_F(DISABLED_SampleTest, hoo) { }

// 2. 테스트 필터
// => 원하는 테스트를 선택적으로 수행할 수 있습니다.
//  : 테스트의 이름을 잘 구성하는 것이 중요합니다.
// $ ./a.out --gtest_filter=ImageTest.goo

//  - 여러개의 테스트를 :을 통해 나열할 수 있습니다.
// $ ./a.out --gtest_filter=ImageTest.goo:ImageProcessorTest.goo

//  - 와일드 카드(*)을 지원합니다.
// $ ./a.out --gtest_filter=*.goo
// $ ./a.out --gtest_filter=Image*.foo

//  - 앞의 조건에서 제외할 수 있는 기능도 제공합니다.
// $ ./a.out --gtest_filter=Image*.foo:-ImageProcessorTest.foo

TEST(ImageTest, foo) { } // ImageTest.foo
TEST(ImageTest, goo) { } // ImageTest.goo
TEST(ImageTest, hoo) { } // ImageTest.hoo

TEST(ImageProcessorTest, foo) { } // ImageProcessorTest.foo
TEST(ImageProcessorTest, goo) { } // ImageProcessorTest.goo
TEST(ImageProcessorTest, hoo) { } // ImageProcessorTest.hoo
