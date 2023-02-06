#pragma once

namespace ft
{
    enum COLOR {
    BLACK,
    RED
    };
    template<
    class value_type
    > struct red_black_node
    {
    public:

        typedef red_black_node< value_type >              node_type;
        typedef node_type*                          pointer;
        typedef const node_type*                    const_pointer;

        value_type  value;
        pointer     right;
        pointer     left;
        pointer     parent;
        bool        color;

        // avl_node() : parent(NULL), left(NULL), right(NULL), value(value_type()) {}

        // avl_node(const node_type& other) { *this = other; }

        // ~avl_node() {}

        // node_type&  operator=( const node_type& other )
        // {
        //     if (this != &other )
        //     {
        //         value = other.value;
        //         right = other.right;
        //         left = other.left;
        //         parent = other.parent;
        //     }
        //     return (*this);
        // }
    };
}