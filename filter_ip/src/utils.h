//
// Created by focus on 14.07.22.
//

#pragma once

#include <algorithm>
#include <cassert>
#include <cstdlib>
#include <iostream>
#include <string>
#include <array>
#include <vector>

namespace utils {

constexpr size_t IP_ADDRESS_SIZE = 4;

using octet_t = uint8_t;
using ip_address_t = std::array<octet_t, IP_ADDRESS_SIZE>;

struct SortPredicate {
	bool operator()(const ip_address_t& lhs, const ip_address_t& rhs);
};

std::vector<std::string> split(const std::string &str, char d);

ip_address_t parse_address(const std::vector<std::string>& address);

std::vector<ip_address_t> read_data(std::istream& stream = std::cin);

void print(const std::vector<ip_address_t>& ip_pool);

} // namespace utils