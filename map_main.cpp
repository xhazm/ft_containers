#include "./inc/map.hpp"
#include <math.h>
#include <iostream>
#include <map>
#include <vector>

#define _map ft::map

#define _ratio 1

#define _make_pair ft::make_pair

template<class U>
std::string print_data(U& test_vec)
{
    typename U::iterator test_it = test_vec.begin();
    for(; test_it != test_vec.end(); ++test_it)
    {
        std::cout << "test_data: " << *test_it << std::endl;
    }
    return ("");
}

template<class U>
std::string print_data(U test_vec)
{
    typename U::iterator test_it = test_vec.begin();
    for(; test_it != test_vec.end(); ++test_it)
    {
        std::cout << "test_data: " << *test_it << std::endl;
    }
    return ("");
}

template<class T>
std::string print_data(std::vector<T> test_ft_vec, std::vector<T> test_std_vec)
{
    typename std::vector<T>::iterator test_ft_it = test_ft_vec.begin();
    typename std::vector<T>::iterator test_std_it = test_std_vec.begin();
    for(; test_ft_it != test_ft_vec.end(); ++test_ft_it, ++test_std_it)
    {
        std::cout << "ft_data: " << *test_ft_it <<  "\t\t\t\tstd_data: " <<  *test_std_it << std::endl;
    }
    return ("");
}


template <class T, class V>
std::vector<int> assign_overload_test(std::map<T, V> mp) {
    std::vector<int> v;
    for (int i = 0, j = 10; i < 20 * _ratio; ++i, ++j)
        mp.insert(std::make_pair(i, j));
    std::map<T, V> mp2;
    for (int i = 20 * _ratio, j = 200010; i < 40 * _ratio; ++i, ++j)
        mp2.insert(std::make_pair(i, j));
    mp2 = mp;
    typename std::map<T, V>::iterator it = mp2.begin();
    for (; it != mp2.end(); it++) {
        v.push_back(it->first);
        v.push_back(it->second);
    }
    v.push_back(mp2.size());
    return v;
}

template <class T, class V>
std::vector<int> assign_overload_test(_map<T, V> mp) {
    std::vector<int> v;
    for (int i = 0, j = 10; i < 20 * _ratio; ++i, ++j)
        mp.insert(_make_pair(i, j));
    _map<T, V> mp2;
    for (int i = 20 * _ratio, j = 200010; i < 40 * _ratio; ++i, ++j)
        mp2.insert(_make_pair(i, j));
    mp2 = mp;
    typename _map<T, V>::iterator it = mp2.begin();
    for (; it != mp2.end(); it++) {
        v.push_back(it->first);
        v.push_back(it->second);
    }
    v.push_back(mp2.size());
    mp2.erase(mp2.begin());
    return v;
}

int main()
{
    // std::vector< ft::pair<int, int> > vec;
    // int arr[] = {10,20,30,25,35,40, 2, 9, 88, 77, 1, 3, 4,5};
    // ft::pair<int, int> test(0,0);
    // for(int i = 0; i < 14; ++i)
    // {
    //     test.first = arr[i];
    //     vec.push_back(test);
    // }

    // ft::map<int,int> map(vec.begin(), vec.end());
    // std::cout << "size: " << map.size() << std::endl;

    // // std::map<int,int> map2(vec.begin(), vec.end());

    // ft::map<int,int>::iterator it = map.begin();
    // for(; it != map.end(); ++it)
    // {
    //     if (it->first == 4)
    //         it->second = 99;
    //     std::cout << it->first << std::endl;
    // }

    // // for(std::map<int,int>::iterator it = map2.begin(); it != map2.end(); ++it)
    // // {
    // //     // if (it->first == 4)
    // //     //     it->second = 99;
    // //     std::cout << it->first << std::endl;
    // // }
    // std::cout << "at 4: " << map.at(4) << std::endl;


    ft::map<int,int> map_ft_test;
    std::map<int,int> map_std_test;
    print_data(assign_overload_test(map_ft_test), assign_overload_test(map_std_test));
    



}