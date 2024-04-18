/* -*- coding: utf-8 -*- */
/*
 * @file        qpragma/shor/continued_fraction.h
 * @authors     Arnaud GAZDA <arnaud.gazda@atos.net>
 * @copyright   2023 Bull S.A.S. - All rights reserved.
 *              This is not Free or Open Source software.
 *              Please contact BULL SAS for details about its license.
 *              Bull - Rue Jean Jaurès - B.P. 68 - 78340 Les Clayes-sous-Bois
 * @brief
 *
 */

#ifndef QPRAGMA_SHOR_CONTINUED_FRACTION_H
#define QPRAGMA_SHOR_CONTINUED_FRACTION_H

#include <list>
#include "qpragma/shor/fraction.h"

namespace qpragma::shor {
    /**
     * Continued fraction algorithm
     * This function returns the complete decomposition, as any rational number has a finite
     * decomposition
     */
    std::list<int64_t> continued_fraction(fraction);


    /**
     * Find candidate
     * Given a fraction p/q, find a candidate
     * r such as the following requirements are satisfied:
     *  - c/r is a convergent of p/q (c and r are coprime)
     *  - abs(p/q - c/r) <= 1/2q
     *  - r is even
     *  - x^r % N == 1
     *
     * If no such r is find, 0 is returned
     */
    uint64_t find_candidate(const fraction & /* fraction */, uint64_t /* x_value */, uint64_t /* N_value */);


    /**
     * Computes pow(x, y) % z
     * The C++ implementation manages double, which may return inacurrate results.
     * Moreover, the modulus avoid overflow
     */
    uint64_t pow_mod(uint64_t /* base */, uint64_t /* exponent */, uint64_t /* modulus */);
}

#endif  /* QPRAGMA_SHOR_CONTINUED_FRACTION_H */
