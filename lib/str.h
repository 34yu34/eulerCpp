#pragma once

#include <stdint.h>
#include <cstring>
#include <iostream>
#include "enumerable.h"

using namespace std;

using str_it = Enumerable<char>::Iterator<char>; 

class str
{
private:
  Enumerable<char> data_;

private:
  void init(const char * data);

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
  friend ostream & operator<<(ostream & o,const str & text); 
};
