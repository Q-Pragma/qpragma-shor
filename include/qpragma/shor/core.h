/* -*- coding: utf-8 -*- */
/*
 * @file        qpragma/shor/core.h
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
 *
 * @brief
 * Main function of shor algorithm
 */

#ifndef QPRAGMA_SHOR_CORE_H
#define QPRAGMA_SHOR_CORE_H

#include <cmath>
#include <random>
#include <cstdint>

#include "qpragma.h"
#include "qpragma/shor/display.h"
#include "qpragma/shor/fraction.h"
#include "qpragma/shor/continued_fraction.h"


namespace qpragma::shor {
    /**
     * Given a uint64_t, find a divisor.
     *
     * This function is templated by the size of then quantum register used to find
     * a solution to this problem.
     */
    template <uint64_t SIZE>
    uint64_t find_divisor(uint64_t /* to_divide */, bool /* quantum_only */ = false);
}

#include "qpragma/shor/core.ipp"

#endif  /* QPRAGMA_SHOR_CORE_H */
