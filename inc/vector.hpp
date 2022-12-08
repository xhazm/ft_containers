#pragma once

#include <memory>

#define Allocator std::allocator

namespace ft
{
template < typename T >
class vector {
public:
    typedef Allocator<T> 						vector_allocator;
    typedef T									value_type;
    typedef vector_allocator::pointer			pointer;
    typedef vector_allocator::pointer			iterator;
    typedef vector_allocator::const_pointer		const_iterator;
    typedef vector_allocator::reference			reference;
    typedef vector_allocator::const_reference	const_reference;
    typedef vector_allocator::size_type			size_type;
    typedef vector_allocator::difference_type	difference_type;
    // typedef reverse_iterator<const_iterator, value_type, const_reference, 
    //                          difference_type>  const_reverse_iterator;
    // typedef reverse_iterator<iterator, value_type, reference, difference_type>
    //     reverse_iterator;

protected:
	static Allocator<T>	static_allocator;
	iterator			start_;
	iterator			finish_;
	iterator 			end_of_storage;

public:

/* =================                Constructors                ================= */

	vector() : start_(0), finish_(0), end_of_storage(0) {}
	vector(size_type n, const T& value = T()) {
	start_ = static_allocator.allocate(n);
	uninitialized_fill_n(start_, n, value);
	finish_ = start_ + n;
	end_of_storage = finish_;
	}
	vector(const vector<T>& x) {
	start_ = static_allocator.allocate(x.end() - x.begin());
	finish_ = uninitialized_copy(x.begin(), x.end(), start_);
	end_of_storage = finish_;
	}

	vector(const_iterator first, const_iterator last) {
	size_type n = 0;
	distance(first, last, n);
	start_ = static_allocator.allocate(n);
	finish_ = uninitialized_copy(first, last, start_);
	end_of_storage = finish_;
	}

	~vector()
	{
		destroy(start_, finish_);
		static_allocator.deallocate(start_, capacity());
	}
/* =================           Element Access               ================= */
	

/* =================                Capacity                ================= */
	size_type	size() const { return size_type(end() - begin()); }
	size_type	max_size() const { return static_allocator.max_size(); }
	size_type	capacity() const { return size_type(end_of_storage - begin()); }
	bool		empty() const { return start_ == finish_; } //or static allocator.empty()?
/* =================                Capacity Modulator      ================= */
	void		reserve(size_type new_cap)
	{
		if (capacity() < new_cap)
		{
			iterator tmp = static_allocator.allocate(new_cap);
			end_of_storage = uninitialized_copy(begin(), end(), tmp);
			destroy(start_, finish_);
			static_allocator.deallocate(start_, capacity()); //wrong? original implementation only gives start_
			finish_ = tmp + size();
			start_ = tmp;
			end_of_storage = begin() + new_cap;
		}
	}
/* =================               Modifiers              ================= */



	void push_back(T& data)
	{
		if (current == capacity) {
            T* temp = new T[2 * capacity];
 
            for (int i = 0; i < capacity; i++) {
                temp[i] = arr[i];
            }
 
            delete[] arr;
            capacity *= 2;
            arr = temp;
        }
        arr[current] = data;
        current++;
    }

};
}