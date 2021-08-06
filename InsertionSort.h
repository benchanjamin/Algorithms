#ifndef ALGORITHMS_INSERTIONSORT_H
#define ALGORITHMS_INSERTIONSORT_H

#include <span>
#include "Comparable.h"

using namespace std;

template<typename T> requires Comparable<T>
class InsertionSort {
public:
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
    static void exch(span<T> a, int i, int j);

    static bool isSorted(span<T> a, bool reverse);

    static bool isSorted(span<T> a, int lo, int hi, bool reverse);
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

#endif //ALGORITHMS_INSERTIONSORT_H
