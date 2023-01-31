#pragma once

#include <functional>
#include <iostream>
#include "./avl.hpp"
#include "./utils.hpp"
#include "./iterator/reverse_iterator.hpp"

namespace ft
{
    template<
    class Key,
    class T,
    class Compare = std::less<Key>,
    class Allocator = std::allocator<std::pair<const Key, T> >
    > class map
    {
        public:

        typedef T                                           mapped_type;
        typedef Key                                         key_type;
        typedef ft::pair<const key_type, mapped_type>       value_type;
        typedef Allocator                                   allocator_type;
        typedef Compare                                     key_compare;
        typedef std::size_t                                 size_type;
        typedef std::ptrdiff_t                              difference_type;
        typedef typename allocator_type::reference          reference;
        typedef typename allocator_type::const_reference    const_reference;
        typedef typename allocator_type::pointer            pointer;
        typedef typename allocator_type::const_pointer      const_pointer;

/* =================				Member class        				================= */

        // std::map::value_compare is a function object that compares objects of type 
        // std::map::value_type (key-value pairs) by comparing of the first components of the pairs. 
        class value_compare : std::binary_function<value_type, value_type, bool>
        {
            protected:  
                key_compare comp;

            public:
            // Initializes the internal instance of the comparator to c.
                value_compare() : comp() {}
                value_compare(key_compare c) : comp(c) {}

            public:
            // Compares lhs.first and rhs.first by calling the stored comparator.
            bool    operator()( const value_type& lhs, const value_type& rhs ) const
            {
                return (comp(lhs.first, rhs.first));
            }
        };

    private:
        typedef avl_tree<value_type, value_compare>             tree;
    
    public:
        typedef typename tree::iterator                         iterator;
        typedef typename tree::const_iterator                   const_iterator;
        typedef typename ft::reverse_iterator<iterator>         reverse_iterator;
        typedef typename ft::reverse_iterator<const_iterator>   const_reverse_iterator;
        // typedef avl_node<key_type, value_type>*             node_pointer;


    
    public:
        value_compare                   cmp_;
        allocator_type                  value_allocator_;
        tree                            avl_tree_;
        
    public:    

/* =================				Member class        				================= */

    explicit map(const Compare& comp = Compare(), const Allocator& alloc = Allocator())
        : cmp_(comp), value_allocator_(alloc), avl_tree_(tree()) {}

    template< class InputIt >
    map(InputIt first, InputIt last,
            const Compare& comp = Compare(),
            const Allocator& alloc = Allocator())
            : cmp_(comp), value_allocator_(alloc)
    {
        insert(first, last);
    }

    map(const map& other) { *this = other; }

    map& operator=(const map& other)
    {
        cmp_ = other.cmp_; 
        value_allocator_ = other.value_allocator_; 
        avl_tree_ = other.avl_tree_; 
    }

    ~map() {}

    allocator_type get_allocator() const { return value_allocator_; }


/* =================                 Element Access                   ================= */
    
    // Returns a reference to the mapped value of the element with key equivalent to key. 
    // If no such element exists, an exception of type std::out_of_range is thrown. 
    T& at(const key_type& key)
    {
        iterator    it = find(key);
        if (it == end())
            throw std::out_of_range("map::at:  key not found");
        else
            return (it->second);
    }

    const T& at(const key_type& key) const
    {
        const_iterator  it = find(key);
        if (it == end())
            throw std::out_of_range("map::at:  key not found");
        else
            return (it->second);
    }
    
    // Returns a reference to the value that is mapped to a key equivalent to key, 
    // performing an insertion if such key does not already exist. 
    T& operator[](const Key& key)
    {
        return (insert(ft::make_pair(key, mapped_type()), NULL).first->second);
    }

/* =================                    Iterators                   ================= */
    iterator        begin()         { return avl_tree_.begin(); }
    const_iterator  begin() const   { return avl_tree_.begin(); }
    iterator        end()           { return avl_tree_.end(); }
    const_iterator  end() const     { return avl_tree_.end(); }
    iterator        rbegin()        { return avl_tree_.rbegin(); }
    const_iterator  rbegin() const  { return avl_tree_.rbegin(); }
    iterator        rend()          { return avl_tree_.rend(); }
    const_iterator  rend() const    { return avl_tree_.rend(); }

/* =================				    Capacity       				================= */

    //  Checks if the container has no elements.
    bool        empty() const       { return (avl_tree_.size() == 0); }

    //  Returns the number of elements in the container.
    size_type   size() const        { return (avl_tree_.size()); }

    //  Returns the maximum number of elements the container is able to hold due to system or library implementation limitations.
    size_type   max_size() const    { return (avl_tree_.max_size()); }
    

/* =================				    Modifiers      				================= */
    
    // Erases all elements from the container. After this call, size() returns zero. 
    // Invalidates any references, pointers, or iterators referring to contained elements.
    // Any past-the-end iterator remains valid. 
    void clear() { avl_tree_.clear(); }

    std::pair<iterator, bool> insert(const value_type& value)
    { 
        return(avl_tree_.insert(value, NULL));
    }

    iterator insert(iterator pos, const value_type& value)
    {
        pos = NULL;
        return ((avl_tree_.insert(value, NULL)).first);
    };

    template< class InputIt >
    void insert(InputIt first, InputIt last)
    {
        for (InputIt it = first; it < last; ++it)
        {
            if((avl_tree_.insert(*it, NULL)).second == false)
                break ;
        }
    };

    size_type erase(const Key& key) 
    {
        return (avl_tree_.erase(ft::make_pair(key, mapped_type()), NULL));
    }

    
    // void erase(iterator pos) {avl_tree_.erase(pos)}

    // void erase( iterator first, iterator last )
    // {
        // for (iterator it = first; it < last; ++it)
        // {
        //     avl_tree_.erase(it);
        // }
    // }

    void swap(map& other)
    {
        ft::swap(cmp_, other.cmp_);
        ft::swap(value_allocator_, other.value_allocator_);
        avl_tree_.swap(other.avl_tree_);
    }

/* =================				    LookUp        				================= */

    // Finds an element with key equivalent to key. 
    iterator find(const Key& key)
    {
        return (avl_tree_.search_node(ft::make_pair(key, mapped_type()), NULL));
    }

    const_iterator find(const Key& key) const
    {
        return (const_iterator(avl_tree_.search_node(ft::make_pair(key, mapped_type()), NULL)));
    }

    // Returns the number of elements with key that compares equivalent to the specified argument.
    // Count max: 1. Since this implementation is not allowed to have duplicates.
    size_type count( const Key& key ) const
    {
        return (find(key) != end());
    }

    // Returns a range containing all elements with the given key in the container. 
    // The range is defined by two iterators, one pointing to the first element that is not less than key and another pointing to the first element greater than key. 
    // Alternatively, the first iterator may be obtained with lower_bound(), and the second with upper_bound().
    ft::pair<iterator, iterator> equal_range( const key_type& key )
    {
        return (ft::pair<iterator, iterator>(lower_bound(key), upper_bound(key)));
    }

    ft::pair<const_iterator, const_iterator> equal_range( const key_type& key ) const
    {
        return (ft::pair<const_iterator, const_iterator>(lower_bound(key), upper_bound(key)));
    }

    // Returns an iterator pointing to the first element that is not less than key.
    iterator lower_bound( const Key& key )
    {
        return (avl_tree_.lower_bound(ft::make_pair(key, mapped_type())));
    }

    const_iterator lower_bound( const Key& key ) const
    {
        return (avl_tree_.lower_bound(ft::make_pair(key, mapped_type())));
    }

    // Returns an iterator pointing to the first element that is greater than key.
    iterator upper_bound( const Key& key )
    {
        return (avl_tree_.upper_bound(ft::make_pair(key, mapped_type())));
    }

    const_iterator upper_bound( const Key& key ) const
    {
        return (avl_tree_.upper_bound(ft::make_pair(key, mapped_type())));
    }

/* =================				    Observers        				================= */

    key_compare key_comp() const        { return (key_compare()); }
    value_compare value_comp() const    { return (value_compare()); }
	
    };

/* =================                Non-member functions                ================= */

template< class Key, class T, class Compare, class Alloc >
bool    operator==( const ft::map< Key, T, Compare, Alloc >& lhs,
                    const ft::map< Key, T, Compare, Alloc >& rhs )
{
    return (lhs.size() == rhs.size()
            && ft::equal(lhs.begin(), lhs.end(), rhs.begin()));
}

template< class Key, class T, class Compare, class Alloc >
bool    operator!=( const ft::map< Key, T, Compare, Alloc >& lhs,
                    const ft::map< Key, T, Compare, Alloc >& rhs )
{
    return (!(lhs == rhs));
}

template< class Key, class T, class Compare, class Alloc >
bool    operator<( const ft::map< Key, T, Compare, Alloc >& lhs,
                    const ft::map< Key, T, Compare, Alloc >& rhs )
{
    return (ft::lexicographical_compare(lhs.begin(), lhs.end(),
                                        rhs.begin(), rhs.end()));
}

template< class Key, class T, class Compare, class Alloc >
bool    operator<=( const ft::map< Key, T, Compare, Alloc >& lhs,
                    const ft::map< Key, T, Compare, Alloc >& rhs )
{
    return (!(rhs < lhs));
}

template< class Key, class T, class Compare, class Alloc >
bool    operator>( const ft::map< Key, T, Compare, Alloc >& lhs,
                    const ft::map< Key, T, Compare, Alloc >& rhs )
{
    return (rhs < lhs);
}

template< class Key, class T, class Compare, class Alloc >
bool    operator>=( const ft::map< Key, T, Compare, Alloc >& lhs,
                    const ft::map< Key, T, Compare, Alloc >& rhs )
{
    return (!(lhs < rhs));
}

} // namespace ft