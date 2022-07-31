//
// Created by focus on 30.07.22.
//

#pragma once

#include <cassert>
#include <concepts>
#include <list>
#include <type_traits>
#include <utility>
#include <vector>


namespace detail {

template<typename T>
concept Integral = std::is_integral_v<T>;;

template<typename T>
concept VectorOrList = std::is_same_v<T, std::vector<typename T::value_type>> ||
						std::is_same_v<T, std::list<typename T::value_type>>;

template<typename T, auto& Stream>
struct ip {
	static constexpr void print(T&& value) {
		Stream << value << std::endl;
	}
};

template<typename T, auto& Stream>
requires Integral<T>
struct ip<T, Stream> {
	static_assert(std::is_integral_v<T>);
	static constexpr void print(T&& value) {
		unpack(std::forward<T>(value),
		        std::make_index_sequence<sizeof(T)>());
	}

private:
	template<std::size_t ...S>
	static void unpack(T&& value, std::index_sequence<S...>) {
		using unsigned_t = typename std::make_unsigned_t<T>;
		constexpr auto mask = static_cast<unsigned_t>(0xFF);
		((Stream << (S==0 ? "" : ".") <<
			((value & (mask << offset<S>() )) >> offset<S>() )),...) << std::endl;
	}

	template<std::size_t S>
	inline static constexpr size_t offset() {
		static_assert(sizeof(T) > S);
		return (sizeof(T) - S - 1) * 8;
	}
};

template<typename T, auto& Stream>
requires VectorOrList<T>
struct ip<T, Stream> {
	using value_type = typename T::value_type;

	static constexpr void print(T&& container) {
		for(auto it = container.begin(); it != container.end(); it++) {
			Stream << (it!=container.begin() ? "." : "") << *it;
		}
		Stream << std::endl;
	}
};

} // namespace detail


template<typename T, auto& Stream = std::cout>
void print_ip(T&& arg) {
	detail::ip<T, Stream>::print(std::forward<T>(arg));
}