#ifndef FRACTION_HPP
#define FRACTION_HPP
#include <iostream>
#include <stdexcept>
#include <limits>
#include <sstream>
#include <fstream>
#include <string>

using namespace std;

namespace ariel{
    class Fraction {
        private:
            int numerator;
            int denominator;
            static const int max_int = numeric_limits<int>::max();
            static const int min_int = numeric_limits<int>::min();

            // Helper function to reduce the fraction
            void reduce();
            // Helper function to compute the greatest common divisor
            int gcd(int num1, int num2) const;
          
        
            static int overflow_addition(int num1, int num2) {
                if ((num2 > 0 && num1 > (max_int - num2)) || (num2 < 0 && num1 < (min_int - num2)))
                {
                    throw overflow_error("Addition overflow");
                }

                return (num1 + num2);
            }

           
            static int overflow_subtraction(int num1, int num2) {
                if ((num2 < 0 && num1 > max_int + num2) || (num2 > 0 && num1 < min_int + num2))
                {
                    throw overflow_error("Subtraction overflow");
                }

                return (num1 - num2);
            }

       
            static int overflow_multiplication(int num1, int num2) {
                if ((num2 > 0 && num1 > max_int / num2) || (num2 < 0 && num1 < max_int / num2))
                {
                    throw overflow_error("Multiplication overflow");
                }

                return (num1 * num2);
            }



        public:
            //constructor
            Fraction();
            Fraction(int numerator, int denominator);
            Fraction(float num);
            Fraction(const Fraction& other);
            Fraction(Fraction&& other) noexcept;
            
            // //destructor
            ~Fraction() = default;

            Fraction& operator=(const Fraction& other);
            Fraction& operator=(Fraction&& other) noexcept;


            // Overloaded operators for arithmetic operations
            const Fraction operator+(const Fraction& other) const;
            const Fraction operator+(const float& other) const;
            friend const Fraction operator+(const float& num1, const Fraction& num2);
            
            const Fraction operator-(const Fraction& other) const;
            const Fraction operator-(const float& other) const;
            friend const Fraction operator-(const float& num1, const Fraction& num2);
            
            const Fraction operator*(const Fraction& other) const;
            const Fraction operator*(const float& other) const;
            friend const Fraction operator*(const float& num1, const Fraction& num2);
            
            const Fraction operator/(const Fraction& other) const;
            const Fraction operator/(const float& other) const;
            friend const Fraction operator/(const float& num1, const Fraction& num2);
        
            // Overloaded operators for comparison operations
            bool operator==(const Fraction& other) const;
            bool operator==(const float& other) const;
            friend bool operator==(const float& num1, const Fraction& num2);
            
            bool operator!=(const Fraction& other) const;
            bool operator!=(const float& other) const;
            friend bool operator!=(const float& num1, const Fraction& num2);
            
            bool operator>(const Fraction& other) const;
            bool operator>(const float& other) const;
            friend bool operator>(const float& num1, const Fraction& num2);
            
            bool operator<(const Fraction& other) const;
            bool operator<(const float& other) const;
            friend bool operator<(const float& num1, const Fraction& num2);
            
            bool operator>=(const Fraction& other) const;
            bool operator>=(const float& other) const;
            friend bool operator>=(const float& num1, const Fraction& num2);
           
            bool operator<=(const Fraction& other) const;
            bool operator<=(const float& other) const;
            friend bool operator<=(const float& num1, const Fraction& num2);

            // Overloaded operators for increment and decrement operations
            Fraction operator++(); // pre-increment
            Fraction operator++(int); // post-increment
            Fraction operator--(); // pre-decrement
            Fraction operator--(int); // post-decrement

            // Overloaded operators for input and output operations
            friend ostream& operator<<(ostream& output, const Fraction& fraction);
            friend istream& operator>>(istream& input, Fraction& fraction);

            // Getter and setter functions
            int getNumerator() const;
            int getDenominator() const;
            void setNumerator(int numerator);
            void setDenominator(int denominator);


    };


};

#endif // FRACTION_HPP

