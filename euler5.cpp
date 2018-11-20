#include <functional>
#include <iostream>
#include "enumerable.h"
#include "number.h"

using namespace Number;

int main(int argc, char const *argv[])
{
    Enumerable<Enumerable<Factor<int>>> en = Enumerable<int>(1,21).map(Enumerable<int>::factors);
    Factor<int> * fact = new Factor<int>[en.size()];
    return 0;
}
