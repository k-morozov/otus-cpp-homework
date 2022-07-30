//
// Created by focus on 14.07.22.
//

#include "gtest/gtest.h"

#include <fstream>
#include <filesystem>

#include "../src/Pool.h"


class SuiteIpPool : public ::testing::Test
{
public:
	SuiteIpPool() = default;

protected:
	void SetUp() override {
		static constexpr auto filename = "static/ip_filter.tsv";
		std::ifstream stream;
		stream.open(filename, std::ios::in);

		if (!stream.is_open()) {
			throw std::invalid_argument("failed open file.");
		}

		pool_ = std::make_unique<Pool>(stream);
		if (!pool_) {
			throw std::invalid_argument("failed alloc.");
		}

		stream.close();
	}

	void TearDown() override {
	}

	std::unique_ptr<Pool> pool_;
};

//TEST_F(SuiteIpPool, ReverseSort) {
////	ASSERT_EQ(ip_pool_.size(), 1000);
//
////	constexpr utils::ip_address_t expected_first = {222, 173, 235, 246};
////	ASSERT_EQ(ip_pool_.front(), expected_first);
////
////	constexpr utils::ip_address_t expected_last = {1, 1, 234, 8};
////	ASSERT_EQ(ip_pool_.back(), expected_last);
//}

TEST_F(SuiteIpPool, FilterByFirstByte) {
	const auto pool = pool_->filter(1);

	Pool expected_pool {{
			{ 1, 231, 69, 33 },
			{ 1, 87, 203, 225 },
			{ 1, 70, 44, 170 },
			{ 1, 29, 168, 152 },
			{ 1, 1, 234, 8 }
	}};
	ASSERT_EQ(pool, expected_pool);
}

TEST_F(SuiteIpPool, FilterByTwoByte) {
	const auto pool = pool_->filter(46, 70);
	Pool expected_pool {{
			{ 46, 70, 225, 39 },
			{ 46, 70, 147, 26 },
			{ 46, 70, 113, 73 },
			{ 46, 70, 29, 76 }
	}};
	ASSERT_EQ(pool, expected_pool);
}

TEST_F(SuiteIpPool, FilterByThreeByte) {
	const auto pool = pool_->filter(46, 70, 225);

	Pool expected_pool {{
			{ 46, 70, 225, 39 }
	}};
	ASSERT_EQ(pool, expected_pool);
}

TEST_F(SuiteIpPool, FilterByAnyByte) {
	const auto pool = pool_->filter_any(46);

	Pool expected_pool {{
								{186, 204, 34, 46},
								{186, 46, 222, 194 },
								{ 185, 46, 87, 231 },
								{ 185, 46, 86, 132 },
								{ 185, 46, 86, 131 },
								{ 185, 46, 86, 131 },
								{ 185, 46, 86, 22 },
								{ 185, 46, 85, 204 },
								{ 185, 46, 85, 78 },
								{ 68, 46, 218, 208 },
								{ 46, 251, 197, 23 },
								{46, 223, 254, 56},
								{ 46, 223, 254, 56 },
								{ 46, 182, 19, 219 },
								{ 46, 161, 63, 66 },
								{ 46, 161, 61, 51 },
								{ 46, 161, 60, 92 },
								{ 46, 161, 60, 35 },
								{ 46, 161, 58, 202 },
								{ 46, 161, 56, 241 },
								{ 46, 161, 56, 203 },
								{ 46, 161, 56, 174 },
								{ 46, 161, 56, 106 },
								{ 46, 161, 56, 106 },
								{ 46, 101, 163, 119 },
								{ 46, 101, 127, 145 },
								{ 46, 70, 225, 39 },
								{ 46, 70, 147, 26 },
								{ 46, 70, 113, 73 },
								{ 46, 70, 29, 76 },
								{ 46, 55, 46, 98 },
								{ 46, 49, 43, 85 },
								{ 39, 46, 86, 85 },
								{ 5, 189, 203, 46 },
						}};
	ASSERT_EQ(pool, expected_pool);
}