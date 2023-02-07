#pragma once

#include <memory>
#include <string>
#include <iostream>
#include "./iterator/vector_iterator.hpp"
#include "./iterator/iterator.hpp"
#include "./iterator/reverse_iterator.hpp"
#include "./utils.hpp"

namespace ft
{
template < class T, class Allocator = std::allocator<T> >
class vector {
public:
	typedef T											value_type;
	typedef	Allocator									allocator_type;
	typedef ft::vector_iterator< value_type >			iterator;
	typedef ft::vector_iterator< value_type >			const_iterator;
	typedef typename allocator_type::pointer			pointer;
	typedef typename allocator_type::const_pointer		const_pointer;
	typedef typename allocator_type::reference			reference;
	typedef typename allocator_type::const_reference	const_reference;
	typedef typename allocator_type::size_type			size_type;
	typedef typename allocator_type::difference_type	difference_type;
	typedef typename ft::reverse_iterator<iterator>  	reverse_iterator;
	typedef typename ft::reverse_iterator<const_iterator> const_reverse_iterator;

private:
	pointer					start_;
	pointer					finish_;
	pointer					end_of_storage_;
	allocator_type			static_allocator;

public:

/* =================				Constructors				================= */

	vector() : start_(NULL), finish_(NULL), end_of_storage_(NULL) {}

	explicit vector(const Allocator& alloc)
        : start_(NULL), finish_(NULL), end_of_storage_(NULL), static_allocator(alloc) {}

	explicit vector(size_type count, const T& value = T(),
						const Allocator& alloc = Allocator())
		: start_(NULL), finish_(NULL), end_of_storage_(NULL), static_allocator(alloc)
	{
		assign(count, value);
	}

	template < class InputIt >
	vector(InputIt first, InputIt last, const Allocator& alloc = Allocator(), typename ft::enable_if<!ft::is_integral<InputIt>::value, bool>::type = true)
		: start_(NULL), finish_(NULL), end_of_storage_(NULL), static_allocator(alloc)
	{
		assign(first, last);
	}
	//enable if is integral input iterator constructor?

	vector(const vector& other) : start_(NULL), finish_(NULL), end_of_storage_(NULL), static_allocator(Allocator())
	{ 
		*this = other;
	}

	~vector()
	{
		clear();
		if (start_ != NULL)
		{
			static_allocator.deallocate(start_, capacity());
			start_ = NULL;
		}
	}

	vector  &operator=(const vector& other)
    {
        if (this != &other)
        {
			static_allocator = other.static_allocator;
			assign(other.begin(), other.end());
        }
        return (*this);
    }

/* =================		 Member Functions		   ================= */
	void assign(size_type count, const T& value)
	{
		clear();
		insert(begin(), count, value);
	}

	// Emptys vector, can be used with iterator tags: input | random
	template< class InputIt >
	void assign( InputIt first, InputIt last, typename ft::enable_if<!is_integral<InputIt>::value, bool>::type = true)
	{
		clear();
		finish_ = start_;
		_assign_range_(first, last, typename ft::iterator_traits<InputIt>::iterator_category());
	}

	allocator_type get_allocator() const { return static_allocator; } //or static_allocator::allocator_type ?
/* =================		   Element Access			   ================= */
	reference at(size_type pos)
	{
		if (pos >= size())
			throw std::out_of_range("vector"); //change to:std::string ret = "vector::_M_range_check: __n (which is" + pos << ") >= this->size() (which is " << size() << ")";? 
		return (*(begin() + pos));
	}
	const_reference at(size_type pos) const
	{
		if (pos >= size())
			throw std::out_of_range("vector");
		return (*(begin() + pos));
	}
	reference		operator[](size_type pos)		{ return *(begin() + pos); }
	const_reference	operator[](size_type pos) const	{ return *(begin() + pos); }
	reference		front()							{ return *begin(); }
	const_reference	front() const					{ return *begin(); }
	reference		back()							{ return *(end() - 1); }
	const_reference	back() const					{ return *(end() - 1); }
	T*  			data() 							{ return (start_); }
    const T*		data() const 					{ return (start_); }

/* =================				Iterators			   ================= */
	iterator				begin()			{ return iterator(start_); }
	const_iterator			begin() const	{ return const_iterator(start_); }
	iterator				end()			{ return iterator(finish_); }
	const_iterator			end() const		{ return const_iterator(finish_); }
	reverse_iterator		rbegin()		{ return reverse_iterator(end()); }
	const_reverse_iterator	rbegin() const	{ return const_reverse_iterator(end() ); }
	reverse_iterator		rend()			{ return reverse_iterator(begin() ); }
	const_reverse_iterator	rend() const	{ return const_reverse_iterator(begin() ); }
/* =================				Capacity				================= */
	size_type	size() const		{ return size_type(finish_ - start_); }
	size_type	max_size() const	{ 
		return std::min<size_type>(this->static_allocator.max_size(), std::numeric_limits<difference_type>::max()); }
	size_type	capacity() const	{ return size_type(end_of_storage_ - start_ ); }
	bool		empty() const		{ return start_ == finish_; } //or static allocator.empty()?
/* =================				Capacity Modulator	  ================= */
	void	reserve(size_type new_cap)
	{
		if (new_cap < capacity())
			return ;
		_grow_(new_cap);
	}
/* =================			   Modifiers			  ================= */
	public:
	void push_back(const T& data)
	{
		if (size() == capacity())
		{
			capacity() ? reserve(capacity() * 2) : reserve(1);
		}
		static_allocator.construct(finish_, data);
		finish_++;
	}

	void pop_back()
	{
		if (size() == 0)
			return ;
		erase(finish_ - 1);
	}

	iterator erase(iterator pos)
	{
		iterator tmp;
		iterator tmp_end = end();
		for (iterator it = pos, tmp = it + 1; it < tmp_end - 1; ++it, ++tmp)
		{
			*it = *tmp;
		}
		static_allocator.destroy(finish_ - 1);
		if (pos != tmp_end)
			finish_ -= 1;
		return (pos);
	}

	iterator erase(iterator first, iterator last )
	{
		difference_type n = ft::distance(first, last);
		for (iterator it = first; last < end(); ++it, ++last)
		{
			*it = *last;
		}
		for (difference_type diff = 1; n >= diff ; diff++)
		{
			static_allocator.destroy(finish_ - diff);
		}
		finish_ -= n;
		return (first);
	}

	void clear() { erase(begin(), end()); finish_ = start_; }

	void resize(size_type count, T value = T())
	{
		if (count > max_size())
			throw std::length_error("vector");
		if (count < size())
		{
			erase(start_ + count, finish_);
			finish_ = start_ + count;
		}
		else if (count > size())
		{
			if (count > capacity())
			{
				if (count <= capacity() * 2)
					reserve(capacity() * 2);
				else
					reserve(count);
			}
			for (size_t i = size(); i < count; i++)
			{
				static_allocator.construct(finish_, value);
				finish_++;
			}
		}
	}

	iterator insert(const_iterator pos, size_type count, const T& value)
	{
		if (count == 0) //make sure that pos is in vector. pos can be end() let distance throw error?
			return (pos);

		difference_type c_pos = ft::distance(begin(), pos);
		size_type		n_size = size() + count;
		size_type		old_end = size();

		resize(n_size);
		backward_copy(begin() + c_pos, begin() + old_end, begin() + c_pos + count);
		_assign_construct_(start_ + c_pos, value, count);
		return (begin() + c_pos);
	}

	iterator insert( const_iterator pos, const T& value )
	{
		return(insert(pos, 1, value));
	}

	template< class InputIt >
	iterator insert(const_iterator pos, InputIt first, InputIt last, typename ft::enable_if<!ft::is_integral<InputIt>::value, bool>::type = true)
	{
 		return (_insert_range_(pos, first, last, typename ft::iterator_traits<InputIt>::iterator_category()));
	}

	void swap(vector& other)
	{
		ft::swap(start_, other.start_);
		ft::swap(finish_, other.finish_);
		ft::swap(end_of_storage_, other.end_of_storage_);
		ft::swap(static_allocator, other.static_allocator);
	}

/* =================			 Helper Functions			  ================= */

private:
	void _copy_destroy_(pointer from, pointer to, size_type count)
	{
		for (size_type dist = 0; dist < count ; ++dist)
		{
			static_allocator.construct(to + dist, *(from + dist));
			static_allocator.destroy(from + dist);
		}
	}

	void _assign_construct_(pointer from, pointer to, size_type count)
	{
		size_type dist = 0;
		for ( ; dist < count && (to + dist) < finish_; ++dist)
		{
			*(to + dist) = *(from + dist);
		}
		for ( ; dist < count ; ++dist)
		{
			static_allocator.construct(to + dist, *(from + dist));
		}
	}

	void _assign_construct_(pointer to, const T& value, size_type count)
	{
		size_type dist = 0;
		for ( ; dist < count && (to + dist) < finish_; ++dist)
		{
			*(to + dist) = value;
		}
		for ( ; dist < count ; ++dist)
		{
			static_allocator.construct(to + dist, value);
			finish_ += 1;
		}
	}

	template< typename InputIterator >
	void _assign_construct_(InputIterator from, pointer to, size_type count, random_access_iterator_tag)
	{
		size_type dist = 0;
		for ( ; dist < count && (to + dist) < finish_; ++dist)
		{
			*(to + dist) = *(from + dist);
		}
		for ( ; dist < count ; ++dist)
		{
			static_allocator.construct(to + dist, *(from + dist));
			finish_ += 1;
		}
	}

	template< typename InputIterator >
	void _assign_construct_(InputIterator from, pointer to, size_type count, forward_iterator_tag)
	{
		size_type dist = 0;
		for ( ; dist < count && (to + dist) < finish_; ++dist, ++from)
		{
			*(to + dist) = *from;
		}
		for ( ; dist < count ; ++dist, ++from)
		{
			static_allocator.construct(to + dist, *from);
			finish_ += 1;
		}
	}

	template< typename InputIterator >
    void _assign_range_( InputIterator first, InputIterator last, input_iterator_tag )
    {
        for ( ; first != last; ++first)
            push_back(*first);
    }

    template< typename InputIterator >
    void _assign_range_( InputIterator first, InputIterator last, random_access_iterator_tag )
    {
		insert(begin(), first, last);
    }

	template< typename InputIterator >
    iterator _insert_range_( iterator pos, InputIterator first, InputIterator last, input_iterator_tag )
    {
		for ( ; first != last; ++first, ++pos)
            pos = insert(pos, 1, *first);
        return (pos);
    }

	template< typename InputIterator >
    iterator _insert_range_( iterator pos, InputIterator first, InputIterator last, forward_iterator_tag )
    {
		difference_type count = ft::distance(first, last);

		if (count == 0) //make sure that pos is in vector. pos can be end() let distance throw error?
			return (pos);

		difference_type c_pos = ft::distance(begin(), pos);
		size_type		n_size = size() + count;
		size_type		alloc_size = capacity() > n_size ? capacity() : n_size;

		if (capacity() >= n_size)
		{
			if (size())
				_assign_construct_(start_ + c_pos, start_ + c_pos + count, size());
			_assign_construct_(first, start_ + c_pos, count, typename iterator_traits< InputIterator >::iterator_category());
			_set_class_vars_(start_, start_ + n_size, start_ + alloc_size);
		}
		else
		{
			pointer n_start = _allocate_safe_(alloc_size);
			_copy_destroy_(start_, n_start, c_pos);
			for (difference_type dist = c_pos; dist < c_pos + count; ++dist, ++first)
				static_allocator.construct(n_start + dist, *first);
			_copy_destroy_(start_ + c_pos, n_start + c_pos + count, n_size - count - c_pos);
			if (start_ != NULL)
				static_allocator.deallocate(start_, capacity());
			_set_class_vars_(n_start, n_start + n_size, n_start + alloc_size);
		}
		return (begin() + c_pos);
    }

	template< typename InputIterator >
    iterator _insert_range_( iterator pos, InputIterator first, InputIterator last, random_access_iterator_tag )
    {
		difference_type count = ft::distance(first, last);

		if (count == 0) //make sure that pos is in vector. pos can be end() let distance throw error?
			return (pos);

		difference_type c_pos = ft::distance(begin(), pos);
		size_type		n_size = size() + count;
		size_type		alloc_size = capacity() > n_size ? capacity() : n_size;

		if (capacity() >= n_size)
		{
			if (size())
				_assign_construct_(start_ + c_pos, start_ + c_pos + count, count);
			_assign_construct_(first, start_ + c_pos, count, typename iterator_traits< InputIterator >::iterator_category());
			_set_class_vars_(start_, start_ + n_size, start_ + alloc_size);
		}
		else
		{
			pointer n_start = _allocate_safe_(alloc_size);
			_copy_destroy_(start_, n_start, c_pos);
			for (difference_type dist = c_pos; dist < c_pos + count; ++dist, ++first)
				static_allocator.construct(n_start + dist, *first);
			_copy_destroy_(start_ + c_pos, n_start + c_pos + count, n_size - count - c_pos);
			if (start_ != NULL)
				static_allocator.deallocate(start_, capacity());
			_set_class_vars_(n_start, n_start + n_size, n_start + alloc_size);
		}
		return (begin() + c_pos);
    }

	pointer _allocate_safe_(size_type new_cap)
	{
		if (new_cap > max_size())
			throw std::length_error("vector");
		return (static_allocator.allocate(new_cap));
	}
	
	void _set_class_vars_(pointer n_start, pointer n_finish, pointer n_end_of_storage)
	{
		start_ = n_start;
		finish_ = n_finish;
		end_of_storage_ = n_end_of_storage;
	}

	inline void _grow_(size_t new_cap)
	{
		if (start_ + new_cap <= end_of_storage_)
			return ;
		pointer	new_start = _allocate_safe_(new_cap);
		size_type i = 0;
		for(iterator it = begin(); it != end(); ++it, ++i)
		{
			static_allocator.construct(new_start + i, *it);
			static_allocator.destroy(start_ + i);
		}
		if (start_ != NULL)
			static_allocator.deallocate(start_, end_of_storage_ - start_);
		start_ = new_start;
		finish_ = start_ + i;
		end_of_storage_ = start_ + new_cap;
	}

	template<typename iterator, typename InputIterator>
		iterator	backward_copy(InputIterator first, InputIterator last, iterator position) {
			--first;
			--last;
			size_t n = ft::distance(first, last);
			position = position + n - 1;
			while (last != first)
			{
				*position = *last; 
				last--;
				position--;
			}
			return(position + n);
		}
};

/* =================    Non-member functions                ================= */

//  Checks if the contents of lhs and rhs are equal, that is, they have the same number of elements
//  and each element in lhs compares equal with the element in rhs at the same position.
template< class T, class Alloc >
bool operator==(const ft::vector<T,Alloc>& lhs, const ft::vector<T,Alloc>& rhs)
{
    return (lhs.size() == rhs.size()
        && ft::equal(lhs.begin(), lhs.end(), rhs.begin()));
}

// see operator ==
template< class T, class Alloc >
bool operator!=(const ft::vector<T,Alloc>& lhs, const ft::vector<T,Alloc>& rhs)
{
    return (!(lhs == rhs));
}

//  Compares the contents of lhs and rhs lexicographically.
//  The comparison is performed by a function equivalent to std::lexicographical_compare.
template< class T, class Alloc >
bool operator<(const ft::vector<T,Alloc>& lhs, const ft::vector<T,Alloc>& rhs)
{
    return (ft::lexicographical_compare(lhs.begin(), lhs.end(),
                                        rhs.begin(), rhs.end()));
}

// see operator <
template< class T, class Alloc >
bool operator<=(const ft::vector<T,Alloc>& lhs, const ft::vector<T,Alloc>& rhs)
{
    return (!(rhs < lhs));
}

// see operator <
template< class T, class Alloc >
bool operator>(const ft::vector<T,Alloc>& lhs, const ft::vector<T,Alloc>& rhs)
{
    return (rhs < lhs);
}

// see operator <
template< class T, class Alloc >
bool operator>=(const ft::vector<T,Alloc>& lhs, const ft::vector<T,Alloc>& rhs)
{
    return (!(lhs < rhs));
}
} // namespace ft
