/*
Hubert Pilichowski's mixed.cpp file
Practice with operator overloading
and classes
*/


#include <iostream>
#include "mixed.h"

using namespace std;

// constructor that checks for valid syntax and makes the Mixed number zero otherwise
Mixed::Mixed(int number, int num, int denom)
{

    if (!checkValid(number, num, denom))
    {
        integer = 0;
        numerator = 0;
        denominator = 1;
    }
    else
    {
        integer = number;
        numerator = num;
        denominator = denom;
    }
}

// type conversion constructor for integers
Mixed::Mixed(int num)
{
    integer = num;
    numerator = 0;
    denominator = 1;

}

// accessor that returns the decimal form of the calling object
double Mixed::Evaluate() const
{
    Mixed temp;
    temp.numerator = numerator;
    temp.denominator = denominator;
    temp.integer = integer;
    temp.ToFraction();

    double a = temp.numerator;
    double b = temp.denominator;

    double result = a/b;
    return result;
}

// simplifies the fraction part of the mixed number
void Mixed::Simplify()
{
    Mixed temp;
    temp.numerator = numerator;
    temp.integer = integer;
    temp.denominator = denominator;
    temp.ToFraction();

    // ensures the positivity of the numerator to make calculations easier
    if (temp.numerator < 0)
        numerator = -temp.numerator;

    // calculate integer value and remaining numerator value
    if (numerator >= denominator)
    {
        integer = temp.numerator/denominator;
        numerator = numerator % denominator;
    }

    // this loop runs numerator amount of time to ensure checking every possible multiple
    for (int i =  1; i <= numerator; i++)
    {
        // checks every value less than the numerator for a common divisor
        for (int j = 2; j <= numerator; j++)
        {
            if (numerator%j == 0 && denominator%j == 0)
            {
                numerator /= j;
                denominator /= j;
                continue;
            }
        }
    }

    // undoes making a negative numerator positive
    if (integer < 0 && numerator < 0)
        numerator = -numerator;
    
    // ensures denominator positive after other calculations
    if (denominator < 0)
        denominator = -denominator;
}

// function that changes the calling object from a Mixed number to a fraction
void Mixed::ToFraction()
{
    // if the integer is negative
    if (integer < 0)
    {
        integer = -integer;
        numerator = (integer * denominator) + numerator;
        numerator = -numerator;
        integer = 0;
    }

    // if both numerator and denominator are both 1
    else if (numerator == 1 && denominator == 1)
    {
        numerator = integer + 1;
        denominator = 1;
        integer = 0;
    }

    // if no integer do nothing
    else if (integer == 0)
        return;


    else
    {
        numerator = (integer * denominator) + numerator;
        integer = 0;
    }
}

// extraction operator overload that returns an istream
istream& operator>>(istream& is, Mixed& m)
{
    char ch;
    int i, n, d;
    is >> i >> n >> ch >> d;
    if (m.checkValid(i, n, d))
    {
        m.integer = i;
        m.numerator = n;
        m.denominator = d;
        return is;
    }
    else
    {
        m.integer = 0;
        m.numerator = 0;
        m.denominator = 1;
        return is;
    }
}

// insertion operator overload that returns an ostream
ostream& operator<<(ostream& os, const Mixed& m)
{
    if (m.integer == 0 && m.numerator == 0)
        os << 0;
    else if (m.integer != 0 && m.numerator == 0)
        os << m.integer;
    else if (m.integer == 0 && m.numerator != 0)
        os << m.numerator << '/' << m.denominator;
    else
        os << m.integer << " " << m.numerator << "/" << m.denominator;
    return os;
}

// less than operator overload
bool operator<(const Mixed& m1, const Mixed& m2)
{
    if (m1.integer < m2.integer)
        return true;

    int tempNum1 = m1.numerator * m2.denominator;
    int tempNum2 = m2.numerator * m1.denominator;
    int tempDenom = m1.denominator * m2.denominator;

    if (tempNum1 < tempNum2)
        return true;
    else
        return false;
}

// greater than operator overload
bool operator>(const Mixed& m1, const Mixed& m2)
{
    if (!(m1 < m2) && !(m1 == m2))
        return true;
    else
        return false;
}

// less than or equal to operator overload
bool operator<=(const Mixed& m1, const Mixed& m2)
{
    if (m1 < m2 || m1 == m2)
        return true;
    else
        return false;
}

// greater than or equal to operator overload
bool operator>=(const Mixed& m1, const Mixed& m2)
{
    if (m1 > m2 || m1 == m2)
        return true;
    else
        return false;
}

// is equal to operator overload
bool operator==(const Mixed& m1, const Mixed& m2)
{
    Mixed temp1, temp2;
    temp1 = m1;
    temp2 = m2;

    temp1.Simplify();
    temp2.Simplify();

    if (temp1.integer == temp2.integer && temp1.numerator == temp2.numerator && temp1.denominator && temp2.denominator)
        return true;
    else 
        return false;
}

// is not equal to operator overload
bool operator!=(const Mixed& m1, const Mixed& m2)
{
    if (!(m1 == m2))
        return true;
    else
        return false;
}

// plus operator overload
Mixed operator+(const Mixed& m1, const Mixed& m2)
{
    Mixed newMixed, temp1, temp2;
    temp1 = m1;
    temp2 = m2;

    temp1.ToFraction();
    temp2.ToFraction();

    newMixed.numerator = (temp1.numerator * temp2.denominator) + (temp2.numerator * temp1.denominator);
    newMixed.denominator = (temp1.denominator * temp2.denominator);
    newMixed.Simplify();

    return newMixed;
}

// minus operator overload
Mixed operator-(const Mixed& m1, const Mixed& m2)
{
    Mixed result, temp1, temp2;
    temp1 = m1;
    temp2 = m2;

    temp1.ToFraction();
    temp2.ToFraction();

    result.numerator = (temp1.numerator * temp2.denominator) - (temp2.numerator * temp1.denominator);
    result.denominator = (temp1.denominator * temp2.denominator);

    result.Simplify();
    
    return result;
}

// multiply operator overload
Mixed operator*(const Mixed& m1, const Mixed& m2)
{
    Mixed result;

    Mixed temp1 = m1;
    Mixed temp2 = m2;

    temp1.ToFraction();
    temp2.ToFraction();

    result.numerator = temp1.numerator * temp2.numerator;
    result.denominator = m1.denominator * m2.denominator;
    result.Simplify();

    return result;
}

// dividing operator overload
Mixed operator/(const Mixed& m1, const Mixed& m2)
{
    Mixed result;

    Mixed temp1 = m1;
    Mixed temp2 = m2;

    temp1.ToFraction();
    temp2.ToFraction();

    result.numerator = temp1.numerator * temp2.denominator;
    result.denominator = temp2.numerator * temp1.denominator;
    result.Simplify();

    return result;
}

// pre-increment operator overload
Mixed& Mixed::operator++()
{
    integer += 1;
    return *this;
}

// post-increment operator overload
Mixed Mixed::operator++(int)
{
    Mixed temp = *this;
    integer += 1;
    return temp;
}

// pre-decrement operator overload
Mixed& Mixed::operator--()
{
    integer -= 1;
    return *this;
}

// post-decrement operator overload
Mixed Mixed::operator--(int)
{
    Mixed temp = *this;
    integer -= 1;
    return temp;
}

// check valid function to ensure valid syntax
bool Mixed::checkValid(int i, int n, int d) const
{
    // if denominator is 0
    if (d == 0)
        return false;
    
    // if integer is 0 and one of the other ones is also 0
    if (i < 0)
    {
        if (n < 0 || d < 0)
            return false;
    }

    // if both numerator and denominator are negative
    if (i == 0 && n < 0 && d < 0)
        return false;
    // if numerator is negative and integer does not equal zero
    if (i != 0 && n < 0)
        return false;
    // // if denominator is negative and integer does not equal zero
    if (i != 0 && d < 0)
        return false;
    
    return true;
}
