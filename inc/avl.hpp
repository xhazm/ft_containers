#pragma once

#include <memory>
#include "./iterator/avl_iterator.hpp"
#include "./iterator/reverse_iterator.hpp"
#include "./pair.hpp"
#include "./utils.hpp"
#include "./avl_node.hpp"


namespace ft
{

template<
    class Value,
    class Compare,
    class Allocator = std::allocator< Value >
> class avl_tree
{
public:
    typedef Value                                           value_type;
    typedef Allocator                                       value_allocator_type;
    typedef typename value_allocator_type::difference_type  difference_type;
    typedef Compare                                         value_compare;
    typedef typename avl_node< value_type >::node_type      node_type;
    typedef typename node_type::pointer                     node_pointer;
    typedef typename value_allocator_type::template rebind<node_type>::other    node_allocator_type;
    typedef typename value_allocator_type::size_type        size_type;
    typedef ft::avl_iterator< value_type >			        iterator;
    typedef ft::const_avl_iterator< value_type >			const_iterator;
    typedef ft::reverse_iterator<iterator>                  reverse_iterator;
    typedef ft::reverse_iterator<const_iterator>            const_reverse_iterator;

public:
    value_allocator_type    value_alloc_;
    node_allocator_type     node_alloc_;
    node_pointer            root_;
    node_pointer            end_;
    node_pointer            begin_;
    value_compare           cmp_;
    size_type               size_;


public:
    // avl_tree(const value_compare& cmp, const value_allocator_type value_alloc = value_allocator_type())
    avl_tree()
    {
        end_ = create_node_(value_type(), NULL);
        root_ = end_;
        begin_ = end_;
        size_ = 0;
        //init also node alloc? or is it auto inited
    }
    ~avl_tree() 
    {
        clear();
        erase_node_(end_);
    }

    avl_tree& operator=(const avl_tree& other) 
    {
        if (this != &other)
        {
            clear();
            erase_node_(end_);
            value_alloc_ = other.value_alloc_;
            node_alloc_ = other.node_alloc_;
            cmp_ = other.cmp_;
            root_ = _copy_tree(other.root_, NULL);
            begin_ = min_value_node_(root_);
            end_->parent = max_value_node_(root_);
            size_ = other.size_;
        }

        return *this;
    }


/* =================                    Iterators                   ================= */
    iterator                begin()         { return iterator(begin_); }
    const_iterator          begin() const   { return const_iterator(begin_); }
    iterator                end()           { return iterator(end_); }
    const_iterator          end() const     { return const_iterator(end_); }
    reverse_iterator        rbegin()        { return reverse_iterator(end()); }
    const_reverse_iterator  rbegin() const  { return const_reverse_iterator(end()); }
    reverse_iterator        rend()          { return reverse_iterator(begin()); }
    const_reverse_iterator  rend() const    { return const_reverse_iterator(begin()); }

/* =================                    Capacity                        ================= */
    size_type   size() const        { return size_; }
    size_type   max_size() const    { return node_alloc_.max_size(); }
    
    
/* =================                    Modifiers                        ================= */
   
    void clear()
    {
        clear_helper_(root_);
        root_ = end_;
        begin_ = root_;
        end_->parent = NULL;
    }
    
    ft::pair<iterator, bool> insert(const value_type& value, node_pointer pos)
    {
        if (pos == NULL)
            pos = root_;
        if (pos == end_)
        {
            root_ = create_node_(value, NULL);
            root_->right = end_;
            begin_ = root_;
            end_->parent = root_;
            return (ft::make_pair(iterator(root_), true));
        }
        while (pos != NULL)
        {
            if (cmp_(value, pos->value) && pos->left != NULL)
                pos = pos->left;
            else if (cmp_(pos->value, value) && pos->right != NULL && pos->right != end_)
                pos = pos->right;
            else
                break ;
        }
        if(cmp_(value, pos->value)) //left
        {
            node_pointer new_node = create_node_(value, pos);
            pos->left = new_node;
            if (pos == begin_)
                begin_ = new_node;
            balance_(new_node);
            return (ft::make_pair(iterator(new_node), true));
        }
        else if(cmp_(pos->value, value)) //right
        {
            node_pointer new_node = create_node_(value, pos);
            if (pos->right == end_)
            {
                pos->right = new_node;
                new_node->right = end_;
                end_->parent = new_node;
            }
            else
                pos->right = new_node;
            balance_(new_node);
            return (ft::make_pair(iterator(new_node), true));
        }
        return (ft::make_pair(iterator(pos), false));
    }

    /**
    *   Erases node out of tree. Can be determined by value OR value and pos
    *   @param pos      If NULL, value is searched in whole tree. If set,
    *                   value will be searched at pos and under.
    *   @param value    The value(key/val pair) to look for
    *   @param erase    The node which should be erased, if found
    *   @param tmp      Saves the node which get on the pos of the erased node
    */

    bool erase(const_iterator pos)
    {
        node_pointer    del = const_cast<node_pointer>(pos.base());
        return erase(del->value, NULL);
    }

    bool erase(value_type value, node_pointer pos)
    {
        node_pointer    erase = search_node(value, pos);
        node_pointer    tmp = NULL;
        bool            erased_begin = false;

        if (erase == end_)
            return (false);
        //either one or no child
        if ((erase->left == NULL) || (erase->right == end_ || erase->right == NULL))
        {
            tmp = (erase->left != NULL ? erase->left : erase->right);
            //no child
            if (tmp == end_ || tmp == NULL)
            {
                tmp = root_;
                if (erase != root_)
                {
                    if (erase->parent->right == erase)
                    {
                        if (erase->right == end_)
                        {
                            erase->parent->right = end_;
                            end_->parent = erase->parent;
                        }
                        else
                            erase->parent->right = NULL;
                    }
                    else
                        erase->parent->left = NULL;
                }
                else if (erase == root_)
                {
                    tmp = end_;
                    root_ = end_;
                    end_->parent = NULL;
                }
            }
            //one child
            else
            {
                tmp->parent = erase->parent;
                if (erase != root_)
                    erase->parent->right == erase ? erase->parent->right = tmp : erase->parent->left = tmp;
                else if (erase == root_)
                    root_ = tmp;
                if(erase->right == end_)
                {
                    tmp->right = end_;
                    end_->parent = tmp;
                }
            }
            if (begin_ == erase)
                erased_begin = true;
            erase_node_(erase);
        }
        //left and right child
        else
        {
            tmp = max_value_node_(erase->left);
            if (tmp->parent == erase)
            {
                erase->left = tmp->left;
                if (erase->left != NULL)
                    erase->left->parent = erase;
            }
            else if (tmp->parent != NULL)
                tmp->parent->right = NULL; //maybe end in some cases?
            if (tmp == begin_)
                erased_begin = true;
            value_alloc_.destroy(&erase->value);
            value_alloc_.construct(&erase->value, tmp->value);
            erase_node_(tmp);
            tmp = erase;
        }
        balance_(tmp);
        if (erased_begin == true)
            begin_ = min_value_node_(root_);
        return (true);
    }

    void swap(avl_tree& other)
    {
        ft::swap(value_alloc_, other.value_alloc_);
        ft::swap(node_alloc_, other.node_alloc_);
        ft::swap(root_, other.root_);
        ft::swap(begin_, other.begin_);
        ft::swap(end_, other.end_);
        ft::swap(size_, other.size_);
        ft::swap(cmp_, other.cmp_);
    }

/* =================                    LookUp                        ================= */

    iterator    lower_bound(const value_type& value)
    {
        node_pointer result = end_;
        node_pointer node = root_;

        while (node != NULL)
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

    const_iterator  lower_bound(const value_type& value) const
    {
        node_pointer result = end_;
        node_pointer node = root_;

        while (node != NULL)
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

    iterator    upper_bound(const value_type& value)
    {
        node_pointer result = end_;
        node_pointer node = root_;

        while (node != NULL)
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

    const_iterator  upper_bound(const value_type& value) const
    {
        node_pointer result = end_;
        node_pointer node = root_;

        while (node != NULL)
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

    /**
    *   Searches node in tree. Can be determined by value OR value and pos
    *   @param pos      If NULL, value is searched in whole tree. If set,
    *                   value will be searched at pos and under.
    *   @param value    The value(key/val pair) to look for
    *   @return         If found, returns pointer to node. If not returns end()
    */
    node_pointer search_node(value_type value, node_pointer n) const
    {
        if (n == NULL)
            n = root_;
        while (n != NULL)
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
        if (root == NULL || root == end_)
            return height - 1;
        size_type l_height = tree_height_(root->left, height + 1);
        size_type r_height = tree_height_(root->right, height + 1);
        return (l_height > r_height ? l_height : r_height);
    }

    /**
    *   Compares height of left and right subtrees.
    *
    *   @param node Compare starts here
    *   @return     Difference between left and right subtrees. Will be negative if right
    *               subtree > left subtree.
    */
    long long balance_of_subtrees_(node_pointer node)
    {
        if (node == NULL)
            return 0;
        return tree_height_(node->left, 1) - tree_height_(node->right, 1);
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
        if (node == end_)
            return ;
        while (node)
        {
            long long balance = balance_of_subtrees_(node);

            if (balance <= -2 && balance_of_subtrees_(node->right) <= -1)
                rotate_left_(node->right);
            else if (balance <= -2 && balance_of_subtrees_(node->right) >= 0)
                rotate_left_(rotate_right_(node->right->left));
            else if (balance >= 2 && balance_of_subtrees_(node->left) >= 1)
                rotate_right_(node->left);
            else if (balance >= 2 && balance_of_subtrees_(node->left) <= 0)
                rotate_right_(rotate_left_(node->left->right));

            node = node->parent;
        }
    }

    node_pointer rotate_right_(node_pointer new_head)
    {
        node_pointer    rotation_node = new_head->parent;

        if (rotation_node == root_)
            root_ = new_head;
        else if(rotation_node != root_)
        {
            if (rotation_node->parent->right == rotation_node)
                rotation_node->parent->right = new_head;
            else
                rotation_node->parent->left = new_head;
        }
        rotation_node->left = new_head->right;
        if (rotation_node->left != NULL)
            rotation_node->left->parent = rotation_node;
        new_head->right = rotation_node;
        new_head->parent = rotation_node->parent;
        rotation_node->parent = new_head;
        return (new_head);
    }


    node_pointer rotate_left_(node_pointer new_head)
    {
        node_pointer    rotation_node = new_head->parent;

        if (rotation_node == root_)
            root_ = new_head;
        else if(rotation_node != root_)
        {
            if (rotation_node->parent->right == rotation_node)
                rotation_node->parent->right = new_head;
            else
                rotation_node->parent->left = new_head;
        }
        rotation_node->right = new_head->left;
        if (rotation_node->right != end_ && rotation_node->right != NULL)
            rotation_node->right->parent = rotation_node;
        new_head->left = rotation_node;
        new_head->parent = rotation_node->parent;
        rotation_node->parent = new_head;
        return (new_head);
    }

    node_pointer create_node_(value_type value, node_pointer parent)
    {
        node_pointer new_node = node_alloc_.allocate(1);
        new_node->parent = parent;
        new_node->left = NULL;
        new_node->right = NULL;
        value_alloc_.construct(&new_node->value, value);
        ++size_;
        return (new_node);
    }

    void erase_node_(node_pointer& node)
    {
        if (node != end_)
            --size_;
        value_alloc_.destroy(&node->value);
        node_alloc_.deallocate(node, 1);
        node = NULL;
    }

    node_pointer min_value_node_(node_pointer pos)
    {
        if (pos == NULL || pos == end_)
            return (pos);
        while (pos->left != NULL)
            pos = pos->left;
        return (pos);
    }

    node_pointer max_value_node_(node_pointer pos)
    {
        if (pos == end_)
            return (pos);
        while (pos->right != end_ && pos->right != NULL)
            pos = pos->right;
        return (pos);
    }

    void clear_helper_(node_pointer n)
    {
        if (n == NULL || n == end_)
            return ;
        clear_helper_(n->left);
        clear_helper_(n->right);
        erase_node_(n);
    }

    node_pointer    _copy_tree(node_pointer from, node_pointer parent)
    {
        if (from == NULL)
            return (NULL);
        node_pointer new_node = create_node_(from->value, parent);
        new_node->left = _copy_tree(from->left, new_node);
        end_ = new_node;                                                     // sets the new end_iterator. should be done differently cause it's not self explainatory ;)
        new_node->right = _copy_tree(from->right, new_node);
        return (new_node);
    }

};
} // namespace ft
//cases:
// -2 -1 = left rot
// +2 +1 = right rot
// -2 +1 = right left rot (bottom starting)
// +2 -1 = left right rot