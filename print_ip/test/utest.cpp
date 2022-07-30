//
// Created by focus on 30.07.22.
//

#include "gtest/gtest.h"

#include <sstream>

#include <print_ip.h>


class Basic : public ::testing::Test {
};


TEST_F(Basic, one_byte) {
	static std::stringstream stream;

	print_ip<int8_t, stream>(int8_t{-1});
	const auto result = stream.str();
	const std::string expected = "255\n";
	ASSERT_EQ(result, expected);
}

TEST_F(Basic, two_byte) {
	static std::stringstream stream;

	print_ip<int16_t, stream>(int16_t{0});
	const auto result = stream.str();
	const std::string expected = "0.0\n";
	ASSERT_EQ(result, expected);
}

TEST_F(Basic, four_byte) {
	static std::stringstream stream;

	print_ip<int32_t, stream>(int32_t{2130706433});
	const auto result = stream.str();
	const std::string expected = "127.0.0.1\n";
	ASSERT_EQ(result, expected);
}

TEST_F(Basic, eight_byte) {
	static std::stringstream stream;

	print_ip<int64_t, stream>(int64_t{8875824491850138409});
	const auto result = stream.str();
	const std::string expected = "123.45.67.89.101.112.131.41\n";
	ASSERT_EQ(result, expected);
}
