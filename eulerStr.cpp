#include "str.h"
#include <iostream>

using namespace std;

int main(int argc, const char** argv) {

    string blah = "vvvv";
    str text = "blah";
    str text2 = "vvvv";
    cout << "blah" << endl;
    cout << text2 << endl;
    cout << text << ", " << text2 << ", " << text[0] << endl;
    return 0;
}