/**
 * Q-Pragma Shor's algorithm implementation
 *
 * This file provide an implementation of Shor's algorithm
 */

// Function to compute b^(2^e) % m using exponentiation by squaring
uint64_t mod_exp(uint64_t base, uint64_t exponent, const uint64_t& modulus) {
    uint64_t result = base % modulus;
    
    for (uint64_t i = 0; i < exponent; ++i) 
        result = (result * result) % modulus;

    return result;
}

template <uint64_t SIZE>
uint64_t qpragma::shor::find_divisor(const uint64_t& to_divide, const bool& quantum_only) {
    // Handle case where to_divide is even
    if(auto gcd = std::gcd(2UL, to_divide); gcd != 1UL) {
        return 2UL;
    }

    // Shor is probabilistic - define maximum attempt
    constexpr uint64_t max_attempt = 20UL;
    qpragma::shor::progress_display progress_bar(max_attempt);

    // Define random generators
    std::mt19937 rd(1234);
    std::uniform_int_distribution<uint64_t> distrib(2UL, to_divide - 1UL);

    for (uint64_t attempt_idx = 0UL; attempt_idx < max_attempt; ++attempt_idx) {
        // Update progress bar
        ++progress_bar;

        // Step 1: find a random number
        uint64_t random_number = distrib(rd);

        // If random_number is not coprime with to_divide, gcd is a solution
        if(auto gcd = std::gcd(random_number, to_divide); gcd != 1UL) {
            if (quantum_only) 
                continue;
            return gcd;
        }

        // Step 2: Perform quantum part
        // Execute the quantum phase estimation
        uint64_t measurement = 0UL;

        #pragma quantum scope with(random_number, to_divide, measurement)
        {
            qpragma::qbool control;
            qpragma::quint_t<SIZE> reg = 1UL;

            for (uint64_t idx = 0UL; idx < 2UL * SIZE; ++ idx) {
                uint64_t base = mod_exp(random_number, 2UL * SIZE - 1UL - idx, to_divide);

                // Apply gates
                qpragma::H(control);

                #pragma quantum ctrl(control)
                qpragma::arith::mult_const_mod_in_place<SIZE>(base, to_divide)(reg);

                double angle = - 2 * M_PI * static_cast<double>(measurement) / static_cast<double>(1UL << idx);
                (qpragma::PH(angle))(control);
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
        auto candidate = qpragma::shor::find_candidate(frac, random_number, to_divide);  // If no candidate, 0UL is returned

        if (candidate != 0UL) {
            auto pow_value = pow_mod(random_number, candidate / 2UL, to_divide);

            // The following equality is true "(pow_value + 1) * (pow_value - 1) % to_divide == 0", but:
            //
            //   - If a non-trival divisor can be computed from "pow_value + 1", a non-trivial divisor can be also computed
            //     from "pow_value - 1".
            //   - If only a trivial divisor can be computed from "pow_value + 1", only a trivial divisor can be computed
            //     from "pow_value - 1".
            //
            // Then, only "pow_value + 1" will be considered to find a divisor.
            if (auto value = std::gcd(pow_value + 1UL, to_divide); value != 1 and value != to_divide) {
                progress_bar += max_attempt - attempt_idx - 1UL;
                return value;
            }
        }
    }

    // No divisor found
    return 0UL;
}
