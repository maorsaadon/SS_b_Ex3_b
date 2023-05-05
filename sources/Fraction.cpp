#include "Fraction.hpp"
#include <cmath>

using namespace std;

namespace ariel
{

    /**
    Constructor for initializing a Fraction object with default values.
    Sets the numerator to 0 and denominator to 1.
    */
    Fraction::Fraction() : numerator(0), denominator(1) {}

    /**
    Constructs a Fraction object with the given numerator and denominator.
    @param numerator The numerator of the fraction
    @param denominator The denominator of the fraction
    @throws std::invalid_argument If the denominator is 0
    @post The created Fraction object will be in reduced form (i.e., with the greatest common divisor of the numerator and denominator factored out).
    If the fraction is negative, then it will be represented with a negative numerator and positive denominator.
    */
    Fraction::Fraction(int numerator, int denominator) : numerator(numerator), denominator(denominator)
    {
        if (denominator == 0)
        {
            throw invalid_argument("Denominator cannot be zero.");
        }
        if (denominator < 0)
        {
            numerator *= -1;
            denominator *= -1;
        }
        reduce();
    }

    /**
     * Constructs a Fraction object from a floating-point number.
     * @param num the floating-point number to convert to a fraction
     * The numerator is set to num multiplied by 1000 and cast to an integer, while the denominator is set to 1000.
     * The resulting fraction is then reduced to its simplest form.
     */
    Fraction::Fraction(float num) : numerator(static_cast<int>(num * 1000)), denominator(1000)
    {
        reduce();
    }

    Fraction::Fraction(const Fraction &other) : numerator(other.numerator), denominator(other.denominator) {}

    Fraction::Fraction(Fraction &&other) noexcept : numerator(other.numerator), denominator(other.denominator) {}

    Fraction &Fraction::operator=(const Fraction &other)
    {
        if (this == &other)
            return *this;

        this->numerator = other.numerator;
        this->denominator = other.denominator;
        return *this;
    }

    Fraction &Fraction::operator=(Fraction &&other) noexcept
    {
        if (this == &other)
            return *this;

        this->numerator = other.numerator;
        this->denominator = other.denominator;
        return *this;
    }


    // Helper function to compute the greatest common divisor
    int Fraction::gcd(int a, int b) const
    {
        return (b == 0) ? a : gcd(b, a % b);
    }

    // Helper function to reduce the fraction
    void Fraction::reduce()
    {
        if (denominator < 0)
        {
            numerator = -numerator;
            denominator = -denominator;
        }
        int gcd = abs(this->gcd(numerator, denominator));
        numerator /= gcd;
        denominator /= gcd;
    }

    // Overloaded operator for addition
    const Fraction Fraction::operator+(const Fraction &other) const
    {
        int lcm = abs(denominator * other.denominator / gcd(denominator, other.denominator));
        int num1 = numerator * (lcm / denominator);
        int num2 = other.numerator * (lcm / other.denominator);
        return Fraction(overflow_addition(num1, num2), lcm);
    }

    const Fraction Fraction::operator+(const float &other) const
    {
        return *this + Fraction(other);
    }

    // Friend function for operator+ with float as the first operand
    const Fraction operator+(const float &num1, const Fraction &num2)
    {
        return Fraction(num1) + num2;
    }

    // Overloaded operator for subtraction
    const Fraction Fraction::operator-(const Fraction &other) const
    {
        int lcm = abs(denominator * other.denominator / gcd(denominator, other.denominator));
        int num1 = numerator * (lcm / denominator);
        int num2 = other.numerator * (lcm / other.denominator);
        return Fraction(overflow_subtraction(num1, num2), lcm);
    }

    const Fraction Fraction::operator-(const float &other) const
    {
        return *this - Fraction(other);
    }

    // Friend function for operator- with float as the first operand
    const Fraction operator-(const float &num1, const Fraction &num2)
    {
        return Fraction(num1) - num2;
    }

    // Overloaded operator for multiplication
    const Fraction Fraction::operator*(const Fraction &other) const
    {
        return Fraction(overflow_multiplication(numerator, other.numerator), overflow_multiplication(denominator, other.denominator));
    }

    const Fraction Fraction::operator*(const float &other) const
    {
        return *this * Fraction(other);
    }

    // Friend function for operator* with float as the first operand
    const Fraction operator*(const float &num1, const Fraction &num2)
    {
        return Fraction(num1) * num2;
    }

    // Overloaded operator for division
    const Fraction Fraction::operator/(const Fraction &other) const
    {
        if (other.numerator == 0)
        {
            throw runtime_error("Cannot divide by zero.");
        }
        return Fraction(overflow_multiplication(numerator, other.denominator), overflow_multiplication(denominator, other.numerator));
    }

    const Fraction Fraction::operator/(const float &other) const
    {
        return *this / Fraction(other);
    }

    // Friend function for operator+ with float as the first operand
    const Fraction operator/(const float &num1, const Fraction &num2)
    {
        return Fraction(num1) / num2;
    }

    // Overloaded operator for equality
    bool Fraction::operator==(const Fraction &other) const
    {
          return (numerator == other.numerator && denominator == other.denominator);
    }

    bool Fraction::operator==(const float &other) const
    {
        return *this == Fraction(other);
    }

    bool operator==(const float &num1, const Fraction &num2)
    {
        return Fraction(num1) == num2;
    }

    // Overloaded operator for inequality
    bool Fraction::operator!=(const Fraction &other) const
    {
        return !(*this == other);
    }

    bool Fraction::operator!=(const float &other) const
    {
        return *this != Fraction(other);
    }

    bool operator!=(const float &num1, const Fraction &num2)
    {
        return Fraction(num1) != num2;
    }

    // Overloaded operator for greater than
    bool Fraction::operator>(const Fraction &other) const
    {
        int lcm = abs(denominator * other.denominator / gcd(denominator, other.denominator));
        int num1 = numerator * (lcm / denominator);
        int num2 = other.numerator * (lcm / other.denominator);
        return num1 > num2;
    }

    bool Fraction::operator>(const float &other) const
    {
        return *this > Fraction(other);
    }

    bool operator>(const float &num1, const Fraction &num2)
    {
        return Fraction(num1) > num2;
    }

    // Overloaded operator for less than
    bool Fraction::operator<(const Fraction &other) const
    {
        return !(*this > other || *this == other);
    }

    bool Fraction::operator<(const float &other) const
    {
        return *this < Fraction(other);
    }

    bool operator<(const float &num1, const Fraction &num2)
    {
        return Fraction(num1) < num2;
    }

    // Overloaded comparison operator >=
    bool Fraction::operator>=(const Fraction &other) const
    {
        return (numerator * other.denominator) >= (denominator * other.numerator);
    }

    bool Fraction::operator>=(const float &other) const
    {
        return *this >= Fraction(other);
    }

    bool operator>=(const float &num1, const Fraction &num2)
    {
        return Fraction(num1) >= num2;
    }

    // Overloaded comparison operator <=
    bool Fraction::operator<=(const Fraction &other) const
    {
        return (numerator * other.denominator) <= (denominator * other.numerator);
    }

    bool Fraction::operator<=(const float &other) const
    {
        return *this <= Fraction(other);
    }

    bool operator<=(const float &num1, const Fraction &num2)
    {
        return Fraction(num1) <= num2;
    }

    // Overloaded increment operator ++
    Fraction Fraction::operator++()
    {
        numerator += denominator;
        reduce();
        return *this;
    }

    // Overloaded increment operator ++ (postfix)
    const Fraction Fraction::operator++(int)
    {
        Fraction temp = *this;
        ++(*this);
        return temp;
    }

    // Overloaded decrement operator --
    Fraction Fraction::operator--()
    {
        numerator -= denominator;
        reduce();
        return *this;
    }

    // Overloaded decrement operator -- (postfix)
    const Fraction Fraction::operator--(int)
    {
        Fraction temp = *this;
        --(*this);
        return temp;
    }

    // Overloaded output operator <<
    ostream &operator<<(ostream &output, const Fraction &fraction)
    {
        output << fraction.numerator << "/" << fraction.denominator;
        return output;
    }

    // Overloaded input operator >>
    istream &operator>>(istream &input, Fraction &fraction)
    {
        input >> fraction.numerator >> fraction.denominator;

        if (input.fail())
        {
            throw runtime_error("Input error");
        }

        if (fraction.denominator == 0)
        {
            throw runtime_error("Denominator cannot be zero");
        }
        fraction.reduce();
        return input;
    }

    // Getter for numerator
    int Fraction::getNumerator() const
    {
        return numerator;
    }

    // Getter for denominator
    int Fraction::getDenominator() const
    {
        return denominator;
    }

    // Setter for numerator
    void Fraction::setNumerator(int numerator)
    {
        this->numerator = numerator;
    }

    // Setter for denominator
    void Fraction::setDenominator(int denominator)
    {
        if (denominator == 0)
        {
            throw invalid_argument("Denominator cannot be zero");
        }
        this->denominator = denominator;
        reduce();
    }

};

