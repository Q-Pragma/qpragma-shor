/* -*- coding: utf-8 -*- */
/*
 * @file        qpragma/shor/fraction.h
 * @authors     Arnaud GAZDA <arnaud.gazda@atos.net>
 * @copyright   2024 Bull S.A.S. - All rights reserved.
 *              This is not Free or Open Source software.
 *              Please contact BULL SAS for details about its license.
 *              Bull - Rue Jean Jaurès - B.P. 68 - 78340 Les Clayes-sous-Bois
 * @brief
 *
 */

#ifndef QPRAGMA_SHOR_FRACTION_H
#define QPRAGMA_SHOR_FRACTION_H

#include <limits>
#include <cstdint>
#include <compare>
#include <ostream>


namespace qpragma::shor {
    /**
     * Enumeration describing the sign of a fraction
     * A sign is either positive of negative
     */
    enum class sign { pos = true, neg = false };


    /**
     * This class describe a fraction ± p/q where p and q are two positive integer
     * (and q is not null)
     *
     * This class is designed to be compatible with the Continued Fraction implementation
     * of boost
     */
    class fraction {
    private:
        sign _sign = sign::pos;
        uint64_t _numerator = 0UL;
        uint64_t _denominator = 1UL;

        void _simplify();

    public:
        fraction() = default;
        explicit fraction(uint64_t /* number */, sign /* fsign */ = sign::pos);                         // Computes "± number / 1"
        fraction(int /* number */);                                                                     // Computes "number / 1"
        fraction(uint64_t /* numerator */, uint64_t /* denominator */, sign /* fsign */ = sign::pos);   // Computes "± numerator / denominator"

        // Get numerator and denomirator
        sign get_sign() const;
        uint64_t numerator() const;
        uint64_t denominator() const;

        // Cast function
        fraction & operator=(uint64_t);
        operator uint64_t() const;

        // Operators
        fraction & operator+=(const fraction &);
        fraction & operator*=(const fraction &);
        std::strong_ordering operator<=>(const fraction &) const;
        
        bool operator==(int) const;
        bool operator==(uint64_t) const;
        bool operator==(const fraction &) const;
    };
}


namespace std {
    /**
     * Checks if a fraction describe a finite number
     * or not
     * The fraction is finite if and only if the denomination is different
     * that 0 (and the numerator is finite, which is always true)
     */
    bool isfinite(const qpragma::shor::fraction &);


    /**
     * Compute the floor of a fraction
     *
     * This function uses the "static_cast<uint64_t>" function, provided by the
     * fraction class
     */
    qpragma::shor::fraction floor(const qpragma::shor::fraction &);


    /**
     * Computes the absolute value of a fraction
     *
     * This function copy the argument but change the sign of the fraction
     */
    qpragma::shor::fraction abs(const qpragma::shor::fraction &);


    /**
     * Numerical limits of a fraction
     * This class does not implement all the specifications of "numeric_limits"
     */
    template <>
    struct numeric_limits<qpragma::shor::fraction> {
        // Number of digits of digits in the base-10 required to display a fraction number
        // The same number of digits as "double" is used
        static constexpr uint64_t max_digits10 = std::numeric_limits<double>::max_digits10;

        // Compute the minimal value.
        // This value is technically (- MAX_UINT64) but (- MAX_UINT32) will be preferred
        // to avoid overflow when manipulating fractions
        static qpragma::shor::fraction min() {
            return qpragma::shor::fraction(std::numeric_limits<uint32_t>::max(), qpragma::shor::sign::neg);
        }

        // Difference between 1.0 and the next value representable using a fraction.
        // This value is technically (1 / MAX_UINT64) but (1 / MAX_UINT32) will be preferred
        // to avoid overflow when manipulating fractions
        static qpragma::shor::fraction epsilon() {
            return qpragma::shor::fraction(1UL, std::numeric_limits<uint32_t>::max());
        }
    };
}


/**
 * C++ operators
 * Required to implemented the continued fraction algorithm
 */

// Add
qpragma::shor::fraction operator+(const qpragma::shor::fraction &, const qpragma::shor::fraction &);


// Substract
qpragma::shor::fraction operator-(const qpragma::shor::fraction &, const qpragma::shor::fraction &);


// Inverse
qpragma::shor::fraction operator/(int, const qpragma::shor::fraction &);
qpragma::shor::fraction operator/(uint64_t, const qpragma::shor::fraction &);
qpragma::shor::fraction operator/(const qpragma::shor::fraction &, const qpragma::shor::fraction &);


// Multiply
qpragma::shor::fraction operator*(int, const qpragma::shor::fraction &);
qpragma::shor::fraction operator*(uint64_t, const qpragma::shor::fraction &);
qpragma::shor::fraction operator*(const qpragma::shor::fraction &, const qpragma::shor::fraction &);


// Display fraction
std::ostream & operator<<(std::ostream &, const qpragma::shor::fraction &);

#endif  /* QPRAGMA_SHOR_FRACTION_H */
