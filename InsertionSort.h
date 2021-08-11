#ifndef ALGORITHMS_INSERTIONSORT_H
#define ALGORITHMS_INSERTIONSORT_H

#include <span>
#include "Comparable.h"

using namespace std;

/**
 *  The {@code Insertion} class provides static methods for sorting an
 *  array using insertion sort.
 *
 *  In the worst case, this implementation makes ~ &frac12; <em>n</em><sup>2</sup>
 *  compares and ~ &frac12; <em>n</em><sup>2</sup> exchanges to sort an array
 *  of length <em>n</em>. So, it is not suitable for sorting large arbitrary
 *  arrays. More precisely, the number of exchanges is exactly equal to the
 *  number of inversions. So, for example, it sorts a partially-sorted array
 *  in linear time.
 *  <p>
 *  This sorting algorithm is stable.
 *  It uses &Theta;(1) extra memory (not including the input array).
 *  <p>
 *  See <a href="https://algs4.cs.princeton.edu/21elementary/InsertionPedantic.java.html">InsertionPedantic.java</a>
 *  for a version that eliminates the compiler warning.
 *  <p>
 *  For additional documentation, see <a href="https://algs4.cs.princeton.edu/21elementary">Section 2.1</a> of
 *  <i>Algorithms, 4th Edition</i> by Robert Sedgewick and Kevin Wayne.
 *
 *  @author Robert Sedgewick
 *  @author Kevin Wayne
 */
template<typename T> requires Comparable<T>
class InsertionSort {
public:
    explicit InsertionSort<T>(span<T> a, bool reverse = false) {
        int n = a.size();
        if (!reverse) {
            for (int i = 1; i < n; i++) {
                for (int j = i; j > 0 && (a[j] < a[j - 1]); j--) {
                    exch(a, j, j - 1);
                }
                assert(isSorted(a, 0, i, reverse));
            }
        } else {
            for (int i = 1; i < n; i++) {
                for (int j = i; j > 0 && (a[j] > a[j - 1]); j--) {
                    exch(a, j, j - 1);
                }
                assert(isSorted(a, 0, i, reverse));
            }
        }
        assert(isSorted(a, reverse));
    };

private:
    static void exch(span<T> a, int i, int j);

    static bool isSorted(span<T> a, bool reverse);

    static bool isSorted(span<T> a, int lo, int hi, bool reverse);
};

template<typename T>
requires Comparable<T>
void InsertionSort<T>::exch(span<T> a, int i, int j) {
    T swap = a[i];
    a[i] = a[j];
    a[j] = swap;
}

template<typename T>
requires Comparable<T>
bool InsertionSort<T>::isSorted(span<T> a, bool reverse) {
    return isSorted(a, 0, a.size() - 1, reverse);
}


template<typename T>
requires Comparable<T>
bool InsertionSort<T>::isSorted(span<T> a, int lo, int hi, bool reverse) {
    if (!reverse) {
        for (int i = 1; i <= hi; i++)
            if (a[i] < a[i - 1]) return false;
        return true;
    } else {
        for (int i = 1; i <= hi; i++)
            if (a[i] > a[i - 1]) return false;
        return true;
    }
}

template<typename T> requires Comparable<T>
InsertionSort(span<T>) -> InsertionSort<T>;

template<typename T> requires Comparable<T>
InsertionSort(vector<T>) -> InsertionSort<T>;

template<typename T, size_t SIZE> requires Comparable<T>
InsertionSort(array<T, SIZE>) -> InsertionSort<T>;

template<typename T> requires Comparable<T>
InsertionSort(T a[]) -> InsertionSort<T>;

template<typename T> requires Comparable<T>
InsertionSort(span<T>, bool reverse) -> InsertionSort<T>;

template<typename T> requires Comparable<T>
InsertionSort(vector<T>, bool reverse) -> InsertionSort<T>;

template<typename T, size_t SIZE> requires Comparable<T>
InsertionSort(array<T, SIZE>, bool reverse) -> InsertionSort<T>;

template<typename T> requires Comparable<T>
InsertionSort(T a[], bool reverse) -> InsertionSort<T>;

#endif //ALGORITHMS_INSERTIONSORT_H
