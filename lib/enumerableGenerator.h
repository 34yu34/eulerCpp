#include "vector"
#include "enumerable.h"
#include "number.h"

namespace EnumerableGenerator
{
    template <class T> Enumerable<Number::Factor<T> *> Factor(const T & max);

    template <class T> Enumerable<T> Fibbonaci(const int & number);
    template <class T> Enumerable<T> FibbonaciUntil(const T & number);
}

template <class T>
Enumerable<Number::Factor<T> *> EnumerableGenerator::Factor(const T & max)
{
    std::vector<Number::Factor<T> *> vect = Number::getFactors(max);
    return Enumerable<Number::Factor<T> *>(vect.data(), vect.size());
}

template <class T>
Enumerable<T> EnumerableGenerator::Fibbonaci(const int & number)
{
    if (number < 3) {
        return Enumerable<T>({T() + 1, T() + 1}, 2);
    }
    T * data = new T[number];
    data[0] = 1;
    data[1] = 1;
    for (int i = 2; i < number; ++i) {
        data[i] = data[i-1] + data[i-2];
    }
    return Enumerable<T>(data, number);
}

template <class T>
Enumerable<T> EnumerableGenerator::FibbonaciUntil(const T & until)
{
    Enumerable<T> en;
    en.push(T() + 1).push(T() + 1);
    T a = 1;
    T b = 1;
    while (b < until)
    {
        T temp = b;
        b = a + b;
        a = temp;
        en.push(b);
    } 
    return en;
}