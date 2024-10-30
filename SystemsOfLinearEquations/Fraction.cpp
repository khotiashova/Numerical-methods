#ifndef SYSTEMSOFLINEAREQUATIONS_FRACTION_CPP
#define SYSTEMSOFLINEAREQUATIONS_FRACTION_CPP

#include "Fraction.h"
#include "cassert"
#include "cstdio"

int Fraction::GcdEuclidean(int a, int b){
    while (b > 0) {
        int c = a % b;
        a = b;
        b = c;
    }
    return a;
}

Fraction::Fraction(const std::string &string) {
    assert(!string.empty());
    std::size_t pos = string.find('/');
    if (pos == string::npos) {
        Numerator = stoi(string);
        Denominator = 1;
    }else {
        Numerator   = stoi(string.substr(0, pos));
        Denominator = stoi(string.substr(pos+1, string::npos));
        assert(Denominator != 0);
    }
    Reduce();
}

Fraction::Fraction(int numerator, int denominator) {
    Numerator = numerator;
    Denominator = denominator;
    assert(denominator != 0);
    Reduce();
}

void Fraction::Reduce() {
    int gcd = GcdEuclidean(abs(Numerator), Denominator);
    if (gcd != 1) {
        Numerator = Numerator / gcd;
        Denominator = Denominator / gcd;
    }
}

string Fraction::ToString() const {
    string fraction;
    if (Numerator == 0) {
        fraction.append("0");
        return fraction;
    }
    fraction.append(std::to_string(Numerator));
    if (Denominator != 1) {
        fraction.append("/");
        fraction.append(std::to_string(Denominator));
    }
    return fraction;
}

int Fraction::GetNumerator() const {
    return this->Numerator;
}
int Fraction::GetDenominator() const {
    return this->Denominator;
}

Fraction Fraction::operator+(const Fraction &fraction) const {
    Fraction result(this->Numerator * fraction.GetDenominator() + this->Denominator * fraction.GetNumerator(),
                    this->Denominator * fraction.Denominator);
    return result;
}
Fraction Fraction::operator-(const Fraction &fraction) const {
    Fraction result(this->Numerator * fraction.GetDenominator() - this->Denominator * fraction.GetNumerator(),
                    this->Denominator * fraction.Denominator);
    return result;
}

Fraction Fraction::operator*(const Fraction &fraction) const {
    Fraction result(this->Numerator * fraction.GetNumerator(),
                    this->Denominator * fraction.GetDenominator());
    return result;
}

Fraction Fraction::operator/(const Fraction &fraction) const {
    assert(fraction.GetNumerator() != 0);
    Fraction result(this->Numerator * fraction.GetDenominator(),
                    this->Denominator * fraction.GetNumerator());
    return result;
}

#endif