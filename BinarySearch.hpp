#ifndef ALGORITHMS_BINARYSEARCH_HPP
#define ALGORITHMS_BINARYSEARCH_HPP

#include <span>                 // std::span
#include <array>                // std::array
#include <vector>               // std::vector
#include "Comparable.hpp"       // includes Comparable concept used as a constraint
#include <cassert>               // std::assert

/**
 *  The {@code BinarySearch} class provides a static method for binary
 *  searching for an integer in a sorted array of integers.
 *
 *  The indexOf operation takes logarithmic time in the worst case.
 *
 *  @author Benjamin Chan
 *
 *  Adapted from Algorithms, 4th edition, {@authors Robert Sedgewick and Kevin Wayne}
 *  and their booksite https://algs4.cs.princeton.edu/
 *
 *  The Java program from which this C++ code was adapted from is found at
 *  https://algs4.cs.princeton.edu/11model/BinarySearch.java.html.
 *
 *  @param <T> the generic type of an item in this searching algorithm
 */
class BinarySearch {
public:
    // this class should not be instantiated
    BinarySearch() = default;

    template<typename T>
    requires Comparable<T>
    static int indexOf(span<const T> a, int key);

private:
    template<typename T>
    requires Comparable<T>
    static void isSorted(span<const T> a, bool reverse);

    template<typename T>
    requires Comparable<T>
    static void isSorted(span<const T> a, int lo, int hi, bool reverse);

    template<typename T>
    requires Comparable<T>
    static bool isSorted(span<const T> a, bool reverse);

    template<typename T>
    requires Comparable<T>
    static bool isSorted(span<const T> a, int lo, int hi, bool reverse);
};

template<typename T>
requires Comparable<T>
int BinarySearch::indexOf(span<const T> a, int key) {
    assert(isSorted(a, reverse));
    int lo = 0;
    int hi = a.length - 1;
    while (lo <= hi) {
        // Key is in a[lo..hi] or not present.
        int mid = lo + (hi - lo) / 2;
        if (key < a[mid]) hi = mid - 1;
        else if (key > a[mid]) lo = mid + 1;
        else return mid;
    }
    return -1;
}

template<typename T>
requires Comparable<T>
bool BinarySearch::isSorted(span<const T> a, bool reverse) {
    return isSorted(a, 0, a.size() - 1, reverse);
}

template<typename T>
requires Comparable<T>
bool BinarySearch::isSorted(span<const T> a, int lo, int hi, bool reverse) {
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
