#ifndef ALGORITHMS_QUICKSELECT_HPP
#define ALGORITHMS_QUICKSELECT_HPP

#include <span>                 // std::span
#include <array>                // std::array
#include <vector>               // std::vector
#include "Comparable.hpp"       // includes Comparable concept used as a constraint
#include <cassert>              // std::assert

/**
 * Rearranges the array so that {@code a[k]} contains the kth smallest key;
 * {@code a[0]} through {@code a[k-1]} are less than (or equal to) {@code a[k]}; and
 * {@code a[k+1]} through {@code a[n-1]} are greater than (or equal to) {@code a[k]}.
 *
 * @param  a the array
 * @param  k the rank of the key
 * @return the key of rank {@code k}
 * @throws IllegalArgumentException unless {@code 0 <= k < a.length}
 */

template<typename T> requires Comparable<T>
class QuickSelect {
public:
    explicit QuickSelect<T>(span <T> a, bool reverse = false) {

    }

private:

};


/**
 * Deduct the type, <T>, of the QuickSelect class based on constructor argument types
 * and number of arguments
 */
template<typename T> requires Comparable<T>
QuickSelect(span <T>) -> QuickSort<T>;

template<typename T> requires Comparable<T>
QuickSelect(vector <T>) -> QuickSort<T>;

template<typename T, size_t SIZE> requires Comparable<T>
QuickSelect(array <T, SIZE>) -> QuickSort<T>;

template<typename T> requires Comparable<T>
QuickSelect(T a[]) -> QuickSort<T>;

template<typename T> requires Comparable<T>
QuickSelect(span <T>, bool reverse) -> QuickSort<T>;

template<typename T> requires Comparable<T>
QuickSelect(vector <T>, bool reverse) -> QuickSort<T>;

template<typename T, size_t SIZE> requires Comparable<T>
QuickSelect(array <T, SIZE>, bool reverse) -> QuickSort<T>;

template<typename T> requires Comparable<T>
QuickSelect(T a[], int length, bool reverse) -> QuickSort<T>;

#endif //ALGORITHMS_QUICKSELECT_HPP
