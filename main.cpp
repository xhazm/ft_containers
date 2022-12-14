// #include "./inc/iterator/VectorIterator.hpp"
#include <vector>
#include <iostream>
#include "./inc/vector.hpp"

int main(void)
{
	std::vector<int> i;
	std::vector<int>::iterator it;
    ft::vector<int> hi;
    ft::vector<int>::iterator itertest;
    ft::vector<int>::iterator itertest2;
    // std::cout << "size: "<<i.size() << std::endl;
    // std::cout << "capa: "<<i.capacity() << std::endl;
	// i.push_back(6);
	// i.push_back(6);
    // std::cout << "size: "<<i.size() << std::endl;
    // std::cout << "capa: "<<i.capacity() << std::endl;

    int test = 0;
	hi.push_back(6);
	hi.push_back(9);
	hi.push_back(6);
	hi.push_back(7);
	hi.push_back(6);
	hi.push_back(5);
	hi.push_back(3);
	hi.push_back(1);

    // try {
    //     // Set element 6
    //     i.at(4) = 666;
    // } catch (std::out_of_range const& exc) {
    //     std::cout << exc.what() << '\n';}
    
    for(ft::vector<int>::iterator it = hi.begin(); it != hi.end(); ++it)
    {
        if (*it == 9)
            itertest = it;
        if (*it == 7)
            itertest2 = it;
        std::cout << *it << std::endl;
    }
    std::cout << "size: "<<hi.size() << std::endl;
    std::cout << "capa: "<<hi.capacity() << std::endl;

    hi.erase(itertest, itertest2);

    std::cout << "after erasing" << std::endl;
    for(ft::vector<int>::iterator it = hi.begin(); it != hi.end(); ++it)
    {
        std::cout << *it << std::endl;
    }
    std::cout << "size: "<<hi.size() << std::endl;
    std::cout << "capa: "<<hi.capacity() << std::endl;

    hi.pop_back();
    std::cout << "popped the back" << std::endl;

    for(ft::vector<int>::iterator it = hi.begin(); it != hi.end(); ++it)
    {
        std::cout << *it << std::endl;
    }

    std::cout << "size: "<<hi.size() << std::endl;
    std::cout << "capa: "<<hi.capacity() << std::endl;


    std::cout << "resize" << std::endl;
    hi.resize(10, 2);
    for(ft::vector<int>::iterator it = hi.begin(); it != hi.end(); ++it)
    {
        std::cout << *it << std::endl;
    }
    std::cout << "size: "<<hi.size() << std::endl;
    std::cout << "capa: "<<hi.capacity() << std::endl;

    hi.resize(0, 2);
    for(ft::vector<int>::iterator it = hi.begin(); it != hi.end(); ++it)
    {
        std::cout << *it << std::endl;
    }

    std::cout << "size: "<<hi.size() << std::endl;
    std::cout << "capa: "<<hi.capacity() << std::endl;

	// ft::VectorIterator<int> test;
	// ft::VectorIterator<int> test2;

	// if (test == test2)
	// 	std::cout << "true" << std::endl;

}
