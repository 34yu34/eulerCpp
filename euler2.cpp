#include "enumerable.h"
#include "iostream"

using namespace std;

int main(int argc, char const *argv[])
{
    cout << Enumerable<int>::fibonacciUntil(4000000)
            .select([](int a){return (a % 2 == 0);})
            .sum();
    return 0;
}
