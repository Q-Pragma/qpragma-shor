/* -*- coding: utf-8 -*- */
/*
 * @file        qpragma/shor/continued_fraction.h
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
