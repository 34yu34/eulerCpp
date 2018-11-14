#include "enumerable.h"
#include "iterator.h"
#include "iostream"

using namespace std;

int main(int argc, char const *argv[])
{
    Enumerable<int> a = Enumerable<int>(2,102, 2).map([](int a){return a/2;});
    for (auto i = a.begin(); i != a.end(); i++)
    {
        cout << (*i) << endl;
    }
    return 0;
}
