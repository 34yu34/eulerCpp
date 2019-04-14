#include "iostream"
#include "enumerable.h"
#include "enumerable_generator.h"

using namespace std;

int main(int argc, char const *argv[])
{
    int sumSquare = Enumerable_Generator::get().range(1,101,1).sum();
    sumSquare *= sumSquare;
    int squareSum = Enumerable_Generator::get().range(1,101,1)
                    .map<int>([](int a){return a * a;}).sum();
    cout << sumSquare - squareSum << endl;
    return 0;
}
