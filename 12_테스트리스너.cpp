// 12_테스트리스너.cpp
// => Google Test Framework 고유의 기능입니다.
//  : 모든 테스트의 과정에서 수행해야 하는 작업을 정의할 수 있습니다.

#include <gtest/gtest.h>

TEST(SampleTest, foo) { }
TEST(SampleTest, goo) { }

TEST(ImageTest, foo) { }

TEST(ImageProcessorTest, foo) { }

// 1) 리스너 정의
//  => testing::TestEventListener
//     testing::EmptyTestEventListener
//       : 필요한 이벤트에 대해서만 재정의하면 됩니다.
using testing::TestSuite;

class TestListener : public testing::EmptyTestEventListener {
public:
    void OnTestSuiteStart(const TestSuite& /*test_suite*/) override
    {
        std::cout << "======[START]======" << std::endl;
    }

    void OnTestSuiteEnd(const TestSuite& /*test_suite*/) override
    {
        std::cout << "======[END]======" << std::endl;
    }
};

// 2) 리스너 등록
// => main 함수를 통해서 리스너를 등록해야 합니다.
int main(int argc, char** argv)
{
    testing::InitGoogleTest(&argc, argv);

    testing::TestEventListeners& litensers = testing::UnitTest::GetInstance()->listeners();
    litensers.Append(new TestListener);

    // 구글 테스트의 출력을 제거할 수 있습니다.
    // delete litensers.Release(litensers.default_result_printer());

    return RUN_ALL_TESTS();
}
