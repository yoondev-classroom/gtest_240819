// 1_시작.cpp
#include <gtest/gtest.h>


// Google Test의 main은 아래 형태로 제공되어야 합니다.
int main(int argc, char** argv)
{
	testing::InitGoogleTest(&argc, argv);

	return RUN_ALL_TESTS();
}
