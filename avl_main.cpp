#include "./inc/map.hpp"
#include <math.h>
#include <iostream>

// int main(int argc, char* argv[])
// {
//     int arr1[] = {10,20,30,25,35,40};
//     int arr2[] = {11,22,33,44,55};
//     ft::map<int, int> map;
//     ft::avl_tree<ft::pair<int, int>, std::less<ft::pair<int,int>>> avl;
//     for(int i = 0; i < argc; ++i)
//     {
//         ft::pair<int, int> test(arr1[i], arr2[0]);
//         avl.insert(test, NULL);
//     }
//     // avl.insert(test2, NULL);
//     // avl.insert(test3, NULL);
//     std::cout << avl.root_->value.first << std::endl;

// }

int main()
{
    int arr1[] = {10,20,30,25,35,40, 2, 9, 88, 77, 1, 3, 4,5};
    int arr2[] = {11,22,33,44,55};
    ft::map<int, int> map;
    ft::avl_tree<ft::pair<int, int>, std::less<ft::pair<int,int>>> avl;
    int argc = 14;
    for(int i = 0; i < argc; ++i)
    {
        ft::pair<int, int> test(arr1[i], arr2[0]);
        avl.insert(test, NULL);
    }
    ft::pair<int, int> test(arr1[5], arr2[0]);
    std::cout << test.first << std::endl;
    avl.erase(test, NULL);
    test.first = 77;
    avl.erase(test, NULL);
    test.first = 20;
    avl.erase(test, NULL);
    test.first = 30;
    avl.erase(test, NULL);
    std::cout << avl.root_->value.first << std::endl;

}