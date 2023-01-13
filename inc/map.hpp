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

        typedef avl_node<key_type, value_type>*             node_pointer;

    protected:
        allocator_type                  value_allocator_;
        allocator_type                  node_allocator_; //different allocators needed?
        avl_node<key_type, value_type>  root_node_;
        
    public:    
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
        allocator_type get_allocator() const { return static_allocator_; }

        private:
        node_pointer create_node_(value_type value, node_pointer parent)
        {
            if (end_node_ != NULL)
                ++size_;
            node_pointer new_node = node_allocator.allocate(1);
            new_node->parent = parent;
            new_node->left = left;
            new_node->right = right;
            new_node->height_diff = 0;
            value_allocator_.construct(&new_node->value, value);
            return new_node;
        }

        void delete_node_(node_pointer node)
        {
            if (node != end_node_)
                --size_; //?
            value_allocator_.destroy(&node->value);
            node_allocator.deallocate(node, 1);
        }
    };
}