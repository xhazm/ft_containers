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
        short       balance_factor;
        long        level;
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
        // typedef typename value_allocator_type::template rebind<node_type>::other    node_allocator_type;
        // typedef typename node_allocator_type::size_type                             size_type;
        typedef size_t                             size_type;

        // typedef ft::vector_iterator< value_type >			iterator;
        // typedef ft::vector_iterator< value_type >			const_iterator;

    private:
        value_allocator_type    value_alloc_;
        value_allocator_type     node_alloc_;
        // node_allocator_type     node_alloc_;
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
        
        
        delete(node_pointer pos)
        {
            if (pos.right == NULL && pos.left == NULL)
            {
                if (pos->parent->left == pos)
                    pos->parent->left = NULL;
                else if (pos->parent->right == pos)
                    pos->parent->right = NULL;
                delete_node_(pos);
            }
        }
        
        insert(value_type& value, node_pointer pos)
        {
            //check if pos is there
            if(cmp_(value, pos->value)) //left
            {
                node_pointer new_node = create_node_(value);
                pos->left = new_node;
                new_node->height = pos->height + 1;
                check_rule_violation_(new_node);
            }
            else if(cmp_(pos->value, value)) //right
            {
                node_pointer new_node = create_node_(value);
                pos->right = new_node;
                new_node->height = pos->height + 1;
                check_rule_violation_(new_node);
            }

        }

        node_pointer search_node(value_type value, node_pointer node)
        {
            if (root_ == NULL)
                return (NULL);
            while (n != NULL)
            {
                if (cmp_(value, n->value))
                    n = n->left;
                else if (cmp_(n->value, value))
                    n = n->right;
                else
                    return (n);
            }
            return (NULL);
        }

        private:
       
        node_pointer rotate_right_(node_pointer rotation_node)
        {
            node_pointer    new_head = rotation_node->left;

            rotation_node->left = new_head->right;
            new_head->right = rotation_node;
            rotation_node->parent = new_head;
        }


        node_pointer rotate_left_(node_pointer rotation_node)
        {
            node_pointer    new_head = rotation_node->right;

            rotation_node->right = new_head->left;
            new_head->left = rotation_node;
            rotation_node->parent = new_head;
        }

        node_pointer create_node_(value_type& value, node_pointer parent)
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

        void check_rule_violation_(node_pointer node)
        {
            ; //logic here
        }
    };
} // namespace ft

//cases:
// -2 -1 = left rot
// +2 +1 = right rot
// -2 +1 = right left rot (bottom starting)
// +2 -1 = left right rot