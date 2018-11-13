#ifndef ITERATOR_H
#define ITERATOR_H

template <class T>
class Iterator
{
public:
    inline Iterator(): _val(*(T *)nullptr), _next(nullptr), _last(nullptr) {;};
    inline Iterator(const T & val):_val(val), _next(nullptr), _last(nullptr) {;}
    inline Iterator(const Iterator<T> & it):_val(it._val), _next(it._next), _last(it._last) {;}
    inline void operator=(const T & val) {_val = val;}
    inline void operator=(const Iterator<T> & it) {_val = it._val; _next = it._next; _last = it._last;}
    inline ~Iterator() {};

    inline Iterator & operator++() {this = _next;}
    Iterator & operator--() {this = _last;}
    T & operator*() {return _val;}

    Iterator<T> & getNext() const {return *_next;}
    Iterator<T> & getLast() const {return *_last;}
    Iterator<T> & setNext(Iterator<T> * next) {_next = next; next->_last = this; return *this;}
    Iterator<T> & setLast(Iterator<T> * last) {_last = last; last->_next = this; return *this;}
    
    
    void operate(void (* fptr)(T val));
    Iterator<T> * unlink() {_next->_last = _last; _last->_next = _next; return _next;}

private:
    T _val;  
    Iterator<T> * _next;
    Iterator<T> * _last;
};
#endif // !ITERATOR_H