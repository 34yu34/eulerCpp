#include "enumerable.h"
#include <iostream>

using namespace std;

int main(int argc, char const *argv[])
{
    Enumerable<int> a = {4, 6, 1, 3};

    a.push(3,4,5,6);

    cout << a << endl;
    return 0;
}
