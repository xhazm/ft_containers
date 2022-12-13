#pragma once

#include <memory>
#include "./iterator/vector_iterator.hpp"

namespace ft
{
template < class T >
class vector {
public:
    typedef std::allocator<T> 								vector_allocator;
    typedef T											value_type;
    typedef vector_iterator< T >						iterator;
    typedef vector_iterator< T >						const_iterator;
    typedef typename vector_allocator::pointer			pointer;
    typedef typename vector_allocator::const_pointer	const_pointer;
    typedef typename vector_allocator::reference		reference;
    typedef typename vector_allocator::const_reference	const_reference;
    typedef typename vector_allocator::size_type		size_type;
    typedef typename vector_allocator::difference_type	difference_type;
    // typedef reverse_iterator<const_iterator, value_type, const_reference, 
    //                          difference_type>  const_reverse_iterator;
    // typedef reverse_iterator<iterator, value_type, reference, difference_type>
    //     reverse_iterator;

protected:
	vector_allocator		static_allocator;
	pointer					start_;
	pointer					finish_;
	pointer					end_of_storage_;

public:

/* =================                Constructors                ================= */

	vector() : start_(0), finish_(0), end_of_storage_(0) { }
	vector(size_type n, const T& value = T()) {
	start_ = static_allocator.allocate(n);
	uninitialized_fill_n(start_, n, value);
	finish_ = start_ + n;
	end_of_storage_ = finish_;
	}
	vector(const vector<T>& x) {
	start_ = static_allocator.allocate(x.end() - x.begin());
	finish_ = uninitialized_copy(x.begin(), x.end(), start_);
	end_of_storage_ = finish_;
	}

	vector(const_iterator first, const_iterator last) {
	size_type n = 0;
	distance(first, last, n);
	start_ = static_allocator.allocate(n);
	finish_ = uninitialized_copy(first, last, start_);
	end_of_storage_ = finish_;
	}

	~vector()
	{
		destroy_range(begin(), end(), &finish_);
		static_allocator.deallocate(&(*start_), capacity());
	}
/* =================           Element Access               ================= */
	reference at(size_type pos)
	{
		if (pos >= size() || pos < 0)
			throw std::out_of_range ("vector");
		return *(begin() + pos);
	}
	const_reference at(size_type pos) const
	{
		if (pos >= size() || pos < 0)
			throw std::out_of_range ("vector");
		return *(begin() + pos);
	}
	reference		operator[](size_type pos)		{ return *(begin() + pos); }
	const_reference	operator[](size_type pos) const	{ return *(begin() + pos); }
	reference		front()							{ return *begin(); }
	const_reference front() const					{ return *begin(); }
	reference		back()							{ return *(end() - 1); }
	const_reference back() const					{ return *(end() - 1); }
/* =================                Iterators               ================= */
	iterator				begin()			{ return iterator(start_); }
	const_iterator			begin() const	{ return iterator(start_); }
	iterator				end()			{ return iterator(finish_); }
	const_iterator			end() const		{ return iterator(finish_); }
	// reverse_iterator		rbegin()		{ return reverse_iterator(end()); }
	// const_reverse_iterator	rbegin() const	{ return const_reverse_iterator(end()); }
	// reverse_iterator		rend()			{ return reverse_iterator(begin()); }
	// const_reverse_iterator	rend() const	{ return const_reverse_iterator(begin()); }
/* =================                Capacity                ================= */
	size_type	size() const		{ return size_type(finish_ - start_); }
	size_type	max_size() const	{ return static_allocator.max_size(); }
	size_type	capacity() const	{ return size_type(end_of_storage_ - start_ ); }
	bool		empty() const		{ return start_ == finish_; } //or static allocator.empty()?
/* =================                Capacity Modulator      ================= */
	void	reserve(size_type new_cap)
	{
		if (capacity() <= new_cap)
			grow_(new_cap);
	}
/* =================               Modifiers              ================= */
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
			if (capacity() != 0)
				grow_(capacity() * 2);
			else
				grow_(1);
		}
		static_allocator.construct(finish_, data);
		finish_++;
		std::cout << "data: " << data << "\tsize: " << size() << "\tcapacity: " << capacity() <<std::endl;
	}

	iterator erase( iterator pos )
	{
		for (iterator it = pos; it < end() - 1; it++)
		{
			*it = *(it + 1);
		}
		static_allocator.destroy(end() - 1);
		if (pos != end())
			finish_ -= 1;
		return (pos);
	}

	iterator erase( iterator first, iterator last )
	{
		destroy_range(first, last, &finish_);
		return (first);
	}

	void clear() { erase(begin(), back()); }

	void grow_(size_t new_cap)
	{
		iterator old_begin = begin();
		iterator old_end = end();
		pointer old_start = start_;
		pointer old_eos = end_of_storage_;
		pointer old_finish = finish_;
		if (start_ + new_cap <= end_of_storage_)
			return ;
		_allocate_n_(new_cap);
		if (new_cap != 1)
		{
			for(iterator it = old_begin; it != old_end; ++it)
			{
				static_allocator.construct(finish_, *it);
				finish_++;
			}
			destroy_range(old_begin, old_end, &old_finish);
			static_allocator.deallocate(old_start, old_eos - old_start); //wrong? original implementation only gives start_
		}
	}

	inline void	_allocate_n_(size_type n)
	{
		start_ = static_allocator.allocate(n);
		finish_ = start_;
		end_of_storage_ = start_ + n;
	}
};
}