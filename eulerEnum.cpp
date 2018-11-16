#include "enumerable.h"
#include "iterator.h"
#include "iostream"

using namespace std;

int main(int argc, char const *argv[])
{
    Enumerable<int> a = Enumerable<int>(2,102, 2).map([](int a){return a * a;}).select([](int a) {return a % 3 == 0;});
    a.each([](int a){cout << a << endl;});
    cout << a.inject([](int sum, int val){return sum + (val%3 == 0 || val%5 == 0 ? val : 0);}) << endl;
    return 0;
}
