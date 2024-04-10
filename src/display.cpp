#include "qpragma/shor/display.h"

#include <string>
#include <iostream>
#include <iterator>
#include <algorithm>

using qpragma::shor::fraction;


void qpragma::shor::pretty_display(const boost::math::tools::simple_continued_fraction<fraction> & frac) {
    // Get numbers
    std::vector<int64_t> numbers = frac.partial_denominators();

    if (numbers.empty()) {
        return;
    }

    // Compute display width
    uint64_t display_size = (numbers.size() - 1UL) * 3UL;
    std::ranges::for_each(numbers, [&display_size](int64_t item){ display_size += std::to_string(item).size(); });

    // Display
    uint64_t indent = 0UL;

    for (auto item: numbers) {
        std::string number_str = std::to_string(item);
        bool is_not_last_line = display_size > indent + 3UL;
        uint64_t nb_dash = 0UL;

        if (is_not_last_line) {
            nb_dash = display_size - indent - number_str.size() - 3UL;
            std::cout << std::string(indent + number_str.size() + 3UL + (nb_dash - 1) / 2, ' ') << "1\n";
        }

        std::cout << std::string(indent, ' ') << number_str;

        if (is_not_last_line)
            std::cout << " + " << std::string(nb_dash, '-');

        std::cout << std::endl;
        indent += number_str.size() + 3UL;
    }
}
