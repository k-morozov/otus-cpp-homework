//
// Created by focus on 17.07.22.
//

#include "Pool.h"

#include <optional>


namespace {

std::vector<std::string> split(const std::string &str, char d) {
	std::vector<std::string> r;

	std::string::size_type start = 0;
	std::string::size_type stop = str.find_first_of(d);
	while(stop != std::string::npos) {
		r.push_back(str.substr(start, stop - start));

		start = stop + 1;
		stop = str.find_first_of(d, start);
	}
	r.push_back(str.substr(start));

	return r;
}

std::optional<ip_address_t> parse_address(const std::vector<std::string>& address) {
	assert(address.size() == IP_ADDRESS_SIZE);

	ip_address_t result_address{};

	try {
		for(size_t i=0; i < IP_ADDRESS_SIZE; ++i) {
			result_address[i] = std::stoi(address[i]);
		}
	} catch (std::exception& ex) {
		return {};
	}

	return result_address;
}

template<class T, std::size_t ...S>
void unpack_impl(std::ostream& os, T&& v, std::index_sequence<S...>) {
	((os << (S==0 ? "" : ".") << static_cast<int>(v[S])),... );
}

template<class T>
void unpack_ip(std::ostream& os, T&& c) {
	// assert size
	unpack_impl(os,
				  std::forward<T>(c),
				  std::make_index_sequence<IP_ADDRESS_SIZE>());
	os << std::endl;
}

} // anonymous namespace


std::ostream& operator<<(std::ostream& os, const Pool& p) {
	std::for_each(std::begin(p.ip_pool_), std::end(p.ip_pool_),
				  [&os](const auto& ip) { unpack_ip(os, ip); });
	return os;
}

bool operator==(const Pool& lhs, const Pool& rhs) {
	return lhs.ip_pool_ == rhs.ip_pool_;
}

Pool::Pool(std::istream &stream) {
	for(std::string line; std::getline(stream, line);) {
		if (line.empty()) {
			break;
		}
		auto v = split(line, '\t');
		if (v.empty()) {
			break;
		}
		auto address_str = split(v.at(0), '.');
		if (address_str.size() != IP_ADDRESS_SIZE) {
			break;
		}
		auto address = parse_address(address_str);
		if (address) {
			ip_pool_.push_back(address.value());
		}
	}

	std::sort(ip_pool_.begin(), ip_pool_.end(),
			  SortPredicate{});
}

Pool Pool::filter_any(uint8_t octet) const {
	std::vector<ip_address_t> addresses;

	std::copy_if(std::begin(ip_pool_), std::end(ip_pool_),
				 std::back_inserter(addresses),
				 [octet](const ip_address_t& v) {
		if (auto it = std::find(v.begin(), v.end(), octet); it != v.end()) {
			return true;
		}
		return false;
	});
	return Pool{std::move(addresses)};
}

bool Pool::SortPredicate::operator()(const ip_address_t& lhs, const ip_address_t& rhs) {
	// @TODO update
	assert(lhs.size() != rhs.size() != IP_ADDRESS_SIZE);

	for(size_t i=0; i<IP_ADDRESS_SIZE; ++i) {
		if (lhs[i] < rhs[i]) {
			return false;
		}
		if (lhs[i] > rhs[i]) {
			return true;
		}
	}
	return false;
}
