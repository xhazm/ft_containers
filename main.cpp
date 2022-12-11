// #include "./inc/iterator/VectorIterator.hpp"
#include <vector>
#include <iostream>
#include "./inc/vector.hpp"

int main(void)
{
	std::vector<int> i;
	std::vector<int>::iterator it;
    ft::vector<int> hi;

	i.push_back(5);
	i.push_back(6);

    int test = 0;
	hi.push_back(6);
	hi.push_back(9);
	hi.push_back(6);
	hi.push_back(7);
	hi.push_back(6);

    try {
        // Set element 6
        i.at(4) = 666;
    } catch (std::out_of_range const& exc) {
        std::cout << exc.what() << '\n';}
    
    for(ft::vector<int>::iterator it = hi.begin(); it != hi.end(); ++it)
    {
        std::cout << *it << std::endl;
    }
	// ft::VectorIterator<int> test;
	// ft::VectorIterator<int> test2;

	// if (test == test2)
	// 	std::cout << "true" << std::endl;

}

// #include <cstddef>
// #include <iostream>
// #include <iterator>
 
// template <typename T, std::size_t SIZE>
// class Stack
// {
//     T arr[SIZE];
//     std::size_t pos = 0;
// public:
//     T pop()
//     {
//         return arr[--pos];
//     }
//     Stack& push(const T& t)
//     {
//         arr[pos++] = t;
//         return *this;
//     }
//     // we wish that looping on Stack would be in LIFO order
//     // thus we use std::reverse_iterator as an adaptor to existing iterators
//     // (which are in this case the simple pointers: [arr, arr+pos)
//     auto begin() { return std::reverse_iterator(arr + pos); }
//     auto end() { return std::reverse_iterator(arr); }
// };
 
// int main()
// {
//     Stack<int, 8> s;
//     s.push(5).push(15).push(25).push(35);
//     for (int val: s)
//         std::cout << val << ' ';
// }