#ifndef ALGORITHMS_BINARYSEARCH_HPP
#define ALGORITHMS_BINARYSEARCH_HPP

#include <span>                 // std::span
#include <array>                // std::array
#include <vector>               // std::vector
#include "Comparable.hpp"       // includes Comparable concept used as a constraint
#include <assert>               // std::assert

class BinarySearch {
public:

private:

};

template<typename T>
requires Comparable<T>
bool BinarySearch<T>::isSorted(span <T> a, bool reverse) {
    return isSorted(a, 0, a.size() - 1, reverse);
}

template<typename T>
requires Comparable<T>
bool BinarySearch<T>::isSorted(span <T> a, int lo, int hi, bool reverse) {
    if (!reverse) {
        for (int i = lo + 1; i <= hi; i++)
            if (a[i] < a[i - 1]) return false;
        return true;
    } else {
        for (int i = lo + 1; i <= hi; i++)
            if (a[i] > a[i - 1]) return false;
        return true;
    }
}

#endif //ALGORITHMS_BINARYSEARCH_HPP
