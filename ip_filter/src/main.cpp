#include <iostream>

#include "Pool.h"


int main(int argc, char const *argv[]) {
    try {
		Pool pool_(std::cin);
		std::cout << pool_;

		auto p1 = pool_.filter(1);
		std::cout << p1;

		auto p2 = pool_.filter(46, 70);
		std::cout << p2;

		auto p3 = pool_.filter_any(46);
		std::cout << p3;
    }
    catch(const std::exception &e) {
        std::cerr << e.what() << std::endl;
    }
    return 0;
}
