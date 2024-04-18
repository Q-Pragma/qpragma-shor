/**
 * Q-Pragma shor implementementation
 *
 * This file provide an implementation of the Shor algorithm
 */

template <uint64_t SIZE>
uint64_t qpragma::shor::find_divisor(uint64_t to_divide, bool quantum_only) {
    // Shor is probabilistic - define maximum attempt
    constexpr uint64_t max_attempt = 20UL;
    qpragma::shor::progress_display progress_bar(max_attempt);

    // Define random generators
    std::mt19937 rd(12345);
    std::uniform_int_distribution<uint64_t> distrib(2UL, to_divide - 1UL);

    for (uint64_t attempt_idx = 0UL; attempt_idx < max_attempt; ++attempt_idx) {
        // Update progress bar
        ++progress_bar;

        // Step 1: find a random number
        uint64_t random_number = distrib(rd);

        // If random_number is not coprime with to_divide, gcd is a solution
        if(auto gcd = std::gcd(random_number, to_divide); gcd != 1UL) {
            if (quantum_only) continue;

            return gcd;
        }

        // Step 2: Perform quantum part
        // Execute the quantum phase estimation
        uint64_t measurement = 0UL;

        #pragma quantum scope with(random_number, to_divide, measurement)
        {
            qpragma::qbool control;
            qpragma::quint_t<SIZE> reg = 1UL;
            uint64_t base = random_number;

            for (uint64_t idx = 0UL; idx < 2UL * SIZE; ++ idx) {
                // Update base
                base = (base * base) % (1UL << SIZE); 

                // Apply gates
                qpragma::H(control);

                #pragma quantum ctrl(control)
                qpragma::arith::mult_const_mod_in_place<SIZE>(base, to_divide)(reg);

                qpragma::PH(M_PI * static_cast<double>(measurement) / static_cast<double>(1UL << (idx + 1UL)))(control);
                qpragma::H(control);

                // Update measurement
                if (qpragma::measure_and_reset(control)) {
                    measurement += 1 << idx;
                }
            }

            qpragma::reset(reg);
        }

        // Step 3: classical part
        qpragma::shor::fraction frac(measurement, 1UL << (2UL * SIZE));
        auto candidate = qpragma::shor::find_candidate(frac, random_number, to_divide);

        if (candidate != 0UL) {
            auto pow_value = pow_mod(random_number, candidate / 2UL, to_divide);

            if (auto value = std::gcd((pow_value + 1UL) % to_divide, to_divide); value != 1 and value != to_divide) {
                progress_bar += max_attempt - attempt_idx - 1UL;
                return value;
            }

            if (auto value = std::gcd((pow_value - 1UL) % to_divide, to_divide); value != 1 and value != to_divide) {
                progress_bar += max_attempt - attempt_idx - 1UL;
                return value;
            }
        }
    }

    // No divisor found
    return 0UL;
}
