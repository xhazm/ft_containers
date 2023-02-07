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
    // print_data(assign_test(vec), assign_test(vec2));
    // print_data(assign_std_test(vec), assign_std_test(vec2));
    // print_data(constructor_test(vec), constructor_test(vec2));
    // print_data(constructor_std_test(vec), constructor_std_test(vec2));


	for (size_t i = 0; i < 15; ++i)
		vec2.push_back(i);
    std::list<int> li(vec2.begin(), vec2.end());
    vec.insert(vec.begin(), li.begin(), li.end());
	for (size_t i = 0; i < 40; ++i)
		vec2.push_back(i);
    vec.reserve(100);
    std::list<int> li2(vec2.begin(), vec2.end());
    vec.insert(vec.end(), li2.begin(), li2.end());

//     ft::vector<std::string> str_vec;
//     std::string s_string[32] = {                                                                   \
//     "QExoqp0nICr0sXsHqty2", "naax9QcpJhvaL7DezsNQ", "25ZTtB6wbptfbxM8AvHB",                    \
//     "tShYNtc0MkdjqLrOatgz", "7Z3kf1Qec0NnsLSEpbOt", "WhkSNrKJC966fvjZ2Or1",                    \
//     "8vlxlFRRgW7yYj4GO7dt", "5sq1aoT8zP0HaHj3nFOK", "61Dv31GYZhkgjKCErpng",                    \
//     "l0IIcWWHhOcPzoxEamQM", "bE1RYclskwXlhCm46YFs", "kXeoi5qz94JYPqSDTs79",                    \
//     "TFsQP1dz8VVos9KzUpY0", "b3wYQR7An193gjgYuRj3", "xSmyNsnSJ47jLqrvbpyr",                    \
//     "guAIP2Wq43Gf8VhHsyu5", "yT6c2loPebHovnq9BQog", "3qvU1xcVm2g1DKFDlqh4",                    \
//     "L0q8RR9P41VD4sVjdnWl", "YdjESsIZM4b1oGQPjpBe", "l1ZVQbWKw7brHUSimJgq",                    \
//     "xdn0cf4vqRzpfXWtl10G", "lYnZvpqaV0s8DowMZwzV", "8P1cyKrwJNLoJyvLjYqO",                    \
//     "4MhOXNbAX23CEijO5cRT", "tHe3miAwCOVQbuoLaEP2", "l6uNLsc8fiLl3eWoG6j6",                    \
//     "477xt6l0lph9ALQdr4HX", "D9UJNe4s8YF02LhrwOdl", "dLCisBNOdE8yugntu6cj",                    \
//     "YvY4aQFHgAuagn4dFLO1", "eGR6Dtv7LW75qlV5Fkik"                                             \
// };    

//     std::size_t s_size = 32;                                                                       \
//     std::size_t b_size = 64;                                                                       \

//     str_vec.insert(str_vec.end(), s_string, s_string + s_size);
//     str_vec.insert(str_vec.begin() + 20, s_string, s_string + s_size);

//     std::string b_string[64] = {                                                                   \
//         "uvg6KqtcgduR31n3ajsv", "wbiAcjgojb9JOagZwyMn", "ATZKCzaPOqgkhPjwuGlf",                    \
//         "MOhaJs56yjOw8f6nLPRA", "0gyB2Tr42v6awMw2nK7J", "e6GsiLFUuoDpVFEhJKZ1",                    \
//         "z0jXAhiV9keBsaLOY0Xf", "P68p2ZAosHJdmoZh1C7N", "Pu3EuZVeY0TCO3ojdK0t",                    \
//         "z7jCHMooHCS73M8GygKB", "uT4KoK83JrZxZjkul7ty", "g8gfrZoY5XwfzRusvHvv",                    \
//         "7PGmkM0OSRnYREt9mFIP", "q1od7mBIpPEsCtpF9kdw", "XQo0LWId5TdZnLnpUNOb",                    \
//         "U0m1R0kFFhAFyS6hmHHw", "K0lPKfxJxIOnE8QB90xn", "cZ5xyQifMJhrKxqBK9A7",                    \
//         "cFBiwjfYw7Js6qEGy5Kt", "1tW0KWfXxeFO69tByqcE", "3Fvq9NxBrhPXHe0IlIVx",                    \
//         "MSRDjdFRvHAhFGhiMtDe", "zGm2joMh71jQkYzg5L4V", "Mq4RRaeLvSAO0z2ibp8Q",                    \
//         "WnLFYnQKP8TNJkqVVbUg", "E98UphbbVSzrW5Mzurmg", "F8HRxeEcaTZDkFPkioij",                    \
//         "jmUVl4Q8X5BwVNzXN219", "n7Xp4w4FwzGKit7AI4SO", "4MxXYr6rKOcXLt9UkVd2",                    \
//         "4RVTDsADtRyboaai9d29", "XaSqsrrtdhAfFoJIc5KK", "9Z9jdVCrTT09bg348ceb",                    \
//         "I6uqLG9dO5mfNdSMwOYm", "UwMTzJPlbnhgwbHpDi6w", "DebjMP9afncYE6GhhO00",                    \
//         "YGPuscYDiGfAjY1UWST0", "K6gbvgGjVZgEFUDlkdSk", "8xCBPI0w6TpC0RA62c2W",                    \
//         "fYMxkNwmKg3moP8KvD9v", "QpPdhwhEYjIugg3OPcPH", "qQBXjSn43I3EMP54SyxZ",                    \
//         "7qvdKwoW1CQEZTWPvuSC", "rCT212rdYO0zTGHXesKg", "dBHvlHsBwcR9MkkenYYG",                    \
//         "NQiSlergqR8fVbOeivLj", "xYVqsV147UIe7jVBVwXo", "tcxayO4DdEJ885TbqUMy",                    \
//         "9TGSMTD8U8ksRpHqq0cL", "TIJ16jCv9BSUiWvhbF9T", "BM9GL2ig1hePkA6lM6Ck",                    \
//         "TfJTYB9JQMU6CGcYg20Q", "Fg6e5YT2FQbpTZNTDqdo", "LI5q6ml40MeE9H1dPb93",                    \
//         "OaxJUSm3nYN9Y8Ela7sS", "BgBeODAwXz7xJo50Rwqd", "xdkgKj1dEoJ6zuVhkvvo",                    \
//         "olIewtUEvXJgs1lB9bCn", "dTsPDS0x2uXtcgOIJHb8", "DYvJ2phLppGNZKboTBrd",                    \
//         "DjNFMtt9PxkzqvWBHI6j", "1Z3YkeTFlPniKnzFhzgu", "76XqQg6hqMf5IXxKPOEs",                    \
//         "gzaapTWW7i9EZjjzLeK6"                                                                     \
//     };    

//     str_vec.insert(str_vec.begin(), b_string, b_string + 10);


//     str_vec.insert(str_vec.begin() + 20, b_string, b_string + b_size);

//     str_vec.insert(str_vec.end(), b_string + 10, b_string + 15);
//     print_data(str_vec);

    return 0;
}
