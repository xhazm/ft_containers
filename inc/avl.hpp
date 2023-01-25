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
        pointer     right;
        pointer     left;
        pointer     parent;
        //copy operator needed because of delete
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
    
    
/* =================				    Modifiers        				================= */
   
    void clear()
    {
        clear_helper_(root_);
        root_ = end_;
        end_->parent = NULL;
    }
    
    ft::pair<iterator, bool> insert(value_type& value, node_pointer pos)
    {
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
            balance_(new_node);
            return (ft::make_pair(iterator(new_node), true));
        }
        else if(cmp_(pos->value, value)) //right
        {
            node_pointer new_node = create_node_(value, pos);
            pos->right = new_node;
            new_node->height = pos->height + 1;
            balance_(new_node);
            return (ft::make_pair(iterator(new_node), true));
        }
        return (ft::make_pair(iterator(pos), false));
    }

    void erase(node_pointer pos)
    {
        if (search_node(pos.get_value(), pos) == pos)
        if (pos->right == NULL && pos->left == NULL)
        {
            if (pos->parent->left == pos)
                pos->parent->left = NULL;
            else if (pos->parent->right == pos)
                pos->parent->right = NULL;
            erase_node_(pos);
        }
    }

    bool erase_helper_(node_pointer pos, value_type value)
    {
        node_pointer    to_delete = search_node(value, pos);
        node_pointer    new_head = NULL;

        if (to_delete == end_)
            return (false);
        //root node is to be deleted
        if (to_delete == root_)
        {
            //no children
            if (to_delete->left == end_ && to_delete->right == end_)
                root_ = end_;
            //either left XOR right child
            else if ((to_delete->left != end_) != (to_delete->right != end_))
            {
                new_head = root_->left != end_ ? root_->left : root_->right;
                if (new_head == end_)
                {
                    new_head = to_delete;
                    to_delete = NULL;
                }
                else
                    to_delete = new_head;
                erase_node_(new_head);
            }
            //left AND right child
            else
            {
                new_head = min_value_node(root_->right);
                root_->value = new_head->value; //make copy operator for this
                // new_head = NULL;
            }
        }
        // //non root node is to be deleted
        // //leaf node
        // else if (to_delete->left == end_ && to_delete->right == end_)
        // {
        //     new_head = to_delete->parent;
        //     new_head->left == to_delete ? new_head->left = end_ : new_head->right = end_;
        // }
        // //either left XOR right child
        // else if ((to_delete->left != end_) != (to_delete->right != end_))
        // {
        //     new_head = to_delete->parent;
        //     if (to_delete->left != end_)
        //         new_head->left = to_delete->left;
        //     else if (to_delete->right != end)
        //         new_head->right = to_delete->right;
        //     if (new_head->left == to_delete)
        //     {
        //         new_head->left = to_delete->left
        //         to_delete->left->parent = new_head;
        //     }
        //     else if (new_head->right == to_delete)
        //     {
        //         new_head->right = to_delete->right
        //         to_delete->right->parent = new_head;
        //     }
        // }
        // //left AND right child
        // else
        // {

        // }
        // balance_(new_head);
        erase_node_(to_delete);
    }

    void swap(avl_tree& other)
    {
        ft::swap(value_alloc_, other.value_alloc_);
        ft::swap(node_alloc_, other.node_alloc_);
        ft::swap(root_, other.root_);
        ft::swap(end_, other.end_);
        ft::swap(size_, other.size_);
        ft::swap(cmp_, other.cmp_);
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

    node_pointer search_node(value_type value, node_pointer n) const
    {
        if (n == NULL)
            n = root_;
        while (n != end_)
        {
            if (cmp_(value, n->value))
                n = n->left;
            else if (cmp_(n->value, value))
                n = n->right;
            else
                return (n);
        //does it work because n may be end?
        }
        return (end_);
    }

    private:

    /**
    *   Calculates the tree's height.
    *   @param root     The root of the tree (start with first node, then call itself with left
    *                   and right node children until meeting leaf).
    *   @param height   The heigth of the actual node. Increases this param by 1 each time 
    *                   it's calling itself on a node's child.
    *   @return         The height of the tree (-1 if empty, 0 if only root node).
    */
    size_type tree_height_(node_pointer root, size_type height)
    {
        if (root_ == end_)
            return height - 1;
        size_type l_height = heightTree(root->left, height + 1);
        size_type r_height = heightTree(root->right, height + 1);
        return (l_height > r_height ? l_height : r_height);
    }

    /**
    *   Compares height of left and right subtrees.
    *
    *   @param node Compare starts here
    *   @return     Difference between left and right subtrees. Will be negative if right
    *               subtree > left subtree.
    */
    long long balance_of_subtrees(node_pointer node)
    {
        if (node == end_)
            return 0;
        return tree_height(node->left, 1) - tree_height(node->right, 1);
    }

    /**
    *   Checks balance nodes up until root, beginning with given node. 
    *   When imbalance is found, it will be balanced according to following cases:
    *
    *   1. case: right right -> right -2 & right right -1
    *   2. case: right left  -> right -2 & right left  +1
    *   3. case: left  left  -> left  +2 & left  left  +1
    *   4. case: left  right -> left  +2 & left  right -1
    * 
    *   @param node Given node to begin with.
    */
    void balance_(node_pointer node)
    {
        if (node == end_ || node == root_)
            return ;
        while (node)
        {
            size_type balance = balance_of_subtrees(node);

            if (balance <= -2 && balance_of_subtrees(node->right) <= -1)
                rotate_left(node);
            else if (balance <= -2 && balance_of_subtrees(node->right) >= 0)
                rotate_right(rotate_left(node));
            else if (balance >= 2 && balance_of_subtrees(node->left) >= 1)
                rotate_right(node);
            else if (balance >= 2 && balance_of_subtrees(node->left) <= 0)
                rotate_left(rotate_right(node));
            node = node->parent;
        }
    }

    node_pointer min_value_node_(node_pointer pos)
    {
        if (pos == end_)
            return (pos);
        while (pos->left != end_)
            pos = pos->left;
        return (pos);
    }

    node_pointer max_value_node_(node_pointer pos)
    {
        if (pos == end_)
            return (pos);
        while (pos->right != end_)
            pos = pos->right;
        return (pos);
    }

    node_pointer rotate_right_(node_pointer rotation_node)
    {
        node_pointer    new_head = rotation_node->left;

        if (rotation_node == root_)
            root_ = new_head;
        rotation_node->left = new_head->right;
        new_head->right = rotation_node;
        rotation_node->parent = new_head;
        return (new_head);
    }


    node_pointer rotate_left_(node_pointer rotation_node)
    {
        node_pointer    new_head = rotation_node->right;

        if (rotation_node == root_)
            root_ = new_head;
        rotation_node->right = new_head->left;
        new_head->left = rotation_node;
        rotation_node->parent = new_head;
        return (new_head);
    }

    node_pointer create_node_(value_type& value, node_pointer parent)
    {
        node_pointer new_node = node_alloc_.allocate(1);
        new_node->parent = parent;
        new_node->left = end_;
        new_node->right = end_;
        new_node.balance_factor = 0; //get height diff function
        value_alloc_.construct(&new_node->value, value);
        ++size_;
        return (new_node);
    }

    void erase_node_(node_pointer node)
    {
        if (node != end_)
            --size_;
        if (node == root_)
            root_ = end_;
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