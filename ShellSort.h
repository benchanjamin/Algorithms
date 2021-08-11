#ifndef ALGORITHMS_SHELLSORT_H
#define ALGORITHMS_SHELLSORT_H

#include <span>
#include "Comparable.h"

using namespace std;

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
    static void exch(span<T> a, int i, int j);

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

#endif //ALGORITHMS_SHELLSORT_H
