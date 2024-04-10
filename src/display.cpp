#include "qpragma/shor/display.h"

#include <string>
#include <iostream>
#include <iterator>
#include <algorithm>

using qpragma::shor::fraction;


void qpragma::shor::pretty_display(const boost::math::tools::simple_continued_fraction<fraction> & frac) {
    pretty_display_internal(frac.partial_denominators(), 0);
}


void qpragma::shor::pretty_display_internal(const std::vector<int64_t> & numbers, uint64_t indent_size) {
    // Ignore empty vector or vector of size 1
    if (numbers.size() == 0UL) {
        return;
    }

    if (numbers.size() == 1UL) {
        std::cout << std::string(indent_size, ' ') << numbers[0UL] << std::endl;
        return;
    }

    // Get first item
    std::string indent(indent_size, ' ');
    auto first = std::to_string(numbers[0UL]);

    std::cout << indent << std::string(first.size() + 5UL, ' ') << "1\n"
              << indent << first + " + ----" << std::endl;

    // Display subvector
    std::vector<int64_t> sub_vector;
    sub_vector.reserve(numbers.size() - 1UL);
    std::copy(numbers.begin() + 1UL, numbers.end(), std::back_inserter(sub_vector));

    pretty_display_internal(sub_vector, indent_size + first.size() + 3UL);
}
