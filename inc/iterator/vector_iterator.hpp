#pragma once

#include "iterator.hpp"

namespace ft {

template < class T >
class vector_iterator
{
   private:
        typedef typename ft::iterator<ft::random_access_iterator_tag, T >       iterator;

    public:
        // typedef Iter                                                            iterator_type;
        typedef typename iterator::value_type                                   value_type;
        typedef typename iterator::difference_type                              difference_type;
        typedef typename iterator::reference                                    reference;
        typedef typename iterator::pointer                                      pointer;
        typedef typename iterator::iterator_category                            iterator_category;

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
        operator        vector_iterator< const T >( void ) const    { return (vector_iterator< const T >(current_)); }

        vector_iterator  &operator=( const vector_iterator &other ) { current_ = other.base(); return (*this); }
        reference        operator*( void ) const                    { return *current_; }
        pointer          operator->() const                         { return &(*current_); }
        vector_iterator& operator++()                               { ++current_; return *this; }
        vector_iterator& operator++(int)                            { vector_iterator tmp(current_); ++current_; return tmp; }
        vector_iterator& operator--()                               { --current_; return *this; }
        vector_iterator& operator--(int)                            { vector_iterator tmp(current_); --current_; return tmp; }
        vector_iterator  operator+ (difference_type __n) const      { return vector_iterator(current_ + __n); }
        vector_iterator  operator+=(difference_type __n)            { current_ += __n; return this; }
        vector_iterator  operator- (difference_type __n) const      { return vector_iterator(current_ - __n); }
        vector_iterator  operator-=(difference_type __n)            { current_ -= __n; return this; }
        reference        operator[](difference_type __n) const      { return *(*this + __n); }
};

/* =================                Non Member Operators                    ================= */
template < typename T >
bool operator==(const vector_iterator<T>& lhs, const vector_iterator<T>& rhs) { return lhs.base() == rhs.base(); }
template < typename T >
bool operator!=(const vector_iterator<T>& lhs, const vector_iterator<T>& rhs) { return !(lhs == rhs); }
template < typename T >
bool operator> (const vector_iterator<T>& lhs, const vector_iterator<T>& rhs) { return lhs.base() > rhs.base(); }
template < typename T >
bool operator>=(const vector_iterator<T>& lhs, const vector_iterator<T>& rhs) { return !(lhs < rhs); }
template < typename T >
bool operator< (const vector_iterator<T>& lhs, const vector_iterator<T>& rhs) { return lhs.base() < rhs.base(); }
template < typename T >
bool operator<=(const vector_iterator<T>& lhs, const vector_iterator<T>& rhs) { return !(lhs > rhs); }


template< typename T >
vector_iterator< T >    operator+( const typename vector_iterator< T >::difference_type& i,
                                    const vector_iterator< T >& iter )
{
    return (vector_iterator< T >(iter.base() + i));
}

template< typename T >
vector_iterator< T >    operator-( const typename vector_iterator< T >::difference_type& i,
                                    const vector_iterator< T >& iter )
{
    return (vector_iterator< T >(iter.base() - i));
}

template< typename T >
typename vector_iterator< T >::difference_type  operator+( const vector_iterator< T >& lhs,
                                                            const vector_iterator< T >& rhs )
{
    return (lhs.base() + rhs.base());
}

template< typename T >
typename vector_iterator< T >::difference_type  operator-( const vector_iterator< T >& lhs,
                                                            const vector_iterator< T >& rhs )
{
    return (lhs.base() - rhs.base());
}

template< typename T1, typename T2 >
typename vector_iterator< T1 >::difference_type operator+( const vector_iterator< T1 >& lhs,
                                                            const vector_iterator< T2 >& rhs )
{
    return (lhs.base() + rhs.base());
}

template< typename T1, typename T2 >
typename vector_iterator< T1 >::difference_type operator-( const vector_iterator< T1 >& lhs,
                                                            const vector_iterator< T2 >& rhs )
{
    return (lhs.base() - rhs.base());
}

}