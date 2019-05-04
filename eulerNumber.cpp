#include "number.h"
#include "iostream"

using namespace std;

int main(int argc, char const *argv[])
{
    cout << Number::is_palindrome<int>(1001) << endl;
    cout << Number::is_palindrome<int>(1011) << endl;
    cout << Number::is_palindrome<int>(9182819) << endl;
    cout << Number::is_palindrome<int>(9172819) << endl;
    return 0;
}
