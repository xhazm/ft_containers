#pragma once

#include <iterator>
#include <cstddef>															  //  for std::ptrdiff_t

namespace ft
{
/* =================	Iterator tags						================= */

// Typedef std::iterator_tags as ft::iterator_tags.
typedef std::input_iterator_tag					input_iterator_tag;
typedef std::output_iterator_tag				output_iterator_tag;
typedef std::forward_iterator_tag				forward_iterator_tag;
typedef std::bidirectional_iterator_tag			bidirectional_iterator_tag;
typedef std::random_access_iterator_tag			random_access_iterator_tag;

/* =================	Iterator traits						================= */

// Used that given iterator can access traits without writing the iterator in front
template< typename Iterator >
struct iterator_traits
{
	typedef typename Iterator::value_type			value_type;
	typedef typename Iterator::pointer				pointer;
	typedef typename Iterator::reference			reference;
	typedef typename Iterator::difference_type		difference_type;
	typedef typename Iterator::iterator_category	iterator_category;
};

// Container conform variable naming
template< typename T >
struct iterator_traits< T* >
{
	typedef T								value_type;
	typedef T*								pointer;
	typedef T&								reference;
	typedef std::ptrdiff_t					difference_type;
	typedef ft::random_access_iterator_tag	iterator_category;
};

// Container conform const variable naming
template< typename T >
struct iterator_traits< const T* >
{
	typedef T								value_type;
	typedef const T*						pointer;
	typedef const T&						reference;
	typedef std::ptrdiff_t					difference_type;
	typedef ft::random_access_iterator_tag	iterator_category;
};

/* =================	Iterator base					   ================= */

// base class which has a default for most types
template< typename Category,
	typename T,
	typename Distance = std::ptrdiff_t,
	typename Pointer = T*,
	typename Reference = T&
>struct iterator
{
	typedef T			value_type;
	typedef Pointer		pointer;
	typedef Reference	reference;
	typedef Distance	difference_type;
	typedef Category	iterator_category;
};




// input_iterator_tag because most standard libs use it
template< typename InputIterator >
typename iterator_traits< InputIterator >::difference_type
_distance_helper( InputIterator first, InputIterator last, input_iterator_tag )
{
    typename iterator_traits< InputIterator >::difference_type dist = 0;

    for (; first != last; ++first)
    	++dist;
    return dist;
}


// random_access_iterator_tag for vector iterator
template< typename InputIterator >
typename iterator_traits< InputIterator >::difference_type
_distance_helper( InputIterator first, InputIterator last, random_access_iterator_tag ) 
{
    return last - first;
}

// distance helpers to get distance between iterators
template< typename InputIterator >
typename iterator_traits< InputIterator >::difference_type
distance( InputIterator first, InputIterator last )
{
    return _distance_helper(first, last, typename iterator_traits< InputIterator >::iterator_category());
}

}
