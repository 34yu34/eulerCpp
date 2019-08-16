//A Pythagorean triplet is a set of three natural numbers, a < b < c, for which,
//
//a2 + b2 = c2
//For example, 32 + 42 = 9 + 16 = 25 = 52.
//
//There exists exactly one Pythagorean triplet for which a + b + c = 1000.
//Find the product abc.

#include <iostream>

using namespace std;

int main(int argc, const char** argv) {
    for(int a = 1; a < 997; ++a) {
        for (int b = a+1; b < 998; ++b) {
            int c = 1000 - a - b;
            if (a * a + b * b == c * c)
            {
                cout << a * b *c << endl;
                return 1;
            }
        }
    }
    return 0;
}