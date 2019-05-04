#include "iostream"
#include "enumerable.h"
#include "enumerable_generator.h"

using namespace std;

int main(int argc, char const *argv[])
{
    int sum_square = Enumerable_Generator::get().range(1,101,1).sum();
    sum_square *= sum_square;
    int square_sum = Enumerable_Generator::get().range(1,101,1)
                    .map<int>([](int a){return a * a;}).sum();
    cout << sum_square - square_sum << endl;
    return 0;
}
