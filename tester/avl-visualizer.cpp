#include "map.hpp"
#include <math.h>

int main()
{
    int arr1[] = {1,2,3,4,5};
    int arr2[] = {11,22,33,44,55};
    ft::map<int, int> map;
    ft::avl_tree<ft::pair<int, int>, std::less<ft::pair<int,int>>> avl;
    ft::pair<int, int> test(arr1[0], arr2[0]);
    avl.insert(test, NULL);

    // size_t height = 0;
    // size_t width = pow(0, 2);
    // size_t pitch = (width / 2);
    // for(int i = 0; i < height; ++i, pitch = (width / height + 1))
    // {
    // }


}