#include "Fraction.h"
#include "iostream"

using namespace std;

int main() {
    Fraction a(4, 7);
    Fraction b("8/12");
    cout << a.ToString() << endl;
    cout << b.ToString() << endl;
    cout << (a * b).ToString() << endl;
    cout << (a - b).ToString() << endl;
    cout << (a + b).ToString() << endl;
    cout << (a / b).ToString() << endl;
}