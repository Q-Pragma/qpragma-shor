/**
 * This test file ensure that functions defined in "qpragma/shor/continued_fraction.h"
 * work as expected
 */

// Include Google tests and C++ stdlib
#include <limits>
#include <random>
#include <gtest/gtest.h>

// Include Q-Pragma shor
#include "qpragma/shor/continued_fraction.h"
#include "qpragma/shor/display.h"

using qpragma::shor::pow_mod;
using qpragma::shor::fraction;
using qpragma::shor::continued_fraction;


/**
 * Compute a fraction described by its decomposition as a
 * continued fraction
 */
template <typename NUM_TYPE>
inline NUM_TYPE compute_fraction(const std::list<int64_t>::const_iterator & begin, const std::list<int64_t>::const_iterator & end) {
    // Ensure begin differs from end
    if (begin == end) {
        throw std::runtime_error("Could not compute fraction - fraction is empty");
    }

    // Init result
    if (std::next(begin) == end) {
        return NUM_TYPE(*begin);
    }

    return NUM_TYPE(*begin) + NUM_TYPE(1UL) / compute_fraction<NUM_TYPE>(std::next(begin), end);
}


/**
 * Test function qpragma::shor::continued_fraction and ensure this function
 * returns the expected result
 */

TEST(ContinuedFraction, DecompositionGreaterThanOne) {
    fraction my_fraction(15625UL, 6842UL);
    auto decomposition = continued_fraction(my_fraction);

    ASSERT_EQ(decomposition, std::list<int64_t>({ 2L, 3L, 1L, 1L, 9L, 1L, 1L, 48L }));
}


TEST(ContinuedFraction, DecompositionLowerThanOne) {
    fraction my_fraction(17UL, 23UL);
    auto decomposition = continued_fraction(my_fraction);

    ASSERT_EQ(decomposition, std::list<int64_t>({ 0L, 1L, 2L, 1L, 5L }));
}


TEST(ContinuedFraction, RandomFractions) {
    std::mt19937 gen(12345);
    std::uniform_int_distribution<uint64_t> distrib(1UL, std::numeric_limits<uint32_t>::max());

    for (uint8_t idx = 0; idx < 100; ++idx) {
        // Create random fraction
        uint64_t numerator = distrib(gen);
        uint64_t denominator = distrib(gen);
        fraction random_fraction(numerator, denominator);

        // Check decomposition
        auto decomposition = continued_fraction(random_fraction);
        double double_convergent = compute_fraction<double>(decomposition.begin(), decomposition.end());
        fraction fraction_convergent = compute_fraction<fraction>(decomposition.begin(), decomposition.end());

        ASSERT_DOUBLE_EQ(static_cast<double>(numerator) / static_cast<double>(denominator), double_convergent)
            << "Fraction " << numerator << "/" << denominator << " is not (almost) equal to its continued fraction decomposition";

        ASSERT_EQ(random_fraction, fraction_convergent)
            << "Fraction " << numerator << "/" << denominator << " is not (exactly) equal to its continued fraction decomposition";
    }
}


/**
 * Test function qpragma::shor::pow and ensure that this function
 * returns the expected result
 */

TEST(Pow, Trivial) {
    std::mt19937 gen(56789);
    std::uniform_int_distribution<uint64_t> distrib(1UL, std::numeric_limits<uint32_t>::max());

    for (uint8_t idx = 0; idx < 100; ++idx) {
        uint64_t base = distrib(gen);
        uint64_t pow_base_one = pow_mod(base, 1UL, 50UL);
        uint64_t pow_base_zero = pow_mod(base, 0UL, 50UL);

        ASSERT_EQ(pow_base_one, base % 50UL) << "pow(" << base << ", 1) is not equal to " << base;
        ASSERT_EQ(pow_base_zero, 1UL) << "pow(" << base << ", 0) is not equal to 1";
    }
}


TEST(Pow, PowerOfTwo) {
    for (uint64_t exponent = 3UL; exponent < 50UL; ++exponent) {
        auto result_no_mod = pow_mod(2UL, exponent, 1UL << 60UL);
        ASSERT_EQ(result_no_mod, 1UL << exponent) << "pow(2, " << exponent << ") is not equal to " << (1UL << exponent);

        auto result_mod = pow_mod(2UL, exponent, 43UL);
        ASSERT_EQ(result_mod, (1UL << exponent) % 43UL) << "pow(2, " << exponent << ") % 43 is not equal to " << ((1UL << exponent) % 43UL);
    }
}


TEST(Pow, Fixed) {
    // Pow(5, 7)
    {
        auto result = pow_mod(5UL, 7UL, std::numeric_limits<uint64_t>::max());
        ASSERT_EQ(result, 78125UL);
    }

    {
        auto result = pow_mod(5UL, 7UL, 100UL);
        ASSERT_EQ(result, 25UL);
    }

    // Pow(12, 2)
    {
        auto result = pow_mod(12UL, 2UL, std::numeric_limits<uint64_t>::max());
        ASSERT_EQ(result, 144UL);
    }

    {
        auto result = pow_mod(12UL, 2UL, 40UL);
        ASSERT_EQ(result, 24UL);
    }

    // Pow(3UL, 13UL)
    {
        auto result = pow_mod(3UL, 13UL, std::numeric_limits<uint64_t>::max());
        ASSERT_EQ(result, 1594323UL);
    }

    {
        auto result = pow_mod(3UL, 13UL, 143UL);
        ASSERT_EQ(result, 16UL);
    }
}
