#pragma once

#include <functional>
#include <iostream>
#include "./avl.hpp"

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

        typedef avl_tree<value_type, Compare>               tree;

        // typedef avl_node<key_type, value_type>*             node_pointer;

    protected:
        allocator_type                  value_allocator_;
        allocator_type                  node_allocator_; //different allocators needed?
        tree                            avl_tree_;
        
    public:    
        map() {}
        explicit map(const Compare& comp = Compare(), const Allocator& alloc = Allocator())
            : avl_tree_(tree()) {}
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
        allocator_type get_allocator() const { return static_allocator_; }

        bool        empty() const               { return avl_tree_.begin() == avl_tree_.end();}

/* =================				    LookUp        				================= */

        iterator find(const Key& key)
        {
            return (avl_tree_.search(ft::make_pair(key, mapped_type()), NULL));
        }

        const iterator find(const Key& key)
        {
            return (const_iterator(avl_tree_.search(ft::make_pair(key, mapped_type()), NULL)));
        }

        //Returns an iterator pointing to the first element that is not less than (i.e. greater or equal to) key.
        iterator    lower_bound( const Key& key )
        {
            return (avl_tree_.lower_bound(ft::make_pair(key, mapped_type())));
        }

        const_iterator  lower_bound( const Key& key ) const
        {
            return (avl_tree_.lower_bound(ft::make_pair(key, mapped_type())));
        }

        //  Returns an iterator pointing to the first element that is greater than key.
        iterator    upper_bound( const Key& key )
        {
            return (avl_tree_.upper_bound(ft::make_pair(key, mapped_type())));
        }

        const_iterator  upper_bound( const Key& key ) const
        {
            return (avl_tree_.upper_bound(ft::make_pair(key, mapped_type())));
        }

    };
} // namespace ft