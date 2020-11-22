#pragma once

#include <stdint.h>
#include <cstring>
#include <iostream>
#include "array.h"

using namespace std;

class str
{
private:
  Array<char> data_;

private:
  void init(const char * data);
  void copy_data(const str & str);

public:
// constructors
  str();
  str(const char * data);
  str(const string & data);
  str(const str & str);

  str & operator=(const char * data);
  str & operator=(const string & str);
  str & operator=(const str & str);
  ~str();
// getters
  uint32_t size() const;
  char & operator[](const uint32_t index);

// operators
  str & operator+=(const str & str);
  str operator+(const str & str) const;
  str & operator-=(const str & str);
  str & operator-=(const string & str);
  str & operator-=(const char & c);
  str operator-(str str) const;
  str operator<<(const str & str);

  friend ostream & operator<<(ostream & o, const str & text); 
};
