#ifndef ALGORITHMS_SHELLSORT_H
#define ALGORITHMS_SHELLSORT_H

#include <span>
#include "Comparable.h"

using namespace std;

template<typename T> requires Comparable<T>
class ShellSort {
    explicit ShellSort<T>(span<T> a) {
        int n = a.size();
        for (int i = 1; i < n; i++) {
            for (int j = i; j > 0 && (a[j] < a[j - 1]); j--) {
                exch(a, j, j - 1);
            }
        }
    };

    static void exch(span<T> a, int i, int j);

public:
};

template<typename T>
requires Comparable<T>
void ShellSort<T>::exch(span<T> a, int i, int j) {
    T swap = a[i];
    a[i] = a[j];
    a[j] = swap;
}

template<typename T> requires Comparable<T>
ShellSort(span<T>) -> ShellSort<T>;

template<typename T> requires Comparable<T>
ShellSort(vector<T>) -> ShellSort<T>;

template<typename T, size_t SIZE> requires Comparable<T>
ShellSort(array<T, SIZE>) -> ShellSort<T>;

template<typename T> requires Comparable<T>
ShellSort(T a[]) -> ShellSort<T>;

#endif //ALGORITHMS_SHELLSORT_H
