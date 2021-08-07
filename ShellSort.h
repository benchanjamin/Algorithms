#ifndef ALGORITHMS_SHELLSORT_H
#define ALGORITHMS_SHELLSORT_H

#include <span>
#include "Comparable.h"

using namespace std;

template<typename T> requires Comparable<T>
class ShellSort {
public:
    explicit ShellSort<T>(span<T> a, bool reverse = true) {
        if (reverse) {
            int n = a.size();
            int h = 1;
            while (h < n / 3)
                h = 3 * h + 1;
            while (h >= 1) {
                for (int i = h; i < n; i++) {
                    for (int j = i; j >= h && (a[j] < a[j - h]); j -= h) {
                        exch(a, j, j - h);
                    }
                }
                h /= 3;
            }
        }
    };


private:
    static void exch(span<T> a, int i, int j);

    static bool isHsorted(span<T>, int h);

};

template<typename T>
requires Comparable<T>
void ShellSort<T>::exch(span<T> a, int i, int j) {
    T swap = a[i];
    a[i] = a[j];
    a[j] = swap;
}

template<typename T>
bool ShellSort<T>::isHsorted(span<T> a, int h) {
    int length = a.size();
    for (int i = h; i < length; i++)
        if (a[i] < a[i - h]) return false;
    return true;
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
