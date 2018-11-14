#ifndef ITERATOR_H
#define ITERATOR_H

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

    inline Iterator & operator++();
    inline Iterator & operator++(int);
    inline Iterator & operator--();
    inline Iterator & operator--(int);

    inline Iterator & operator+(int time) const {Iterator<T> * n = this;for (int i = 0; i< time; i++){n = n->_next;} return *n;}
    inline Iterator & operator+=(int time) {for (int i = 0; i< time; i++){this->operator++();} return *this;}
    inline Iterator & operator-(int time) const {Iterator<T> * n = this;for (int i = 0; i< time; i++){n = n->_last;} return *n;}
    inline Iterator & operator-=(int time) {for (int i = 0; i< time; i++){this->operator--();} return *this;}

    inline bool operator==(const Iterator & it) {return (it._val == _val);}
    inline bool operator!=(const Iterator & it) {return !(this->operator==(it));}

    T & operator*() {return *_val;}

    Iterator<T> & next() const {return *_next;}
    Iterator<T> & last() const {return *_last;}
    Iterator<T> & setNext(Iterator<T> * next) {_next = next; next->_last = this; return *_next;}
    Iterator<T> & setLast(Iterator<T> * last) {_last = last; last->_next = this; return *_last;}
    Iterator<T> & add( T  val, bool forward = true);

    void operate(T (* fptr)(T val));
    Iterator<T> & unlink(bool forward = true);

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
inline Iterator<T> & Iterator<T>::operator++() {
    Iterator * n = new Iterator(*this); 
    *this = *_next;
    _last = n; 
    return *this;
}

template<class T>
inline Iterator<T> & Iterator<T>::operator++(int) {
    this->operator++();
    return *(this->_last);
}

template<class T>
inline Iterator<T> & Iterator<T>::operator--(){
    Iterator * n = new Iterator(*this); 
    *this = *_last;
    _next = n; 
    return *this;
}

template<class T>
inline Iterator<T> & Iterator<T>::operator--(int) {
    this->operator--();
    return *(this->_next);
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
void Iterator<T>::operate(T (* fptr)(T val)){
    *_val = func(*_val);
}

template<class T>
Iterator<T> & Iterator<T>::unlink(bool forward) {
    _next->_last = _last; 
    _last->_next = _next; 
    *this = forward ? *_next : *_last;
    return *this;
}

#endif // !ITERATOR_H