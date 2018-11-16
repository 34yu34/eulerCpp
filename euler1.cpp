#include "iostream"
#include "enumerable.h"

using namespace std;

int main(int argc, char const *argv[])
{
    cout << Enumerable<int>(1,1000)
            .select([](int a){return (a % 3 == 0 || a % 5 == 0);})
            .sum();
    return 0;
}
