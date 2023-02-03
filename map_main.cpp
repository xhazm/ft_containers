#include "./inc/map.hpp"
#include <math.h>
#include <iostream>
#include <map>
#include <vector>


int main()
{
    std::vector< ft::pair<int, int> > vec;
    int arr[] = {10,20,30,25,35,40, 2, 9, 88, 77, 1, 3, 4,5};
    ft::pair<int, int> test(0,0);
    for(int i = 0; i < 14; ++i)
    {
        test.first = arr[i];
        vec.push_back(test);
    }

    ft::map<int,int> map(vec.begin(), vec.end());
    std::cout << "size: " << map.size() << std::endl;

    // std::map<int,int> map2(vec.begin(), vec.end());

    ft::map<int,int>::iterator it = map.begin();
    for(; it != map.end(); ++it)
    {
        if (it->first == 4)
            it->second = 99;
        std::cout << it->first << std::endl;
    }

    // for(std::map<int,int>::iterator it = map2.begin(); it != map2.end(); ++it)
    // {
    //     // if (it->first == 4)
    //     //     it->second = 99;
    //     std::cout << it->first << std::endl;
    // }
    std::cout << "at 4: " << map.at(4) << std::endl;




    // int arr2[] = {11,22,33,44,55};
    // ft::map<int, int> map;
    // ft::avl_tree<ft::pair<int, int>, std::less<ft::pair<int,int>>> avl;
    // int argc = 14;
    // for(int i = 0; i < argc; ++i)
    // {
    //     ft::pair<int, int> test(arr[i], arr2[0]);
    //     avl.insert(test, NULL);
    // }
    // test.first = 40;
    // avl.erase(test, NULL);
    // test.first = 77;
    // avl.erase(test, NULL);
    // test.first = 20;
    // avl.erase(test, NULL);
    // test.first = 30;
    // avl.erase(test, NULL);

    // for(ft::avl_tree<ft::pair<int, int>, std::less<ft::pair<int,int>>>::iterator it = avl.begin(); it != avl.end(); ++it)
    // {
    //     std::cout << it->first << std::endl;
    // }

}
// ft::avl_node<ft::pair<const int, int> >::node_type*&
// ft::avl_node<ft::pair<const int, int> >*&

// ft::avl_tree<ft::pair<const int, int>
// ft::map<int, int>::value_compare, std::allocator<ft::pair<const int, int> > >::node_pointer
// ft::avl_node<ft::pair<const int, int> >*