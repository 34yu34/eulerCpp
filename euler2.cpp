#include "iostream"
#include "fibonacci.h"
#include "array.h"

using namespace std;

int main(int argc, char const *argv[])
{
    Fibonacci f = Fibonacci<uint64_t>::until([](uint64_t i) { return i < 4000000 ; });

    f.get_array().each([](uint64_t i) {
        cout << i << endl; 
    });

    return 0;
}
