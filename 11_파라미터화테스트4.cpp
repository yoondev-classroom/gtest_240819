// 11_파라미터화테스트4.cpp
#include <string>
#include <vector>

#include <gtest/gtest.h>

enum Color {
    RED,
    WHITE,
    BLACK,
    BLUE,
};

Color colors[] = { Color::RED, Color::WHITE, Color::BLACK, Color::BLUE };

std::vector<std::string> cars = {
    "Sonata", "Avante", "Genesis"
};

// 구글 테스트의 파라미터화 테스트는 두 개 이상의 데이터 셋을 조합해서
// 테스트를 수행할 수 있습니다.
// => tuple

using CarType = std::tuple<std::string, Color>;

class CarTest : public testing::TestWithParam<CarType> { };

INSTANTIATE_TEST_SUITE_P(CarValues, CarTest,
    testing::Combine(
        testing::ValuesIn(cars),
        testing::ValuesIn(colors)));

TEST_P(CarTest, Sample)
{
    const CarType& data = GetParam();

    std::string model = std::get<0>(data);
    Color color = std::get<1>(data);

    std::cout << model << ", " << color << std::endl;
}
