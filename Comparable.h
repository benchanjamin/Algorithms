//
// Created by Ben Chan on 8/5/21.
//

#ifndef ALGORITHMS_COMPARABLE_H
#define ALGORITHMS_COMPARABLE_H

#include <concepts>

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

#endif //ALGORITHMS_COMPARABLE_H
