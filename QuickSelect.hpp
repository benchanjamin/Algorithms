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
    int indexOf(int rank);

private:
    span<T> container;
};

template<typename T>
requires Comparable<T>
int QuickSelect<T>::indexOf(int rank) {
    int containerLength = this->container.size();
    if (rank < 0 || rank >= containerLength) {
        throw invalid_argument("index is not between 0 and " + to_string(containerLength) + ": " +
                               to_string(rank));
    }
    shuffle(container.begin(), container.end());
    int lo = 0, hi = containerLength - 1;
    while (hi > lo) {
        int i = partition(container, lo, hi);
        if (i > rank) hi = i - 1;
        else if (i < rank) lo = i + 1;
        else return container[i];
    }
    return container[lo];
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
