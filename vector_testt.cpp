// #include "./inc/iterator/VectorIterator.hpp"
#include <vector>
#include <list>
#include <stack>
#include <iostream>
#include "./inc/vector.hpp"
#include "./inc/utils.hpp"
#include "./tester/vector/vector_test.hpp"

#define _ratio 1

#define _vector ft::vector


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

int main(void)
{
    ft::vector<int> v;

    for (int i = 0; i < 1; ++i) {
        v.insert(v.end(), 20, i);
    }
    ft::vector<int>::iterator it = v.insert(v.begin(), 4);
    print_data(v);
    std::cout << v.size() << " before " <<v.capacity() << std::endl;
    v.resize(6);
    std::cout << v.size() << " " <<v.capacity() << std::endl;
    print_data(v);
    

    std::vector<int> v2;

    for (int i = 0; i < 1; ++i) {
        v2.insert(v2.end(), 20, i);
    }
    std::vector<int>::iterator it2 = v2.insert(v2.begin(), 4);
    print_data(v2);
    std::cout << v2.size() << " before  " <<v2.capacity() << std::endl;
    v2.resize(6);
    std::cout << v2.size() << " " <<v2.capacity() << std::endl;
    print_data(v2);
    

    // for (int i = 0; i < 2; ++i) {
    //     ft::vector<int> v;

    //     for (std::size_t i = 0; i < 3000; ++i) {
    //         v.insert(v.begin(), i, rand());
    //     }
    //     for (std::size_t i = 0; i < 3000; ++i) {
    //         v.insert(v.begin(), 20, rand());
    //     }
    // }

    // for (int i = 0; i < 2; ++i) {
    //     ft::vector<int> v;

    //     for (std::size_t i = 0; i < 1000; ++i) {
    //         v.insert(v.end(), rand());
    //     }
    //     for (std::size_t i = 0; i < 3000; ++i) {
    //         v.insert(v.begin() + 450, i, rand());
    //     }
    // }
    return 0;
}
