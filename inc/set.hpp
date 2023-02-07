#pragma once

#include "./vector.hpp"
#include "./utils.hpp"
#include "./red_black_tree.hpp"
#include "./iterator/rb_tree_iterator.hpp"
#include "./iterator/reverse_iterator.hpp"
#include "./pair.hpp"

namespace ft
{

template<
    class Key,
    class Compare = std::less<Key>,
    class Allocator = std::allocator<Key>
> class set
{
public:
/* =================    Member types                        ================= */

    typedef Key                                             key_type;
    typedef Key                                             value_type;
    typedef std::size_t                                     size_type;
    typedef std::ptrdiff_t                                  difference_type;
    typedef Compare                                         key_compare;
    typedef Compare                                         value_compare;
    typedef Allocator                                       allocator_type;
    typedef value_type&                                     reference;
    typedef const value_type&                               const_reference;
    typedef typename allocator_type::pointer                pointer;
    typedef typename allocator_type::const_pointer          const_pointer;

private:
    typedef ft::red_black_tree<value_type, value_compare>   tree;
    
public:
    typedef typename tree::const_iterator                   iterator;
    typedef typename tree::const_iterator                   const_iterator;
    typedef typename ft::reverse_iterator<iterator>         reverse_iterator;
    typedef typename ft::reverse_iterator<const_iterator>   const_reverse_iterator;


private:
/* =================    Member objects                      ================= */
    value_compare                   cmp_;
    allocator_type                  value_allocator_;
    tree                            rb_tree_;
/* =================    Constructors                        ================= */

public:

    explicit set(const Compare& comp = Compare(), const Allocator& alloc = Allocator())
        : cmp_(comp), value_allocator_(alloc) {}

    template< class InputIt >
    set(InputIt first, InputIt last,
            const Compare& comp = Compare(),
            const Allocator& alloc = Allocator())
            : cmp_(comp), value_allocator_(alloc)
    {
        insert(first, last);
    }

    set(const set& other) { *this = other; }

    set& operator=(const set& other)
    {
        if (this != &other)
        {
            cmp_ = other.cmp_; 
            value_allocator_ = other.value_allocator_; 
            rb_tree_ = other.rb_tree_;
        }
        return *this;
    }

    ~set() {}

    allocator_type get_allocator() const { return value_allocator_; }

/* =================                    Iterators                   ================= */
    iterator        begin()         { return rb_tree_.begin(); }
    const_iterator  begin() const   { return rb_tree_.begin(); }
    iterator        end()           { return rb_tree_.end(); }
    const_iterator  end() const     { return rb_tree_.end(); }
    reverse_iterator        rbegin()        { return rb_tree_.rbegin(); }
    const_reverse_iterator  rbegin() const  { return rb_tree_.rbegin(); }
    reverse_iterator        rend()          { return rb_tree_.rend(); }
    const_reverse_iterator  rend() const    { return rb_tree_.rend(); }

/* =================                    Capacity                    ================= */

    //  Checks if the container has no elements.
    bool        empty() const       { return (rb_tree_.size() == 0); }

    //  Returns the number of elements in the container.
    size_type   size() const        { return (rb_tree_.size()); }

    //  Returns the maximum number of elements the container is able to hold due to system or library implementation limitations.
    size_type   max_size() const    { return (rb_tree_.max_size()); }

/* =================                    Modifiers                   ================= */
    
    // Erases all elements from the container. After this call, size() returns zero. 
    // Invalidates any references, pointers, or iterators referring to contained elements.
    // Any past-the-end iterator remains valid. 
    void clear() { rb_tree_.clear(); }

    ft::pair<iterator, bool> insert(const value_type& value)
    { 
        return(rb_tree_.insert(value, NULL));
    }

    iterator insert(iterator pos, const value_type& value)
    {
        pos = NULL;
        return ((rb_tree_.insert(value, NULL)).first);
    };

    template< class InputIt >
    void insert(InputIt first, InputIt last)
    {
        for (InputIt it = first; it != last; ++it)
            rb_tree_.insert(*it, NULL);
    };

    size_type erase(const Key& key) 
    {
        return (rb_tree_.erase(key, NULL));
    }

    void erase(iterator pos) { rb_tree_.erase(pos); }

    void erase(iterator first, iterator last)
    {
        while (first != last)
        {
            iterator    it = first;
            ++it;
            rb_tree_.erase(first);
            first = it;
        }
    }

    void swap(set& other)
    {
        ft::swap(cmp_, other.cmp_);
        ft::swap(value_allocator_, other.value_allocator_);
        rb_tree_.swap(other.rb_tree_);
    }
/* =================                    LookUp                      ================= */

    // Finds an element with key equivalent to key. 
    iterator find(const Key& key)
    {
        return (iterator(rb_tree_.search_node(key, NULL)));
    }

    const_iterator find(const Key& key) const
    {
        return (const_iterator(rb_tree_.search_node(key, NULL)));
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
        return (rb_tree_.lower_bound(key));
    }

    const_iterator lower_bound( const Key& key ) const
    {
        return (rb_tree_.lower_bound(key));
    }

    // Returns an iterator pointing to the first element that is greater than key.
    iterator upper_bound( const Key& key )
    {
        return (rb_tree_.upper_bound(key));
    }

    const_iterator upper_bound( const Key& key ) const
    {
        return (rb_tree_.upper_bound(key));
    }

/* =================                    Observers                       ================= */

    key_compare key_comp() const        { return (key_compare()); }
    value_compare value_comp() const    { return (value_compare()); }
}; //end of set

/* =================                Non-member functions                ================= */

template< class Key, class Compare, class Alloc >
bool    operator==( const ft::set< Key, Compare, Alloc >& lhs,
                    const ft::set< Key, Compare, Alloc >& rhs )
{
    return (lhs.size() == rhs.size()
            && ft::equal(lhs.begin(), lhs.end(), rhs.begin()));
}

template< class Key, class Compare, class Alloc >
bool    operator!=( const ft::set< Key, Compare, Alloc >& lhs,
                    const ft::set< Key, Compare, Alloc >& rhs )
{
    return (!(lhs == rhs));
}

template< class Key, class Compare, class Alloc >
bool    operator<( const ft::set< Key, Compare, Alloc >& lhs,
                    const ft::set< Key, Compare, Alloc >& rhs )
{
    return (ft::lexicographical_compare(lhs.begin(), lhs.end(),
                                        rhs.begin(), rhs.end()));
}

template< class Key, class Compare, class Alloc >
bool    operator<=( const ft::set< Key, Compare, Alloc >& lhs,
                    const ft::set< Key, Compare, Alloc >& rhs )
{
    return (!(rhs < lhs));
}

template< class Key, class Compare, class Alloc >
bool    operator>( const ft::set< Key, Compare, Alloc >& lhs,
                    const ft::set< Key, Compare, Alloc >& rhs )
{
    return (rhs < lhs);
}

template< class Key, class Compare, class Alloc >
bool    operator>=( const ft::set< Key, Compare, Alloc >& lhs,
                    const ft::set< Key, Compare, Alloc >& rhs )
{
    return (!(lhs < rhs));
}
} // namespace ft