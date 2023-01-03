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

	reverse_iterator() { current_ = iterator_type(); }
	explicit reverse_iterator(iterator_type x) : current_(x) {}
	Iter base() const { return current_; }
};
}