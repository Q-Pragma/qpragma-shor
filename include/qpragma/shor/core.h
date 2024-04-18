/* -*- coding: utf-8 -*- */
/*
 * @file        qpragma/shor/core.h
 * @authors     Arnaud GAZDA <arnaud.gazda@atos.net>
 * @copyright   2023 Bull S.A.S. - All rights reserved.
 *              This is not Free or Open Source software.
 *              Please contact BULL SAS for details about its license.
 *              Bull - Rue Jean Jaurès - B.P. 68 - 78340 Les Clayes-sous-Bois
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
