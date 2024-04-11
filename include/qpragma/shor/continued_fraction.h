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
}

#endif  /* QPRAGMA_SHOR_CONTINUED_FRACTION_H */
