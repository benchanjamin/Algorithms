#ifndef ALGORITHMS_QUICKSORT_HPP
#define ALGORITHMS_QUICKSORT_HPP

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
class QuickSort {
public:
    explicit QuickSort<T>(span<T> a, bool reverse = false) {
        random_device rd;
        mt19937 g(rd());
        shuffle(a.begin(), a.end(), g);
        sort(a, 0, a.size() - 1, reverse);
        assert(isSorted(a, reverse));
    };

    explicit QuickSort<T>(T a[], int length, bool reverse = false) {
        random_device rd;
        mt19937 g(rd());
        shuffle(a, a + length, g);
        sort(a, 0, length - 1, reverse);
        assert(isSorted(a, reverse));
    };
private:
    void sort(span<T> a, int lo, int hi, bool reverse = false);

    void sort(T a[], int length, int lo, int hi, bool reverse = false);

    int partition(span<T> a, int lo, int hi, bool reverse = false);

    void exch(span<T> a, int i, int j);

    // check if entire container is sorted -- useful for debugging
    bool isSorted(span<T> a, int lo, int hi, bool reverse = false);

    // check if container is sorted between two indices, lo and hi -- useful for debugging
    bool isSorted(span<T> a, bool reverse = false);
};

template<typename T>
requires Comparable<T>
void QuickSort<T>::sort(span<T> a, int lo, int hi, bool reverse) {
    if (hi <= lo) return;
    int j = partition(a, lo, hi, reverse);
    sort(a, lo, j - 1, reverse);
    sort(a, j + 1, hi, reverse);
    assert(isSorted(a, lo, hi, reverse));
}

template<typename T>
requires Comparable<T>
int QuickSort<T>::partition(span<T> a, int lo, int hi, bool reverse) {
    int i = lo;
    int j = hi + 1;
    T v = a[lo];
    if (!reverse) {
        while (true) {

            // find item on lo to swap
            while (a[++i] < v) {
                if (i == hi) break;
            }

            // find item on hi to swap
            while (v < a[--j]) {
                if (j == lo) break;      // redundant since a[lo] acts as sentinel
            }

            // check if pointers cross
            if (i >= j) break;

            exch(a, i, j);
        }
    } else {
        while (true) {
            // find item on lo to swap
            while (a[++i] > v) {
                if (i == hi) break;
            }

            // find item on hi to swap
            while (v > a[--j]) {
                if (j == lo) break;      // redundant since a[lo] acts as sentinel
            }

            // check if pointers cross
            if (i >= j) break;

            exch(a, i, j);
        }
    }

    // put partitioning item v at a[j]
    exch(a, lo, j);

    // now, a[lo .. j-1] <= a[j] <= a[j+1 .. hi]
    return j;
}

template<typename T>
requires Comparable<T>
void QuickSort<T>::exch(span<T> a, int i, int j) {
    T swap = a[i];
    a[i] = a[j];
    a[j] = swap;
}

template<typename T>
requires Comparable<T>
bool QuickSort<T>::isSorted(span<T> a, bool reverse) {
    return isSorted(a, 0, a.size() - 1, reverse);
}


template<typename T>
requires Comparable<T>
bool QuickSort<T>::isSorted(span<T> a, int lo, int hi, bool reverse) {
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
void QuickSort<T>::sort(T a[], int length, int lo, int hi, bool reverse) {
    if (hi <= lo) return;
    int j = partition(a, lo, hi, reverse);
    sort(a, lo, j - 1, reverse);
    sort(a, j + 1, hi, reverse);
    assert(isSorted(a, lo, hi, reverse));
}

/**
 * Deduct the type, <T>, of the MergeSort class based on constructor argument types
 * and number of arguments
 */
template<typename T> requires Comparable<T>
QuickSort(span<T>) -> QuickSort<T>;

template<typename T> requires Comparable<T>
QuickSort(vector<T>) -> QuickSort<T>;

template<typename T, size_t SIZE> requires Comparable<T>
QuickSort(array<T, SIZE>) -> QuickSort<T>;

template<typename T> requires Comparable<T>
QuickSort(T a[]) -> QuickSort<T>;

template<typename T> requires Comparable<T>
QuickSort(span<T>, bool reverse) -> QuickSort<T>;

template<typename T> requires Comparable<T>
QuickSort(vector<T>, bool reverse) -> QuickSort<T>;

template<typename T, size_t SIZE> requires Comparable<T>
QuickSort(array<T, SIZE>, bool reverse) -> QuickSort<T>;

template<typename T> requires Comparable<T>
QuickSort(T a[], int length, bool reverse) -> QuickSort<T>;

#endif //ALGORITHMS_QUICKSORT_HPP
