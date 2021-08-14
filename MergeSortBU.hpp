#ifndef ALGORITHMS_MERGESORTBU_HPP
#define ALGORITHMS_MERGESORTBU_HPP

#include <span>                 // std::span, std::array, std::vector
#include "Comparable.hpp"       // includes Comparable concept used as a constraint
#include <algorithm>            // std::min

using namespace std;

/**
 *  The {@code MergeSortBU} class uses merge-sort (bottom-up) to sort
 *  a container through invoking its
 *  constructor with the container variable. It is non-recursive.
 *
 *  This implementation takes Θ(n * log(n)) time
 *  to sort any array of length n (assuming comparisons
 *  take constant time). It makes between
 *  ~ ½ * n * lg(n) and
 *  ~ 1 * n * lg(n) compares.
 *
 *  This sorting algorithm is stable.
 *  It uses Θ(n) extra memory (not including the input array).
 *
 *  @author Benjamin Chan
 *
 *  Adapted from Algorithms, 4th edition, {@authors Robert Sedgewick and Kevin Wayne}
 *  and their booksite https://algs4.cs.princeton.edu/
 *
 *  The Java program from which this C++ code was adapted from is found at
 *  https://algs4.cs.princeton.edu/22mergesort/MergeBU.java.html.
 *
 *  @param <T> the generic type of an item in this sorting algorithm
 */
template<typename T> requires Comparable<T>
class MergeSortBU {
public:
    /**
     * Rearranges the container in ascending order, using the natural order, or descending order.
     *
     * @param a, the container to be sorted
     * @param a boolean specifying whether it should be reverse
     */
    explicit MergeSortBU<T>(span<T> a, bool reverse = false) {
        int n = a.size();
        vector<T> aux(n);
        for (int len = 1; len < n; len *= 2) {
            for (int lo = 0; lo < n - len; lo += len + len) {
                int mid = lo + len - 1;
                int hi = min(lo + len + len - 1, n - 1);
                merge(a, aux, lo, mid, hi, reverse);
            }
        }
        assert(isSorted(a, reverse));
    };
private:

    // merge the two sub-arrays
    void merge(span<T> a, span<T> aux, int lo, int mid, int hi, bool reverse = false);

    // check if entire container is sorted -- useful for debugging
    bool isSorted(span<T> a, int lo, int hi, bool reverse = false);

    // check if container is sorted between two indices, lo and hi -- useful for debugging
    bool isSorted(span<T> a, bool reverse = false);
};

template<typename T>
requires Comparable<T>
void MergeSortBU<T>::merge(span<T> a, span<T> aux, int lo, int mid, int hi, bool reverse) {
    // copy to aux[]
    for (int k = lo; k <= hi; k++) {
        aux[k] = a[k];
    }

    // merge back to a[]
    int i = lo, j = mid + 1;
    if (!reverse) {
        for (int k = lo; k <= hi; k++) {
            if (i > mid)
                a[k] = aux[j++];
            else if (j > hi)
                a[k] = aux[i++];
            else if (aux[j] < aux[i])
                a[k] = aux[j++];
            else
                a[k] = aux[i++];
        }
    } else {
        for (int k = lo; k <= hi; k++) {
            if (i > mid)
                a[k] = aux[j++];
            else if (j > hi)
                a[k] = aux[i++];
            else if (aux[j] > aux[i])
                a[k] = aux[j++];
            else
                a[k] = aux[i++];
        }
    }
}

template<typename T>
requires Comparable<T>
bool MergeSortBU<T>::isSorted(span<T> a, bool reverse) {
    return isSorted(a, 0, a.size() - 1, reverse);
}


template<typename T>
requires Comparable<T>
bool MergeSortBU<T>::isSorted(span<T> a, int lo, int hi, bool reverse) {
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
MergeSortBU(span<T>) -> MergeSortBU<T>;

template<typename T> requires Comparable<T>
MergeSortBU(vector<T>) -> MergeSortBU<T>;

template<typename T, size_t SIZE> requires Comparable<T>
MergeSortBU(array<T, SIZE>) -> MergeSortBU<T>;

template<typename T> requires Comparable<T>
MergeSortBU(T a[]) -> MergeSortBU<T>;

template<typename T> requires Comparable<T>
MergeSortBU(span<T>, bool reverse) -> MergeSortBU<T>;

template<typename T> requires Comparable<T>
MergeSortBU(vector<T>, bool reverse) -> MergeSortBU<T>;

template<typename T, size_t SIZE> requires Comparable<T>
MergeSortBU(array<T, SIZE>, bool reverse) -> MergeSortBU<T>;

template<typename T> requires Comparable<T>
MergeSortBU(T a[], bool reverse) -> MergeSortBU<T>;

#endif //ALGORITHMS_MERGESORTBU_HPP
