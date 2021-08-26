#ifndef ALGORITHMS_MINPQ_HPP
#define ALGORITHMS_MINPQ_HPP

#include <span>                 // std::span
#include <array>                // std::array
#include <vector>               // std::vector
#include "Comparable.hpp"       // includes Comparable concept used as a constraint
#include <cassert>              // std::assert

/**
 *  The {@code MinPQ} class represents a priority queue of generic keys.
 *  It supports the usual <em>insert</em> and <em>delete-the-minimum</em>
 *  operations, along with methods for peeking at the minimum key,
 *  testing if the priority queue is empty, and iterating through
 *  the keys.
 *  <p>
 *  This implementation uses a <em>binary heap</em>.
 *  The <em>insert</em> and <em>delete-the-minimum</em> operations take
 *  &Theta;(log <em>n</em>) amortized time, where <em>n</em> is the number
 *  of elements in the priority queue. This is an amortized bound
 *  (and not a worst-case bound) because of array resizing operations.
 *  The <em>min</em>, <em>size</em>, and <em>is-empty</em> operations take
 *  &Theta;(1) time in the worst case.
 *  Construction takes time proportional to the specified capacity or the
 *  number of items used to initialize the data structure.
 *  <p>
 *  For additional documentation, see
 *  <a href="https://algs4.cs.princeton.edu/24pq">Section 2.4</a> of
 *  <i>Algorithms, 4th Edition</i> by Robert Sedgewick and Kevin Wayne.
 *
 *  @author Robert Sedgewick
 *  @author Kevin Wayne
 *
 *  @param <Key> the generic type of key on this priority queue
 */
template<typename T> requires Comparable<T>
class MinPQ {
public:
    /**
 * Initializes an empty priority queue with the given initial capacity.
 *
 * @param  initCapacity the initial capacity of this priority queue
 */
    explicit MinPQ(int initCapacity) {
        pq = (Key[])
        new Object[initCapacity + 1];
        n = 0;
    }

private:
    std::vector<T> pq;              // store items at indices 1 to n
    int n;                          // number of items on priority queue
};

#endif //ALGORITHMS_MINPQ_HPP
