#pragma once

#include <stdint.h>
#include <cstring>
#include <iostream>

using namespace std;

class str
{
private:
  char * data_;
  uint32_t size_;

private:
  void init(const char * data);

public:
  str(const char * data);
  str(const string & data);
  str(const str & str);

  str & operator=(const char * data);
  str & operator=(const string & str);
  str & operator=(const str & str);
  ~str();
};
