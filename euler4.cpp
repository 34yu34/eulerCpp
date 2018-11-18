#include "enumerable.h"
#include "number.h"

using namespace std;

int main(int argc, char const *argv[])
{
    int size = 999 * 999 / 2;
    int * data = new int[size];
    int index = 0;
    for (size_t i = 100; i < 999; i++) {
        for(size_t j = 100; j <= i; j++) {
            data[index++] = i * j;
        }
    }
    Enumerable<int> en = Enumerable<int>(data, index);
    en.select(Number::isPalindrome<int>);
    cout << en.inject(Number::max<int>) <<endl;
    return 0;
}
