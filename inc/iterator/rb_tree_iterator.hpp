#pragma once

#include "iterator.hpp"
#include "../pair.hpp"
#include  "../red_black_node.hpp"

namespace ft {

template < class node_ptr >
node_ptr rb_tree_max(node_ptr node)
{
    while (node->right != NULL)
        node = node->right;
    return node;
}

template < class node_ptr >
node_ptr rb_tree_min(node_ptr node)
{
    while (node->left != NULL)
        node = node->left;
    return node;
}

template < class node_ptr >
node_ptr rb_tree_prev(node_ptr x)
{
    if (x->left != NULL)
        return rb_tree_max(x->left);
    while (x == x->parent->left)
        x = x->parent;
    return x->parent;
}

template < class node_ptr >
node_ptr rb_tree_next(node_ptr node)
{
    if (node->right != NULL)
        return rb_tree_min(node->right);
    while (node == node->parent->right)
        node = node->parent;
    return node->parent;
}

template < class T_value >
class const_rb_tree_iterator;

template <
    class T_value
> class rb_tree_iterator
{
   public:
/* =================    Member types                        ================= */

    typedef T_value                                     value_type;
    typedef value_type&                                 reference;
    typedef value_type*                                 pointer;
    typedef std::ptrdiff_t                              difference_type;
    typedef ft::bidirectional_iterator_tag              iterator_category;

   private:
    typedef typename red_black_node< T_value >::pointer         node_pointer;
    typedef typename red_black_node< T_value >::const_pointer   const_node_pointer;
    typedef rb_tree_iterator                                  iterator;
    typedef const_rb_tree_iterator< T_value >                 const_iterator;

/* =================    Member objects                      ================= */

    node_pointer    current_;
    
   public:
/* =================    Constructors / Destructor           ================= */

    rb_tree_iterator( const node_pointer& ptr = NULL ) : current_(ptr) {}

    rb_tree_iterator( const iterator& rhs ) : current_(rhs.base()) {}

    ~rb_tree_iterator() {}
    
/* =================    Accessors                           ================= */

    node_pointer    base() const { return (current_); }
    
/* =================    Operator overloads                  ================= */
    reference     operator*()           { return current_->value; }
    pointer       operator->()          { return &(current_->value); }
    reference     operator*() const     { return current_->value; }
    pointer       operator->() const    { return &(current_->value); }
    iterator& operator++()                              
    {
        current_ = rb_tree_next< node_pointer >(current_);
        return *this;
    }
    iterator  operator++(int)                           
    { 
        iterator tmp(current_);
         ++*this; 
         return tmp; 
    }
    iterator& operator--()                              
    {
        current_ = rb_tree_prev< node_pointer >(current_);
        return *this; 
    }
    iterator  operator--(int)                           
    {
        iterator tmp(current_);
        --*this;
        return tmp; 
    }

    bool operator==(const iterator& other)       const { return (current_ == other.current_); }
    bool operator==(const const_iterator& other) const { return (current_ == other.base()); }
    bool operator!=(const iterator& other)       const { return (!(*this == other)); }
    bool operator!=(const const_iterator& other) const {return (!(*this == other)); }
};

template <
    class T_value
> class const_rb_tree_iterator
{
   public:
/* =================    Member types                        ================= */
    typedef const T_value                               value_type;
    typedef value_type&                                 reference;
    typedef value_type*                                 pointer;
    typedef std::ptrdiff_t                              difference_type;
    typedef ft::bidirectional_iterator_tag              iterator_category;

   private:
    typedef typename red_black_node< T_value >::pointer        node_pointer;
    typedef typename red_black_node< T_value >::const_pointer  const_node_pointer;
    typedef rb_tree_iterator< T_value >                      iterator;
    typedef const_rb_tree_iterator                           const_iterator;

/* =================    Member objects                      ================= */

    const_node_pointer    current_;

   public:
/* =================    Constructors / Destructor           ================= */

    const_rb_tree_iterator(const const_node_pointer& ptr = NULL) : current_(ptr) {}

    const_rb_tree_iterator(const const_iterator& other) : current_(other.base()) {}

    const_rb_tree_iterator(const iterator& other) : current_(other.base()) {}

    ~const_rb_tree_iterator() {}

/* =================    Accessors                           ================= */

    const_node_pointer base() const { return (current_); }

/* =================    Operator overloads                  ================= */

    reference     operator*()           { return current_->value; }
    pointer       operator->()          { return &(current_->value); }
    reference     operator*() const     { return current_->value; }
    pointer       operator->() const    { return &(current_->value); }
    const_iterator& operator++()                              
    {
        current_ = rb_tree_next< const_node_pointer >(current_);
        return *this;
    }
    const_iterator  operator++(int)                           
    { 
        const_iterator tmp(current_);
         ++*this; 
         return tmp; 
    }
    const_iterator& operator--()                              
    {
        current_ = rb_tree_prev< const_node_pointer >(current_);
        return *this; 
    }
    const_iterator  operator--(int)                           
    {
        const_iterator tmp(current_);
        --*this;
        return tmp; 
    }

    bool operator==(const const_iterator& other) const    { return (current_ == other.current_); }
    bool operator==(const iterator& other)       const    { return (current_ == other.base()); }
    bool operator!=(const const_iterator& other) const    { return (!(*this == other)); }
    bool operator!=(const iterator& other)       const    { return (!(*this == other)); }
};
}