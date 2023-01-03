#pragma once

#include "../../inc/vector.hpp"

std::string convert_string_to_line(std::string  str)
{
    std::string ret;
    for(int i = 0; i < str.size(); ++i)
        ret += "-";
    return (ret);
}

template <class T>
class vector_test
{

#define DISRUPT(what) "---------------------------------" << what << "---------------------------------" << std::endl
#define PRINT(what, value) std::cout << what << value << std::endl;
#define FOO(fmt, ...) printf(fmt, ##__VA_ARGS__);
#define PRINT_CAPA_SIZE(when,vec, print_fun) std::cout << DISRUPT(when) << "size: " <<  vec.size() << "\tcapa: " << vec.capacity() << std::endl << print_fun << DISRUPT(convert_string_to_line(when));

public:

ft::vector<T> vec;

vector_test(){
    vec.push_back(6);
	vec.push_back(9);
	vec.push_back(6);
	vec.push_back(7);
	vec.push_back(6);
	vec.push_back(5);
	vec.push_back(3);
	vec.push_back(1);
    PRINT_CAPA_SIZE("starting numbers", vec, print_data());
}
~vector_test(){}

void test_erase()
{
    typename ft::vector<T>::iterator itertest;
    typename ft::vector<T>::iterator itertest2;
    typename ft::vector<T>::iterator it = vec.begin();
    for(; it != vec.end(); ++it)
    {
        if (*it == 9)
            itertest = it;
        if (*it == 7)
            itertest2 = it;
    }
    PRINT("start erase from\t", *itertest)
    PRINT("end erase until\t\t", *itertest2);
    vec.erase(itertest, itertest2); 
    PRINT_CAPA_SIZE("after erasing",vec, print_data());
}

void test_at(T first, T second)
{

    try {
        // Set element 6
        vec.at(100) = first;
    } catch (std::out_of_range const& exc) {
        PRINT("exception, trying changing at[100]. exc.what: ", exc.what())}
    try {
        // Set element 6
        vec.at(4) = second;
    } catch (std::out_of_range const& exc) {
        std::cout << exc.what() << '\n';}
    PRINT_CAPA_SIZE("after changing [4] pos",vec, print_data());
}

void test_pop_back(size_t num)
{
    vec.pop_back();
    vec.pop_back();
    PRINT_CAPA_SIZE("after popping back",vec, print_data());
}

void test_resize(size_t num)
{
    vec.resize(num);
    PRINT_CAPA_SIZE("after resizing",vec, print_data());
}

std::string print_data()
{
    typename ft::vector<T>::iterator it = vec.begin();
    for(; it != vec.end(); ++it)
        PRINT("data:\t", *it)
    return ("");
}




	// std::vector<int> i;
	// std::vector<int>::iterator it;
    // ft::vector<int> hi;
    // ft::vector<int>::iterator itertest;
    // ft::vector<int>::iterator itertest2;



    // hi.pop_back();
    // std::cout << "popped the back" << std::endl;

    // for(ft::vector<int>::iterator it = hi.begin(); it != hi.end(); ++it)
    // {
    //     std::cout << *it << std::endl;
    // }

    // std::cout << "size: "<<hi.size() << std::endl;
    // std::cout << "capa: "<<hi.capacity() << std::endl;

    // std::cout << "resize" << std::endl;
    // hi.resize(10, 2);
    // for(ft::vector<int>::iterator it = hi.begin(); it != hi.end(); ++it)
    // {
    //     std::cout << *it << std::endl;
    // }
    // std::cout << "size: "<<hi.size() << std::endl;
    // std::cout << "capa: "<<hi.capacity() << std::endl;

    // hi.resize(0, 2);
    // for(ft::vector<int>::iterator it = hi.begin(); it != hi.end(); ++it)
    // {
    //     std::cout << *it << std::endl;
    // }

    // std::cout << "size: "<<hi.size() << std::endl;
    // std::cout << "capa: "<<hi.capacity() << std::endl;

	// ft::VectorIterator<int> test;
	// ft::VectorIterator<int> test2;

	// if (test == test2)
	// 	std::cout << "true" << std::endl;

};