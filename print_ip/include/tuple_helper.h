//
// Created by focus on 31.07.22.
//

#pragma once

#include <concepts>

namespace detail {

namespace impl {

template<typename T>
constexpr auto check_same_type(T&& data) {
	return std::apply([](auto&& ... v) constexpr {
						  return std::array{std::forward<decltype(v)>(v) ... };
					  },
					  std::forward<T>(data));
}

template<typename T>
concept is_same_types = requires(T&& a) {
	(check_same_type<T>(std::forward<T>(a)));
};

template<auto& Stream, typename T, std::size_t ...S>
requires is_same_types<T>
void print_impl(T&& tuple, std::index_sequence<S...>) {
	((Stream << (S!=0 ? "." : "") << std::get<S>(tuple)),...) << std::endl;
}

} // namespace impl


template<typename T>
struct is_tuple {
	static constexpr bool value = false;
};

template<typename ...Args>
struct is_tuple<std::tuple<Args...>> {
	static constexpr bool value = true;
};

template<auto& Stream, typename ...Args>
void print_tuple(const std::tuple<Args...>& tuple) {
	impl::print_impl<Stream>(tuple, std::make_index_sequence<sizeof...(Args)>());
}

} // namespace detail