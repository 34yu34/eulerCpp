#pragma once

#include "enumerable.h"

class Enumerable_Generator
{
private:

public:
  static Enumerable_Generator & get();

  template<class T>
  Enumerable<T> range(T start, const T & end, const T & jump);

  Enumerable<int> prime(int max);
  Enumerable<int> prime_for(int n);
  Enumerable<int> fibonacci_max(int max);
  Enumerable<int> fibonacci_sequence(int times);

  ~Enumerable_Generator();
private:
  Enumerable_Generator();
};

template<class T>
Enumerable<T> Enumerable_Generator::range(T start, const T & end, const T & jump)
{
  Enumerable<T> en;
  while (start != end) {
    en << start;
    start += jump;
  }
  return en;
}
