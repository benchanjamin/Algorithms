#ifndef ALGORITHMS_MERGESORT_HPP
#define ALGORITHMS_MERGESORT_HPP

#include <span>                 // std::span, std::array, std::vector
#include "Comparable.hpp"       // includes Comparable concept used as a constraint

using namespace std;

/**
 *  The {@code MergeSort} class uses merge-sort to sort
 *  a container through invoking its
 *  constructor with the container variable.
 *
 *  This implementation takes Θ(nlog(n)) time
 *  to sort any array of length n (assuming comparisons
 *  take constant time). It makes between
 *  ~ ½ * n * lg(n) and
 *  ~ 1 * n * lg(n) compares.
 *
 *  @author Benjamin Chan
 *
 *  Adapted from Algorithms, 4th edition, {@authors Robert Sedgewick and Kevin Wayne}
 *  and their booksite https://algs4.cs.princeton.edu/
 *
 *  The Java program from which this C++ code was adapted from is found at
 *  https://algs4.cs.princeton.edu/22mergesort/Merge.java.html.
 *
 * @param <T> the generic type of an item in this sorting algorithm */
template<typename T> requires Comparable<T>
class MergeSort {
public:
    /**
     * Rearranges the container in ascending order, using the natural order, or descending order.
     *
     * @param a, the container to be sorted
     * @param a boolean specifying whether it should be reverse
     */
    explicit MergeSort<T>(span<T> a, bool reverse = false) {
        int length = a.size();
        vector<T> aux(length);
        sort(a, aux, 0, a.size() - 1, reverse);
        assert(isSorted(a, reverse));
    };
private:
    // private helper sort
    void sort(span<T> a, span<T> aux, int lo, int hi, bool reverse = false);

    // merge the two sub-arrays
    void merge(span<T> a, span<T> aux, int lo, int mid, int hi, bool reverse = false);

    // check if entire container is sorted -- useful for debugging
    bool isSorted(span<T> a, int lo, int hi, bool reverse = false);

    // check if container is sorted between two indices, lo and hi -- useful for debugging
    bool isSorted(span<T> a, bool reverse = false);
};

template<typename T>
requires Comparable<T>
void MergeSort<T>::sort(span<T> a, span<T> aux, int lo, int hi, bool reverse) {
    if (hi <= lo) return;
    int mid = lo + (hi - lo) / 2;
    sort(a, aux, lo, mid, reverse);
    sort(a, aux, mid + 1, hi, reverse);
    merge(a, aux, lo, mid, hi, reverse);
}

template<typename T>
requires Comparable<T>
void MergeSort<T>::merge(span<T> a, span<T> aux, int lo, int mid, int hi, bool reverse) {
    // precondition: a[lo .. mid] and a[mid+1 .. hi] are sorted subarrays
    assert(isSorted(a, lo, mid, reverse));
    assert(isSorted(a, mid + 1, hi, reverse));

    // copy to aux[]
    for (int k = lo; k <= hi; k++) {
        aux[k] = a[k];
    }

    // merge back to a[]
    int i = lo, j = mid + 1;
    if (!reverse) {
        for (int k = lo; k <= hi; k++) {
            if (i > mid) {
                a[k] = aux[j++];
            } else if (j > hi) {
                a[k] = aux[i++];
            } else if (aux[j] < aux[i]) {
                a[k] = aux[j++];
            } else {
                a[k] = aux[i++];
            }
        }
    } else {
        for (int k = lo; k <= hi; k++) {
            if (i > mid) {
                a[k] = aux[j++];
            } else if (j > hi) {
                a[k] = aux[i++];
            } else if (aux[j] > aux[i]) {
                a[k] = aux[j++];
            } else {
                a[k] = aux[i++];
            }
        }
    }

    // postcondition: a[lo .. hi] is sorted
    assert(isSorted(a, lo, hi, reverse));
}

template<typename T>
requires Comparable<T>
bool MergeSort<T>::isSorted(span<T> a, bool reverse) {
    return isSorted(a, 0, a.size() - 1, reverse);
}


template<typename T>
requires Comparable<T>
bool MergeSort<T>::isSorted(span<T> a, int lo, int hi, bool reverse) {
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
MergeSort(span<T>) -> MergeSort<T>;

template<typename T> requires Comparable<T>
MergeSort(vector<T>) -> MergeSort<T>;

template<typename T, size_t SIZE> requires Comparable<T>
MergeSort(array<T, SIZE>) -> MergeSort<T>;

template<typename T> requires Comparable<T>
MergeSort(T a[]) -> MergeSort<T>;

template<typename T> requires Comparable<T>
MergeSort(span<T>, bool reverse) -> MergeSort<T>;

template<typename T> requires Comparable<T>
MergeSort(vector<T>, bool reverse) -> MergeSort<T>;

template<typename T, size_t SIZE> requires Comparable<T>
MergeSort(array<T, SIZE>, bool reverse) -> MergeSort<T>;

template<typename T> requires Comparable<T>
MergeSort(T a[], bool reverse) -> MergeSort<T>;

#endif //ALGORITHMS_MERGESORT_HPP
