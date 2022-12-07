#pragma once

#include <iterator>
#include <cstddef>															  //  for std::ptrdiff_t

namespace ft
{
/* =================	Iterator tags						================= */
// Typedefining the std::tags enables compatibility with std::containers.

typedef std::input_iterator_tag					input_iterator_tag;
typedef std::output_iterator_tag				output_iterator_tag;
typedef std::forward_iterator_tag				forward_iterator_tag;
typedef std::bidirectional_iterator_tag			bidirectional_iterator_tag;
typedef std::random_access_iterator_tag			random_access_iterator_tag;

/* =================	Iterator traits						================= */

template< typename Iterator >
struct iterator_traits
{
	typedef typename Iterator::difference_type		difference_type;
	typedef typename Iterator::value_type			value_type;
	typedef typename Iterator::pointer				pointer;
	typedef typename Iterator::reference			reference;
	typedef typename Iterator::iterator_category	iterator_category;
};

template< typename T >
struct iterator_traits< T* >
{
	typedef T								value_type;
	typedef T*								pointer;
	typedef T&								reference;
	typedef std::ptrdiff_t					difference_type;
	typedef ft::random_access_iterator_tag	iterator_category;
};

/* =================	Iterator base					   ================= */

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

}
