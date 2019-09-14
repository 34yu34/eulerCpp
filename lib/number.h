#pragma once

#include "iostream"
#include "enumerable.h"
#include "array.h"
#include "bignum.h"

namespace Number
{
  template<class T>
  struct Factor {
    T factor;
    int repetition;
  };

  template<class T>
  Enumerable<Factor<T> *> get_factors(T num);

  template<class T>
  void add_factor(Factor<T> * fact, Enumerable<Factor<T> *> & vect);

  template<class T>
  Factor<T> * find_factor(const T & factor, T & num);

  template<class T>
  bool is_palindrome(const T & num);

  template<class T>
  bool is_prime(const T & num);

  template<class T>
  Enumerable<T> get_diviser(const T & num);

  template <class T>
  T max(const T & num1, const T & num2)
  {
    return num1 > num2 ? num1 : num2;
  }

  template<class T>
  T min(const T & num1, const T & num2)
  {
    return num1 < num2 ? num1 : num2;
  }

  template<class T>
  void print(const T & val)
  {
    std::cout << val << std::endl;
  }

  template<class T>
  T pow(const T & val1, const T & val2)
  {
    T res = 1;for (T i = 0; i < val2; i++) {
      res *= val1;
    }
    return res;
  }
}

template<class T>
bool Number::is_palindrome(const T & num)
{
  unsigned int size = 0;
  int top = 1;
  int bot = 1;
  while (num / (top) > 0) {
    size += 1;top *= 10;
  }
  top /= 10;
  for (uint64_t i = 0; i < size / 2; i++) {
    if ((num / top) % 10 != ((num / bot) % 10)) {
      return false;
    }
    top /= 10;
    bot *= 10;
  }
  return true;
}

template<class T>
bool Number::is_prime(const T & num)
{
  if (num % 2 == 0) return false;
  if (num % 3 == 0) return false;
  if (num % 5 == 0) return false;
  if (num % 7 == 0) return false;

  for (uint64_t i = 12; (i-1) * (i-1) <= num; i += 6)
  {
    if (num % (i - 1) == 0 || num % (i + 1) == 0)
    {
      return false;
    }
  }
  return true;
}


template<class T>
Enumerable<Number::Factor<T> *> Number::get_factors(T num)
{
  Enumerable<Number::Factor<T> *> solutions;
  add_factor(find_factor(T() + 2, num), solutions);
  add_factor(find_factor(T() + 3, num), solutions);
  add_factor(find_factor(T() + 5, num), solutions);
  add_factor(find_factor(T() + 7, num), solutions);
  for (T i = 12; i < num; i += 6) {
    add_factor(find_factor(i + 1, num), solutions);
    add_factor(find_factor(i - 1, num), solutions);
  }
  if (num != 1) {
    Number::Factor<T> * fact = new Number::Factor<T>();
    fact->factor = num;
    fact->repetition = 1;
    solutions << fact;
  }
  return solutions;
}

template<class T>
void Number::add_factor(Number::Factor<T> * fact, Enumerable<Number::Factor<T> *> & vect)
{
  if (fact != nullptr) {
    vect << fact;
  }
}

template<class T>
Number::Factor<T> * Number::find_factor(const T & factor, T & num)
{
  Number::Factor<T> * fact = new Number::Factor<T>();
  fact->factor = factor;
  fact->repetition = 0;
  while (num % factor == 0) {
    num /= factor;
    fact->repetition += 1;
  }
  if (fact->repetition == 0) {
    return nullptr;
  }
  return fact;
}

template<class T>
Enumerable<T> Number::get_diviser(const T & num)
{
  Enumerable<T> result;
  result << 1 << num;
  for(T i = 2; i * i < num; ++i)
  {
    if (num % i == 0)
    {
      result << i << num / i;
    }
  }
  return result;
}
