#pragma once

namespace ft
{

template< bool B, class T = void >
struct enable_if{ };

template< class T >
struct enable_if< true, T >{ typedef T type; };

template< class T, T v >
struct integral_constant
{
    static constexpr    T   value = v;
    typedef             T   value_type;
};

typedef struct integral_constant<bool, true>    true_type;
typedef struct integral_constant<bool, false>   false_type;

template< class T > struct is_integral_base: false_type {};

template<> struct is_integral_base<bool>: true_type {};
template<> struct is_integral_base<char>: true_type {};
template<> struct is_integral_base<short int>: true_type {};
template<> struct is_integral_base<int>: true_type {};
template<> struct is_integral_base<long int>: true_type {};
template<> struct is_integral_base<long long int>: true_type {};
template<> struct is_integral_base<unsigned char>: true_type {};
template<> struct is_integral_base<unsigned short int>: true_type {};
template<> struct is_integral_base<unsigned int>: true_type {};
template<> struct is_integral_base<unsigned long int>: true_type {};
template<> struct is_integral_base<unsigned long long int>: true_type {};
template<> struct is_integral_base<char16_t>: true_type {};
template<> struct is_integral_base<char32_t>: true_type {};
template<> struct is_integral_base<wchar_t>: true_type {};
template<> struct is_integral_base<signed char>: true_type {};

template<> struct is_integral_base<const bool>: true_type {};
template<> struct is_integral_base<const char>: true_type {};
template<> struct is_integral_base<const short int>: true_type {};
template<> struct is_integral_base<const int>: true_type {};
template<> struct is_integral_base<const long int>: true_type {};
template<> struct is_integral_base<const long long int>: true_type {};
template<> struct is_integral_base<const unsigned char>: true_type {};
template<> struct is_integral_base<const unsigned short int>: true_type {};
template<> struct is_integral_base<const unsigned int>: true_type {};
template<> struct is_integral_base<const unsigned long int>: true_type {};
template<> struct is_integral_base<const unsigned long long int>: true_type {};
template<> struct is_integral_base<const char16_t>: true_type {};
template<> struct is_integral_base<const char32_t>: true_type {};
template<> struct is_integral_base<const wchar_t>: true_type {};
template<> struct is_integral_base<const signed char>: true_type {};

template<> struct is_integral_base<volatile bool>: true_type {};
template<> struct is_integral_base<volatile char>: true_type {};
template<> struct is_integral_base<volatile short int>: true_type {};
template<> struct is_integral_base<volatile int>: true_type {};
template<> struct is_integral_base<volatile long int>: true_type {};
template<> struct is_integral_base<volatile long long int>: true_type {};
template<> struct is_integral_base<volatile unsigned char>: true_type {};
template<> struct is_integral_base<volatile unsigned short int>: true_type {};
template<> struct is_integral_base<volatile unsigned int>: true_type {};
template<> struct is_integral_base<volatile unsigned long int>: true_type {};
template<> struct is_integral_base<volatile unsigned long long int>: true_type {};
template<> struct is_integral_base<volatile char16_t>: true_type {};
template<> struct is_integral_base<volatile char32_t>: true_type {};
template<> struct is_integral_base<volatile wchar_t>: true_type {};
template<> struct is_integral_base<volatile signed char>: true_type {};

template< class T >
struct is_integral: is_integral_base <T> {};

// Returns true if the range [first1, last1) is equal to the range [first2, first2 + (last1 - first1)), 
// and false otherwise, using binary function 'p' for compare
template< class InputIt1, class InputIt2, class BinaryPredicate >
bool equal( InputIt1 first1,
            InputIt1 last1,
            InputIt2 first2,
            BinaryPredicate p )
{
    for (; first1 != last1; ++first1, ++first2) {
        if (!p(*first1, *first2)) {
            return false;
        }
    }
    return true;
};

// Returns true if the range [first1, last1) is equal to the range [first2, first2 + (last1 - first1)), 
// and false otherwise, using ==
template< class InputIt1, class InputIt2 >
bool equal( InputIt1 first1, InputIt1 last1, InputIt2 first2 )
{
    for (; first1 != last1; ++first1, ++first2) {
        if (!(*first1 == *first2)) {
            return false;
        }
    }
    return true;
};


// Elements are compared using operator<
template< class InputIt1, class InputIt2 >
bool lexicographical_compare( InputIt1 first1, InputIt1 last1,
                              InputIt2 first2, InputIt2 last2 )
{
    for (; (first1 != last1) && (first2 != last2); ++first1, (void) ++first2)
    {
        if (*first1 < *first2)
            return (true);
        if (*first2 < *first1)
            return (false);
    }
    return (first1 == last1) && (first2 != last2);
}

//Elements are compared using given binary comparison function comp
template< class InputIt1, class InputIt2, class Compare >
bool lexicographical_compare( InputIt1 first1, InputIt1 last1,
                              InputIt2 first2, InputIt2 last2, Compare comp )
{
    for (; (first1 != last1) && (first2 != last2); ++first1, (void) ++first2)
    {
        if (comp(*first1, *first2))
            return (true);
        if (comp(*first2, *first1))
            return (false);
    }
    return (first1 == last1) && (first2 != last2);
}
} // namespace ft