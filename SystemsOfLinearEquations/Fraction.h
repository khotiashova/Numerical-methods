#ifndef SYSTEMSOFLINEAREQUATIONS_FRACTION_H
#define SYSTEMSOFLINEAREQUATIONS_FRACTION_H

#include <string>
using namespace std;

class Fraction {
private:
    int Numerator{};
    int Denominator{};
    void Reduce();
public:
    Fraction(int numerator, int denominator);
    explicit Fraction(const string &string);
    [[nodiscard]] string ToString() const;
    [[nodiscard]] int GetNumerator() const;
    [[nodiscard]] int GetDenominator() const;

    Fraction operator+(const Fraction &fraction) const;
    Fraction operator-(const Fraction &fraction) const;
    Fraction operator*(const Fraction &fraction) const;
    Fraction operator/(const Fraction &fraction) const;
    static int GcdEuclidean(int a, int b);
};

#include "Fraction.cpp"

#endif