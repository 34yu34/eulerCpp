#include "enumerable.h"
#include "iterator.h"
#include "iostream"

using namespace std;

int main(int argc, char const *argv[])
{
    Enumerable<int> a = Enumerable<int>(2,102, 2).map([](int a){return a * a;}).select([](int a) {return a % 3 == 0;});
    cout << "blah";
    for (auto i = a.begin(); i != a.end(); i = i.next())
    {
        cout << (*i) << endl;
    }
    return 0;
}
