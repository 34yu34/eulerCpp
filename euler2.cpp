#include "iostream"
#include "enumerable.h"
#include "bignum.h"

using namespace std;

int main(int argc, char const *argv[])
{
     cout << Enumerable<int>::fibonacciUntil(4000000)
            .select([](const int & a){return (a % 2 == 0);})
            .sum();
    return 0;
}
