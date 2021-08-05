#ifndef ALGORITHMS_SELECTIONSORT_H
#define ALGORITHMS_SELECTIONSORT_H

#include <span>

using namespace std;

template<class From, class To>
concept convertible_to =
std::is_convertible_v<From, To> && requires(From (&f)()) {
    static_cast<To>(f());
};

template<typename T>
concept Equal =requires(T a, T b) {
    { a == b } -> convertible_to<bool>;
    { a != b } -> convertible_to<bool>;
};

template<typename T>
concept Comparable =
Equal<T> && requires(T a, T b) {
    { a <= b } -> convertible_to<bool>;
    { a < b } -> convertible_to<bool>;
    { a > b } -> convertible_to<bool>;
    { a >= b } -> convertible_to<bool>;
};

template<typename T> requires Comparable<T>
class SelectionSort {
public:
    explicit SelectionSort<T>(span<T> a) {
        int n = a.size();
        for (int i = 0; i < n; i++) {
            int min = i;
            for (int j = i + 1; j < n; j++) {
                if (a[j] < a[min]) min = j;
            }
            exch(a, i, min);
        }
    };
private:
    static void exch(span<T> a, int i, int j);
};

template<typename T>
requires Comparable<T>
void SelectionSort<T>::exch(span<T> a, int i, int j) {
    T swap = a[i];
    a[i] = a[j];
    a[j] = swap;
}

template<typename T> requires Comparable<T>
SelectionSort(span<T>) -> SelectionSort<T>;

template<typename T> requires Comparable<T>
SelectionSort(vector<T>) -> SelectionSort<T>;

template<typename T, size_t SIZE> requires Comparable<T>
SelectionSort(array<T, SIZE>) -> SelectionSort<T>;

template<typename T> requires Comparable<T>
SelectionSort(T a[]) -> SelectionSort<T>;

#endif //ALGORITHMS_SELECTIONSORT_H
