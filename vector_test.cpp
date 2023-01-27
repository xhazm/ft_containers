// #include "./inc/iterator/VectorIterator.hpp"
#include <vector>
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

template<class U>
std::string print_data(U test_vec)
{
    typename U::iterator test_it = test_vec.begin();
    for(; test_it != test_vec.end(); ++test_it)
    {
        std::cout << "test_data: " << *test_it << std::endl;
    }
    return ("");
}

template<class T>
std::string print_data(std::vector<T> test_ft_vec, std::vector<T> test_std_vec)
{
    typename std::vector<T>::iterator test_ft_it = test_ft_vec.begin();
    typename std::vector<T>::iterator test_std_it = test_std_vec.begin();
    for(; test_ft_it != test_ft_vec.end(); ++test_ft_it, ++test_std_it)
    {
        std::cout << "ft_data: " << *test_ft_it <<  "\t\t\t\tstd_data: " <<  *test_std_it << std::endl;
    }
    return ("");
}

template <typename T>
std::vector<long long> assign_test(std::vector<T> vector) {
    std::vector<long long> v;
    std::vector<long long> tmp, tmp2;
    vector.assign(3, 3);
    tmp.assign(4000 * _ratio, 1);
    tmp2.assign(4 * _ratio, 1);
    vector.assign(tmp.begin(), tmp.end());
    v.push_back(vector[1]);
    v.push_back(vector.size());
    v.push_back(vector.capacity());
    vector.assign(tmp2.begin(), tmp2.end());
    // v.push_back(vector[444]);
    v.push_back(vector.at(1));
    v.push_back(vector.size());
    v.push_back(vector.capacity());
    return v;
}

template <typename T>
std::vector<long long> assign_test(_vector<T> vector) {
    std::vector<long long> v;
    _vector<long long> tmp, tmp2;
    vector.assign(3, 3);
    tmp.assign(4000 * _ratio, 1);
    tmp2.assign(4 * _ratio, 1);
    vector.assign(tmp.begin(), tmp.end());
    v.push_back(vector[1]);
    v.push_back(vector.size());
    v.push_back(vector.capacity());
    vector.assign(tmp2.begin(), tmp2.end());
    // v.push_back(vector[444]); //undefined behavior?? or because it shouldnt realloc?
    v.push_back(vector.at(1));
    v.push_back(vector.size());
    v.push_back(vector.capacity());
    return v;
}

template <typename T>
std::vector<long long> constructor_test(std::vector<T> vector) {
    std::vector<long long> v;
    std::vector<long long> tmp0(vector);
    std::vector<long long> tmp(1000 * _ratio, 4), tmp2(1000 * _ratio, 5);
    tmp = tmp2;
    std::vector<long long> tmp3(tmp);
    std::vector<long long> tmp4(tmp.begin(), tmp.end());
    v.push_back(tmp4.size());
    v.push_back(tmp4.capacity());
    v.push_back(tmp[2]);
    v.push_back(tmp3[2]);
    v.push_back(tmp4[2]);
    try { std::vector<long long> tmp5(-1, -1); }
    catch (std::exception &e) { v.push_back(1); }
    return v;
}

template <typename T>
std::vector<long long> constructor_test(_vector<T> vector) {
    std::vector<long long> v;
	_vector<long long> tmp0(vector);
    _vector<long long> tmp(1000 * _ratio, 4), tmp2(1000 * _ratio, 5);
    tmp = tmp2;
    _vector<long long> tmp3(tmp);
    _vector<long long> tmp4(tmp.begin(), tmp.end());
    v.push_back(tmp4.size());
    v.push_back(tmp4.capacity());
    v.push_back(tmp[2]);
    v.push_back(tmp3[2]);
    v.push_back(tmp4[2]);
    try { _vector<long long> tmp5(-1, -1); }
    catch (std::exception &e) { v.push_back(1); }
    return v;
}

template <typename T>
std::vector<long long> constructor_std_test(std::vector<T> vector) {
	std::vector<long long> v;
	vector.assign(3, 3);
	std::vector<long long> tmp(1000 * _ratio, 4);
	std::vector<long long> tmp2(tmp.begin(), tmp.end());
	v.push_back(tmp2.size());
	v.push_back(tmp2.capacity());
	for (size_t i = 0; i < tmp.size(); ++i)
		v.push_back(tmp2[i]);
	return v;
}

template <typename T>
std::vector<long long> constructor_std_test(_vector<T> vecto) {
	(void)vecto;
	std::vector<long long> v;
	_vector<T> vector(3, 3);
	std::vector<long long> tmp(1000 * _ratio, 4);
	_vector<long long> tmp2(tmp.begin(), tmp.end());
	v.push_back(tmp2.size());
	v.push_back(tmp2.capacity());
	for (size_t i = 0; i < tmp.size(); ++i)
		v.push_back(tmp2[i]);
	return v;
}
template <typename T>
std::vector<long long> assign_std_test(std::vector<T> vector) {
	std::vector<long long> v;
	std::vector<long long> tmp;
	vector.assign(3, 3);
	tmp.assign(4000 * _ratio, 1);
	vector.assign(tmp.begin(), tmp.end());
	for (size_t i = 0; i < tmp.size(); ++i)
		v.push_back(vector[i]);
	v.push_back(vector.size());
	v.push_back(vector.capacity());
	return v;
}

template <typename T>
std::vector<long long> assign_std_test(_vector<T> vector) {
	std::vector<long long> v;
	std::vector<long long> tmp;
	vector.assign(3, 3);
	tmp.assign(4000 * _ratio, 1);
	vector.assign(tmp.begin(), tmp.end());
	for (size_t i = 0; i < tmp.size(); ++i)
		v.push_back(vector[i]);
	v.push_back(vector.size());
	v.push_back(vector.capacity());
	return v;
}


int main(void)
{
    ft::vector<long long> vec;
    std::vector<long long> vec2;
    print_data(assign_test(vec), assign_test(vec2));
    print_data(assign_std_test(vec), assign_std_test(vec2));
    print_data(constructor_test(vec), constructor_test(vec2));
    print_data(constructor_std_test(vec), constructor_std_test(vec2));
    


    return 0;
}