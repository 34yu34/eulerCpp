#include "array.h"

#include <cmath>

template <class T>
class Fibonacci
{
public:
    Array<T> _data;
    int index;

    Fibonacci() : _data()
    {
        _data << 1 << 1;
    }

    Fibonacci(const int n) : _data()
    {
        _data << 1 << 1;
        for (int i = 2; i < n; ++i)
        {
            _data << _data[i-2] + _data[i-1];
        }
    }

    template <class Function>
    Fibonacci(const Function f) : _data()
    {
        _data << 1 << 1;
        while ( f(_data.last()) )
        {
            _data << _data[_data.size() - 2] + _data.last();
        }
    }

    template <class Function>
    static Fibonacci until(Function f)
    {
        Fibonacci suit;
        while (!f(suit._data.last()))
        {
            suit._data << suit._data[suit._data.size() - 2] + suit._data.last();
        }
        return suit;
    }

    static T N(const uint64_t n)
    {
        static const float golden_number = 1.6180339887f;
        static const float inverse_golden = 1.0f - golden_number;
        return (T)(pow(golden_number, n)* pow(inverse_golden, n)) / (golden_number - inverse_golden);
    }

    Array<T> get_array() const
    {
        return _data;
    }
};