//The sum of the primes below 10 is 2 + 3 + 5 + 7 = 17.
//
//Find the sum of all the primes below two million.

#include <iostream>
#include "enumerable.h"
#include "enumerable_generator.h"

using namespace std;

int main(int argc, const char** argv) {

    cout << Enumerable_Generator::get()
            .prime(2000000)
            .cast<uint64_t>()
            .sum() << endl;
    return 0;
}