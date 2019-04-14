#include "iostream"
#include "enumerable.h"
#include "enumerable_generator.h"

using namespace std;

int main(int argc, char const *argv[])
{
    cout << Enumerable_Generator::get().range(0, 1000, 1)
            .select([](const int & a){return (a % 3 == 0 || a % 5 == 0);})
            .sum();
    return 0;
}
