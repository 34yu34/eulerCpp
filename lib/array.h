#pragma once

#define HEAVY true 

#include <cstdint>

#if HEAVY
#include <iostream>
#include <stdio.h>
#include <exception>
#include <initializer_list>
#endif



template <class T>
class Array
{
private:
    T *data_;
    uint64_t size_;
    uint64_t max_size_;

public:
    static const uint64_t BASIC_SIZE = 20;

public:
    ////////////////////////////////////////////////////////////////////////////////
    // Constructor
    ////////////////////////////////////////////////////////////////////////////////
    Array()
        : size_(0), max_size_(BASIC_SIZE)
    {
        data_ = new T[BASIC_SIZE];
    }

    Array(uint64_t allocated_size)
        : size_(0), max_size_(allocated_size)
    {
        data_ = new T[allocated_size];
    }

    Array(uint64_t allocated_size, const T &default_value)
        : size_(allocated_size), max_size_(allocated_size)
    {
        data_ = new T[allocated_size];
        for (uint64_t i = 0; i < allocated_size; ++i)
        {
            data_[i] = T(default_value);
        }
    }

    Array(uint64_t size, T *data)
        : size_(size), max_size_(size)
    {
        data_ = new T[size];
        for (uint64_t i = 0; i < size; ++i)
        {
            data_[i] = data[i];
        }
    }

    Array(const Array &arr)
        : size_(arr.size_), max_size_(arr.max_size_)
    {
        data_ = new T[arr.max_size_];
        for (uint64_t i = 0; i < arr.size_; ++i)
        {
            data_[i] = arr.data_[i];
        }
    }

    Array &operator=(const Array &arr)
    {
        size_ = arr.size_;
        max_size_ = arr.max_size_;
        delete[] data_;
        data_ = new T[max_size_];
        for (uint64_t i = 0; i < arr.size_; ++i)
        {
            data_[i] = arr.data_[i];
        }
        return *this;
    }

#if HEAVY
    Array(std::initializer_list<T> list)
        : size_(0), max_size_(BASIC_SIZE)
    {
        data_ = new T[max_size_];
        for (T item : list)
        {
            push(item);
        }
    }
#endif

    ~Array()
    {
        delete[] data_;
    }
    ////////////////////////////////////////////////////////////////////////////////
    // Getters
    ////////////////////////////////////////////////////////////////////////////////

    uint64_t size() const
    {
        return size_;
    }

    T &operator[](uint64_t index)
    {
        check_index(index);
        return data_[index];
    }

    T operator[](uint64_t index) const
    {
        check_index(index);
        return data_[index];
    }
    /*
     * remove the last element and returns it
    */
    T pop()
    {
        return data_[--size_];
    }

    /*
     * copy all the data in the pointer;
    */
    T * data() const
    {
        T *data = new T[size_];
        for (uint64_t i = 0; i < size_; ++i)
        {
            data[i] = data_[i];
        }
        return data;
    }

    T * begin()
    {
        return data_;
    }

    T * end()
    {
        return data_ + size_ ;
    }

    ////////////////////////////////////////////////////////////////////////////////
    // Adders
    ////////////////////////////////////////////////////////////////////////////////

    template <typename... Ts>
    Array &push(const T &val, Ts... other_vals)
    {
        check_addable();
        data_[size_++] = T(val);
        return push(other_vals...);
    }

    Array &push()
    {
        return *this;
    }

    Array &operator<<(T val)
    {
        return push(val);
    }

    Array &operator+=(const Array &arr)
    {
        check_addable(arr.size_);
        for (uint64_t i = 0; i < arr.size_; ++i)
        {
            push(arr[i]);
        }
        return *this;
    }

    Array operator+(Array arr)
    {
        return (arr += *this);
    }

    ////////////////////////////////////////////////////////////////////////////////
    // manipulator
    ////////////////////////////////////////////////////////////////////////////////
#if HEAVY
    // apply a <f> function to all elements of the array and return an array containing all the result in the same order.
    template <class U, class Function>
    Array<U> map(Function f) const
    {
        Array<U> new_data = Array<U>();
        for (uint64_t i = 0; i < size_; ++i)
        {
            new_data << f(data_[i]);
        }
        return new_data;
    }

    /*
     * return a new array containing all the elements cast in <U> type
     * usage : a.cast<int>() // return array cast in int
    */
    template <class U>
    Array<U> cast() const
    {
        Array<U> new_data;
        for (uint64_t i = 0; i < size_; ++i)
        {
            new_data << (U)data_[i];
        }
        return new_data;
    }

    // Create a new array containing all the elements that returned true when pass to <f> function
    template <class Function>
    Array<T> select(Function f) const
    {
        Array<T> new_data = Array<T>();
        for (uint64_t i = 0; i < size_; ++i)
        {
            if (f(data_[i]))
            {
                new_data << data_[i];
            }
        }
        return new_data;
    }

    // run a function <f> on each elememts of the array
    template <class Function>
    Array<T> &each(Function f)
    {
        for (uint64_t i = 0; i < size_; i++)
        {
            f(data_[i]);
        }
        return *this;
    }

    // apply <f> function to <start_val> and first element of the array. it then collect the result and recall <f> function on the result and the second element until the end of the array
    template <class U, class Function>
    U inject(U start_val, Function f) const
    {
        U adder = start_val;
        for (uint64_t i = 0; i < size_; i++)
        {
            adder = f(adder, data_[i]);
        }
        return adder;
    }

    // return the sum of all the array elements starting with a null value
    T sum()
    {
        return inject(T(), [](T a, T b) { return a + b; });
    }

    // return the biggest value of the array
    T max()
    {
        return inject(data_[0], [](T a, T b){ return a > b ? a : b;});
    }

        // return the smallest value of the array
    T min()
    {
        return inject(data_[0], [](T a, T b){ return a > b ? b : a;});
    }
#endif
    // remove all element from the array
    void empty()
    {
        delete data_;
        data_ = new T[BASIC_SIZE];
        size_ = 0;
        max_size_ = BASIC_SIZE;
    }

    ////////////////////////////////////////////////////////////////////////////////
    // Generator
    ////////////////////////////////////////////////////////////////////////////////
#if HEAVY
    // generate an array containing all value from <initial_val> to <end_val> by <step> jumps
    static Array<T> range(T initial_val, T end_val, T step = 1)
    {
        Array<T> res; 
        if (step > 0)
        {
            if (initial_val > end_val) {throw std::out_of_range("Empty Range");}
            
            res = Array<T>((int)((end_val - initial_val) / step) + 1);
            for (T i = initial_val; i < end_val; i += step)
            {
                res << i;
            }
        }
        else if(step < 0)
        {
            if (initial_val < end_val) {throw std::out_of_range("Empty Range");}
            
            res = Array<T>((int)((initial_val - end_val) / (step * -1) ) + 1);
            for (T i = initial_val; i > end_val; i += step)
            {
                res << i;
            }
        } 
        else
        {
            throw std::out_of_range("null step value");
        }
        
        return res;
    }
    // generate an array containing all integer from 0 to <end_val>
    static Array<T> range(T end_val)
    {
        return range((T)0, end_val);
    }
#endif 

    ////////////////////////////////////////////////////////////////////////////////
    // informations
    ////////////////////////////////////////////////////////////////////////////////
#if HEAVY
    friend std ::ostream &operator<<(std::ostream &o, const Array &en)
    {
        o << "[";
        if (en.size_ > 0)
        {
            for (uint64_t i = 0; i < en.size_ - 1; ++i)
            {
                o << en.data_[i];
                o << ", ";
            }
            o << en.data_[en.size_ - 1];
        }
        o << "]";
        return o;
    }
#endif

    // return true in a boolean operation if the enumerable is not empty
    explicit operator bool() const
    {
        return size_ > 0;
    }

    template <class Function>
    bool contains(const T &val)
    {
        for (uint64_t i = 0; i < size_; ++i)
        {
            if (val == data_[i])
            {
                return true;
            }
        }
        return false;
    }

    ////////////////////////////////////////////////////////////////////////////////
    // check function
    ////////////////////////////////////////////////////////////////////////////////
private:
    void check_index(uint64_t index = 0) const
    {
        if (index >= size_)
        {
#if HEAVY
            throw std::out_of_range("index doesn't exist");
#else
            throw "index doesn't exist";
#endif
        }
    }

    void check_addable(uint64_t amount = 1)
    {
        if (size_ + amount >= max_size_)
        {
            addsize(amount);
        }
    }

    void addsize(uint64_t amount)
    {
        check_not_max(amount);
        amount = amount < size_ ? size_ : amount; // make sure that the amount is at least doubled
        uint64_t new_size = max_size_ + amount < max_size_ ? UINT32_MAX : max_size_ + amount;

        T *new_data = new T[new_size];
        max_size_ = new_size;
        for (uint64_t i = 0; i < size_; ++i)
        {
            new_data[i] = data_[i];
        }
        data_ = new_data;
    }

    void check_not_max(uint64_t amount) const
    {
        if ((uint64_t)size_ + (uint64_t)amount > UINT32_MAX)
        {
#if HEAVY
            throw std::out_of_range("Array is too full");
#else
            throw "Array is too full";
#endif
        }
    }
};
