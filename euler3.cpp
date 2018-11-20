#include "iostream"
#include "enumerable.h"
#include "bignum.h"

using namespace std;

int main(int argc, char const *argv[])
{
    Bignum a = "600851475143";
    Enumerable<Number::Factor<Bignum>> en = Enumerable<Bignum>::factors(a);
    en.each([](Number::Factor<Bignum> a){cout << a.factor << endl;});
    return 0;
}
