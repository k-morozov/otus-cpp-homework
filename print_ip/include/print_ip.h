//
// Created by focus on 30.07.22.
//

#pragma once

#include <iosfwd>
#include <print_impl.h>

template<typename T, auto& Stream = std::cout>
void print_ip(T&& arg) {
	detail::ip<T, Stream>::print(std::forward<T>(arg));
}