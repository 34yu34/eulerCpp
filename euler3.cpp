#include "iostream"
#include "enumerable.h"
#include "bignum.h"

using namespace std;

int main(int argc, char const *argv[])
{
    Bignum a = "600851475143";
    Enumerable<Bignum> en = Enumerable<Bignum>::factors(a);
    en.each([](Bignum a){cout << a << endl;});
    return 0;
}
