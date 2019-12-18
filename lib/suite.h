#pragma once

#include "array.h"


template <class Function, class T>
class Suite
{
////////////////////////////////////////////////////////////////////////////////
// Data
////////////////////////////////////////////////////////////////////////////////
private:
    const Function fct_;
    T init_val_;
    T curr_val_;

////////////////////////////////////////////////////////////////////////////////
// constructor
////////////////////////////////////////////////////////////////////////////////
private:
    Suite()
    : fct_(), init_val_(), curr_val_()
    {}


public:
    
    Suite(const Function & fct, const T & init_val)
    : fct_(fct), init_val_(init_val), curr_val_(init_val)
    { }
    ~Suite();

////////////////////////////////////////////////////////////////////////////////
// Data Manipulation
////////////////////////////////////////////////////////////////////////////////
public:

    T next()
    {
        T return_val = curr_val_;
        curr_val_ = fct_(curr_val_);
        return return_val;
    }

    Suite & reset()
    {
        curr_val_ = init_val_;
        return *this;
    }

    Array<T> next(uint32_t times)
    {
        Array<T> result(times);
        for (uint32_t i = 0; i < times; ++i)
        {
            result << next();
        }
        return result;
    } 

    T first()
    {
        return init_val_;
    }

    Array<T> first(uint32_t times)
    {
        T temp_curr = init_val_;
        Array<T> result(times);
        result << temp_curr;
        for (uint32_t i = 0; i < times-1; ++i)
        {
            temp_curr = fct_(temp_curr);
            result << temp_curr;
        }
        return result;
    }
};