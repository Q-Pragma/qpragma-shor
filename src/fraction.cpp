#include "qpragma/shor/fraction.h"

#include <numeric>
#include <stdexcept>
#include <algorithm>


/**
 * Internal functions
 */

inline std::strong_ordering invert_comparison(std::strong_ordering value) {
    // Unfortunatly, the switch statement does not work here :(
    //   less -> greater
    //   greater -> less
    //   _ -> _
    if (value == std::strong_ordering::less) {
        return std::strong_ordering::greater;
    }

    if (value == std::strong_ordering::greater) {
        return std::strong_ordering::less;
    }

    return value;
}


inline qpragma::shor::sign invert_sign(qpragma::shor::sign my_sign) {
    switch (my_sign) {
    case qpragma::shor::sign::pos:
        return qpragma::shor::sign::neg;
    case qpragma::shor::sign::neg:
        return qpragma::shor::sign::pos;
    }

    throw std::runtime_error("Something weird occured");
}


/**
 * Fraction class implementation
 */

// Constructors
qpragma::shor::fraction::fraction(uint64_t numerator, sign fsign): _sign(fsign), _numerator(numerator) {}


qpragma::shor::fraction::fraction(int number): _sign((number < 0) ? sign::neg : sign::pos), _numerator(std::abs(number)) {}


qpragma::shor::fraction::fraction(int64_t number): _sign((number < 0) ? sign::neg : sign::pos), _numerator(std::abs(number)) {}


qpragma::shor::fraction::fraction(uint64_t numerator, uint64_t denominator, sign fsign)
    : _sign(fsign), _numerator(numerator), _denominator(denominator) {
    // Ensure the fraction is finite
    if (_denominator == 0UL) {
        throw std::out_of_range("Could not create a a fraction with a denominator equal to 0");
    }

    _simplify();
}


// Simplify fraction
void qpragma::shor::fraction::_simplify() {
    uint64_t factor = std::gcd(_numerator, _denominator);

    _numerator /= factor;
    _denominator /= factor;

    // Ensure "-0" is not encodable
    if (_numerator == 0UL) {
        _sign = sign::pos;
    }
}


// Getters
qpragma::shor::sign qpragma::shor::fraction::get_sign() const {
    return _sign;
}


uint64_t qpragma::shor::fraction::numerator() const {
    return _numerator;
}


uint64_t qpragma::shor::fraction::denominator() const {
    return _denominator;
}


// Cast method
qpragma::shor::fraction & qpragma::shor::fraction::operator=(uint64_t value) {
    _sign = sign::pos;
    _numerator = value;
    _denominator = 1UL;

    return *this;
}


qpragma::shor::fraction::operator uint64_t() const {
    return _numerator / _denominator;
}


qpragma::shor::fraction:: operator int64_t() const {
    // Get absolute value and check if castable in int64_t
    uint64_t abs_result = _numerator / _denominator;

    if (abs_result > std::numeric_limits<int64_t>::max()) {
        throw std::domain_error("Could not cast fraction into a int64_t");
    }

    // Return result
    return _sign == sign::pos ?
        static_cast<int64_t>(abs_result) : -1L * static_cast<int64_t>(abs_result);
}


// Operators
qpragma::shor::fraction & qpragma::shor::fraction::operator+=(const fraction & other) {
    (*this) = (*this) + other;
    return (*this);
}


qpragma::shor::fraction & qpragma::shor::fraction::operator-=(const fraction & other) {
    (*this) = (*this) - other;
    return (*this);
}


qpragma::shor::fraction & qpragma::shor::fraction::operator*=(const fraction & other) {
    (*this) = (*this) * other;
    return (*this);
}


std::strong_ordering qpragma::shor::fraction::operator<=>(const fraction & other) const {
    // Check different signs
    if (_sign == sign::neg and other.get_sign() == sign::pos) {
        return std::strong_ordering::less;
    }

    if (_sign == sign::pos and other.get_sign() == sign::neg) {
        return::std::strong_ordering::greater;
    }

    // Same sign
    if (_sign == sign::pos) {
        return (_numerator * other.denominator()) <=> (other.numerator() * _denominator);
    }

    return invert_comparison((_numerator * other.denominator()) <=> (other.numerator() * _denominator));
}


bool qpragma::shor::fraction::operator==(int other) const {
    return (*this) == fraction(other);
}


bool qpragma::shor::fraction::operator==(uint64_t other) const {
    return (*this) == fraction(other);
}


bool qpragma::shor::fraction::operator==(const fraction & other) const {
    return ((*this) <=> other) == std::strong_ordering::equal;
}


qpragma::shor::fraction qpragma::shor::fraction::operator-() const {
    return fraction(_numerator, _denominator, invert_sign(_sign));
}


/**
 * Useful functions
 */

// Is finite
bool std::isfinite(const qpragma::shor::fraction & frac) {
    return frac.denominator() != 0UL;  // Should be always true
}


// Floor
qpragma::shor::fraction std::floor(const qpragma::shor::fraction & frac) {
    return qpragma::shor::fraction(static_cast<uint64_t>(frac), frac.get_sign());
}

// Absolute value
qpragma::shor::fraction std::abs(const qpragma::shor::fraction & frac) {
    return qpragma::shor::fraction(frac.numerator(), frac.denominator(), qpragma::shor::sign::pos);
}


/**
 * Operators
 */

// Add
qpragma::shor::fraction operator+(const qpragma::shor::fraction & first, const qpragma::shor::fraction & second) {
    // Implementation of "+" operators works only if fractions have the same sign
    // Otherwise, this correspond to a substraction
    if (first.get_sign() != second.get_sign()) {
        auto [min, max] = std::minmax(first, second);
        return max - std::abs(min);
    }

    // Perform addition
    return qpragma::shor::fraction(
        first.numerator() * second.denominator() + second.numerator() * first.denominator(),
        first.denominator() * second.denominator(),
        first.get_sign()
    );
}


// Substract
qpragma::shor::fraction operator-(const qpragma::shor::fraction & first, const qpragma::shor::fraction & second) {
    // Implementation of "-" operators works only if fractions have the same sign
    // If fractions have different signs, the result is "±(abs(first) + abs(second))"
    if (first.get_sign() != second.get_sign()) {
        return first.get_sign() == qpragma::shor::sign::pos ?
            (first + std::abs(second)) : -(std::abs(first) + second);
    }

    // Get sign
    auto result_sign =
        (first.numerator() * second.denominator()) < (second.numerator() * first.denominator()) ?
        invert_sign(first.get_sign()) : first.get_sign();

    // Return result
    auto [min, max] = std::minmax(first.numerator() * second.denominator(), second.numerator() * first.denominator());

    return qpragma::shor::fraction(
        max - min,
        first.denominator() * second.denominator(),
        result_sign
    );
}


// Inverse
qpragma::shor::fraction operator/(int first, const qpragma::shor::fraction & second) {
    return qpragma::shor::fraction(first) / second;
}


qpragma::shor::fraction operator/(uint64_t first, const qpragma::shor::fraction & second) {
    return qpragma::shor::fraction(first) / second;
}


qpragma::shor::fraction operator/(const qpragma::shor::fraction & first, const qpragma::shor::fraction & second) {
    return qpragma::shor::fraction(
        first.numerator() * second.denominator(),
        first.denominator() * second.numerator(),
        (first.get_sign() == second.get_sign()) ? qpragma::shor::sign::pos : qpragma::shor::sign::neg
    );
}


// Multiply
qpragma::shor::fraction operator*(int first, const qpragma::shor::fraction & second) {
    return qpragma::shor::fraction(first) * second;
}


qpragma::shor::fraction operator*(uint64_t first, const qpragma::shor::fraction & second) {
    return qpragma::shor::fraction(first) * second;
}


qpragma::shor::fraction operator*(const qpragma::shor::fraction & first, const qpragma::shor::fraction & second) {
    return qpragma::shor::fraction(
        first.numerator() * second.numerator(),
        first.denominator() * second.denominator(),
        (first.get_sign() == second.get_sign()) ? qpragma::shor::sign::pos : qpragma::shor::sign::neg
    );
}


// Display
std::ostream & operator<<(std::ostream & stream, const qpragma::shor::fraction & frac) {
    // Display sign
    if (frac.get_sign() == qpragma::shor::sign::neg) {
        stream << "-";
    }

    // Display and return stream
    stream << frac.numerator() << "/" << frac.denominator();
    return stream;
}
