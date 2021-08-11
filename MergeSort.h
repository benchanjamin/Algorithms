#ifndef ALGORITHMS_MERGESORT_H
#define ALGORITHMS_MERGESORT_H

#include <span>                 // std::span, std::array, std::vector
#include "Comparable.h"         // includes Comparable concept used as a constraint

using namespace std;

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
        // precondition: a[lo .. mid] and a[mid+1 .. hi] are sorted subarrays
        assert(isSorted(a, lo, mid));
        assert(isSorted(a, mid + 1, hi));

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
void MergeSort<T>::exch(span<T> a, int i, int j) {
    T swap = a[i];
    a[i] = a[j];
    a[j] = swap;
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

#endif //ALGORITHMS_MERGESORT_H
