#include "./inc/iterator/VectorIterator.hpp"
#include <vector>
#include <iostream>

int main(void)
{
	std::vector<int> i;
	std::vector<int>::iterator it;

	i.push_back(5);
	i.push_back(6);

	ft::VectorIterator<int> test;
	ft::VectorIterator<int> test2;

	if (test == test2)
		std::cout << "true" << std::endl;

}