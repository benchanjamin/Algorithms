#ifndef ALGORITHMS_QUICKSORT_HPP
#define ALGORITHMS_QUICKSORT_HPP

#include <span>                 // std::span, std::array, std::vector
#include "Comparable.hpp"       // includes Comparable concept used as a constraint
#include <algorithm>            // std::min

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


private:
    int partition(span<T> a, int lo, int hi, bool reverse = false);
};

template<typename T>
int QuickSort<T>::partition(span<T> a, int lo, int hi, bool reverse) {
    int i = lo;
    int j = hi + 1;
    Comparable
    v = a[lo];
    while (true) {

        // find item on lo to swap
        while (less(a[++i], v)) {
            if (i == hi) break;
        }

        // find item on hi to swap
        while (less(v, a[--j])) {
            if (j == lo) break;      // redundant since a[lo] acts as sentinel
        }

        // check if pointers cross
        if (i >= j) break;

        exch(a, i, j);
    }

    // put partitioning item v at a[j]
    exch(a, lo, j);

    // now, a[lo .. j-1] <= a[j] <= a[j+1 .. hi]
    return j;
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
QuickSort(span<T>, bool reverse) -> MergeSortBU<T>;

template<typename T> requires Comparable<T>
MergeSortBU(vector<T>,
bool reverse
) ->
MergeSortBU<T>;

template<typename T, size_t SIZE> requires Comparable<T>
MergeSortBU(array<T, SIZE>,
bool reverse
) ->
MergeSortBU<T>;

template<typename T> requires Comparable<T>
MergeSortBU(T
a[],
bool reverse
) ->
MergeSortBU<T>;

#endif //ALGORITHMS_QUICKSORT_HPP
