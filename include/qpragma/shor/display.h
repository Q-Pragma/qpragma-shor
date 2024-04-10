/* -*- coding: utf-8 -*- */
/*
 * @file        qpragma/shor/display.h
 * @authors     Arnaud GAZDA <arnaud.gazda@atos.net>
 * @copyright   2023 Bull S.A.S. - All rights reserved.
 *              This is not Free or Open Source software.
 *              Please contact BULL SAS for details about its license.
 *              Bull - Rue Jean Jaurès - B.P. 68 - 78340 Les Clayes-sous-Bois
 * @brief
 *
 */

#ifndef QPRAGMA_SHOR_DISPLAY_H
#define QPRAGMA_SHOR_DISPLAY_H

#include "qpragma/shor/fraction.h"
#include <boost/math/tools/simple_continued_fraction.hpp>

namespace qpragma::shor {
    /**
     * Display in a pretty way a continued fraction
     * representation
     */
    void pretty_display(const boost::math::tools::simple_continued_fraction<fraction> & /* continued_fraction */);


    /**
     * Internal function used by pretty_display
     */
    void pretty_display_internal(const std::vector<int64_t> & /* numbers */, uint64_t /* indentation */);
}

#endif  /* QPRAGMA_SHOR_DISPLAY_H */
