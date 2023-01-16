#pragma once

#include <memory>
#include "./iterator/vector_iterator.hpp"

namespace ft
{
    template<
    class value_type
    > struct avl_node
    {
        typedef T                                   value_type;
        typedef avl_node<value_type>                node_type;
        typedef node_type*                          pointer;
        typedef const node_type*                    const_pointer;

        value_type  value;
        // key_type    key;
        pointer     right;
        pointer     left;
        pointer     parent;
        short       height_diff;
    };

    template<
        class Value,
        class Compare,
        class Allocator = std::allocator< Value >
    > class avl_tree
    {
        typedef Value                                           value_type;
        typedef Allocator                                       value_allocator_type;
        typedef typename value_allocator_type::difference_type  difference_type;

        typedef Compare                                         value_compare;

        typedef typename avl_node< value_type >::node_type      node_type;
        typedef typename node_type::point                       node_pointer;
        typedef typename value_allocator_type::template rebind<node_type>::other    node_allocator_type;
        typedef typename node_allocator_type::size_type                             size_type;

        typedef ft::vector_iterator< value_type >			iterator;
        typedef ft::vector_iterator< value_type >			const_iterator;

    private:
        value_allocator_type    value_alloc_;
        node_allocator_type     node_alloc_;
        node_pointer            root_;
        node_pointer            begin_;
        node_pointer            end_;
        size_type               size_;
        value_compare           cmp_;
    

    public:
        // avl_tree() : root_(NULL), size(0)
        // {
        //     begin_ = NULL;
        //     end_ = NULL;
        // }
        // avl_tree(const value_compare& cmp, const value_allocator_type value_alloc = value_allocator_type())
        avl_tree()
            : root_(NULL), size_(0), cmp_(cmp), value_alloc_(value_alloc), begin_(NULL), end_(NULL)
        {
            //init also node alloc? or is it auto inited
        }
        ~avl_tree() { clear(); }

/* =================				    Iterators   				================= */
        iterator				begin()			{ return iterator(begin_); }
        const_iterator			begin() const	{ return const_iterator(begin_); }
        iterator				end()			{ return iterator(end_); }
        const_iterator			end() const		{ return const_iterator(end_); }

/* =================				    Capacity        				================= */
        size_type   size() const                { return size_; }
        size_type   max_size() const            { return node_alloc_.max_size(); }
        
        
        
        
        private:
        node_pointer create_node_(value_type value, node_pointer parent)
        {
            node_pointer new_node = node_alloc_.allocate(1);
            new_node->parent = parent;
            new_node->left = NULL;
            new_node->right = NULL;
            new_node->height_diff = 0; //get height diff function
            value_alloc_.construct(&new_node->value, value);
            ++size_;
            if (parent == NULL)
            {
                root_ = new_node;
                end_ = root_;
                begin_ = root_;
            }
            return new_node;
        }

        void delete_node_(node_pointer node)
        {
            if (node != end_node_)
                --size_; //?
            value_alloc_.destroy(&node->value);
            node_allocator.deallocate(node, 1);
        }
    };
} // namespace ft
