#include "./inc/map.hpp"
#include <math.h>

int main()
{
    int arr1[] = {1,2,3,4,5};
    int arr2[] = {11,22,33,44,55};
    ft::map<int, int> map;
    ft::avl_tree<ft::pair<int, int>, std::less<ft::pair<int,int>>> avl;
    ft::pair<int, int> test(arr1[0], arr2[0]);
    avl.insert(test, NULL);

}