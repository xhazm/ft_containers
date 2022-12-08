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
        pointer current_;

/* =================                Constructors                ================= */
    public:

        vector_iterator(pointer ptr = NULL) : current_(ptr) {}

        vector_iterator(const vector_iterator &other) { *this = other; }

/* =================                Destructor                  ================= */
        ~vector_iterator() {}

/* =================                Accessor                    ================= */
        pointer base( void ) const { return (current_); }

/* =================                Operator Overloads                    ================= */
        operator        vector_iterator< const T >( void ) const { return (vector_iterator< const T >(current_)); }

        vector_iterator  &operator=( const vector_iterator &other ) { current_ = other.base(); return (*this); }
        reference        operator*( void ) const { return *current_; }
        pointer          operator->() const {return &(*current_);}
        vector_iterator& operator++() {++current_; return *this;}
        vector_iterator& operator++(int) {vector_iterator tmp(current_), ++current_; return tmp;}
        vector_iterator& operator--() {--current_; return *this;}
        vector_iterator& operator--(int) {vector_iterator tmp(current_), --current_; return tmp;}
        vector_iterator  operator+ (difference_type __n) const {return vector_iterator(current_ + __n);}
        vector_iterator  operator+=(difference_type __n) const {current_ += n; return this;}
        vector_iterator  operator- (difference_type __n) const {return vector_iterator(current_ + __n);}
        vector_iterator  operator-=(difference_type __n) const {current_ -= n; return this;}
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