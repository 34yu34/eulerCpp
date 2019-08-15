#include "str.h"
#include <iostream>

using namespace std;

int main(int argc, const char** argv) {

    str text = "blah";
    char * blah = "blah";
    str text2 = blah;
    cout << text << " " << text2 << endl;
    return 0;
}