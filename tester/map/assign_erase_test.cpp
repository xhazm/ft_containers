#include "../../inc/map.hpp"
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
    typename std::map<T, V>::iterator it_del;
    it_del = mp2.find(15);
    mp2.erase(it_del);
    mp2.erase(7);
    for (; it != mp2.end(); ) {
        v.push_back(it->first);
        v.push_back(it->second);
        it_del = it;
        ++it;
        mp2.erase(it_del);
        if (it == mp2.end())
            break;
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
    typename _map<T, V>::iterator it_del;
    it_del = mp2.find(15);
    mp2.erase(it_del);
    mp2.erase(7);
    for (; it != mp2.end(); ) {
        v.push_back(it->first);
        v.push_back(it->second);
        it_del = it;
        ++it;
        mp2.erase(it_del);
        if (it == mp2.end())
            break;
    }
    v.push_back(mp2.size());

    return v;
}
