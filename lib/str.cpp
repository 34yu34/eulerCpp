#include "str.h"

str::str()
{
  string base = "";
  init(base.c_str());
}

void str::init(const char * data)
{
  data_ = Enumerable<char>();
  for (uint32_t i = 0; data[i] != '\0'; ++i) {
    data_ << data[i];
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
  data_ = str.data_;
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
  data_ = str.data_;
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
  for (str_it it = text.data_.begin(); it != text.data_.end(); ++it)
  {
    data_ << *it;
  }
  return *this;
}

str str::operator+(const str & text) const
{
  str result = *this;
  return (result += text);
}

ostream & operator<<(ostream & o, const str & text)
{
  for (str_it it = text.data_.begin(); it != text.data_.end(); ++it)
  {
    o << *it;
  }
  return o;
}