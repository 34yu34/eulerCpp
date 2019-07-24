#include "str.h"

void str::init(const char * data)
{
  size_ = (uint32_t)strlen(data);
  data_ = new char[size_];
  for (uint32_t i = 0; i < size_; ++i) {
    data_[i] = data[i];
  }
}

str::str(const char * data)
{
  init(data);
}

str::str(const string & str)
{
  init(str.c_str());
}

str::str(const str & str)
{
  init(str.data_);
}

str & str::operator=(const char * data)
{
  init(data);
  return *this;
}

str & str::operator=(const string & data)
{
  init(data.c_str());
  return *this;
}

str & str::operator=(const str & data)
{
  init(data.data_);
  return *this;
}

str::~str()
{
  delete data_;
}
