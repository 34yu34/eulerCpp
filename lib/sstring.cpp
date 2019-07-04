#include "sstring.h"

void Sstring::init(const char * data)
{    
    size_ = (uint32_t)strlen(data);
    data_ = new char[size_];
    for (uint32_t i = 0; i < size_; ++i)
    {
       data_[i] = data[i];
    }
}

Sstring::Sstring(const char * data)
{
    init(data);
}

Sstring::Sstring(const string & str)
{
    init(str.c_str());
}

Sstring::Sstring(const Sstring & str)
{
    init(str.data_);
}

Sstring & Sstring::operator=(const char * data)
{
    init(data);
    return *this;
}

Sstring & Sstring::operator=(const string & data)
{
    init(data.c_str());
    return *this;
}

Sstring & Sstring::operator=(const Sstring & data)
{
    init(data.data_);
    return *this;
}

Sstring::~Sstring()
{
    delete data_;
}