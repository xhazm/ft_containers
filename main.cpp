// #include "./inc/iterator/VectorIterator.hpp"
#include <vector>
#include <iostream>
#include "./inc/vector.hpp"
#include "./inc/utils.hpp"
#include "./tester/vector/vector_test.hpp"


int main(void)
{
    vector_test<int> vec_tester;
    vec_tester.push_back(6);
	vec_tester.push_back(9);
	vec_tester.push_back(6);
	vec_tester.push_back(7);
	vec_tester.push_back(6);
	vec_tester.push_back(5);
	vec_tester.push_back(3);
	vec_tester.push_back(1);
    vec_tester.print_data();
    vec_tester.test_erase();
    vec_tester.test_at(5, 99, 4);
    vec_tester.test_pop_back(2);
    vec_tester.test_resize(3);
    vec_tester.test_swap();
}
