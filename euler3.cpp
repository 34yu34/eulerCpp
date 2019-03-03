#include "iostream"
#include "vector"
#include "enumerable.h"
#include "enumerableGenerator.h"
#include "bignum.h"
#include "number.h"

using namespace std;

int main(int argc, char const *argv[])
{
    Bignum a = "600851475143";
    std::vector<Number::Factor<Bignum> *> vect = Number::getFactors(a);
    Enumerable<Number::Factor<Bignum> *> en(vect.data(), vect.size());
    en.each([](Number::Factor<Bignum> * a){cout << a->factor << endl;});
    return 0;
}
