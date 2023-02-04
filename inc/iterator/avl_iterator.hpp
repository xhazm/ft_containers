#pragma once

#include "iterator.hpp"
#include "../pair.hpp"
#include  "../avl_node.hpp"

namespace ft {

template < class node_ptr >
node_ptr avl_tree_max(node_ptr node)
{
    while (node->right != NULL)
        node = node->right;
    return node;
}

template < class node_ptr >
node_ptr avl_tree_min(node_ptr node)
{
    while (node->left != NULL)
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

        avl_iterator(const node_pointer& ptr = NULL) : current_(ptr) {}

        avl_iterator(const avl_iterator &other) : current_(other.base()) {}

/* =================                Destructor                  ================= */
        ~avl_iterator() {}

/* =================                Accessor                    ================= */
        node_pointer base( void ) const     { return (current_); }

/* =================                Operator Overloads                    ================= */

        avl_iterator& operator=(const avl_iterator &other)      { current_ = other.base(); return (*this); }
        reference     operator*()                               { return current_->value; }
        pointer       operator->()                              { return &(current_->value); }
        reference     operator*() const                         { return current_->value; }
        pointer       operator->() const                        { return &(current_->value); }
        avl_iterator& operator++()                              
        {
            current_ = avl_tree_next< node_pointer >(current_);
            return *this;
        }
        avl_iterator  operator++(int)                           { avl_iterator tmp(current_); ++*this; return tmp; }
        avl_iterator& operator--()                              
        {
            current_ = avl_tree_prev< node_pointer >(current_);
            return *this; 
        }
        avl_iterator  operator--(int)                           { avl_iterator tmp(current_); --*this; return tmp; }
        
        bool    operator==(const avl_iterator& other) {return current_ == other.current_;}
        bool    operator!=(const avl_iterator& other) {return current_ != other.current_;}
};

template < class T >
class const_avl_iterator
{
   private:
        typedef typename ft::iterator<ft::bidirectional_iterator_tag, const T >       iterator_base;

    public:
        // typedef Iter                                                            iterator_type;
        typedef typename iterator_base::value_type                                   value_type;
        typedef typename iterator_base::difference_type                              difference_type;
        typedef typename iterator_base::reference                                    reference;
        typedef typename iterator_base::pointer                                      pointer;
        typedef typename iterator_base::iterator_category                            iterator_category;
        typedef typename ft::avl_node<const T>::const_pointer                   node_pointer;
        typedef avl_iterator<T>                                                 iterator;
        typedef const_avl_iterator                                              const_iterator;
        //reference == avl_node reference??         

    private:
        node_pointer current_;

/* =================                Constructors                ================= */
    public:

        const_avl_iterator(const node_pointer& ptr = NULL) : current_(ptr) {}

        const_avl_iterator(const const_iterator &other) : current_(other.base()) {}
        
        const_avl_iterator(const iterator &other) : current_(reinterpret_cast<node_pointer>(other.base())) {}

/* =================                Destructor                  ================= */
        ~const_avl_iterator() {}

/* =================                Accessor                    ================= */
        node_pointer base( void ) const { return (current_); }

/* =================                Operator Overloads                    ================= */
        // operator        const_avl_iterator< const T >( void ) const    { return (const_avl_iterator< const T >(current_)); }

        const_iterator& operator=(const const_iterator &other)      { current_ = other.base(); return (*this); }
        reference     operator*()                               { return current_->value; }
        pointer       operator->()                              { return &(current_->value); }
        reference       operator*() const                         { return current_->value; }
        pointer         operator->() const                        { return &(current_->value); }
        const_iterator& operator++()                              
        {
            current_ = avl_tree_next< node_pointer >(current_);
            return *this;
        }
        const_iterator  operator++(int)                           { const_iterator tmp(current_); ++*this; return tmp; }
        const_iterator& operator--()                              
        {
            current_ = avl_tree_prev< node_pointer >(current_);
            return *this;
        }
        const_iterator  operator--(int)                           { const_iterator tmp(current_); --*this; return tmp; }
        
        bool    operator==(const const_avl_iterator& other) {return current_ == other.current_;}
        bool    operator!=(const const_avl_iterator& other) {return current_ != other.current_;}
};
}