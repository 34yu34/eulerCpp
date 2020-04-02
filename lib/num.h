#include <cstdint>
#include "array.h"
#include <cmath>

typedef unsigned __int128 uint128_t;

class num
{
private:
    Array<uint64_t> _data;
    bool _neg;

    static const uint64_t BASE = 10000000000000000000U;
    static const uint32_t BASE_LENGTH = 19; // 10^19 gives BASE

    void initialize_string(std::string n);
    void initialize_int(const int & n);
    void initialize_num(const num & n);

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

    std::string to_s();

};