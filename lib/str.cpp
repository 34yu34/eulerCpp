#include "str.h"

str::str()
{
  string base = "";
  init(base.c_str());
}

void str::init(const char * data)
{
  data_.empty();
  uint32_t len = strlen(data);
  for (uint32_t i = 0; i < len; ++i) {
    data_ << data[i];
  }
}

void str::copy_data(const str & line)
{
  data_.empty();
  for (uint32_t i = 0; i < line.data_.size(); ++i)
  {
    data_ << line.data_[i];
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
  copy_data(str);
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

str & str::operator=(const str & str)
{
  copy_data(str);
  return *this;
}

str::~str()
{

}
////////////////////////////////////////////////////////////////////////////////
// getters
////////////////////////////////////////////////////////////////////////////////
uint32_t str::size() const
{
  return data_.size(); 
}

char & str::operator[](const uint32_t i)
{
  return data_[i];
}

////////////////////////////////////////////////////////////////////////////////
// operator
////////////////////////////////////////////////////////////////////////////////

str & str::operator+=(const str & text)
{
  for (uint32_t i = 0; i < text.data_.size(); ++i)
  {
    data_ << text.data_[i];
  }
  return *this;
}

str str::operator+(const str & text) const
{
  str result = *this;
  return (result += text);
}

str & str::operator-=(const str & str)
{
  return *this;
}

str & str::operator-=(const string & str)
{
  return *this;
}


str & str::operator-=(const char & c)
{
  return *this;
}


str str::operator-(str str) const
{
  return *this;
}

str str::operator<<(const str & str)
{
  return *this += str;
}


ostream & operator<<(ostream & o,const str & text)
{
  for (uint32_t i = 0; i < text.data_.size(); ++i)
  {
    o << text.data_[i];
  }
  return o;
}