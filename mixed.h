/*
Hubert Pilichowski's header file for the mixed class
includes definitions for all of the operator overloading functions
includes definitions for member functions that simplify and evaluate 
the mixed numbers
*/


#include <iostream>
using namespace std;

class Mixed
{
public:

    // constructors
    Mixed(int integer, int numerator, int denominator);
    Mixed(int integer = 0);
    
    // member functions to manipulate mixed numbers
    double Evaluate() const;
    void Simplify();
    void ToFraction();

    // member function because of specific formatting of increments and decrements
    Mixed& operator++();
    Mixed operator++(int);
    Mixed& operator--();
    Mixed operator--(int);


    // friend functions to ensure that parameters can be reversed
    friend istream& operator>>(istream& is, Mixed& m2);
    friend ostream& operator<<(ostream& os, const Mixed& m2);

    friend bool operator<(const Mixed& m1, const Mixed& m2);
    friend bool operator>(const Mixed& m1, const Mixed& m2);
    friend bool operator>=(const Mixed& m1, const Mixed& m2);
    friend bool operator<=(const Mixed& m1, const Mixed& m2);
    friend bool operator==(const Mixed& m1, const Mixed& m2);
    friend bool operator!=(const Mixed& m1, const Mixed& m2);

    friend Mixed operator+(const Mixed& m1, const Mixed& m2);
    friend Mixed operator-(const Mixed& m1, const Mixed& m2);
    friend Mixed operator*(const Mixed& m1, const Mixed& m2);
    friend Mixed operator/(const Mixed& m1, const Mixed& m2);

private:
    int integer;
    int numerator;
    int denominator;

    // extra member function to check validity of the mixed numbers
    bool checkValid(int i, int n, int d) const;
};
