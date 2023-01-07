#pragma once

#include <memory>
#include <string>
#include "./iterator/vector_iterator.hpp"
#include "./iterator/reverse_iterator.hpp"
#include "./utils.hpp"

namespace ft
{
template < class T >
class vector {
public:
	typedef std::allocator<T> 							allocator_type;
	typedef T											value_type;
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

protected:
	allocator_type		static_allocator;
	pointer					start_;
	pointer					finish_;
	pointer					end_of_storage_;

public:

/* =================				Constructors				================= */

	vector() : start_(0), finish_(0), end_of_storage_(0) { }
	vector(size_type n, const T& value = T()) {
	start_ = static_allocator.allocate(n);
	std::uninitialized_fill_n(start_, n, value);
	finish_ = start_ + n;
	end_of_storage_ = finish_;
	}

	vector(const vector<T>& x) {
	start_ = static_allocator.allocate(x.size());
	finish_ = _copy_(x.begin().base(), start_, x.size()); 
	end_of_storage_ = finish_;
	}

	vector(const_iterator first, const_iterator last) {
	size_type n = 0;
	n = ft::distance(first, last);
	start_ = static_allocator.allocate(n);
	finish_ = _copy_(first.base(), start_, n);
	end_of_storage_ = start_ + n;
	}
	//enable if is integral input iterator constructor?

	~vector()
	{
		destroy_range(begin(), end(), &finish_);
		static_allocator.deallocate(&(*start_), capacity());
	}

/* =================		 Member Functions		   ================= */

	void assign(size_type count, const T& value)
	{
		clear();
		insert(begin(), count, value);
	}

	template< class InputIt >
	void assign( InputIt first, InputIt last, typename ft::enable_if<!is_integral<InputIt>::value, bool>::type = true)
	{
		clear();
		insert(begin(), first, last);
	}

	allocator_type get_allocator() const { return (static_allocator); } //or static_allocator::allocator_type ?
/* =================		   Element Access			   ================= */
	reference at(size_type pos)
	{
		if (pos >= size() || pos < 0)
			throw std::out_of_range("vetor"); //change to:std::string ret = "vector::_M_range_check: __n (which is" + pos << ") >= this->size() (which is " << size() << ")";? 
		return *(begin() + pos);
	}
	const_reference at(size_type pos) const
	{
		if (pos >= size() || pos < 0)
			throw std::out_of_range("vector");
		return *(begin() + pos);
	}
	reference		operator[](size_type pos)		{ return *(begin() + pos); }
	const_reference	operator[](size_type pos) const	{ return *(begin() + pos); }
	reference		front()							{ return *begin(); }
	const_reference	front() const					{ return *begin(); }
	reference		back()							{ return *(end() - 1); }
	const_reference	back() const					{ return *(end() - 1); }
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
	size_type	max_size() const	{ return static_allocator.max_size(); }
	size_type	capacity() const	{ return size_type(end_of_storage_ - start_ ); }
	bool		empty() const		{ return start_ == finish_; } //or static allocator.empty()?
/* =================				Capacity Modulator	  ================= */
	void	reserve(size_type new_cap)
	{
		if (new_cap > max_size())
			throw std::length_error("vector");
		if (capacity() < new_cap)
			_grow_(new_cap);
	}
/* =================			   Modifiers			  ================= */
	private:
	void destroy_range(iterator first, iterator last, pointer* finish)
	{
		difference_type n = ft::distance(first, last);
		for (iterator it = first; last < end(); ++it, ++last)
		{
			*it = *last;
		}
		for (difference_type diff = 1; n >= diff ; diff++)
		{
			static_allocator.destroy((*finish) - diff);
		}
		*finish -= n;
	}

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

	iterator erase( iterator pos )
	{
		for (iterator it = pos; it < end() - 1; ++it)
		{
			*it = *(it + 1);
		}
		static_allocator.destroy(finish_ - 1);
		if (pos != end())
			finish_ -= 1;
		return (pos);
	}

	iterator erase( iterator first, iterator last )
	{
		if (first == last)
			return(first);
		destroy_range(first, last, &finish_);
		return (first);
	}

	void clear() { erase(iterator(start_), iterator(finish_)); }

	void resize(size_type count, T value = T())
	{
		size_type size = this->size();
		if (count > size)
		{
			reserve(count);
			for (int i = 0; i < (count - size); ++i)
				push_back(value);
		}
		else if (count < size)
			erase(begin() + count, end());
	}

	iterator insert( const_iterator pos, size_type count, const T& value )
	{
		if (count == 0) //make sure that pos is in vector. pos can be end() let distance throw error?
			return (pos);

		difference_type c_pos = ft::distance(begin(), pos);
		size_type		n_size = size() + count;
		size_type		alloc_size = capacity() > size() + n_size ? capacity() : size() + n_size;
		pointer			n_start = static_allocator.allocate(alloc_size);

		_copy_destroy_(start_, n_start, c_pos);
		for (size_type temp_pos = c_pos; temp_pos < c_pos + count; ++temp_pos)
			static_allocator.construct(n_start + temp_pos, value);
		_copy_destroy_(start_ + c_pos, n_start + c_pos + count, n_size - count - c_pos);
		clear();
		_set_class_vars_(n_start, n_start + n_size, n_start + alloc_size);
		return (begin() + c_pos);
	}

	iterator insert( const_iterator pos, const T& value )
	{
		return(insert(pos, 1, value));
	}

	template< class InputIt >
	iterator insert(const_iterator pos, InputIt first, InputIt last, typename ft::enable_if<!ft::is_integral<InputIt>::value, bool>::type = true)
	{
		difference_type count = ft::distance(first, last);

		if (count == 0) //make sure that pos is in vector. pos can be end() let distance throw error?
			return (pos);

		difference_type c_pos = ft::distance(begin(), pos);
		size_type		n_size = size() + count;
		pointer			n_start = static_allocator.allocate(size() + n_size);

		_copy_destroy_(start_, n_start, c_pos);
		for (size_type dist = c_pos; dist < c_pos + count; ++dist, ++first)
			static_allocator.construct(n_start + dist, *first);
		_copy_destroy_(start_ + c_pos, n_start + c_pos + count, n_size - count - c_pos);
		clear();
		_set_class_vars_(n_start, n_start + n_size, n_start + n_size);
		return (begin() + c_pos);
	}

	void swap(vector& other)
	{
		std::swap(start_, other.start_);
		std::swap(finish_, other.finish_);
		std::swap(end_of_storage_, other.end_of_storage_);
		std::swap(static_allocator, other.static_allocator);
	}

/* =================			 Helper Functions			  ================= */
	void _copy_destroy_(pointer from, pointer to, size_type count)
	{
		for (size_type dist = 0; dist < count ; ++dist)
		{
			static_allocator.construct(to + dist, *(from + dist));
			static_allocator.destroy(from + dist);
		}
	}

	pointer _copy_(pointer from, pointer to, size_type count)
	{
		size_type dist = 0;
		for (; dist < count ; ++dist)
		{
			static_allocator.construct(to + dist, *(from + dist));
		}
		return(to + dist);
	}
	
	void _set_class_vars_(pointer n_start, pointer n_finish, pointer n_end_of_storage)
	{
		if (start_ != NULL)
			static_allocator.deallocate(start_, capacity());
		start_ = n_start;
		finish_ = n_finish;
		end_of_storage_ = n_end_of_storage;
	}

	void _insert_reserve_(size_type count)
	{
		reserve(size() + count);
		// if (count > 1 && size() > 0)
		// 	reserve(capacity() * 2);
		// else if (c)
		// reserve(count > 1 ? capacity() * 2 : size() + count); //reserve double capacity?
	}

	inline void _grow_(size_t new_cap)
	{
		pointer	new_start = static_allocator.allocate(new_cap);;
		if (start_ + new_cap <= end_of_storage_)
			return ;
		int i = 0;
		for(iterator it = begin(); it != end(); ++it, i++)
		{
			static_allocator.construct(new_start + i, *it);
			static_allocator.destroy(start_ + i);
		}
		if (start_ != 0)
			static_allocator.deallocate(start_, end_of_storage_ - start_);
		start_ = new_start;
		finish_ = start_ + i;
		end_of_storage_ = start_ + new_cap;
	}

	inline void	_allocate_n_(size_type n)
	{
		start_ = static_allocator.allocate(n);
		finish_ = start_;
		end_of_storage_ = start_ + n;
	}

};
}