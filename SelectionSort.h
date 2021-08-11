#ifndef ALGORITHMS_SELECTIONSORT_H
#define ALGORITHMS_SELECTIONSORT_H

#include <span>                 // std::span, std::array, std::vector
#include "Comparable.h"         // includes Comparable concept used as a constraint

using namespace std;

/**
 * The {@code SelectionSort} class provides static methods for sorting an
 * array using selection sort.
 * This implementation makes ~ ½ n^2 compares to sort
 * any array of length n, so it is not suitable for sorting large arrays.
 * It performs exactly n exchanges.
 *
 *  @author Benjamin Chan
 *
 *  Adapted from Algorithms, 4th edition, {@authors Robert Sedgewick and Kevin Wayne}
 *  and their booksite https://algs4.cs.princeton.edu/
 *
 *  The Java program from which this C++ code was adapted from is found at
 *  https://algs4.cs.princeton.edu/21elementary/Selection.java.html.
 *
 *  @param <T> the generic type of an item in this sorting algorithm
 */
template<typename T> requires Comparable<T>
class SelectionSort {
public:
    /**
     * Rearranges the container in ascending order, using the natural order, or descending order.
     *
     * @param a, the container to be sorted
     * @param a boolean specifying whether it should be reverse
     */
    explicit SelectionSort<T>(span<T> a, bool reverse = false) {
        if (!reverse) {
            int n = a.size();
            for (int i = 0; i < n; i++) {
                int min = i;
                for (int j = i + 1; j < n; j++) {
                    if (a[j] < a[min]) min = j;
                }
                exch(a, i, min);
                assert(isSorted(a, 0, i, reverse));
            }
        } else {
            int n = a.size();
            for (int i = 0; i < n; i++) {
                int max = i;
                for (int j = i + 1; j < n; j++) {
                    if (a[j] > a[max]) max = j;
                }
                exch(a, i, max);
                assert(isSorted(a, 0, i, reverse));
            }
        }
        assert(isSorted(a, reverse));
    };
private:
    // exchange a[i] and a[j]
    static void exch(span<T> a, int i, int j);

    // check if entire container is sorted -- useful for debugging
    static bool isSorted(span<T> a, int lo, int hi, bool reverse = false);

    // check if container is sorted between two indices, lo and hi -- useful for debugging
    static bool isSorted(span<T> a, bool reverse = false);
};

template<typename T>
requires Comparable<T>
void SelectionSort<T>::exch(span<T> a, int i, int j) {
    T swap = a[i];
    a[i] = a[j];
    a[j] = swap;
}

template<typename T>
requires Comparable<T>
bool SelectionSort<T>::isSorted(span<T> a, bool reverse) {
    return isSorted(a, 0, a.size() - 1, reverse);
}


template<typename T>
requires Comparable<T>
bool SelectionSort<T>::isSorted(span<T> a, int lo, int hi, bool reverse) {
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

/**
 * Deduct the type, <T>, of the InsertionSort class based on constructor argument types
 * and number of arguments
 */
template<typename T> requires Comparable<T>
SelectionSort(span<T>) -> SelectionSort<T>;

template<typename T> requires Comparable<T>
SelectionSort(vector<T>) -> SelectionSort<T>;

template<typename T, size_t SIZE> requires Comparable<T>
SelectionSort(array<T, SIZE>) -> SelectionSort<T>;

template<typename T> requires Comparable<T>
SelectionSort(T a[]) -> SelectionSort<T>;

template<typename T> requires Comparable<T>
SelectionSort(span<T>, bool reverse) -> SelectionSort<T>;

template<typename T> requires Comparable<T>
SelectionSort(vector<T>, bool reverse) -> SelectionSort<T>;

template<typename T, size_t SIZE> requires Comparable<T>
SelectionSort(array<T, SIZE>, bool reverse) -> SelectionSort<T>;

template<typename T> requires Comparable<T>
SelectionSort(T a[], bool reverse) -> SelectionSort<T>;

#endif //ALGORITHMS_SELECTIONSORT_H
