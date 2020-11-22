#include <cstdint>
#include "array.h"
#include <cmath>
#include <iostream>

typedef unsigned __int128 uint128_t;

class num
{
private:
    Array<int32_t> _data;

    static const unsigned int BASE = 1000000000;
    static const unsigned short BASE_LENGTH = 9; // 10^9 gives BASE

    void initialize_string(std::string n);
    void initialize_int(const int & n);
    void initialize_num(const num & n);
    bool operate(const num & n, bool (*fptr)(int, int)) const;

public: 
    num();
    num(const num &n);
    num(const int &i);
    num(const std::string &n);
    ~num();

    num & operator=(const std::string &n);
    num & operator=(const int & n);
    num & operator=(const num & n);

    num & operator+=(const num & n);
    num & operator+=(const int & n);
    num operator+(const num & n) const;
    num operator+(const int & n) const;
    friend num operator+(const int & n1, num n2);
    num & operator++();
    num operator++(int);

    num & operator-=(const num & n);

    bool operator==(const num & n) const;
    bool operator==(const int & n) const;
    friend bool operator==(const int & n1, const num & i);
    bool operator>(const num & n) const;
    bool operator>(const int & n) const;
    friend bool operator>(const int & n1, const num & i);
    bool operator<(const num & n) const;
    bool operator<(const int & n) const;
    friend bool operator<(const int &n1, const num & i);

    std::string to_s() const;
    friend std::ostream &operator<<(std::ostream &o, const num &n);
};
