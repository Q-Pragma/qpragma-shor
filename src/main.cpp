#include <iostream>
#include "qpragma/shor.h"

using qpragma::shor::fraction;
using qpragma::shor::continued_fraction;
using qpragma::shor::pretty_display;


int main() {
    // Example
    {
        std::cout << "================ EXAMPLE ===============" << std::endl;
        fraction frac(15625UL, 6842UL);
        auto continued_frac = continued_fraction(frac);

        std::cout << frac << " = " << continued_frac << std::endl << std::endl;
        pretty_display(continued_frac);
        std::cout << std::endl;
    }

    // With user inputs
    {
        std::cout << "================ INPUTS ===============" << std::endl;

        // Get user inputs
        uint64_t num, denom;
        std::cout << "Numerator: ";
        std::cin >> num;

        std::cout << "Denominator: ";
        std::cin >> denom;

        // Compute
        fraction frac(num, denom);
        auto continued_frac = continued_fraction(frac);

        std::cout << frac << " = " << continued_frac << std::endl << std::endl;
        pretty_display(continued_frac);
    }
}
