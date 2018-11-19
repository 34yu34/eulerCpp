#include "iostream"
#include "enumerable.h"

using namespace std;

int main(int argc, char const *argv[])
{
    int sumSquare = Enumerable<int>(1,101).sum();
    sumSquare *= sumSquare;
    int squareSum = Enumerable<int>(1,101).map([](int a){return a * a;}).sum();
    cout << sumSquare - squareSum << endl;
    return 0;
}
