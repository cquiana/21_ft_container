#pragma once

namespace ft
{
	struct is_int { };
	struct not_int { };

	template<typename T>
    struct is_integer
    {
    enum { value = 0 };
    typedef not_int type;
    };

	template<>
    struct is_integer<int>
    {
    enum { value = 1 };
    typedef is_int type;
    };

    template <typename T>
    void swap(T& x, T& y) {
        T tmp = x;
        x = y;
        y = tmp;
    };

    template<bool B, class T = void>
    struct enable_if {};

    template<class T>
    struct enable_if<true, T> { typedef T type; };

    template <class InputIterator1, class InputIterator2>
    bool lexicographical_compare (InputIterator1 first1, InputIterator1 last1,
                                InputIterator2 first2, InputIterator2 last2)
    {
        while (first1!=last1)
        {
            if (first2==last2 || *first2<*first1) return false;
            else if (*first1<*first2) return true;
            ++first1; ++first2;
        }
        return (first2!=last2);
    };
}
