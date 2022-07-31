//
// Created by focus on 31.07.22.
//

#pragma once

namespace detail {

template<typename T>
struct is_tuple {
	static constexpr bool value = false;
};

template<typename ...Args>
struct is_tuple<std::tuple<Args...>> {
	static constexpr bool value = true;
};

namespace impl {

template<auto& Stream, typename T, std::size_t ...S>
void print_impl(T&& tuple, std::index_sequence<S...>) {
	((Stream << (S!=0 ? "." : "") << std::get<S>(tuple)),...) << std::endl;
}

}

template<auto& Stream, typename ...Args>
void print_tuple(const std::tuple<Args...>& tuple) {
	impl::print_impl<Stream>(tuple, std::make_index_sequence<sizeof...(Args)>());
}

} // namespace detail