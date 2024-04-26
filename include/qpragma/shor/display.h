/* -*- coding: utf-8 -*- */
/*
 * @file        qpragma/shor/display.h
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
