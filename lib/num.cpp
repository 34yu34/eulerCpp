#include "num.h"
#include "dev.h"

void num::initialize_string(std::string n)
{
  if (n[0] == *("-") || n[0] == *("+"))
  {
    _neg = n[0] == *("-");
    n = n.substr(1);
  } else
  {
    _neg = false;
  }
  _data = Array<uint64_t>();
  for (uint64_t i = 0; i < n.size(); i += BASE_LENGTH)
  {
    uint64_t num = 0;
    uint64_t initial_loop_val = n.size() - 1 - i;
    for (uint64_t j = initial_loop_val; (initial_loop_val - j < BASE_LENGTH) && (j + 1 > 0); --j)
    {
      num += ((uint64_t)n[j] - 48) * (uint64_t)pow(10, initial_loop_val - j);
    }
    _data << num;
  }
}

void num::initialize_int(const int &n)
{
  _data = Array<uint64_t>();
  _neg = n < 0;
  uint128_t abs = (uint128_t)(n > 0 ? n : -n);
  uint64_t top = (uint64_t)(abs / (uint128_t)BASE);
  uint64_t bot = uint64_t(abs % (uint128_t)BASE);
  _data << bot;
  if (top)
  {
    _data << top;
  }
}

bool num::operate(const num &num, bool (*fptr)(int, int)) const
{
  if (_data.size() == num._data.size())
  {
    for (uint128_t i = _data.size() - 1; i > UINT64_MAX; --i)
    {
      if (_data[i] != num._data[i])
      {
        return fptr(_data[i], num._data[i]);
      }
    }
    return fptr(1, 1);
  }
  else
  {
    return fptr(_data.size(), num._data.size());
  }
}

void num::initialize_num(const num &n)
{
  _data = Array<uint64_t>(n._data.size(), n._data.data());
  _neg = n._neg;
}

num::num() : _data(), _neg(false)
{
  _data << 0;
}

num::num(const num &n)
{
  initialize_num(n);
}

num::num(const std::string &n)
{
  initialize_string(n);
}

num::num(const int &n)
{
  initialize_int(n);
}

num::~num() {}

num &num::operator=(const std::string &n)
{
  initialize_string(n);
  return *this;
}

num &num::operator=(const int &n)
{
  initialize_int(n);
  return *this;
};

num &num::operator=(const num &n)
{
  initialize_num(n);
  return *this;
};

num &num::operator+=(const num &n)
{
  uint64_t max_size = n._data.size() > _data.size() ? n._data.size() : _data.size();
  uint128_t rem = 0;
  for (uint64_t i = 0; i < max_size; ++i)
  {
    if (n._data.size() > i && _data.size() > i)
    {
      uint128_t add = (uint128_t)n._data[i] + (uint128_t)_data[i];
      _data[i] = (uint64_t)((add + rem) % (uint128_t)BASE);
      rem = add / (uint128_t)BASE;
    }
    else if (n._data.size() > i)
    {
      _data << (n._data[i] + rem);
      rem = 0;
    }
    else if (_data.size() > i)
    {
      _data[i] = _data[i] + rem;
      rem = 0;
    }
  }
  return *this;
}

num &num::operator+=(const int &i)
{
  num n = i;
  return this->operator+=(n);
}

num num::operator+(const num & n) const
{
  num a = *this;
  return a += n; 
}

num num::operator+(const int &n) const
{
  num a = *this;
  return a += n;
}

num operator+(const int &n1, num n2)
{
  return n2 += n1;
}

num & num::operator++()
{
  return (this->operator+=(1));
}

num num::operator++(int)
{
  num res = *this;
  this->operator+=(1);
  return res;
}

num & num::operator-=(const num & n)
{
  return *this;
}

bool num::operator==(const num & n) const
{
  return operate(n, [](int n1, int n2)
  {
    return n1 == n2;
  });
}

bool num::operator==(const int & n) const
{
  num n2 = n;
  return n2 == *this;
}

bool operator==(const int & n1, const num & n2)
{
  return n2 == n1;
} 

std::string num::to_s() const
{

  std::string front = _neg ? "-" : "";
  std::string rep = "";
  for (uint64_t i = 0; i < _data.size(); ++i)
  {
    std::string str_val = std::to_string(_data[i]);
    if (str_val.size() < BASE_LENGTH && i != (_data.size() - 1))
    {
      for (uint64_t j = 0; str_val.size() < BASE_LENGTH; ++j)
      {
        str_val += "0";
      }
    }
    rep = str_val + rep;
  }
  return front + rep;
}

std::ostream &operator<<(std::ostream &o, const num &n)
{
  o << n.to_s();
  return o;
}
