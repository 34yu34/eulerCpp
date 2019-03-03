#ifndef ITERATOR_H
#define ITERATOR_H

#include "iostream"

template <class T>
class Iterator
{
public:
    inline Iterator(): _val((T *)nullptr), _next(nullptr), _last(nullptr) {;};
    inline Iterator(T val):_val(new T(val)) {setNext(new Iterator<T>()); setLast(new Iterator<T>());}
    inline Iterator(const Iterator<T> & it):_val(it._val), _next(it._next), _last(it._last) {;}
    inline void operator=(T val);
    inline void operator=(const Iterator<T> & it) {_val = it._val; _next = it._next; _last = it._last;}
    inline ~Iterator() {};

    inline Iterator & operator+(int time) const {Iterator<T> * n = this->_next;for (int i = 0; i< time-1; i++){n = n->_next;} return *n;}
    inline Iterator & operator-(int time) const {Iterator<T> * n = this->_last;for (int i = 0; i< time-1; i++){n = n->_last;} return *n;}

    inline bool operator==(const Iterator & it) {return (it._val == _val);}
    inline bool operator!=(const Iterator & it) {return !(this->operator==(it));}

    T & operator*() {return *_val;}

    Iterator<T> & next() const {return *_next;}
    Iterator<T> * pNext() const {return _next;}
    Iterator<T> & last() const {return *_last;}
    Iterator<T> * pLast() const {return _last;}
    Iterator<T> & setNext(Iterator<T> * next) {_next = next; next->_last = this; return *_next;}
    Iterator<T> & setLast(Iterator<T> * last) {_last = last; last->_next = this; return *_last;}
    Iterator<T> & add( T  val, bool forward = true);

    template <typename F> void operate(F function);
    template<class U, typename F> Iterator<U> * operate(F function);
    Iterator<T> * unlink(bool forward = true);

private:
    T * _val;  
    Iterator<T> * _next;
    Iterator<T> * _last;
};

template<class T>
inline void Iterator<T>::operator=(T val) 
{
    _val = new T(val);
    if (_next == nullptr) {
        setNext(new Iterator<T>());
    } else if (_last == nullptr) {
        setLast(new Iterator<T>());
    }
}

template<class T>
Iterator<T> & Iterator<T>::add(T  val, bool forward) {
    Iterator<T> * it = new Iterator<T>(val);
    Iterator<T> * n;
    if (forward) {
        n = _next;
        this->setNext(it);
        it->setNext(n);
    } else {
        n = _last;
        this->setLast(it);
        it->setLast(n);
    }
    return *it;
}

template<class T>
template<typename F>
void Iterator<T>::operate(F fptr){
    (*_val) = fptr(*_val);
}

template<class T>
template<class U, typename F>
Iterator<U> * Iterator<T>::operate(F fptr){    
    return new Iterator<U>(fptr(*_val));
}


template<class T>
Iterator<T> * Iterator<T>::unlink(bool forward) {
    _next->_last = _last; 
    _last->_next = _next; 
    return forward ? _next : _last;
}

#endif // !ITERATOR_H