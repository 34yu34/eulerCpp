#pragma once

#include <iostream>
#include <stdint.h>
#include <exception>
#include <initializer_list>

template <class T>
class Array
{
private:
    T * data_;
    uint32_t size_;
    uint32_t max_size_;
    static const uint32_t BASIC_SIZE = 20; 
public:
////////////////////////////////////////////////////////////////////////////////
// Constructor
////////////////////////////////////////////////////////////////////////////////
    Array()
    : size_(0), max_size_(BASIC_SIZE)
    {
        data_ = new T[BASIC_SIZE];
    }

    Array(uint32_t allocated_size)
    : size_(0), max_size_(allocated_size)
    {
        data_ = new T[allocated_size];
    }

    Array(uint32_t size, T * data)
    : size_(size), max_size_(size)
    {
        data_ = new T [size];
        max_size_ = size;
        size = size;
    }

    Array(const Array & arr)
    : size_(arr.size_), max_size_(arr.max_size_) 
    {
        data_ = new T[arr.max_size_];
        for (uint32_t i = 0; i < arr.size_; ++i)
        {
            data_[i] = arr.data_[i];
        }
    }

    Array(std::initializer_list<T> list)
    {
        size_ = 0;
        max_size_ = BASIC_SIZE;
        data_ = new T[BASIC_SIZE];
        for (auto it = list.begin(); it != list.end(); ++it) {
                push(*it);
        }
    }

    template <class... Ts>
    Array & operator=(Ts ... vals)
    {
        size_ = 0;
        max_size_ = BASIC_SIZE;
        delete data_;
        data_ = new T[BASIC_SIZE];
        return push(vals...);
    }

    ~Array()
    {
        delete data_;
    }
////////////////////////////////////////////////////////////////////////////////
// Getters
////////////////////////////////////////////////////////////////////////////////

    uint32_t size() const
    {
        return size_;
    }

    T & operator[](uint32_t index)
    {
        check_index(index);
        return data_[index];
    }

    T operator[](uint32_t index) const
    {
        check_index(index);
        return data_[index];
    }

    T pop()
    {
        return data_[--size_];
    }

////////////////////////////////////////////////////////////////////////////////
// Adders
////////////////////////////////////////////////////////////////////////////////
    
    template <typename... Ts>
    Array & push(T val, Ts ... other_vals)
    {
        check_addable();
        data_[size_++] = val; 
        return push(other_vals...); 
        
    }

    Array & push()
    {
        return *this;
    }

    Array & operator<<(T val)
    {
        return push(val);
    }

    Array & operator+=(const Array & arr)
    {
        check_addable(arr.size_);
        for (uint32_t i = 0; i < arr.size_; ++i)
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

    template <class U, class Function>
    Array<U> map(Function f) const
    {
        Array<U> new_data = Array<U>();
        for (uint32_t i = 0; i < size_; ++i)
        {
            new_data << f(data_[i]);
        }
        return new_data;
    }

    template <class U, class Function>
    Array<U> cast() const
    {
        Array<U> new_data;
        for (uint32_t i = 0; i < size_; ++i)
        {
            new_data << (U)data_[i];
        }
        return new_data;
    }

    template <class Function>
    Array<T> select(Function f) const
    {
        Array<T> new_data = Array<T>();
        for (uint32_t i = 0; i < size_; ++i)
        {
            if (f(data_[i]))
            {
                new_data << data_[i]; 
            }
        }
        return new_data;
    }

    template <class Function>
    Array<T> & each(Function f)
    {
        for (uint32_t i = 0; i < size_; i++)
        {
            f(data_[i]);
        }
        return *this;
    }

    template <class U, class Function>
    U inject(U start_val, Function f) const
    {
        U adder = start_val;
        for (uint32_t i = 1; i < size_; i++)
        {
            adder = f(adder, data_[i]);
        }
        return adder;
    }

    T sum()
    {
        return inject(T(), [](T a, T b){return a + b;});
    }

    void empty()
    {
        delete data_;
        data_ = new T[BASIC_SIZE];
        size_ = 0;
        max_size_ = BASIC_SIZE;
    }

////////////////////////////////////////////////////////////////////////////////
// informations
////////////////////////////////////////////////////////////////////////////////
    
    friend std ::ostream & operator<<(std::ostream & o, const Array & en)
    {
        o << "[";
        if (en.size_ > 0) {
            for (uint32_t i = 0; i < en.size_-1; ++i) {
                o << en.data_[i];
                o << ", ";
            }
            o << en.data_[en.size_-1];
        }
        o << "]";
        return o;
    }

    // return true in a boolean operation if the enumerable is not empty
    explicit operator bool() const
    {
        return size_ > 0;
    }

    template <class Function>
    bool contains(const T & val)
    {
        for (uint32_t i = 0; i < size_; ++i)
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

    void check_index(uint32_t index = 0) const
    {
        if (index >= size_)
        {
            throw std::out_of_range("index doesn't exist");
        }
    }

    void check_addable(uint32_t amount = 1)
    {
        if (size_ + amount >= max_size_)
        {
            addsize(amount);
        }
    }

    void addsize(uint32_t amount)
    {
        check_not_max(amount);
        amount = amount < size_ ? size_ : amount; // make sure that the amount is at least doubled
        uint32_t new_size = max_size_ + amount < max_size_ ? UINT32_MAX : max_size_ + amount;        

        T * new_data = new T[new_size];
        max_size_ = new_size;
        for (uint32_t i = 0; i < size_; ++i)
        {
            new_data[i] = data_[i];
        }
        data_ = new_data;
    }

    void check_not_max(uint32_t amount) const
    {
        if ((uint64_t)size_ + (uint64_t)amount > UINT32_MAX)
        {
            throw std::out_of_range("Array is too full");
        }
    }
};