//
// Created by focus on 17.07.22.
//

#pragma once

#include <algorithm>
#include <cassert>
#include <cstdlib>
#include <iostream>
#include <string>
#include <array>
#include <vector>

constexpr size_t IP_ADDRESS_SIZE = 4;

using octet_t = uint8_t;
using ip_address_t = std::array<octet_t, IP_ADDRESS_SIZE>;

class Pool;
std::ostream& operator<<(std::ostream& os, const Pool& p);
bool operator==(const Pool& lhs, const Pool& rhs);


class Pool {
public:
	Pool() = default;

	explicit Pool(std::istream& stream);

	explicit Pool(std::vector<ip_address_t>&& pool) :
		ip_pool_(std::move(pool))
		{};

	template<typename ...Args>
	Pool filter(Args&& ...args) const;

	[[nodiscard]]
	Pool filter_any(octet_t octet) const;

private:
	std::vector<ip_address_t> ip_pool_;

	friend std::ostream& operator<<(std::ostream& os, const Pool& p);
	friend bool operator==(const Pool& lhs, const Pool& rhs);

	struct SortPredicate {
		bool operator()(const ip_address_t& lhs, const ip_address_t& rhs);
	};

	template<typename T, typename U, size_t ...N>
	static bool check_comp_impl(T&& ip, U&& t, std::index_sequence<N...>);

	template<typename T, typename ...Args>
	static bool check_comp_ip(T&& ip, Args&& ...args);
};


template<typename ...Args>
Pool Pool::filter(Args&& ...args) const {
	static_assert(sizeof...(args) < IP_ADDRESS_SIZE);

	std::vector<ip_address_t> ip_pool_filtered;

	std::copy_if(ip_pool_.cbegin(), ip_pool_.cend(),
				 std::back_inserter(ip_pool_filtered),
	[...param = std::forward<Args>(args)](auto&& ip) mutable {
		return check_comp_ip(std::forward<decltype(ip)>(ip),
							 std::forward<decltype(param)>(param)...);
	});

	return Pool{std::move(ip_pool_filtered)};
}

template<typename T, typename U, size_t ...N>
bool Pool::check_comp_impl(T&& ip, U&& t, std::index_sequence<N...>) {
	bool result = true;
	(( ip[N] != static_cast<octet_t>(std::get<N>(t)) ? result = false : result &= true), ...);
	return result;
}


template<typename T, typename ...Args>
bool Pool::check_comp_ip(T&& ip, Args&& ...args) {
	return check_comp_impl(std::forward<T>(ip),
						   std::make_tuple<Args...>(std::forward<Args>(args)...),
						   std::make_index_sequence<sizeof...(Args)>());
}


