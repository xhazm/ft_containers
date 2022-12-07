#pragma once

#include "iterator.hpp"

namespace ft {

template < class T >
class vector_iterator
{
    public:
        typedef typename ft::iterator<ft::random_access_iterator_tag, T >::value_type           value_type;
        typedef typename ft::iterator<ft::random_access_iterator_tag, T >::difference_type      difference_type;
        typedef typename ft::iterator<ft::random_access_iterator_tag, T >::reference            reference;
        typedef typename ft::iterator<ft::random_access_iterator_tag, T >::pointer              pointer;
        typedef typename ft::iterator<ft::random_access_iterator_tag, T >::iterator_category    iterator_category;

    private:
        pointer _current;

/* =================                Constructors                ================= */
    public:

        vector_iterator(pointer ptr = NULL) : _current(ptr) {}

        vector_iterator(const vector_iterator &other) { *this = other; }

/* =================                Destructor                  ================= */
        ~vector_iterator() {}

/* =================                Accessor                    ================= */
        pointer base( void ) const { return (_current); }

/* =================                Operator Overloads                    ================= */
        operator        vector_iterator< const T >( void ) const { return (vector_iterator< const T >(_current)); }

        vector_iterator  &operator=( const vector_iterator &other ) { _current = other.base(); return (*this); }
        reference        operator*( void ) const { return *_current; }
        pointer          operator->() const {return &(*_current);}
        vector_iterator& operator++() {++_current; return *this;}
        vector_iterator& operator++(int) {vector_iterator tmp(_current), ++_current; return tmp;}
        vector_iterator& operator--() {--_current; return *this;}
        vector_iterator& operator--(int) {vector_iterator tmp(_current), --_current; return tmp;}
        vector_iterator  operator+ (difference_type __n) const {return vector_iterator(_current + __n);}
        vector_iterator  operator+=(difference_type __n) const {_current += n; return this;}
        vector_iterator  operator- (difference_type __n) const {return vector_iterator(_current + __n);}
        vector_iterator  operator-=(difference_type __n) const {_current -= n; return this;}
        reference        operator[](difference_type __n) const {return *(*this + __n);}

};
        // template < typename T >
        // bool operator==(const VectorIterator<T>& lhs, const VectorIterator<T>& rhs) { return lhs.base() == rhs.base(); }
        // bool operator<(const VectorIterator<T>& lhs, const VectorIterator<T>& rhs) { return lhs.base() < rhs.base(); }
        // bool operator!=(const VectorIterator<T>& lhs, const VectorIterator<T>& rhs) { return lhs.base() != rhs.base(); }
        // bool operator>(const VectorIterator<T>& lhs, const VectorIterator<T>& rhs) { return lhs.base() > rhs.base(); }
        // bool operator>=(const VectorIterator<T>& lhs, const VectorIterator<T>& rhs) { return lhs.base() >= rhs.base(); }
        // bool operator add(const VectorIterator<T>& lhs, const VectorIterator<T>& rhs) { return lhs.base() add rhs.base(); }
        // bool operator add(const VectorIterator<T>& lhs, const VectorIterator<T>& rhs) { return lhs.base() add rhs.base(); }
        // bool operator add(const VectorIterator<T>& lhs, const VectorIterator<T>& rhs) { return lhs.base() add rhs.base(); }
        // bool operator add(const VectorIterator<T>& lhs, const VectorIterator<T>& rhs) { return lhs.base() add rhs.base(); }
        // bool operator add(const VectorIterator<T>& lhs, const VectorIterator<T>& rhs) { return lhs.base() add rhs.base(); }



}