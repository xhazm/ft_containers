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

        typedef ft::vector_iterator< value_type >			iterator;
        typedef ft::vector_iterator< value_type >			const_iterator;

    private:
        value_allocator_type    value_alloc_;
        value_allocator_type     node_alloc_;
        // node_allocator_type     node_alloc_;
        node_pointer            root_;
        node_pointer            end_;
        size_type               size_;
        value_compare           cmp_;
    

    public:
        // avl_tree(const value_compare& cmp, const value_allocator_type value_alloc = value_allocator_type())
        avl_tree() : size_(0), cmp_(cmp), value_alloc_(value_alloc)
        {
            end_ = create_node_(value_type(), NULL);
            root_ = end_;
            //init also node alloc? or is it auto inited
        }
        ~avl_tree() 
        {
            clear();
            delete_node_(end_);
        }

/* =================				    Iterators   				================= */
    iterator				begin()			{ return iterator(root_); }
    const_iterator			begin() const	{ return const_iterator(root_); }
    iterator				end()			{ return iterator(end_); }
    const_iterator			end() const		{ return const_iterator(end_); }

/* =================				    Capacity        				================= */
    size_type   size() const                { return size_; }
    size_type   max_size() const            { return node_alloc_.max_size(); }
    
    
    delete(node_pointer pos)
    {
        if (pos->right == NULL && pos->left == NULL)
        {
            if (pos->parent->left == pos)
                pos->parent->left = NULL;
            else if (pos->parent->right == pos)
                pos->parent->right = NULL;
            delete_node_(pos);
        }
    }
    

    ft::pair<iterator, bool> insert(value_type& value, node_pointer pos)
    {
        //check if pos is there
        if (pos == NULL)
            pos = root_;
        if (pos == end_)
        {
            root_ = create_node_(value, NULL);
            end_->parent = root_;
            return (ft::make_pair(iterator(root_), true))
        }
        while (pos != end_)
        {
            if (cmp_(value, pos->value) && pos->left != end_)
                pos = pos->left;
            else if (cmp_(pos->value, value) && pos->right != end_)
                pos = pos->right;
            else
                break ;
        }
        if(cmp_(value, pos->value)) //left
        {
            node_pointer new_node = create_node_(value, pos);
            pos->left = new_node;
            new_node->height = pos->height + 1;
            check_rule_violation_(new_node);
            return (ft::make_pair(iterator(new_node), true));
        }
        else if(cmp_(pos->value, value)) //right
        {
            node_pointer new_node = create_node_(value, pos);
            pos->right = new_node;
            new_node->height = pos->height + 1;
            check_rule_violation_(new_node);
            return (ft::make_pair(iterator(new_node), true));
        }
        return (ft::make_pair(iterator(pos), false));
    }

    void clear()
    {
        clear_helper_(root_);
        root_ = end_;
        end_->parent = NULL;
    }

/* =================				    LookUp        				================= */

    iterator    lower_bound(const value_type& value)
    {
        node_pointer result = end_;
        node_pointer node = root_;

        while (node != end_)
        {
            if (!cmp_(node->value, value))
            {
                result = node;
                node = node->left;
            }
            else
                node = node->right;
        }
        return (iterator(result));
    }

    const_iterator  lower_bound( onst value_type& value) const
    {
        node_pointer result = end_;
        node_pointer node = root_;

        while (node != end_)
        {
            if (!cmp_(node->value, value))
            {
                result = node;
                node = node->left;
            }
            else
                node = node->right;
        }
        return (const_iterator(result));
    }

    iterator    upper_bound( const value_type& value )
    {
        node_pointer result = end_;
        node_pointer node = root_;

        while (node != end_)
        {
            if (cmp_(value, node->value))
            {
                result = node;
                node = node->left;
            }
            else
                node = node->right;
        }
        return (iterator(result));
    }

    const_iterator  upper_bound( const value_type& value ) const
    {
        node_pointer result = end_;
        node_pointer node = root_;

        while (node != end_)
        {
            if (cmp_(value, node->value))
            {
                result = node;
                node = node->left;
            }
            else
                node = node->right;
        }
        return (const_iterator(result));
    }

    node_pointer search_node(value_type value, node_pointer node)
    {
        if (root_ == end_)
            return (end_);
        while (n != end_)
        {
            if (cmp_(value, n->value))
                n = n->left;
            else if (cmp_(n->value, value))
                n = n->right;
            else
                return (n);
        }
        return (end_);
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
        new_node->left = end_;
        new_node->right = end_;
        new_node->height_diff = 0; //get height diff function
        value_alloc_.construct(&new_node->value, value);
        ++size_;
        return new_node;
    }

    void delete_node_(node_pointer node)
    {
        if (node != end_node_)
            --size_;
        value_alloc_.destroy(&node->value);
        node_allocator.deallocate(node, 1);
    }

    void check_rule_violation_(node_pointer node)
    {
        ; //logic here
    }

    void clear_helper_(node_pointer n)
    {
        if (n == NULL || n == end_)
            return ;
        _clear_helper(n->left);
        _clear_helper(n->right);
        _delete_node(n);
    }
};
} // namespace ft

//cases:
// -2 -1 = left rot
// +2 +1 = right rot
// -2 +1 = right left rot (bottom starting)
// +2 -1 = left right rot