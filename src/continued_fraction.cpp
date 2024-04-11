#include "qpragma/shor/continued_fraction.h"


// Continued fraction implementation
std::list<int64_t> qpragma::shor::continued_fraction(qpragma::shor::fraction to_decompose) {
    // Init result
    std::list<int64_t> result;

    // Decompose item
    while (true) {
        fraction item = std::floor(to_decompose);
        result.push_back(item);
        to_decompose -= item;

        if (to_decompose == 0UL) {
            break;
        }

        to_decompose = 1UL / to_decompose;
    }

    return result;
}
