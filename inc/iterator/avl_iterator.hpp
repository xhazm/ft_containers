#pragma once

#include "iterator.hpp"
#include "../pair.hpp"
#include  "../avl_node.hpp"

namespace ft {

template < class node_ptr >
node_ptr avl_tree_max(node_ptr node)
{
    while (node->right->right != NULL)
        node = node->right;
    return node;
}

template < class node_ptr >
node_ptr avl_tree_min(node_ptr node)
{
    while (node->left->left != NULL)
        node = node->left;
    return node;
}

template < class node_ptr >
node_ptr avl_tree_prev(node_ptr x)
{
    if (x->left != NULL)
        return avl_tree_max(x->left);
    while (x == x->parent->left)
        x = x->parent;
    return x->parent;
}

template < class node_ptr >
node_ptr avl_tree_next(node_ptr node)
{
    if (node->right != NULL)
        return avl_tree_min(node->right);
    while (node == node->parent->right)
        node = node->parent;
    return node->parent;
}

template < class T >
class avl_iterator
{
   private:
        typedef typename ft::iterator<ft::bidirectional_iterator_tag, T >       iterator;

    public:
        // typedef Iter                                                            iterator_type;
        typedef typename iterator::value_type                                   value_type;
        typedef typename iterator::difference_type                              difference_type;
        typedef typename iterator::reference                                    reference;
        typedef typename iterator::pointer                                      pointer;
        typedef typename iterator::iterator_category                            iterator_category;
        typedef typename ft::avl_node<T>::pointer                               node_pointer;   

        //reference == avl_node reference??         

    private:
        node_pointer current_;

/* =================                Constructors                ================= */
    public:

        avl_iterator(node_pointer& ptr = NULL) : current_(ptr) {}

        avl_iterator(const avl_iterator &other) : current_(other.base()) {}

/* =================                Destructor                  ================= */
        ~avl_iterator() {}

/* =================                Accessor                    ================= */
        node_pointer base( void ) const { return (current_); }

/* =================                Operator Overloads                    ================= */
        operator        avl_iterator< const T >( void ) const    { return (avl_iterator< const T >(current_)); }

        avl_iterator& operator=(const avl_iterator &other)      { current_ = other.base(); return (*this); }
        reference     operator*() const                         { return current_->value; }
        pointer       operator->() const                        { return &(current_->value); }
        avl_iterator& operator++()                              
        {
            current_ = avl_tree_next< node_pointer >(current_);
            return *this;
        }
        avl_iterator  operator++(int)                           { avl_iterator tmp(current_); ++current_; return tmp; }
        avl_iterator& operator--()                              
        {
            current_ = avl_tree_prev< node_pointer >(current_);
            return *this; 
        }
        avl_iterator  operator--(int)                           { avl_iterator tmp(current_); --current_; return tmp; }
};

/* =================                Non Member Operators                    ================= */
template < typename T >
bool operator==(const avl_iterator<T>& lhs, const avl_iterator<T>& rhs) { return lhs.base() == rhs.base(); }
template < typename T >
bool operator!=(const avl_iterator<T>& lhs, const avl_iterator<T>& rhs) { return !(lhs == rhs); }

}