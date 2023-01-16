#pragma once

#include <memory>
#include <string>
#include "./vector.hpp"
#include "./utils.hpp"

namespace ft
{

template<
    class T,
    class Container = ft::vector<T>
> class stack
{
    public:
/* =================    Member types                        ================= */

    typedef Container                                   container_type;
    typedef typename container_type::value_type         value_type;
    typedef typename container_type::size_type          size_type;
    typedef typename container_type::reference          reference;
    typedef typename container_type::const_reference    const_reference;

   protected:
/* =================    Member objects                      ================= */

    container_type  c;

   public:
/* =================    Constructors                        ================= */

    explicit stack(const container_type& cont = Container()) : c(cont) {}

    stack(const stack& other) { c = other.c; }

    ~stack() {}

    stack &operator=(const stack& other)
    {
        if (this != &other)
            c = other.c;
        return (*this);
    }

/* =================    Element access                      ================= */
    reference       top()       { return (c.back()); }
    const_reference top() const { return (c.back()); }

/* =================    Capacity                            ================= */
    bool        empty() const   { return (c.empty()); }
    size_type   size() const    { return (c.size()); }

/* =================    Modifiers                           ================= */
    void    push(const value_type& value)   { c.push_back(value); }
    void    pop()                           { c.pop_back(); }

    template< class T, class Container >
    friend bool operator==(const ft::stack<T, Container>& lhs, const ft::stack<T, Container>& rhs);

    template< class T, class Container >
    friend bool operator<(const ft::stack<T, Container>& lhs, const ft::stack<T, Container>& rhs);
};

/* =================    Non-member functions                ================= */

template< class T, class Container >
bool operator==(const ft::stack<T,Container>& lhs, const ft::stack<T,Container>& rhs)
{
    return (lhs.c == rhs.c);
}

template< class T, class Container >
bool operator!=(const ft::stack<T,Container>& lhs, const ft::stack<T,Container>& rhs)
{
    return (!(lhs == rhs));
}

template< class T, class Container >
bool operator<(const ft::stack<T,Container>& lhs, const ft::stack<T,Container>& rhs)
{
    return (lhs.c < rhs.c)
}

template< class T, class Container >
bool operator<=(const ft::stack<T,Container>& lhs, const ft::stack<T,Container>& rhs)
{
    return (!(rhs < lhs));
}

template< class T, class Container >
bool operator>(const ft::stack<T,Container>& lhs, const ft::stack<T,Container>& rhs)
{
    return (rhs < lhs);
}

template< class T, class Container >
bool operator>=(const ft::stack<T,Container>& lhs, const ft::stack<T,Container>& rhs)
{
    return (!(lhs < rhs));
}
} // namespace ft