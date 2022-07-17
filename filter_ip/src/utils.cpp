//
// Created by focus on 17.07.22.
//

#include "utils.h"

namespace utils {

namespace impl {

	template<class T, std::size_t ...S>
	void unpack_vector(T&& v, std::index_sequence<S...>) {
		((std::cout << (S==0 ? "" : ".") << static_cast<int>(v[S])),... );
		std::cout << std::endl;
	}

	template<class T>
	void unpack(T&& c) {
		// assert size
		unpack_vector(std::forward<T>(c),
					  std::make_index_sequence<IP_ADDRESS_SIZE>());
	}

} // namespace impl

bool SortPredicate::operator()(const ip_address_t& lhs, const ip_address_t& rhs) {
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

ip_address_t parse_address(const std::vector<std::string>& address) {
	assert(address.size() == IP_ADDRESS_SIZE);

	ip_address_t result_address{};

	for(size_t i=0; i < IP_ADDRESS_SIZE; ++i) {
		// except
		result_address[i] = std::stoi(address[i]);
	}
	return result_address;
}

std::vector<ip_address_t> read_data(std::istream& stream) {
	std::vector<ip_address_t> ip_pool;

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
		ip_pool.push_back(address);
	}

	return ip_pool;
}

void print(const std::vector<ip_address_t>& ip_pool) {
	std::for_each(std::begin(ip_pool), std::end(ip_pool),
				  [](const auto& ip) {impl::unpack(ip);});
}


} // namespace utils