
#include "Fraction.hpp"
#include <cmath>
#include <numeric>

using namespace std;

namespace ariel
{
    // Constants for maximum and minimum integer values
    static const int max_int = numeric_limits<int>::max();
    static const int min_int = numeric_limits<int>::min();

    // Helper function to check for integer overflow
    static int overflow_check(int num1, int num2, char c)
    {
        switch (c)
        {
        case '+':
            if ((num2 > 0 && num1 > (max_int - num2)) || (num2 < 0 && num1 < (min_int - num2)))
            {
                throw overflow_error("Overflow");
            }
            return (num1 + num2);

        case '-':
            if ((num2 < 0 && num1 > max_int + num2) || (num2 > 0 && num1 < min_int + num2))
            {
                throw overflow_error("Overflow");
            }
            return (num1 - num2);
        case '*':
            if ((num2 > 0 && num1 > max_int / num2) || (num2 < 0 && num1 < max_int / num2))
            {
                throw overflow_error("Overflow");
            }
            return (num1 * num2);
        default:
            return 1;
        }
    }

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

    /**
     * Copy constructor for the Fraction class.
     * @param other The Fraction object to copy.
     */
    Fraction::Fraction(const Fraction &other) : numerator(other.numerator), denominator(other.denominator) {}

    /**
     * Move constructor for the Fraction class.
     * @param other The Fraction object to move.
     */
    Fraction::Fraction(Fraction &&other) noexcept : numerator(other.numerator), denominator(other.denominator) {}

    /**
     * This is the assignment operator, which assigns the values of the given Fraction object to the current object.
     * It returns a reference to the current object after assignment.
     */
    Fraction &Fraction::operator=(const Fraction &other)
    {
        if (this == &other)
            return *this;

        this->numerator = other.numerator;
        this->denominator = other.denominator;
        return *this;
    }

    /**
     * This is the move assignment operator, which moves the values of the given Fraction object to the current object.
     * It returns a reference to the current object after move.
     */
    Fraction &Fraction::operator=(Fraction &&other) noexcept
    {
        if (this == &other)
            return *this;

        this->numerator = other.numerator;
        this->denominator = other.denominator;
        return *this;
    }

    /**
     * This is a helper function that reduces the current fraction to its simplest form by dividing both numerator
     * and denominator by their greatest common divisor.
     */
    void Fraction::reduce()
    {
        if (denominator < 0)
        {
            numerator = -numerator;
            denominator = -denominator;
        }
        int my_gcd = abs(gcd(numerator, denominator));
        numerator /= my_gcd;
        denominator /= my_gcd;
    }

    /**
     * This is a friend function that overloads the + operator for Fraction objects.
     * It adds two fractions and returns the result as a new Fraction object.
     */
    const Fraction operator+(const Fraction &num1, const Fraction &num2)
    {
        int lcm = abs(num1.denominator * num2.denominator / gcd(num1.denominator, num2.denominator));
        int num_1 = num1.numerator * (lcm / num1.denominator);
        int num_2 = num2.numerator * (lcm / num2.denominator);
        return Fraction(overflow_check(num_1, num_2, '+'), lcm);
    }

    /**
     * This is a friend function that overloads the - operator for Fraction objects.
     * It subtracts one fraction from another and returns the result as a new Fraction object.
     */
    const Fraction operator-(const Fraction &num1, const Fraction &num2)
    {
        int lcm = abs(num1.denominator * num2.denominator / gcd(num1.denominator, num2.denominator));
        int num_1 = num1.numerator * (lcm / num1.denominator);
        int num_2 = num2.numerator * (lcm / num2.denominator);
        return Fraction(overflow_check(num_1, num_2, '-'), lcm);
    }

    /**
     * This is a friend function that overloads the * operator for Fraction objects.
     * It multiplies two fractions and returns the result as a new Fraction object.
     */
    const Fraction operator*(const Fraction &num1, const Fraction &num2)
    {
        return Fraction(overflow_check(num1.numerator, num2.numerator, '*'), overflow_check(num1.denominator, num2.denominator, '*'));
    }

    /**
     * This is a friend function that overloads the / operator for Fraction objects.
     * It divides one fraction by another and returns the result as a new Fraction object.
     */
    const Fraction operator/(const Fraction &num1, const Fraction &num2)
    {
        if (num2.numerator == 0)
        {
            throw runtime_error("Cannot divide by zero.");
        }
        return Fraction(overflow_check(num1.numerator, num2.denominator, '*'), overflow_check(num1.denominator, num2.numerator, '*'));
    }

    /**
     * This is a friend function that overloads the == operator for Fraction objects.
     * It checks if two fractions are equal and returns true if they are, otherwise false.
     */
    bool operator==(const Fraction &num1, const Fraction &num2)
    {
        return (num1.numerator == num2.numerator && num1.denominator == num2.denominator);
    }

    /**
     *  This is a friend function that overloads the != operator for Fraction objects.
     * It checks if two fractions are not equal and returns true if they are not, otherwise false.
     */
    bool operator!=(const Fraction &num1, const Fraction &num2)
    {
        return !(num1 == num2);
    }

    /**
     * This is a friend function that overloads the > operator for Fraction objects.
     * It checks if the first fraction is greater than the second fraction and returns true if it is, otherwise false.
     */
    bool operator>(const Fraction &num1, const Fraction &num2)
    {
        int lcm = abs(num1.denominator * num2.denominator / gcd(num1.denominator, num2.denominator));
        int num_1 = num1.numerator * (lcm / num1.denominator);
        int num_2 = num2.numerator * (lcm / num2.denominator);
        return num_1 > num_2;
    }

    /**
     * This is a friend function that overloads the < operator for Fraction objects.
     * It checks if the first fraction is less than the second fraction and returns true if it is, otherwise false.
     */
    bool operator<(const Fraction &num1, const Fraction &num2)
    {
        return !(num1 > num2 || num1 == num2);
    }

    /**
     * This is a friend function that overloads the >= operator for Fraction objects.
     * It checks if the first fraction is greater than or equal to the second fraction and returns true if it is, otherwise false.
     */
    bool operator>=(const Fraction &num1, const Fraction &num2)
    {
        return (num1.numerator * num2.denominator) >= (num1.denominator * num2.numerator);
    }

    /**
     * This is a friend function that overloads the <= operator for Fraction objects.
     * It checks if the first fraction is less than or equal to the second fraction and returns true if it is, otherwise false.
     */
    bool operator<=(const Fraction &num1, const Fraction &num2)
    {
        return (num1.numerator * num2.denominator) <= (num1.denominator * num2.numerator);
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