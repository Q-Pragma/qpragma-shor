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

#include <list>
#include <ostream>
#include <cstdint>
#include <boost/timer/progress_display.hpp>


namespace qpragma::shor {
    /**
     * Display in a pretty way a continued fraction
     * representation
     */
    void pretty_display(const std::list<int64_t> & /* continued_fraction */);


    /**
     * Progress bar
     * This progress bar inherit from boost::timer::progress_bar
     */
    class progress_display: public boost::timer::progress_display {
    public:
        // Cnstructor (non-copyable)
        progress_display(uint64_t /* progress_size */);
        progress_display(const progress_display &) = delete;
        progress_display & operator=(const progress_display &) = delete;

        // Destructor
        ~progress_display();
    };
}


/**
 * Display a continued fraction representation
 * This operator displays a list
 */
std::ostream & operator<<(std::ostream &, const std::list<int64_t> &);

#endif  /* QPRAGMA_SHOR_DISPLAY_H */
