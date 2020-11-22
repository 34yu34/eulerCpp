#include "iostream"
#include "fibonacci.h"
#include "array.h"

using namespace std;

int main(int argc, char const *argv[])
{
    Fibonacci<uint64_t> f = Fibonacci<uint64_t>::until([](uint64_t i) { return i >= 4000000 ; });

    cout << f.get_array().select([](uint64_t i) { return i % 2 == 0; }).sum() << endl;

    return 0;
}
