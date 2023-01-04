#pragma once

#include "../../inc/vector.hpp"
#include <sstream>

std::string convert_string_to_line(std::string  str)
{
    std::string ret;
    for(int i = 0; i < str.size(); ++i)
        ret += "-";
    return (ret);
}
std::string convert_string_to_line(long long num)
{
    std::string ret;
    if (num < 0)
        return("");
    while (num > 9)
    {
        ret += "-";
        num = num / 10;
    }
    ret += "-";
    return (ret);
}

template <class T>
class vector_test
{

#define DISRUPT(what, how_often) "---------------------------------" << what << how_often << "---------------------------------" << std::endl << std::endl
#define PRINT(what, value) std::cout << what << value << std::endl;
#define FOO(fmt, ...) printf(fmt, ##__VA_ARGS__);
#define PRINT_CAPA_SIZE(vec, what) what << "size: " <<  vec.size() << "\t" << what <<"capa: " << vec.capacity()
#define PRINT_ALL(when, how_often, ft_vec, std_vec, print_fun) std::cout << DISRUPT(when, how_often) << PRINT_CAPA_SIZE(ft_vec, "ft_") << "\t\t" << PRINT_CAPA_SIZE(std_vec, "std_") << std::endl << print_fun << DISRUPT(convert_string_to_line(when), convert_string_to_line(how_often));
public:

ft::vector<T> ft_vec;
std::vector<T> std_vec;

vector_test(){}
~vector_test(){}

void push_back(T value)
{
    ft_vec.push_back(value);
    std_vec.push_back(value);
}

template <class U>
void test_erase_sub(U& test_vec)
{
    typename U::iterator itertest;
    typename U::iterator itertest2;
    typename U::iterator it = test_vec.begin();
    for(; it != test_vec.end(); ++it)
    {
        if (*it == 9)
            itertest = it;
        if (*it == 7)
            itertest2 = it;
    }
    PRINT("start erase from\t", *itertest)
    PRINT("end erase until\t\t", *itertest2);
    test_vec.erase(itertest, itertest2); 
}
void test_erase()
{
    test_erase_sub(ft_vec);
    test_erase_sub(std_vec);
    PRINT_ALL("after erasing", "" ,ft_vec, std_vec, print_data());
}

template<class U>
void test_at_sub(T first, T second, U& test_vec)
{
    try {
        test_vec.at(100) = first;
    } catch (std::out_of_range const& exc) {
        PRINT("exception thrown. exc.what: ", exc.what())}
    try {
        test_vec.at(4) = second;
    } catch (std::out_of_range const& exc) {
        std::cout << exc.what() << '\n';}
}

void test_at(T first_num, T second_num, long pos_to_change)
{
    test_at_sub(first_num, second_num, ft_vec);
    test_at_sub(first_num, second_num, std_vec);
    PRINT_ALL("after changing pos: ", pos_to_change ,ft_vec, std_vec, print_data());
}

void test_pop_back(size_t num_times)
{
    for(int i = 0; i < num_times; i++)
    {
        ft_vec.pop_back();
        std_vec.pop_back();
    }
    PRINT_ALL("after pop_back times: ", num_times, ft_vec, std_vec, print_data());
}

void test_resize(size_t num)
{
    ft_vec.resize(num);
    std_vec.resize(num);
    PRINT_ALL("after resizing to: ", num ,ft_vec, std_vec, print_data());
}


template <class U>
void test_swap_sub(U& test_vec)
{
    typename U::iterator it;
    U   swap_vec;
    swap_vec.insert(swap_vec.begin(), test_vec.begin(), test_vec.end());
    for(typename U::iterator swap_it = swap_vec.begin(); swap_it != swap_vec.end(); ++swap_it)
    {
        std::cout << "insert_data: " << *swap_it << std::endl;
    }
}

void test_swap()
{
    test_swap_sub(ft_vec);
    test_swap_sub(std_vec);
}


std::string print_data()
{
    typename ft::vector<T>::iterator ft_it = ft_vec.begin();
    typename std::vector<T>::iterator std_it = std_vec.begin();
    for(; ft_it != ft_vec.end(); ++ft_it, ++std_it)
    {
        std::cout << "ft_data: " << *ft_it <<  "\t\t\t\tstd_data: " <<  *std_it << std::endl;
    }
    return ("");
}
};