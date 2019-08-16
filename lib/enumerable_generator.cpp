#include "enumerable_generator.h"
#include <iostream>

Enumerable_Generator::Enumerable_Generator()
{
};

Enumerable_Generator::~Enumerable_Generator()
{
};

Enumerable_Generator & Enumerable_Generator::get()
{
  static Enumerable_Generator En;
  return En;
}

Enumerable<int> Enumerable_Generator::prime(int max)
{

  Enumerable<int> En;

  // setup
  int * table = new int[max+1];
  for (int i = 0; i < max+1; ++i)
  {
    table[i] = i;
  }

  // removing the divising values
  int jumper = 2;
  while (jumper * jumper < max)
  {
    for (int i = jumper + jumper; i < max + 1; i += jumper) {
      table[i] = 0;
    }

    do {
      jumper += 1;
    } while(table[jumper] == 0);
  }

  //put it in the enumerable
  for (int i = 0; i < max+1; ++i)
  {
    if ( table[i] != 0 && table[i] != 1)
    {
      En << table[i];
    }
  }

  return En;
}

Enumerable<int> Enumerable_Generator::prime_for(int n)
{
  static auto is_divisible = [] (int i)
                             {
                               return [i] (int j) {
                                        return i % j == 0;
                               };
                             };

  Enumerable<int> En;
  if (n < 1) {return En;}
  En.push(2);
  if (n < 2) {return En;}
  En.push(3);
  if (n < 3) {return En;}
  En.push(5);
  if (n < 4) {return En;}
  En.push(7);

  int i = 12;
  while ((int)En.size() < n) {
    if (!En.contains_condition(is_divisible(i - 1))) En << i - 1;
    if ((int)En.size() >= n) return En;
    if (!En.contains_condition(is_divisible(i + 1))) En << i + 1;
    i += 6;
  }
  return En;
}

Enumerable<int> Enumerable_Generator::fibonacci_sequence(int times)
{
  Enumerable<int> En;
  int a = 1;
  int b = 1;
  if (times >= 1) En.push(a);
  if (times >= 2) En.push(b);

  for (int i = 2; i <= times; ++i) {
    int temp = b;
    b = a + b;
    a = temp;
    En << b;
  }
  return En;
}

Enumerable<int> Enumerable_Generator::fibonacci_max(int max)
{
  Enumerable<int> En;
  int a = 1;
  int b = 1;
  if (max >= 1) {
    En << a;
    En << b;
  }

  while (b < max) {
    int temp = b;
    b = a + b;
    a = temp;
    En << b;
  }
  return En;
}
