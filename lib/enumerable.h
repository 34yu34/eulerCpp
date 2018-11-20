#ifndef ENUMERABLE_H
#define ENUMERABLE_H

#include "iterator.h"
#include "number.h"
#include "iostream"

template<class T>
class Enumerable
{
private:
    bool _forward;
    unsigned int _size;
    Iterator<T> * _end;
    Iterator<T> * _begin;
    Iterator<T> * _curr;

    static void addFactor(T & num, const T & val, bool & isFirst, Enumerable<Number::Factor<T>>& en);

public:
    template <class> friend class Enumerable;
    Enumerable() {_begin = new Iterator<T>(); _end = _begin->pNext(); _curr = _begin; _size = 1; _forward = true;}
    Enumerable(const T & start , const T & end , const int & bounce = 1);
    Enumerable(const T * data, int size);
    ~Enumerable(){;}

    static Enumerable<T> fibonacci(int time);
    static Enumerable<T> fibonacciUntil(T until);
    static Enumerable<Number::Factor<T>> factors(T num);

    Iterator<T> & begin() {return *_begin;}
    Iterator<T> * pBegin() {return _begin;}
    Iterator<T> & end() {return *_end;}
    Iterator<T> * pEnd() {return _end;}

    void reset(T val = T()) { _begin = new Iterator<T>(val);_end = _begin->pNext(); _size = 1; _forward = true;}
    void push(T val = T()) { _forward ? _end->add(val, false) : _begin->pLast()->add(val);}
    T next() {return _forward ? *(*_curr++) : *(*_curr--);}
    unsigned int size() {return _size;}

    Enumerable<T> & map(T (* fptr)(T val));
    template <class U> Enumerable<U> map(U (* fptr)(T val));
    Enumerable<T> & select(bool (* fptr)(T val));
    void each(void (* fptr)(T val));
    T inject(T (* fptr)(T sum, T val));
    template <class U> U inject(U & obj, U & (* fptr)(U & obj, T val));
    T sum();
};

template <class T>
Enumerable<T>::Enumerable(const T & start, const T & end, const int & bounce) {
    _begin = new Iterator<T>(start);
    _end = _begin->pNext();
    _size = 1;
    _forward = true;
    for (T i = start + bounce; i != end; i += bounce) {
        _end->add(i, false);
        _size++;
    }
    _curr = _begin;
}

template <class T>
Enumerable<T>::Enumerable(const T * data, int size) {
    _begin = new Iterator<T>(data[0]);
    _end = _begin->pNext();
    _size = 1;
    _forward = true;
    for (int i = 1; i < size; i++) {
        _end->add(data[i], false);
        _size++;
    }
}

template <class T>
Enumerable<T> Enumerable<T>::fibonacci(int time) {
    Enumerable<T> en = Enumerable<T>();
    en._begin = new Iterator<T>(T() + 1);
    en._end = en._begin->pNext();
    en._end->add((T() + 1), false);
    en._size = 2;
    for (int i = 1; i < time-1; i++) {
        en._end->add(*(*(en._end)-1) + *(*(en._end)-2), false);
        en._size++;
    }
    return en;
}

template <class T>
Enumerable<T> Enumerable<T>::fibonacciUntil(T until) {
    Enumerable<T> en = Enumerable<T>();
    en._begin = new Iterator<T>(T() + 1);
    en._end = en._begin->pNext();
    en._end->add((T() + 1), false);
    en._size = 2;
    while (*(en._end->last())< until) {
        en._end->add(*(*(en._end)-1) + *(*(en._end)-2), false);
        en._size++;
    }
    return en;
}

template <class T>
Enumerable<Number::Factor<T>> Enumerable<T>::factors(T num) {
    T max = num;
    Enumerable<Number::Factor<T>> en = Enumerable<Number::Factor<T>>();
    bool isFirst = true;
    en._size = 0;
    addFactor(max, T() + 2, isFirst, en);
    addFactor(max, T() + 3, isFirst, en);
    addFactor(max, T() + 5, isFirst, en);
    addFactor(max, T() + 7, isFirst, en);
    for (T i = 12; i * i < num; i+= 6) {
        addFactor(max, i-1, isFirst, en);
        addFactor(max, i+1, isFirst, en);
    }
    return en;
}

template <class T>
void Enumerable<T>::addFactor(T & num, const T & val, bool & isFirst, Enumerable<Number::Factor<T>> & en) {
    if (num % val == 0 && num != 0) {
        Number::Factor<T> fact;
        fact.repetition = 0;
        fact.factor = val;
        while (num % val == 0 && num != 0) { 
            num /= val;
            fact.repetition += 1;
        }
        if (isFirst) {
            *(en._begin) = fact;
            en._end = en._begin->pNext();
            isFirst = false;
        } else {
            en._end->add(fact, false);
        }
        en._size++;
    }
}

template <class T>
Enumerable<T> & Enumerable<T>::map(T (* fptr)(T val)) {
    for (auto it = _begin; it != _end; it =  it->pNext()) {
        it->operate(fptr);
    }
    return *this;
}

template <class T>
template <class U>
Enumerable<U> Enumerable<T>::map(U (* fptr)(T val)) {
    Enumerable<U> en;
    en.reset(fptr(*(*(_begin))));
    for (Iterator<T> * it = _begin->pNext(); it != _end; it =  it->pNext()) {
        en.push(fptr(*(*(it))));
    }
    return en;
}

template <class T>
Enumerable<T> & Enumerable<T>::select(bool (* fptr)(T val)) {
    Iterator<T> * it = _begin;
    bool begining = true;
    while (it != _end) {
        if (!fptr(*(*it))) {
            it = it->unlink();
            _size--;
            if (begining) {
                _begin = it;
            }
        } else {
            begining = false;
            it = it->pNext();
        };
    }
    return *this;
}

template <class T>
T Enumerable<T>::inject(T (* fptr)(T sum, T val)) {
    Iterator<T> * it = _begin->pNext();
    T sum = *(*_begin);
    while (it != _end) {
        sum = fptr(sum, *(*it));
        it = it->pNext();
    }
    return sum;
}

template <class T>
T Enumerable<T>::sum() {
    return this->inject([](T sum, T val){return sum + val;});
}

template <class T>
void Enumerable<T>::each(void (* fptr)(T val)) {
    Iterator<T> * it = _begin;
    while (it != _end) {
        fptr(*(*it));
        it = it->pNext();
    }
}

#endif // !ENUMERABLE_H