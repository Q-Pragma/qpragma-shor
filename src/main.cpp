#include <iostream>
#include "qpragma/shor.h"

#define GREEN   "\x1B[32m"
#define YELLOW  "\x1B[33m"
#define CYAN    "\x1B[36m"
#define NOCOLOR "\x1B[0m"

using qpragma::shor::fraction;
using qpragma::shor::continued_fraction;
using qpragma::shor::pretty_display;


int main() {
    std::cout << "================ SHOR ALGORITHM ===============" << std::endl;
    constexpr uint64_t size = 4UL;
    uint64_t to_divide = 0UL;

    do {
        std::cout << CYAN "Please insert a number to divide (needs to be greater than 3 and lower than " << ((1UL << size) - 1UL) << ")" NOCOLOR
                  << std::endl << "Number: ";
        std::cin >> to_divide;
    } while (to_divide > (1UL << size) or to_divide < 3UL);

    auto result = qpragma::shor::find_divisor<size>(to_divide);

    if (result) {
        std::cout << GREEN "Find a divisor: " << result << NOCOLOR << std::endl;
        std::cout << " > " << to_divide << " = " << result << " * " << (to_divide / result) << std::endl;
    }

    else {
        std::cout << YELLOW "ERROR - No divisor found" NOCOLOR << std::endl;
    }

    // // Example
    // {
    //     std::cout << "================ EXAMPLE ===============" << std::endl;
    //     fraction frac(15625UL, 6842UL);
    //     auto continued_frac = continued_fraction(frac);

    //     std::cout << frac << " = " << continued_frac << std::endl << std::endl;
    //     pretty_display(continued_frac);
    //     std::cout << std::endl;
    // }

    // // With user inputs
    // {
    //     std::cout << "================ INPUTS ===============" << std::endl;

    //     // Get user inputs
    //     uint64_t num, denom;
    //     std::cout << "Numerator: ";
    //     std::cin >> num;

    //     std::cout << "Denominator: ";
    //     std::cin >> denom;

    //     // Compute
    //     fraction frac(num, denom);
    //     auto continued_frac = continued_fraction(frac);

    //     std::cout << frac << " = " << continued_frac << std::endl << std::endl;
    //     pretty_display(continued_frac);
    // }
}
