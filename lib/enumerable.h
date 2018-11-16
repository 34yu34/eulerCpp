#ifndef ENUMERABLE_H
#define ENUMERABLE_H

#include "iterator.h"
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
public:
    Enumerable(const T & start = T(), const T & end = (T()+1), const int & bounce = 1);
    ~Enumerable(){;}

    static Enumerable<T> fibonacci(int time);
    static Enumerable<T> fibonacciUntil(T until);

    Iterator<T> & begin() {return *_begin;}
    Iterator<T> * pBegin() {return _begin;}
    Iterator<T> & end() {return *_end;}
    Iterator<T> * pEnd() {return _end;}

    T next() {return _forward ? *(*_curr++) : *(*_curr--);}
    unsigned int size() {return _size;}

    Enumerable<T> & map(T (* fptr)(T val));
    Enumerable<T> & select(bool (* fptr)(T val));
    void each(void (* fptr)(T val));
    T inject(T (* fptr)(T sum, T val));
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
Enumerable<T> Enumerable<T>::fibonacci(int time) {
    Enumerable<T> en = Enumerable<T>();
    en._begin = new Iterator<T>(T() + 1);
    en._end = en._begin->pNext();
    en._end->add((T() + 1), false);
    for (int i = 1; i < time-1; i++) {
        en._end->add(*(*(en._end)-1) + *(*(en._end)-2), false);
    }
    return en;
}

template <class T>
Enumerable<T> Enumerable<T>::fibonacciUntil(T until) {
    Enumerable<T> en = Enumerable<T>();
    en._begin = new Iterator<T>(T() + 1);
    en._end = en._begin->pNext();
    en._end->add((T() + 1), false);
    while (*(en._end->last())< until) {
        en._end->add(*(*(en._end)-1) + *(*(en._end)-2), false);
    }
    return en;
}

template <class T>
Enumerable<T> & Enumerable<T>::map(T (* fptr)(T val)) {
    for (auto it = _begin; it != _end; it =  it->pNext()) {
        it->operate(fptr);
    }
    return *this;
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