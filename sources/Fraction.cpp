#include "Fraction.hpp"
#include <cmath>

using namespace std;

namespace ariel {

    // Default constructor
    Fraction::Fraction() : numerator(0), denominator(1) {}

    // Constructor with only numerator
    Fraction::Fraction(int numerator) : numerator(numerator), denominator(1) {}

    // Constructor with numerator and denominator
    Fraction::Fraction(int numerator, int denominator) : numerator(numerator), denominator(denominator) {
        if (denominator == 0) {
            throw invalid_argument("Denominator cannot be zero.");
        }
        reduce();
    }

    // Constructor with a double value
    Fraction::Fraction(float num) : numerator(static_cast<int>(num * 10000)), denominator(10000) {
        reduce();
    }

    // Helper function to compute the greatest common divisor
    int Fraction::gcd(int a, int b) const {
        return (b == 0) ? a : gcd(b, a % b);
    }

    // Helper function to reduce the fraction
    void Fraction::reduce() {
        if (denominator < 0) {
            numerator = -numerator;
            denominator = -denominator;
        }
        int gcd = abs(this->gcd(numerator, denominator));
        numerator /= gcd;
        denominator /= gcd;
    }

    // Overloaded operator for addition
    Fraction Fraction::operator+(const Fraction& other) const {
        int lcm = abs(denominator * other.denominator / gcd(denominator, other.denominator));
        int num1 = numerator * (lcm / denominator);
        int num2 = other.numerator * (lcm / other.denominator);
        return Fraction(num1 + num2, lcm);
    }

    // Friend function for operator+ with float as the first operand
    Fraction operator+(float num1, const Fraction& num2) {
        return Fraction(num1) + num2;
    }

    Fraction operator+(const Fraction& num1, float num2) {
        return num1 + Fraction(num2);
    }

    // Overloaded operator for subtraction
    Fraction Fraction::operator-(const Fraction& other) const {
        int lcm = abs(denominator * other.denominator / gcd(denominator, other.denominator));
        int num1 = numerator * (lcm / denominator);
        int num2 = other.numerator * (lcm / other.denominator);
        return Fraction(num1 - num2, lcm);
    }

    // Friend function for operator- with float as the first operand
    Fraction operator-(float num1, const Fraction& num2) {
        return Fraction(num1) - num2;
    }

    Fraction operator-(const Fraction& num1, float num2) {
        return num1 - Fraction(num2);
    }

    // Overloaded operator for multiplication
    Fraction Fraction::operator*(const Fraction& other) const {
        return Fraction(numerator * other.numerator, denominator * other.denominator);
    }

    // Friend function for operator* with float as the first operand
    Fraction operator*(float num1, const Fraction& num2) {
        return Fraction(num1) * num2;
    }

    // Friend function for operator* with float as the first operand
    Fraction operator*(const Fraction& num1, float num2) {
        return num1 * Fraction(num2);
    }

    // Overloaded operator for division
    Fraction Fraction::operator/(const Fraction& other) const {
        if (other.numerator == 0) {
            throw invalid_argument("Cannot divide by zero.");
        }
        return Fraction(numerator * other.denominator, denominator * other.numerator);
    }

    // Friend function for operator+ with float as the first operand
    Fraction operator/(float num1, const Fraction& num2) {
        return Fraction(num1) / num2;
    }

    Fraction operator/(const Fraction& num1, float num2) {
        return num1 / Fraction(num2);
    }

    // Overloaded operator for equality
    bool Fraction::operator==(const Fraction& other) const {
        return (numerator == other.numerator && denominator == other.denominator);
    }

    bool operator==(float num1, const Fraction& num2) {
        return Fraction(num1) == num2;
    }

    bool operator==(const Fraction& num1, float num2) {
        return num1 == Fraction(num2);
    }

    // Overloaded operator for inequality
    bool Fraction::operator!=(const Fraction& other) const {
        return !(*this == other);
    }

    bool operator!=(float num1, const Fraction& num2) {
        return Fraction(num1) != num2;
    }

    bool operator!=(const Fraction& num1, float num2) {
        return num1 != Fraction(num2);
    }

    // Overloaded operator for greater than
    bool Fraction::operator>(const Fraction& other) const {
        int lcm = abs(denominator * other.denominator / gcd(denominator, other.denominator));
        int num1 = numerator * (lcm / denominator);
        int num2 = other.numerator * (lcm / other.denominator);
        return num1 > num2;
    }

    bool operator>(float num1, const Fraction& num2) {
        return Fraction(num1) > num2;
    }

    bool operator>(const Fraction& num1, float num2) {
        return num1 > Fraction(num2);
    }

    // Overloaded operator for less than
    bool Fraction::operator<(const Fraction& other) const {
        return !(*this > other || *this == other);
    }

    bool operator<(float num1, const Fraction& num2) {
        return Fraction(num1) < num2;
    }

    bool operator<(const Fraction& num1, float num2) {
        return num1 < Fraction(num2);
    }

    // Overloaded comparison operator >=
    bool Fraction::operator>=(const Fraction& other) const {
        return (numerator * other.denominator) >= (denominator * other.numerator);
    }

    bool operator>=(float num1, const Fraction& num2) {
        return Fraction(num1) >= num2;
    }

    bool operator>=(const Fraction& num1, float num2) {
        return num1 >= Fraction(num2);
    }

    // Overloaded comparison operator <=
    bool Fraction::operator<=(const Fraction& other) const {
        return (numerator * other.denominator) <= (denominator * other.numerator);
    }

    bool operator<=(float num1, const Fraction& num2) {
        return Fraction(num1) <= num2;
    }

    bool operator<=(const Fraction& num1, float num2) {
        return num1 <= Fraction(num2);
    }

    // Overloaded increment operator ++
    Fraction Fraction::operator++() {
        numerator += denominator;
        reduce();
        return *this;
    }

    // Overloaded increment operator ++ (postfix)
    Fraction Fraction::operator++(int) {
        Fraction temp = *this;
        ++(*this);
        return temp;
    }

    // Overloaded decrement operator --
    Fraction Fraction::operator--() {
        numerator -= denominator;
        reduce();
        return *this;
    }

    // Overloaded decrement operator -- (postfix)
    Fraction Fraction::operator--(int) {
        Fraction temp = *this;
        --(*this);
        return temp;
    }

    // Overloaded output operator <<
    ostream& operator<<(ostream& output, const Fraction& fraction) {
        output << fraction.numerator << "/" << fraction.denominator;
        return output;
    }

    // Overloaded input operator >>
    istream& operator>>(istream& input, Fraction& fraction) {
        char slash;
        input >> fraction.numerator >> slash >> fraction.denominator;
        if (fraction.denominator == 0) {
            throw invalid_argument("Denominator cannot be zero");
        }
        fraction.reduce();
        return input;
    }

    // Conversion operator to float
    Fraction::operator float() const {
        return static_cast<float>(numerator) / static_cast<float>(denominator);
    }

    // Conversion operator to double
    Fraction::operator double() const {
        return static_cast<double>(numerator) / static_cast<double>(denominator);
    }

    // Getter for numerator
    int Fraction::getNumerator() const {
        return numerator;
    }

    // Getter for denominator
    int Fraction::getDenominator() const {
        return denominator;
    }

    // Setter for numerator
    void Fraction::setNumerator(int numerator) {
        this->numerator = numerator;
    }

    // Setter for denominator
    void Fraction::setDenominator(int denominator) {
        if (denominator == 0) {
            throw invalid_argument("Denominator cannot be zero");
        }
        this->denominator = denominator;
        reduce();
    }

};