// Include C++ stdlib (and boost)
#include <optional>
#include <iostream>
#include <boost/program_options/parsers.hpp>
#include <boost/program_options/variables_map.hpp>
#include <boost/program_options/options_description.hpp>

// Include Q-Pragma
#include "qpragma/shor.h"

#define GREEN   "\x1B[32m"
#define YELLOW  "\x1B[33m"
#define CYAN    "\x1B[36m"
#define NOCOLOR "\x1B[0m"

// Use Boost
using boost::program_options::options_description;
using boost::program_options::parse_command_line;
using boost::program_options::variables_map;
using boost::program_options::bool_switch;

// Use Q-Pragma
using qpragma::shor::fraction;
using qpragma::shor::continued_fraction;
using qpragma::shor::pretty_display;


// Useful classes
struct Configuration {
    bool quantum_only = false;
};


/**
 * Parse command line arguments
 * This function is based on boost/program_options
 */
std::optional<Configuration> parse_arguments(int argc, char ** argv) {
    // List all options
    options_description options("Shor algorithm implemented using Q-Pragma");
    options.add_options()
        ("help,h", bool_switch()->default_value(false), "Display help")
        ("quantum-only,q", bool_switch()->default_value(false), "Ignore cases where the algorithm finds a solution classically")
        ;

    // Parse arguments
    variables_map parsed_arguments;
    store(parse_command_line(argc, argv, options), parsed_arguments);

    // Create configuration
    if (parsed_arguments["help"].as<bool>()) {
        std::cout << options;
        return std::nullopt;
    }

    return Configuration {
        .quantum_only = parsed_arguments["quantum-only"].as<bool>()
    };
}


/**
 * Main function.
 * Execute Shor algorithm
 */
int main(int argc, char ** argv) {
    // Parse arguments
    auto configuration = parse_arguments(argc, argv);

    if (not configuration) {
        // No arguments
        return 1;
    }

    // Execute shor
    std::cout << "================ SHOR ALGORITHM ===============" << std::endl;
    constexpr uint64_t size = 4UL;
    uint64_t to_divide = 0UL;

    do {
        std::cout << CYAN "Please insert a number to divide (needs to be greater than 3 and lower than " << ((1UL << size) - 1UL) << ")" NOCOLOR
                  << std::endl << "Number: ";
        std::cin >> to_divide;
    } while (to_divide > (1UL << size) or to_divide < 3UL);

    auto result = qpragma::shor::find_divisor<size>(to_divide, configuration->quantum_only);

    if (result) {
        std::cout << GREEN "Find a divisor: " << result << NOCOLOR << std::endl;
        std::cout << " > " << to_divide << " = " << result << " * " << (to_divide / result) << std::endl;
    }

    else {
        std::cout << YELLOW "ERROR - No divisor found" NOCOLOR << std::endl;
    }
}
