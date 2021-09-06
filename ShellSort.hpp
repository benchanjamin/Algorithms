#ifndef ALGORITHMS_SHELLSORT_HPP
#define ALGORITHMS_SHELLSORT_HPP

#include <span>
#include "Comparable.hpp"

using namespace std;

/**
 *  The {@code ShellSort} class use shell-sort to sort
 *  a container through invoking its constructor
 *  with the container variable and with
 *  Knuth's increment sequence
 *  (1, 4, 13, 40, ...). In the worst case, this implementation makes
 *  Θ(n^(3/2)) compares and exchanges to sort
 *  an array of length n.
 *
 *  This sorting algorithm is not stable.
 *  It uses Θ(1) extra memory (not including the input array).
 *
 *  @author Benjamin Chan
 *
 *  Adapted from Algorithms, 4th edition, {@authors Robert Sedgewick and Kevin Wayne}
 *  and their booksite https://algs4.cs.princeton.edu/
 *
 *  The Java program from which this C++ code was adapted from is found at
 *  https://algs4.cs.princeton.edu/21elementary/Shell.java.html.
 *
 *  @param <T> the generic type of an item in this sorting algorithm
 */
template<typename T> requires Comparable<T>
class ShellSort {
public:
    /**
     * Rearranges the container in ascending order, using the natural order, or descending order.
     *
     * @param a, the container to be sorted
     * @param a boolean specifying whether it should be reverse
     */
    explicit ShellSort<T>(span<T> a, bool reverse = false) {
        int n = a.size();
        int h = 1;
        while (h < n / 3)
            h = 3 * h + 1;
        if (!reverse) {
            while (h >= 1) {
                for (int i = h; i < n; i++) {
                    for (int j = i; j >= h && (a[j] < a[j - h]); j -= h) {
                        exch(a, j, j - h);
                    }
                }
                assert(isHsorted(a, h, reverse));
                h /= 3;
            }
        } else {
            while (h >= 1) {
                for (int i = h; i < n; i++) {
                    for (int j = i; j >= h && (a[j] > a[j - h]); j -= h) {
                        exch(a, j, j - h);
                    }
                }
                assert(isHsorted(a, h, reverse));
                h /= 3;
            }
        }
    };


private:
    void exch(span<T> a, int i, int j);

    bool isHsorted(span<T> a, int h, bool reverse);
};

template<typename T>
requires Comparable<T>
void ShellSort<T>::exch(span<T> a, int i, int j) {
    T swap = a[i];
    a[i] = a[j];
    a[j] = swap;
}

template<typename T>
requires Comparable<T>
bool ShellSort<T>::isHsorted(span<T> a, int h, bool reverse) {
    int length = a.size();
    if (!reverse) {
        for (int i = h; i < length; i++)
            if (a[i] < a[i - h]) return false;
        return true;
    } else {
        for (int i = h; i < length; i++)
            if (a[i] > a[i - h]) return false;
        return true;
    }
}

template<typename T> requires Comparable<T>
ShellSort(span<T>) -> ShellSort<T>;

template<typename T> requires Comparable<T>
ShellSort(vector<T>) -> ShellSort<T>;

template<typename T, size_t SIZE> requires Comparable<T>
ShellSort(array<T, SIZE>) -> ShellSort<T>;

template<typename T> requires Comparable<T>
ShellSort(T a[]) -> ShellSort<T>;

template<typename T> requires Comparable<T>
ShellSort(span<T>, bool reverse) -> ShellSort<T>;

template<typename T> requires Comparable<T>
ShellSort(vector<T>, bool reverse) -> ShellSort<T>;

template<typename T, size_t SIZE> requires Comparable<T>
ShellSort(array<T, SIZE>, bool reverse) -> ShellSort<T>;

template<typename T> requires Comparable<T>
ShellSort(T a[], bool reverse) -> ShellSort<T>;

#endif //ALGORITHMS_SHELLSORT_HPP
