#ifndef NUMBER_H
#define NUMBER_H

#include "iostream"
#include "bignum.h"

namespace Number
{
    template<class T>
    struct Factor
    {
        T factor;
        int repetition;
    };
    
    template <class T> bool isPalindrome(T num);
    template <class T> T max(T num1, T num2) {return num1 > num2 ? num1 : num2;}
    template <class T> void print(T val) {std::cout << val << std::endl;}
    template <class T> T pow(T val1, T val2) {T res = 1;for (T i = 0; i < val2; i++){ res *= val1;} return res;}
} // Number

template <class T>
bool Number::isPalindrome(T num) {
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

#endif // !NUMBER_H