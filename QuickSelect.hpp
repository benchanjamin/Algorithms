#ifndef ALGORITHMS_QUICKSELECT_HPP
#define ALGORITHMS_QUICKSELECT_HPP

#include <span>                 // std::span
#include <array>                // std::array
#include <vector>               // std::vector
#include "Comparable.hpp"       // includes Comparable concept used as a constraint
#include <cassert>              // std::assert
#include <stdexcept>            // std::invalid_argument


template<typename T> requires Comparable<T>
class QuickSelect {
public:
    explicit QuickSelect<T>(span<T> a, bool reverse = false) {
        this->container = a;
    }

    /**
     * Rearranges the array so that {@code a[k]} contains the kth smallest key;
     * {@code a[0]} through {@code a[k-1]} are less than (or equal to) {@code a[k]}; and
     * {@code a[k+1]} through {@code a[n-1]} are greater than (or equal to) {@code a[k]}.
     *
     * @param  k the rank of the key
     * @return the key of rank {@code k}
     * @throws IllegalArgumentException unless {@code 0 <= k < a.length}
     */
    int rankOf(int rank, bool reverse = false);

private:
    span<T> container;

    void sort(span<T> a, int lo, int hi, bool reverse = false);

    int partition(span<T> a, int lo, int hi, bool reverse = false);

    void exch(span<T> a, int i, int j);

    // check if entire container is sorted -- useful for debugging
    bool isSorted(span<T> a, int lo, int hi, bool reverse = false);

    // check if container is sorted between two indices, lo and hi -- useful for debugging
    bool isSorted(span<T> a, bool reverse = false);
};

template<typename T>
requires Comparable<T>
int QuickSelect<T>::rankOf(int rank, bool reverse) {
    int containerLength = this->container.size();
    if (rank < 0 || rank >= containerLength) {
        throw invalid_argument("index is not between 0 and " + to_string(containerLength) + ": " +
                               to_string(rank));
    }
    random_device rd;
    mt19937 g(rd());
    shuffle(container.begin(), container.end(), g);
    int lo = 0, hi = containerLength - 1;
    while (hi > lo) {
        int i = partition(container, lo, hi, reverse);
        if (i > rank) hi = i - 1;
        else if (i < rank) lo = i + 1;
        else return container[i];
    }
    return container[lo];
}

template<typename T>
requires Comparable<T>
void QuickSelect<T>::sort(span<T> a, int lo, int hi, bool reverse) {
    if (hi <= lo) return;
    int j = partition(a, lo, hi, reverse);
    sort(a, lo, j - 1, reverse);
    sort(a, j + 1, hi, reverse);
    assert(isSorted(a, lo, hi, reverse));
}

template<typename T>
requires Comparable<T>
int QuickSelect<T>::partition(span<T> a, int lo, int hi, bool reverse) {
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
void QuickSelect<T>::exch(span<T> a, int i, int j) {
    T swap = a[i];
    a[i] = a[j];
    a[j] = swap;
}

template<typename T>
requires Comparable<T>
bool QuickSelect<T>::isSorted(span<T> a, bool reverse) {
    return isSorted(a, 0, a.size() - 1, reverse);
}


template<typename T>
requires Comparable<T>
bool QuickSelect<T>::isSorted(span<T> a, int lo, int hi, bool reverse) {
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
 * Deduct the type, <T>, of the QuickSelect class based on constructor argument types
 * and number of arguments
 */
template<typename T> requires Comparable<T>
QuickSelect(span<T>) -> QuickSelect<T>;

template<typename T> requires Comparable<T>
QuickSelect(vector<T>) -> QuickSelect<T>;

template<typename T, size_t SIZE> requires Comparable<T>
QuickSelect(array<T, SIZE>) -> QuickSelect<T>;

template<typename T> requires Comparable<T>
QuickSelect(T a[]) -> QuickSelect<T>;

template<typename T> requires Comparable<T>
QuickSelect(span<T>, bool reverse) -> QuickSelect<T>;

template<typename T> requires Comparable<T>
QuickSelect(vector<T>, bool reverse) -> QuickSelect<T>;

template<typename T, size_t SIZE> requires Comparable<T>
QuickSelect(array<T, SIZE>, bool reverse) -> QuickSelect<T>;

template<typename T> requires Comparable<T>
QuickSelect(T a[], int length, bool reverse) -> QuickSelect<T>;

#endif //ALGORITHMS_QUICKSELECT_HPP
