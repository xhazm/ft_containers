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

/* =================	    	   Member Functions			   ================= */
void test_assign(size_t count, T value)
{
    ft_vec.assign(count, value);
    std_vec.assign(count, value);
    PRINT_ALL("after assigning times: ", count ,ft_vec, std_vec, print_data());
}

/* =================		   Element Access			   ================= */
template<class U>
void test_at_sub(T first, const T second, long pos_to_change, U& test_vec)
{
    try {
        test_vec.at(100) = first;
    } catch (std::out_of_range const& exc) {
        PRINT("exception thrown. exc.what: ", exc.what())}
    try {
        test_vec.at(pos_to_change) = second;
        const T const_ref_test = test_vec.at(4);
    } catch (std::out_of_range const& exc) {
        std::cout << exc.what() << '\n';}
}

void test_at(T first_num, T second_num, long pos_to_change)
{
    test_at_sub(first_num, second_num, pos_to_change, ft_vec);
    test_at_sub(first_num, second_num, pos_to_change, std_vec);
    PRINT_ALL("after changing pos: ", pos_to_change ,ft_vec, std_vec, print_data());
}

void test_brackets(T value, long pos_to_change)
{
    ft_vec[pos_to_change] = value;
    std_vec[pos_to_change] = value;
    PRINT_ALL("after changing pos: ", pos_to_change ,ft_vec, std_vec, print_data());
}
void test_front_back_access()
{
    PRINT("ft_front: ", ft_vec.front());
    PRINT("std_front: ", ft_vec.front());
    PRINT("ft_back: ", ft_vec.back());
    PRINT("std_back: ", ft_vec.back());
}

/* =================				Capacity				================= */
void test_capacity_functions()
{
    PRINT("ft max_size?: ",ft_vec.max_size());
    PRINT("ft empty?: ", ft_vec.empty());
    PRINT("std max_size?: ",std_vec.max_size());
    PRINT("std empty?: ", std_vec.empty());
    PRINT_ALL("", "", ft_vec, std_vec, "")
}

/* =================				Capacity Modulator	  ================= */
void reserve(size_t value)
{
    ft_vec.reserve(value);
    std_vec.reserve(value);
    PRINT_ALL("after reserving: ", value ,ft_vec, std_vec, print_data());
}
/* =================			   Modifiers			  ================= */

void clear()
{
    ft_vec.clear();
    std_vec.clear();
    PRINT_ALL("clearing: ", "" ,ft_vec, std_vec, print_data());
}

void push_back(T value)
{
    ft_vec.push_back(value);
    std_vec.push_back(value);
}

template <class U>
void test_erase_sub(T& from, T& to, U& test_vec)
{
    typename U::iterator from_it;
    typename U::iterator to_it;
    typename U::iterator it = test_vec.begin();
    for(; it != test_vec.end(); ++it)
    {
        if (*it == from)
            from_it = it;
        if (*it == to)
            to_it = it;
    }
    PRINT("start erase from\t", *from_it)
    PRINT("end erase until\t\t", *to_it);
    test_vec.erase(from_it, to_it); 
    if (*(test_vec.begin()))
    {
        PRINT("erase beginning\t", *(test_vec.begin()))
    }
    test_vec.erase(test_vec.begin()); 

}

void test_erase(T from, T to)
{
    test_erase_sub(from, to, ft_vec);
    test_erase_sub(from, to, std_vec);
    PRINT_ALL("after erasing", "" ,ft_vec, std_vec, print_data());
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
void test_insert_sub(U& test_vec, std::string what)
{
    test_vec.insert(test_vec.begin(), 10, test_vec[0]);
    test_vec.insert(test_vec.begin(), test_vec[0]);
    test_vec.insert(test_vec.begin() + 1, test_vec.begin(), test_vec.end());
}


void test_insert()
{
    test_insert_sub(ft_vec, " __ft_insert__ ");
    test_insert_sub(std_vec, " __std_insert__ ");
    PRINT_ALL("after insert in new vector: ", "" ,ft_vec, std_vec, print_data());
}

template <class U>
void test_swap_sub(U& test_vec, std::string what)
{
    U   inverted_vec;
    inverted_vec.reserve(test_vec.size());
    for (typename U::reverse_iterator it = test_vec.rbegin(); it != test_vec.rend(); ++it)
    {
        inverted_vec.push_back(*it);
    }
    test_vec.swap(inverted_vec);
}


void test_swap()
{
    test_swap_sub(ft_vec, " __ft_insert__ ");
    test_swap_sub(std_vec, " __std_insert__ ");
    PRINT_ALL("after swap with inverted vector: ", "" ,ft_vec, std_vec, print_data());
}

/* =================			 Utils			  ================= */
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
};