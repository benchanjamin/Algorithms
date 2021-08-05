#ifndef ALGORITHMS_INSERTIONSORT_H
#define ALGORITHMS_INSERTIONSORT_H

#include <span>
#include "Comparable.h"

using namespace std;

template<typename T> requires Comparable<T>
class InsertionSort {
    explicit InsertionSort<T>(span<T> a) {
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
void InsertionSort<T>::exch(span<T> a, int i, int j) {
    T swap = a[i];
    a[i] = a[j];
    a[j] = swap;
}

template<typename T> requires Comparable<T>
InsertionSort(span<T>) -> InsertionSort<T>;

template<typename T> requires Comparable<T>
InsertionSort(vector<T>) -> InsertionSort<T>;

template<typename T, size_t SIZE> requires Comparable<T>
InsertionSort(array<T, SIZE>) -> InsertionSort<T>;

template<typename T> requires Comparable<T>
InsertionSort(T a[]) -> InsertionSort<T>;

#endif //ALGORITHMS_INSERTIONSORT_H
