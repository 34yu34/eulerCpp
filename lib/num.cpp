#include "num.h"
#include "dev.h"

num::num()
{
    _data = Array<uint64_t>();
    _neg = false;
}

num::num(const num &n)
{
    _data = Array<uint64_t>(n._data.size(), n._data.data());
    _neg = n._neg;
}

num::~num() {}

num &num::operator=(const std::string &n)
{
    _data = Array<uint64_t>();
    for (uint64_t i = 0; i < n.size(); i += BASE_LENGTH)
    {
        uint64_t num = 0;
        uint64_t initial_loop_val = n.size() - 1 - i;
        for (uint64_t j = initial_loop_val; (initial_loop_val - j <  BASE_LENGTH) && (j+1 > 0); --j)
        {
            num +=  ((uint64_t)n[j] - 48) * (uint64_t)pow(10, initial_loop_val - j);
        }
        _data << num;
    }
    return *this;
}

num &num::operator=(const int &n)
{
    _data = Array<uint64_t>();
    uint64_t top = n / BASE;
    uint64_t bot = n % BASE;
    _data << bot << top;
    return *this;
};

num &num::operator=(const num &n) {
    _data = Array<uint64_t>(n._data.size(), n._data.data());
    _neg = n._neg;
    return *this;
};

num & num::operator+=(const num & n)
{
  uint64_t max_size = n._data.size() > _data.size() ? n._data.size() : _data.size();
  uint64_t rem = 0;
  for(uint64_t i = 0; i < max_size; ++i)
  {
      if(n._data.size() > i && _data.size() > i)
      {
        uint128_t add = n._data[i] + _data[i];
        _data[i] = add % BASE + rem;
        rem = add / BASE;
      }
      else if (n._data.size() > max_size)
      {
        _data << (n._data[i] + rem);
        rem = 0;
      }
      else if (_data.size() > max_size)
      {
        _data[i] = _data[i] + rem;
        rem = 0;
      }
  }
  return *this;
}

std::string num::to_s()
{
    std::string rep = "";
    for (uint64_t i = 0; i < _data.size(); ++i)
    {
      std::string str_val = std::to_string(_data[i]);
      if (str_val.size() < BASE_LENGTH && i != (_data.size()-1))
      {
        for (uint64_t j = 0; str_val.size() < BASE_LENGTH; ++j) { str_val += "0"; }
      }
      rep = str_val + rep;
    }
    return rep;
}
