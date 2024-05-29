#pragma once

#include <algorithm>
#include <iterator>

namespace algo 
{    

template <class It, class Compare>
void bubble_sort(It first, It last, Compare comp) {
    for (It r = last - 1; r != first; --r) {
        size_t count = 0;
        for (It l = first; l != r; ++l) {
            if (comp(*std::next(l), *l)) {
                std::iter_swap(std::next(l), l);
                ++count;
            }
        }
        if (count == 0) 
            break;
    }
}

template <class It, class Compare>
void insertion_sort(It first, It last, Compare comp) {
    std::__insertion_sort(first,last,comp);
}

template <class It>
void bubble_sort(It first, It last) {
    bubble_sort(first, last, std::less<typename std::iterator_traits<It>::value_type>());
}

}
