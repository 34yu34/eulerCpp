#include <iostream>

using namespace std;

#define DEBUG true

#if DEBUG
#define PRINT(x) {cout << #x << " : " << x << endl;} 
#else

#define PRINT(x) 
#endif