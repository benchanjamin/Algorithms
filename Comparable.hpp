//
// Created by Ben Chan on 8/5/21.
//

#ifndef ALGORITHMS_COMPARABLE_HPP
#define ALGORITHMS_COMPARABLE_HPP

#include <concepts>

/**
 * Checks if the From class is implicitly and explicitly convertible to the
 * To class.
 *
 * @throws an error at compile-time if this constraint is violated
 */
template<class From, class To>
concept convertible_to =
std::is_convertible_v<From, To> && requires(From (&f)()) {
    static_cast<To>(f());
};

/**
 * Checks if two classes are able to be compared with the "==" and "!=" operators
 *
 * @throws an error at compile-time if this constraint is violated
 */
template<typename T>
concept Equal =requires(T a, T b) {
    { a == b } -> same_as<bool>;
    { a != b } -> same_as<bool>;
};

/**
 * Checks if two classes are able to be compared with the ">", ">=", "<=", and "<"
 * operators
 *
 * @throws an error at compile-time if this constraint is violated
 */
template<typename T>
concept Comparable =
Equal<T> && requires(T a, T b) {
    { a <= b } -> same_as<bool>;
    { a < b } -> same_as<bool>;
    { a > b } -> same_as<bool>;
    { a >= b } -> same_as<bool>;
};

#endif //ALGORITHMS_COMPARABLE_HPP
