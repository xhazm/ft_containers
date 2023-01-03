// #include "./inc/iterator/VectorIterator.hpp"
#include <vector>
#include <iostream>
#include "./inc/vector.hpp"
#include "./tester/vector/vector_test.hpp"

int main(void)
{
    vector_test<int> vec_tester;

    vec_tester.test_erase();
    vec_tester.test_at(5, 99);
    vec_tester.test_pop_back(2);
    vec_tester.test_resize(3);



}
