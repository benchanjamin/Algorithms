#ifndef ALGORITHMS_QUICKSORT3WAY_HPP
#define ALGORITHMS_QUICKSORT3WAY_HPP

#include <span>                 // std::span
#include <array>                // std::array
#include <vector>               // std::vector
#include "Comparable.hpp"       // includes Comparable concept used as a constraint
#include <algorithm>            // std::shuffle
#include <random>               // std::random_device
#include <cassert>              // std::assert

using namespace std;

/**
 *  The {@code QuickSort} class provides a public method for sorting a
 *  container and selecting the ith smallest element in an array using quicksort.
 *
 *  @author Benjamin Chan
 *
 *  Adapted from Algorithms, 4th edition, {@authors Robert Sedgewick and Kevin Wayne}
 *  and their booksite https://algs4.cs.princeton.edu/
 *
 *  The Java program from which this C++ code was adapted from is found at
 *  https://algs4.cs.princeton.edu/23quicksort/Quick.java.html.
 *
 *  @param <T> the generic type of an item in this sorting algorithm
 */

template<typename T> requires Comparable<T>
class QuickSort3way {
public:
    explicit QuickSort3way<T>(span<T> a, bool reverse = false) {
        random_device rd;
        mt19937 g(rd());
        shuffle(a.begin(), a.end(), g);
        sort(a, 0, a.size() - 1, reverse);
        assert(isSorted(a, reverse));
    };
private:
    void sort(span<T> a, int lo, int hi, bool reverse = false);

    void exch(span<T> a, int i, int j);

    // check if entire container is sorted -- useful for debugging
    bool isSorted(span<T> a, int lo, int hi, bool reverse = false);

    // check if container is sorted between two indices, lo and hi -- useful for debugging
    bool isSorted(span<T> a, bool reverse = false);
};

template<typename T>
requires Comparable<T>
void QuickSort3way<T>::sort(span<T> a, int lo, int hi, bool reverse) {
    if (!reverse) {
        if (hi <= lo) return;
        int lt = lo, gt = hi;
        T v = a[lo];
        int i = lo + 1;
        while (i <= gt) {
            int cmp = a[i].compareTo(v);
            if (cmp < 0) exch(a, lt++, i++);
            else if (cmp > 0) exch(a, i, gt--);
            else i++;
        }
    } else {
        if (hi <= lo) return;
        int lt = lo, gt = hi;
        T v = a[lo];
        int i = lo + 1;
        while (i <= gt) {
            int cmp = a[i].compareTo(v);
            if (cmp > 0) exch(a, lt++, i++);
            else if (cmp < 0) exch(a, i, gt--);
            else i++;
        }
    }

    // a[lo..lt-1] < v = a[lt..gt] < a[gt+1..hi].
    sort(a, lo, lt - 1, reverse);
    sort(a, gt + 1, hi, reverse);
    assert(isSorted(a, lo, hi, reverse));
}

template<typename T>
requires Comparable<T>
void QuickSort3way<T>::exch(span<T> a, int i, int j) {
    T swap = a[i];
    a[i] = a[j];
    a[j] = swap;
}

template<typename T>
requires Comparable<T>
bool QuickSort3way<T>::isSorted(span<T> a, bool reverse) {
    return isSorted(a, 0, a.size() - 1, reverse);
}

template<typename T>
requires Comparable<T>
bool QuickSort3way<T>::isSorted(span<T> a, int lo, int hi, bool reverse) {
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

/**
 * Deduct the type, <T>, of the MergeSort class based on constructor argument types
 * and number of arguments
 */
template<typename T> requires Comparable<T>
QuickSort3way(span<T>) -> QuickSort3way<T>;

template<typename T> requires Comparable<T>
QuickSort3way(vector<T>) -> QuickSort3way<T>;

template<typename T, size_t SIZE> requires Comparable<T>
QuickSort3way(array<T, SIZE>) -> QuickSort3way<T>;

template<typename T> requires Comparable<T>
QuickSort3way(T a[]) -> QuickSort3way<T>;

template<typename T> requires Comparable<T>
QuickSort3way(span<T>, bool reverse) -> QuickSort3way<T>;

template<typename T> requires Comparable<T>
QuickSort3way(vector<T>, bool reverse) -> QuickSort3way<T>;

template<typename T, size_t SIZE> requires Comparable<T>
QuickSort3way(array<T, SIZE>, bool reverse) -> QuickSort3way<T>;

template<typename T> requires Comparable<T>
QuickSort3way(T a[], bool reverse) -> QuickSort3way<T>;

#endif //ALGORITHMS_QUICKSORT3WAY_HPP
