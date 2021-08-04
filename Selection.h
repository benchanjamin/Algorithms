//
// Created by Ben Chan on 7/31/21.
//

#ifndef ALGORITHMS_SELECTION_H
#define ALGORITHMS_SELECTION_H

#include <algorithm>
#include <concepts>
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


class Selection {
    Selection() = default;

    template<typename T>
    requires Comparable<T>
    static void exch(span<T> a, int i, int j);

public:
    template<typename T>
    requires Comparable<T>
    static void sort(span<T> a);
};

template<typename T>
requires Comparable<T>
void Selection::sort(span<T> a) {
    int n = a.size();
    for (int i = 0; i < n; i++) {
        int min = i;
        for (int j = i + 1; j < n; j++) {
            if (a[j] < a[min]) min = j;
        }
        exch(a, i, min);
    }
}

template<typename T>
requires Comparable<T>
void Selection::exch(span<T> a, int i, int j) {
    T swap = a[i];
    a[i] = a[j];
    a[j] = swap;
}


#endif //ALGORITHMS_SELECTION_H
