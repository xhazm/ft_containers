#pragma once

#include "iterator.hpp"

namespace ft
{
template < class Iter >
class reverse_iterator
{
public:
	typedef Iter													iterator_type;
	typedef typename std::iterator_traits<Iter>::iterator_category	iterator_category;
	typedef typename std::iterator_traits<Iter>::value_type			value_type;
	typedef typename std::iterator_traits<Iter>::difference_type	difference_type;
	typedef typename std::iterator_traits<Iter>::pointer			pointer;
	typedef typename std::iterator_traits<Iter>::reference			reference;

private:
	iterator_type	current_;


public:
/* =================                Constructors                ================= */
	reverse_iterator(void) { current_ = iterator_type(); }
	explicit reverse_iterator(iterator_type it) : current_(it) {}

	template< class U >
    reverse_iterator(const reverse_iterator<U>& other) { *this = other; }

/* =================                Accessor                    ================= */
	Iter base() const { return current_; }

/* =================                Operator Overloads                    ================= */
    template < class U >
	reverse_iterator&   operator=(const reverse_iterator<U>& other)	{current_ = other.base(); return *this;}

	reference			operator*() const 							{iterator_type tmp = current_; return *(--tmp);}
	pointer             operator->() const							{return &(operator*());}
    reverse_iterator&   operator++()                              	{ --current_; return *this; }
    reverse_iterator    operator++(int)                           	{ reverse_iterator tmp(current_); --current_; return tmp; }
    reverse_iterator&   operator--()                              	{ ++current_; return *this; }
    reverse_iterator    operator--(int)                           	{ reverse_iterator tmp(current_); ++current_; return tmp; }
    reverse_iterator    operator+ (difference_type __n) const     	{ return reverse_iterator(current_ - __n); }
    reverse_iterator&   operator+=(difference_type __n)           	{ current_ -= __n; return *this; }
    reverse_iterator    operator- (difference_type __n) const     	{ return reverse_iterator(current_ + __n); }
    reverse_iterator&   operator-=(difference_type __n)           	{ current_ += __n; return *this; }
    reference           operator[](difference_type __n) const
	{       
		iterator_type	tmp = base();
		while (__n-- > 0) //do i need this?
			--tmp;
		--tmp;
		return (*tmp);
	}
};

/* =================                Non Member Operators                    ================= */
template < typename T >
bool operator==(const reverse_iterator<T>& lhs, const reverse_iterator<T>& rhs) { return lhs.base() == rhs.base(); }
template < typename T >
bool operator!=(const reverse_iterator<T>& lhs, const reverse_iterator<T>& rhs) { return !(lhs == rhs); }
template < typename T >
bool operator> (const reverse_iterator<T>& lhs, const reverse_iterator<T>& rhs) { return lhs.base() < rhs.base(); }
template < typename T >
bool operator>=(const reverse_iterator<T>& lhs, const reverse_iterator<T>& rhs) { return !(lhs < rhs); }
template < typename T >
bool operator< (const reverse_iterator<T>& lhs, const reverse_iterator<T>& rhs) { return lhs.base() > rhs.base(); }
template < typename T >
bool operator<=(const reverse_iterator<T>& lhs, const reverse_iterator<T>& rhs) { return !(lhs > rhs); }
template < typename T1, typename T2>
bool operator==(const reverse_iterator<T1>& lhs, const reverse_iterator<T2>& rhs) { return lhs.base() == rhs.base(); }
template < typename T1, typename T2>
bool operator!=(const reverse_iterator<T1>& lhs, const reverse_iterator<T2>& rhs) { return !(lhs == rhs); }
template < typename T1, typename T2>
bool operator> (const reverse_iterator<T1>& lhs, const reverse_iterator<T2>& rhs) { return lhs.base() < rhs.base(); }
template < typename T1, typename T2>
bool operator>=(const reverse_iterator<T1>& lhs, const reverse_iterator<T2>& rhs) { return !(lhs < rhs); }
template < typename T1, typename T2>
bool operator< (const reverse_iterator<T1>& lhs, const reverse_iterator<T2>& rhs) { return lhs.base() > rhs.base(); }
template < typename T1, typename T2>
bool operator<=(const reverse_iterator<T1>& lhs, const reverse_iterator<T2>& rhs) { return !(lhs > rhs); }


template< typename T >
reverse_iterator< T >    operator+( const typename reverse_iterator< T >::difference_type& i,
                                    const reverse_iterator< T >& iter )
{
    return (reverse_iterator< T >(iter.base() - i));
}

template< typename T >
reverse_iterator< T >    operator-( const typename reverse_iterator< T >::difference_type& i,
                                    const reverse_iterator< T >& iter )
{
    return (reverse_iterator< T >(iter.base() + i));
}

template< typename T >
typename reverse_iterator< T >::difference_type  operator+( const reverse_iterator< T >& lhs,
                                                            const reverse_iterator< T >& rhs )
{
    return (lhs.base() + rhs.base());
}

template< typename T >
typename reverse_iterator< T >::difference_type  operator-( const reverse_iterator< T >& lhs,
                                                            const reverse_iterator< T >& rhs )
{
    return (rhs.base() - lhs.base());
}

template< typename T1, typename T2 >
typename reverse_iterator< T1 >::difference_type operator+( const reverse_iterator< T1 >& lhs,
                                                            const reverse_iterator< T2 >& rhs )
{
    return (lhs.base() + rhs.base());
}

template< typename T1, typename T2 >
typename reverse_iterator< T1 >::difference_type operator-( const reverse_iterator< T1 >& lhs,
                                                            const reverse_iterator< T2 >& rhs )
{
    return (rhs.base() - lhs.base());
}

}