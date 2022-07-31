//
// Created by focus on 30.07.22.
//

#include "gtest/gtest.h"

#include <sstream>

#include <print_ip.h>


class Basic : public ::testing::Test {
};


TEST_F(Basic, integral_one_byte) {
	static std::stringstream stream;

	print_ip<int8_t, stream>(int8_t{-1});
	const auto result = stream.str();
	const std::string expected = "255\n";
	ASSERT_EQ(result, expected);
}

TEST_F(Basic, integral_two_byte) {
	static std::stringstream stream;

	print_ip<int16_t, stream>(int16_t{0});
	const auto result = stream.str();
	const std::string expected = "0.0\n";
	ASSERT_EQ(result, expected);
}

TEST_F(Basic, integral_four_byte) {
	static std::stringstream stream;

	print_ip<int32_t, stream>(int32_t{2130706433});
	const auto result = stream.str();
	const std::string expected = "127.0.0.1\n";
	ASSERT_EQ(result, expected);
}

TEST_F(Basic, integral_eight_byte) {
	static std::stringstream stream;

	print_ip<int64_t, stream>(int64_t{8875824491850138409});
	const auto result = stream.str();
	const std::string expected = "123.45.67.89.101.112.131.41\n";
	ASSERT_EQ(result, expected);
}

TEST_F(Basic, string_value) {
	static std::stringstream stream;

	print_ip<std::string, stream>(std::string{"Hello, World!"});
	const auto result = stream.str();
	const std::string expected = "Hello, World!\n";
	ASSERT_EQ(result, expected);
}

TEST_F(Basic, vector_value) {
	static std::stringstream stream;

	print_ip<std::vector<int>, stream>(std::vector<int>{100, 200, 300, 400});
	const auto result = stream.str();
	const std::string expected = "100.200.300.400\n";
	ASSERT_EQ(result, expected);
}