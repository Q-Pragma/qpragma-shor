/* -*- coding: utf-8 -*- */
/*
 * @file        qpragma/shor/fraction.h
 * @authors     Arnaud GAZDA <arnaud.gazda@eviden.com>
 *
 * @copyright
 *     Licensed to the Apache Software Foundation (ASF) under one
 *     or more contributor license agreements.  See the NOTICE file
 *     distributed with this work for additional information
 *     regarding copyright ownership.  The ASF licenses this file
 *     to you under the Apache License, Version 2.0 (the
 *     "License"); you may not use this file except in compliance
 *     with the License.  You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 *     Unless required by applicable law or agreed to in writing,
 *     software distributed under the License is distributed on an
 *     "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY
 *     KIND, either express or implied.  See the License for the
 *     specific language governing permissions and limitations
 *     under the License.
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
        explicit fraction(int /* number */);                                                            // Computes "number / 1"
        explicit fraction(int64_t /* number */);                                                        // Computes "number / 1"
        fraction(uint64_t /* numerator */, uint64_t /* denominator */, sign /* fsign */ = sign::pos);   // Computes "± numerator / denominator"

        // Get numerator and denomirator
        sign get_sign() const;
        uint64_t numerator() const;
        uint64_t denominator() const;

        // Cast function
        fraction & operator=(uint64_t);
        operator uint64_t() const;
        operator int64_t() const;

        // Operators
        fraction & operator+=(const fraction &);
        fraction & operator-=(const fraction &);
        fraction & operator*=(const fraction &);
        std::strong_ordering operator<=>(const fraction &) const;
        
        bool operator==(int) const;
        bool operator==(uint64_t) const;
        bool operator==(const fraction &) const;

        fraction operator-() const;
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
