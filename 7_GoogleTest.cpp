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

// 테스트의 성격에 따라서, 접두를 다르게 표현하였습니다.
// A_foo
// B_foo

// 3. 반복 / 무작위
// => 모든 테스트는 몇번을 수행하든, 순서에 상관없이 항상 동일한 결과가 나와야 합니다.
//   : "신뢰성"

// $ ./a.out --gtest_shuffle --gtest_repeat=10 --gtest_break_on_failure
//  : --gtest_break_on_failure
//  - 테스트가 실패할 경우, 강제적으로 프로세스를 종료 합니다.
int n = 0;
TEST(SampleTest, foo)
{
    // if (++n == 5) {
    FAIL() << "작성 중입니다.";
    // }
}

// * xUnit Test Pattern
// TestSuite
// - TestCase
// - TestCase
// - TestCase

// * Google Test 1.10 이후
// TestSuite
// - Test
// - Test
// - Test

// * Google Test 1.10 이전 => 주의해야 합니다.
// TestCase
// - Test
// - Test
// - Test

// 4. 테스트 결과 포맷터(Test Result Formatter)
// => 테스트의 결과를 XML 형식으로 export 할 수 있습니다. - xUnit Test Framework
//  $ ./a.out --gtest_output=xml:output.xml

// => 테스트의 결과를 JSON 형식으로 export 할 수 있습니다.
//  : Google Test 고유의 기능입니다. (1.10 이후로 지원합니다.)
//  $ ./a.out --gtest_output=json

// 5. 테스트 결과 포맷(xml/json)에 추가적인 정보도 기록할 수 있습니다.
TEST(ImageTest, ResizeImage)
{
    // cpu / mem
    RecordProperty("cpu", "1.4");
    RecordProperty("mem", "2312322");
}
