#pragma once
#include <iterator>
#include <type_traits>

template<typename T, typename = void>
struct is_iterator {
   static constexpr bool value = false;
};

template<typename T>
struct is_iterator<T, typename std::enable_if<!std::is_same<typename std::iterator_traits<T>::value_type, void>::value>::type> {
   static constexpr bool value = true;
};


template <class Iterator, class = typename std::enable_if<is_iterator<Iterator>::value>::type>
bool is_sorted(Iterator first, Iterator last);

template <class Iterator, class Compare, class = typename std::enable_if<is_iterator<Iterator>::value>::type>
bool is_sorted(Iterator first, Iterator last, Compare comp);


template <class Iterator, class = typename std::enable_if<is_iterator<Iterator>::value>::type>
void bubble_sort(Iterator first, Iterator last);

template <class Iterator, class Compare, class = typename std::enable_if<is_iterator<Iterator>::value>::type>
void bubble_sort(Iterator first, Iterator last, Compare comp);


template <class Iterator, class = typename std::enable_if<is_iterator<Iterator>::value>::type>
void cocktail_shaker_sort(Iterator first, Iterator last);

template <class Iterator, class Compare, class = typename std::enable_if<is_iterator<Iterator>::value>::type>
void cocktail_shaker_sort(Iterator first, Iterator last, Compare comp);


template <class Iterator, class = typename std::enable_if<is_iterator<Iterator>::value>::type>
void comb_sort(Iterator first, Iterator last);

template <class Iterator, class Compare, class = typename std::enable_if<is_iterator<Iterator>::value>::type>
void comb_sort(Iterator first, Iterator last, Compare comp);

#include "sort.tpp"
