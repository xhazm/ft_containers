#pragma once

namespace ft
{
    template<
    class key_type,
    class value_type>
    struct avl_node
    {
        value_type* value;
        key_type*   key;
        avl_node*   right;
        avl_node*   left;
        avl_node*   parent;
        short       height_diff;
    };

    template<
    class key_type,
    class value_type>
    class avl_tree
    {
        
    };
} // namespace ft
