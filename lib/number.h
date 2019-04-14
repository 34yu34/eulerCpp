#pragma once

#include "iostream"
#include "enumerable.h"
#include "bignum.h"

namespace Number
{
    template<class T>
    struct Factor
    {
        T factor;
        int repetition;
    };

    template <class T> Enumerable<Factor<T> *> getFactors(T  num); 
    template <class T> void addFactor(Factor<T> * fact, Enumerable<Factor<T> *> & vect);
    template <class T> Factor<T> * findFactor(const T & factor, T & num);
    
    template <class T> bool isPalindrome(const T & num);
    template <class T> T max(const T & num1,const T & num2) {return num1 > num2 ? num1 : num2;}
    template <class T> T min(const T & num1,const T & num2) {return num1 < num2 ? num1 : num2;}
    template <class T> void print(const T & val) {std::cout << val << std::endl;}
    template <class T> T pow(const T & val1,const T & val2) {T res = 1;for (T i = 0; i < val2; i++){ res *= val1;} return res;}
}

template <class T>
bool Number::isPalindrome(const T & num) {
        unsigned int size = 0;
        int top = 1;
        int bot = 1;
        while ( num / (top) > 0) {size += 1; top *= 10;}
        top /= 10;
        for(unsigned int i = 0; i < size / 2; i++) {
            if ((num / top) % 10 != ((num / bot) % 10)) {
                return false;
            }
            top /= 10; 
            bot *= 10;
        }
        return true;
}

template <class T>
Enumerable<Number::Factor<T> *> Number::getFactors(T num)
{
    Enumerable<Number::Factor<T> *> solutions;
    addFactor(findFactor(T() + 2, num), solutions);
    addFactor(findFactor(T() + 3, num), solutions);
    addFactor(findFactor(T() + 5, num), solutions);
    addFactor(findFactor(T() + 7, num), solutions);
    for (T i = 12; i < num; i += 6)
    {
        addFactor(findFactor(i + 1, num), solutions);
        addFactor(findFactor(i - 1, num), solutions);
    }
    if (num != 1)
    {
        Number::Factor<T> * fact = new Number::Factor<T>();
        fact->factor = num;
        fact->repetition = 1;
        solutions << fact;
    }
    return solutions;
}

template<class T>
void Number::addFactor(Number::Factor<T> * fact, Enumerable<Number::Factor<T> *> & vect)
{
    if (fact != nullptr)
    {
        vect << fact;
    }
}

template <class T>
Number::Factor<T> * Number::findFactor(const T & factor, T & num)
{
    Number::Factor<T> * fact = new Number::Factor<T>();
    fact->factor = factor;
    fact->repetition = 0;
    while (num % factor == 0)
    {
        num /= factor;
        fact->repetition += 1;
    }
    if (fact->repetition == 0){
        return nullptr;
    }
    return fact;
} 