#include <iostream>
#include "array.h"

using namespace std;

int main(int argc, char const *argv[])
{
    Array<int> a = Array<int>();
    Array<int> c;
    Array<int> d = {1, 2, 6, 7};

    c.push(2,3,4,5,6,7,8);
    a << 4 << 5 << 6 << 7;

    cout << a << endl;

    cout << d << endl;

    cout << a.map<int>([](int b){ return 2 * b;}) << endl;
    cout << a.sum() << endl; 

    cout << a.select([](int b){return (b % 2 == 0);}) << endl;

    if (a)
    {
        cout << "blah" << endl;
    }
    return 0;
}
