// #include "./inc/iterator/VectorIterator.hpp"
#include <vector>
#include <iostream>
#include "./inc/vector.hpp"
#include "./inc/utils.hpp"
#include "./tester/vector/vector_test.hpp"


int main(void)
{
    // std::vector<int> stdtest;
    // stdtest.push_back(6);
	// stdtest.push_back(9);
	// stdtest.push_back(6);
	// stdtest.push_back(7);
	// stdtest.push_back(6);

    // std::vector<int> stdtest2;
    // stdtest2.insert(stdtest.begin(), stdtest.begin(), stdtest.end());
    // for(std::vector<int>::iterator it = stdtest2.begin(); it < stdtest2.end(); ++it)
    //     std::cout << *it << std::endl;


    vector_test<int> vec_tester;
    vec_tester.reserve(2);
    vec_tester.push_back(6);
	vec_tester.push_back(9);
	vec_tester.push_back(99);
	vec_tester.push_back(7);
	vec_tester.push_back(0);
	vec_tester.push_back(5);
	vec_tester.push_back(300);
	vec_tester.push_back(1);
    vec_tester.print_data();
    vec_tester.test_erase(9, 7);
    vec_tester.test_at(5, 99, 4);
    vec_tester.test_pop_back(2);
    vec_tester.test_swap();
    vec_tester.test_resize(3);
    vec_tester.test_capacity_functions();
    vec_tester.test_brackets(200, 2);
    vec_tester.test_front_back_access();
    vec_tester.clear();
    vec_tester.reserve(900);
    vec_tester.test_assign(5, 12);


}
