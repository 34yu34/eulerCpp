#ifndef BIGNUM_H
#define BIGNUM_H
#include <stdint.h>
#include <cstring>
#include <iostream>

using namespace std;
class Bignum
{
private:
  uint8_t * data;
  uint32_t data_size;
  bool neg;

  void init(const char * num);
  template<class T>
  void init_size(T num);

  bool operate(const Bignum & num, bool (* fptr)(int, int)) const;
  int find_sign(const Bignum & num) const;
  uint32_t chop(const uint8_t d[], uint32_t currSize) const;

  void addition_step(uint8_t * result, const Bignum & num1, const Bignum & num2, uint8_t & ret, uint32_t index) const;
  void substraction_step(uint8_t * result, const Bignum * max, const Bignum * min, uint8_t & stole, uint32_t index) const;

  void init_division(const Bignum & num, Bignum & quotient, Bignum & denominator, int & index) const;
  void divise_step(Bignum & reminder, Bignum & denominator, uint8_t * newData) const;

public:

  static const uint32_t BASE = 100;

  Bignum();
  Bignum(const char * num);
  Bignum(string num);
  Bignum(int num);
  Bignum(const Bignum & num);
  Bignum(const uint8_t d[], const uint32_t s, bool n);
  void operator=(const Bignum & num);
  void operator=(int num);
  void operator=(string num);
  ~Bignum();

  friend ostream & operator<<(ostream & o, const Bignum & num);

  bool operator<(const Bignum & num) const;
  bool operator<(int num) const;
  friend bool operator<(int num, const Bignum & num2);
  bool operator<=(const Bignum & num) const;
  bool operator<=(int num) const;
  friend bool operator<=(int num, const Bignum & num2);
  bool operator==(const Bignum & num) const;
  bool operator==(int num) const;
  friend bool operator==(int num, const Bignum & num2);
  bool operator!=(const Bignum & num) const;
  bool operator!=(int num) const;
  friend bool operator!=(int num, const Bignum & num2);
  bool operator>=(const Bignum & num) const;
  bool operator>=(int num) const;
  friend bool operator>=(int num, const Bignum & num2);
  bool operator>(const Bignum & num) const;
  bool operator>(int num) const;
  friend bool operator>(int num, const Bignum & num2);

  Bignum operator+(const Bignum & num) const;
  Bignum operator+(int num) const;
  friend Bignum operator+(int num, const Bignum & num2);
  Bignum operator+() const;
  void operator+=(const Bignum & num);
  void operator+=(int num);

  Bignum operator-(const Bignum & num) const;
  Bignum operator-(int num) const;
  friend Bignum operator-(int num, const Bignum & num2);
  Bignum operator-() const;
  void operator-=(const Bignum & num);
  void operator-=(int num);

  Bignum operator*(const Bignum & num) const;
  Bignum operator*(int num) const;
  friend Bignum operator*(int num, const Bignum & num2);
  void operator*=(const Bignum & num);
  void operator*=(int num);

  Bignum operator/(const Bignum & num) const;
  Bignum operator/(int num) const;
  friend Bignum operator/(int num, const Bignum & num2);
  void operator/=(const Bignum & num);
  void operator/=(int num);

  Bignum operator%(const Bignum & num) const;
  Bignum operator%(int num) const;
  friend Bignum operator%(int num, const Bignum & num2);
  void operator%=(const Bignum & num);
  void operator%=(int num);
};
#endif // !BIGNUM_H
