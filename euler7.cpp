#include "enumerable.h"
#include "enumerable_generator.h"
#include <iostream>

using namespace std;
int main(int argc, char const *argv[])
{
    Enumerable<int> en = Enumerable_Generator::get().prime_for(10001); 
    cout << en.last() << endl;
    return 0;
}
