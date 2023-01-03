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

// ~vector_test(){vec.clear();}

void test_erase()
{
    typename ft::vector<T>::iterator itertest;
    typename ft::vector<T>::iterator itertest2;
    typename ft::vector<T>::iterator it = vec.begin();
    for(int i = 0; it != vec.end(); ++it, ++i)
    {
        if (*it == 9)
            itertest = it;
        if (*it == 7)
            itertest2 = it;
    }
    PRINT("start erase from\t",*itertest)
    PRINT("end erase until\t\t" ,*itertest2);
    vec.erase(itertest, itertest2); 
    PRINT_CAPA_SIZE("after erasing",vec, print_data());
    // std::cout << "size: "<<vec.size() << std::endl;
    // std::cout << "capa: "<<vec.capacity() << std::endl;

    // vec.erase(itertest, itertest2); 
    // std::cout << "after erasing" << std::endl;
    // for(ft::vector<T>::iterator it = vec.begin(); it != vec.end(); ++it)
    // {
    //     std::cout << *it << std::endl;
    // }
    // std::cout << "size: "<<vec.size() << std::endl;
    // std::cout << "capa: "<<vec.capacity() << std::endl;
}

std::string print_data()
{
    typename ft::vector<T>::iterator it = vec.begin();
    for(; it != vec.end(); ++it)
        PRINT("data:\t", *it)
    return ("");
}
};