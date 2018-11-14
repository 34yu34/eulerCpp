#include "iterator.h"
#include <iostream>

using namespace std;

int main(int argc, char const * argv[])
{
  Iterator<int> e;
  Iterator<int> a = Iterator<int>(5);
  Iterator<int> b = Iterator<int>(6);
  Iterator<int> c = Iterator<int>(7);
  Iterator<int> d = Iterator<int>(8);
  e = 45;
  a.setNext(&b).setNext(&c).setNext(&d);
  a.setLast(&e);
  (++(++a)).unlink();
  cout << *(a) << *(--a) << *(--a) << *(a--) << *a << endl;

  Iterator<int> z = 6;
  z.add(2).add(3).add(4,false);
  cout << *(z++) << *(++z) << *(++z) << endl;
  return 0;
}