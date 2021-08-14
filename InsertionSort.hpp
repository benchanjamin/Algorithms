#ifndef ALGORITHMS_INSERTIONSORT_HPP
#define ALGORITHMS_INSERTIONSORT_HPP

#include <span>             // std::span, std::array, std::vector
#include "Comparable.hpp"     // includes Comparable concept used as a constraint

using namespace std;

/**
 *  The {@code InsertionSort} class sorts a container through invoking its
 *  constructor with the container variable.
 *
 *  In the worst case, this implementation makes ~ ½ n^2
 *  compares and ~ ½ * n^2 exchanges to sort a container
 *  of length n. So, it is not suitable for sorting large arbitrary
 *  arrays. More precisely, the number of exchanges is exactly equal to the
 *  number of inversions. So, for example, it sorts a partially-sorted container
 *  in linear time.
 *
 *  This sorting algorithm is stable.
 *  It uses Θ(1) extra memory (not including the input array).
 *
 *  @author Benjamin Chan
 *
 *  Adapted from Algorithms, 4th edition, {@authors Robert Sedgewick and Kevin Wayne}
 *  and their booksite https://algs4.cs.princeton.edu/
 *
 *  The Java program from which this C++ code was adapted from is found at
 *  https://algs4.cs.princeton.edu/25applications/Insertion.java.html.
 *
 *  @param <T> the generic type of an item in this sorting algorithm
 */
template<typename T> requires Comparable<T>
class InsertionSort {
public:
    /**
     * Rearranges the container in ascending order, using the natural order, or descending order.
     *
     * @param a, the container to be sorted
     * @param a boolean specifying whether it should be reverse
     */
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
    // exchange a[i] and a[j]
    void exch(span<T> a, int i, int j);

    // check if entire container is sorted -- useful for debugging
    bool isSorted(span<T> a, bool reverse);

    // check if container is sorted between two indices, lo and hi -- useful for debugging
    bool isSorted(span<T> a, int lo, int hi, bool reverse);
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

/**
 * Deduct the type, <T>, of the InsertionSort class based on constructor argument types
 * and number of arguments
 */
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

#endif //ALGORITHMS_INSERTIONSORT_HPP
