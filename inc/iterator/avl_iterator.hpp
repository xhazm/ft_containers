#pragma once

#include "iterator.hpp"
#include "../pair.hpp"
#include  "../avl_node.hpp"

namespace ft {

template < class T >
class avl_iterator
{
   private:
        typedef typename ft::iterator<ft::bidirectional_iterator_tag, T >       iterator;

    public:
        // typedef Iter                                                            iterator_type;
        typedef typename iterator::value_type                                   value_type;
        typedef typename iterator::difference_type                              difference_type;
        typedef typename iterator::reference                                    reference;
        typedef typename iterator::pointer                                      pointer;
        typedef typename iterator::iterator_category                            iterator_category;

        typedef typename ft::avl_node<T>::pointer                              node_pointer;            

    private:
        node_pointer current_;

/* =================                Constructors                ================= */
    public:

        avl_iterator(node_pointer& ptr = NULL) : current_(ptr) {}

        avl_iterator(const avl_iterator &other) : current_(other.base()) {}

/* =================                Destructor                  ================= */
        ~avl_iterator() {}

/* =================                Accessor                    ================= */
        node_pointer base( void ) const { return (current_); }

/* =================                Operator Overloads                    ================= */
        operator        avl_iterator< const T >( void ) const    { return (avl_iterator< const T >(current_)); }

        avl_iterator  &operator=( const avl_iterator &other ) { current_ = other.base(); return (*this); }
        reference        operator*( void ) const                    { return *current_; }
        node_pointer          operator->() const                         { return &(*current_); }
        avl_iterator& operator++()                               { ++current_; return *this; }
        avl_iterator  operator++(int)                            { avl_iterator tmp(current_); ++current_; return tmp; }
        avl_iterator& operator--()                               { --current_; return *this; }
        avl_iterator  operator--(int)                            { avl_iterator tmp(current_); --current_; return tmp; }
        avl_iterator  operator+ (difference_type __n) const      { return avl_iterator(current_ + __n); }
        avl_iterator& operator+=(difference_type __n)            { current_ += __n; return *this; }
        avl_iterator  operator- (difference_type __n) const      { return avl_iterator(current_ - __n); }
        avl_iterator& operator-=(difference_type __n)            { current_ -= __n; return *this; }
        reference        operator[](difference_type __n) const      { return *(*this + __n); }
};

/* =================                Non Member Operators                    ================= */
template < typename T >
bool operator==(const avl_iterator<T>& lhs, const avl_iterator<T>& rhs) { return lhs.base() == rhs.base(); }
template < typename T >
bool operator!=(const avl_iterator<T>& lhs, const avl_iterator<T>& rhs) { return !(lhs == rhs); }
template < typename T >
bool operator> (const avl_iterator<T>& lhs, const avl_iterator<T>& rhs) { return lhs.base() > rhs.base(); }
template < typename T >
bool operator>=(const avl_iterator<T>& lhs, const avl_iterator<T>& rhs) { return !(lhs < rhs); }
template < typename T >
bool operator< (const avl_iterator<T>& lhs, const avl_iterator<T>& rhs) { return lhs.base() < rhs.base(); }
template < typename T >
bool operator<=(const avl_iterator<T>& lhs, const avl_iterator<T>& rhs) { return !(lhs > rhs); }


template< typename T >
avl_iterator< T >    operator+( const typename avl_iterator< T >::difference_type& i,
                                    const avl_iterator< T >& iter )
{
    return (avl_iterator< T >(iter.base() + i));
}

template< typename T >
avl_iterator< T >    operator-( const typename avl_iterator< T >::difference_type& i,
                                    const avl_iterator< T >& iter )
{
    return (avl_iterator< T >(iter.base() - i));
}

template< typename T >
typename avl_iterator< T >::difference_type  operator+( const avl_iterator< T >& lhs,
                                                            const avl_iterator< T >& rhs )
{
    return (lhs.base() + rhs.base());
}

template< typename T >
typename avl_iterator< T >::difference_type  operator-( const avl_iterator< T >& lhs,
                                                            const avl_iterator< T >& rhs )
{
    return (lhs.base() - rhs.base());
}

template< typename T1, typename T2 >
typename avl_iterator< T1 >::difference_type operator+( const avl_iterator< T1 >& lhs,
                                                            const avl_iterator< T2 >& rhs )
{
    return (lhs.base() + rhs.base());
}

template< typename T1, typename T2 >
typename avl_iterator< T1 >::difference_type operator-( const avl_iterator< T1 >& lhs,
                                                            const avl_iterator< T2 >& rhs )
{
    return (lhs.base() - rhs.base());
}

}