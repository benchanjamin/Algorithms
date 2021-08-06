#ifndef ALGORITHMS_SELECTIONSORT_H
#define ALGORITHMS_SELECTIONSORT_H

#include <span>
#include "Comparable.h"

using namespace std;


template<typename T> requires Comparable<T>
class SelectionSort {
public:
    explicit SelectionSort<T>(span<T> a, bool reverse = false) {
        if (!reverse) {
            int n = a.size();
            for (int i = 0; i < n; i++) {
                int min = i;
                for (int j = i + 1; j < n; j++) {
                    if (a[j] < a[min]) min = j;
                }
                exch(a, i, min);
                assert(isSorted(a, 0, i, reverse));
            }
        } else {
            int n = a.size();
            for (int i = 0; i < n; i++) {
                int max = i;
                for (int j = i + 1; j < n; j++) {
                    if (a[j] > a[max]) max = j;
                }
                exch(a, i, max);
                assert(isSorted(a, 0, i, reverse));
            }
        }
        assert(isSorted(a, reverse));
    };
private:
    static void exch(span<T> a, int i, int j);

    static bool isSorted(span<T> a, int lo, int hi, bool reverse = false);

    static bool isSorted(span<T> a, bool reverse = false);
};

template<typename T>
requires Comparable<T>
void SelectionSort<T>::exch(span<T> a, int i, int j) {
    T swap = a[i];
    a[i] = a[j];
    a[j] = swap;
}

template<typename T>
requires Comparable<T>
bool SelectionSort<T>::isSorted(span<T> a, bool reverse) {
    return isSorted(a, 0, a.size() - 1, reverse);
}


template<typename T>
requires Comparable<T>
bool SelectionSort<T>::isSorted(span<T> a, int lo, int hi, bool reverse) {
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
SelectionSort(span<T>) -> SelectionSort<T>;

template<typename T> requires Comparable<T>
SelectionSort(vector<T>) -> SelectionSort<T>;

template<typename T, size_t SIZE> requires Comparable<T>
SelectionSort(array<T, SIZE>) -> SelectionSort<T>;

template<typename T> requires Comparable<T>
SelectionSort(T a[]) -> SelectionSort<T>;

template<typename T> requires Comparable<T>
SelectionSort(span<T>, bool reverse) -> SelectionSort<T>;

template<typename T> requires Comparable<T>
SelectionSort(vector<T>, bool reverse) -> SelectionSort<T>;

template<typename T, size_t SIZE> requires Comparable<T>
SelectionSort(array<T, SIZE>, bool reverse) -> SelectionSort<T>;

template<typename T> requires Comparable<T>
SelectionSort(T a[], bool reverse) -> SelectionSort<T>;

#endif //ALGORITHMS_SELECTIONSORT_H
