//
// Created by focus on 14.07.22.
//

#include "gtest/gtest.h"

#include <fstream>

#include "../src/utils.h"


class SuiteIpPool : public ::testing::Test
{
public:
	SuiteIpPool() = default;

protected:
	void SetUp() override {
		static constexpr auto filename = "ip_filter.tsv";
		std::ifstream stream;
		stream.open(filename, std::ios::in);

		if (!stream.is_open()) {
			throw std::invalid_argument("failed open file.");
		}

		ip_pool_ = utils::read_data(stream);
	}

	void TearDown() override {
	}

	std::vector<utils::ip_address_t> ip_pool_;
};

TEST_F(SuiteIpPool, ReverseSort) {
	std::sort(ip_pool_.begin(), ip_pool_.end(),
			  utils::SortPredicate{});

	ASSERT_EQ(ip_pool_.size(), 1000);

	constexpr utils::ip_address_t expected_first = {222, 173, 235, 246};
	ASSERT_EQ(ip_pool_.front(), expected_first);

	constexpr utils::ip_address_t expected_last = {1, 1, 234, 8};
	ASSERT_EQ(ip_pool_.back(), expected_last);
}