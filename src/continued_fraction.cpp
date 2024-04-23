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


// Find a candidate
//
// Given a fraction [a0, a1, ...], its convergents [a0, a1, ..., aN] are equals
// to h[N]/k[N]
//
// where:
// h[N] = aN * h[N - 1] + h[N - 2]  (and h[-1] = 1 and h[-2] = 0)
// k[n] = aN * k[N - 1] + k[N - 2]  (and k[-1] = 0 and k[-2] = 1)
uint64_t qpragma::shor::find_candidate(
    const qpragma::shor::fraction & frac, uint64_t x_value, uint64_t N_value
) {
    // Computes threshold
    const fraction threshold(1UL, 2UL * frac.denominator());

    // Define fraction
    int64_t h_n = 1;
    int64_t h_n_prev = 0;

    int64_t k_n = 0;
    int64_t k_n_prev = 1;

    // Computes all the convergents and checks if these convergents are candidates
    for (int64_t item: continued_fraction(frac)) {
        // Copy h[N] and k[N]
        auto h_n_copy = h_n;
        auto k_n_copy = k_n;

        // Computes h[N + 1] and k[N + 1]
        h_n = item * h_n + h_n_prev;
        k_n = item * k_n + k_n_prev;

        h_n_prev = h_n_copy;
        k_n_prev = k_n_copy;

        // Checks if the convergent is a candidate
        fraction convergent(h_n, k_n);

        if (
            std::abs(frac - convergent) < threshold
            and convergent.denominator() % 2UL == 0UL
            and pow_mod(x_value, convergent.denominator(), N_value) == 1UL
        ) {
            return convergent.denominator();
        }
    }

    // No value found
    return 0UL;
}


// Pow
uint64_t qpragma::shor::pow_mod(uint64_t base, uint64_t exponent, uint64_t modulus) {
    // Trivial case
    if (exponent == 0UL)
        return 1;

    // Recurse call
    uint64_t square_root = pow_mod(base, exponent / 2UL, modulus);

    if (exponent % 2UL == 0UL)
        return (square_root * square_root) % modulus;

    return (base * square_root * square_root) % modulus;
}
