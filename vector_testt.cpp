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


int main(void)
{

    for (int i = 0; i < 2; ++i) {
    ft::vector<int> v;

    for (std::size_t i = 0; i < 10000; ++i) {
        v.insert(v.end(), i, i);
    }
    }

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
