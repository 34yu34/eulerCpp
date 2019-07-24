#pragma once

#include <stdint.h>
#include <cstring>
#include <iostream>

using namespace std;

class Sstring
{
private:
  char * data_;
  uint32_t size_;

private:
  void init(const char * data);

public:
  Sstring(const char * data);
  Sstring(const string & data);
  Sstring(const Sstring & str);

  Sstring & operator=(const char * data);
  Sstring & operator=(const string & str);
  Sstring & operator=(const Sstring & str);
  ~Sstring();
};
