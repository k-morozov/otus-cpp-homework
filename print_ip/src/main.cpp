//
// Created by focus on 30.07.22.
//
#include <iostream>

#include <print_ip.h>


int main() {
	print_ip( int8_t{-1} ); // 255

	print_ip( int16_t{0} ); // 0.0

	print_ip( int32_t{2130706433} ); // 127.0.0.1

	print_ip( int64_t{8875824491850138409} );// 123.45.67.89.101.112.131.41
}
