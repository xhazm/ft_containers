#pragma once

#include <functional>
#include <iostream>

namespace ft
{
    template<
    class Key,
    class T,
    class Compare = std::less<Key>,
    class Allocator = std::allocator<std::pair<const Key, T>>
    > class map
    {
        public:

        typedef T											mapped_type;
        typedef Key											key_type;
        typedef std::pair<const Key, T>						value_type;
	    typedef	Allocator									allocator_type;
        typedef Compare                                     key_compare;
        typedef std::size_t                                 size_type;
        typedef std::ptrdiff_t                              difference_type;
        typedef typename allocator_type::reference          reference;
        typedef typename allocator_type::const_reference    const_reference;
        typedef typename allocator_type::pointer            pointer;
        typedef typename allocator_type::const_pointer      const_pointer;

        struct avl_node
        {
            value_type*  value;
            key_type*    key;
            avl_node*   right;
            avl_node*   left;
        }

        map()
        {

        }
        explicit map(const Compare& comp, const Allocator& alloc = Allocator())
        {
                    
        }
        template< class InputIt >
        map(InputIt first, InputIt last,
                const Compare& comp = Compare(),
                const Allocator& alloc = Allocator())
        {

        }
        map(const map& other) { this = &other }
        map& operator=(const map& other)
        {

        }
    };
}