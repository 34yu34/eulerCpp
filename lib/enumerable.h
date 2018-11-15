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
    
    Iterator<T> & begin() {return *_begin;}
    Iterator<T> * pBegin() {return _begin;}
    Iterator<T> & end() {return *_end;}
    Iterator<T> * pEnd() {return _end;}

    T next() {return _forward ? *(*_curr++) : *(*_curr--);}
    unsigned int size() {return _size;}

    Enumerable<T> & map(T (* fptr)(T val));
    Enumerable<T> & select(bool (* fptr)(T val));
};

template <class T>
Enumerable<T>::Enumerable(const T & start,const T & end, const int & bounce) {
    _begin = new Iterator<T>(start);
    _end = &_begin->next();
    _size = 1;
    _forward = true;
    for (T i = start + bounce; i != end; i += bounce) {
        _end->add(i, false);
        _size++;
    }
    _curr = _begin;
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
            if (begining) {
                _begin = it;
            }
        } else {
            begining = false;
            it = it->pNext();
        };
    }
    std::cout << "blah";
    return *this;
}

#endif // !ENUMERABLE_H