#ifndef ALGORITHMS_BINARYSEARCH_HPP
#define ALGORITHMS_BINARYSEARCH_HPP

#include <span>                 // std::span
#include <array>                // std::array
#include <vector>               // std::vector
#include "Comparable.hpp"       // includes Comparable concept used as a constraint
#include <cassert>              // std::assert
#include <iostream>             // std::sizeof

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
 */
class BinarySearch {
public:
    // this class should not be instantiated
    BinarySearch() = default;

    template<typename T>
    requires Comparable<T>
    static int indexOf(span<T> a, int key, bool reverse = false);

    template<typename T>
    requires Comparable<T>
    static int indexOf(vector<T> a, int key, bool reverse = false);

    template<typename T, size_t SIZE>
    requires Comparable<T>
    static int indexOf(array<T, SIZE> a, int key, bool reverse = false);

    template<typename T>
    requires Comparable<T>
    static int indexOf(T a[], int arrayLength, int key, bool reverse = false);

private:
    template<typename T>
    requires Comparable<T>
    static bool isSorted(span<T> a, bool reverse = false);

    template<typename T>
    requires Comparable<T>
    static bool isSorted(span<T> a, int lo, int hi, bool reverse = false);

    template<typename T>
    requires Comparable<T>
    static bool isSorted(vector<T> a, bool reverse = false);

    template<typename T>
    requires Comparable<T>
    static bool isSorted(vector<T> a, int lo, int hi, bool reverse = false);

    template<typename T, size_t SIZE>
    requires Comparable<T>
    static bool isSorted(array<T, SIZE> a, bool reverse = false);

    template<typename T, size_t SIZE>
    requires Comparable<T>
    static bool isSorted(array<T, SIZE> a, int lo, int hi, bool reverse = false);

    template<typename T>
    requires Comparable<T>
    static bool isSorted(T a[], int length, bool reverse = false);

    template<typename T>
    requires Comparable<T>
    static bool isSorted(T a[], int lo, int hi, bool reverse = false);
};

template<typename T>
requires Comparable<T>
int BinarySearch::indexOf(span<T> a, int key, bool reverse) {
    assert(isSorted(a, reverse));
    int lo = 0;
    int hi = a.size() - 1;
    if (!reverse) {
        while (lo <= hi) {
            // Key is in a[lo..hi] or not present.
            int mid = lo + (hi - lo) / 2;
            if (key < a[mid]) hi = mid - 1;
            else if (key > a[mid]) lo = mid + 1;
            else return mid;
        }
    } else {
        while (lo <= hi) {
            // Key is in a[lo..hi] or not present.
            int mid = lo + (hi - lo) / 2;
            if (key > a[mid]) hi = mid - 1;
            else if (key < a[mid]) lo = mid + 1;
            else return mid;
        }
    }
    return -1;
}

template<typename T>
requires Comparable<T>
int BinarySearch::indexOf(vector<T> a, int key, bool reverse) {
    assert(isSorted(a, reverse));
    int lo = 0;
    int hi = a.size() - 1;
    if (!reverse) {
        while (lo <= hi) {
            // Key is in a[lo..hi] or not present.
            int mid = lo + (hi - lo) / 2;
            if (key < a[mid]) hi = mid - 1;
            else if (key > a[mid]) lo = mid + 1;
            else return mid;
        }
    } else {
        while (lo <= hi) {
            // Key is in a[lo..hi] or not present.
            int mid = lo + (hi - lo) / 2;
            if (key > a[mid]) hi = mid - 1;
            else if (key < a[mid]) lo = mid + 1;
            else return mid;
        }
    }
    return -1;
}

template<typename T, size_t SIZE>
requires Comparable<T>
int BinarySearch::indexOf(array<T, SIZE> a, int key, bool reverse) {
    assert(isSorted(a, reverse));
    int lo = 0;
    int hi = a.size() - 1;
    if (!reverse) {
        while (lo <= hi) {
            // Key is in a[lo..hi] or not present.
            int mid = lo + (hi - lo) / 2;
            if (key < a[mid]) hi = mid - 1;
            else if (key > a[mid]) lo = mid + 1;
            else return mid;
        }
    } else {
        while (lo <= hi) {
            // Key is in a[lo..hi] or not present.
            int mid = lo + (hi - lo) / 2;
            if (key > a[mid]) hi = mid - 1;
            else if (key < a[mid]) lo = mid + 1;
            else return mid;
        }
    }
    return -1;
}

template<typename T>
requires Comparable<T>
int BinarySearch::indexOf(T a[], int length, int key, bool reverse) {
    assert(isSorted(a, reverse));
    int lo = 0;
    int hi = length - 1;
    if (!reverse) {
        while (lo <= hi) {
            // Key is in a[lo..hi] or not present.
            int mid = lo + (hi - lo) / 2;
            if (key < a[mid]) hi = mid - 1;
            else if (key > a[mid]) lo = mid + 1;
            else return mid;
        }
    } else {
        while (lo <= hi) {
            // Key is in a[lo..hi] or not present.
            int mid = lo + (hi - lo) / 2;
            if (key > a[mid]) hi = mid - 1;
            else if (key < a[mid]) lo = mid + 1;
            else return mid;
        }
    }
    return -1;
};

template<typename T>
requires Comparable<T>
bool BinarySearch::isSorted(span<T> a, bool reverse) {
    return isSorted(a, 0, a.size() - 1, reverse);
}

template<typename T>
requires Comparable<T>
bool BinarySearch::isSorted(span<T> a, int lo, int hi, bool reverse) {
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

template<typename T>
requires Comparable<T>
bool BinarySearch::isSorted(vector<T> a, bool reverse) {
    return isSorted(a, 0, a.size() - 1, reverse);
}

template<typename T>
requires Comparable<T>
bool BinarySearch::isSorted(vector<T> a, int lo, int hi, bool reverse) {
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

template<typename T, size_t SIZE>
requires Comparable<T>
bool BinarySearch::isSorted(array<T, SIZE> a, bool reverse) {
    return isSorted(a, 0, a.size() - 1, reverse);
}

template<typename T, size_t SIZE>
requires Comparable<T>
bool BinarySearch::isSorted(array<T, SIZE> a, int lo, int hi, bool reverse) {
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

template<typename T>
requires Comparable<T>
bool BinarySearch::isSorted(T a[], int arrayLength, bool reverse) {
    return isSorted(a, 0, arrayLength, reverse);
}

template<typename T>
requires Comparable<T>
bool BinarySearch::isSorted(T a[], int lo, int hi, bool reverse) {
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
