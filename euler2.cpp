#include "iostream"
#include "enumerable.h"
#include "lib/enumerable_generator.h"

using namespace std;

int main(int argc, char const *argv[])
{
     cout << Enumerable_Generator::get().fibonacci_max(4000000)
            .select([](const int & a){return (a % 2 == 0);})
            .sum();
    return 0;
}
