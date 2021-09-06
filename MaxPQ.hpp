#ifndef ALGORITHMS_MAXPQ_HPP
#define ALGORITHMS_MAXPQ_HPP

#include <span>                     // std::span
#include <array>                    // std::array
#include <vector>                   // std::vector
#include "Comparable.hpp"           // includes Comparable concept used as a constraint
#include <cassert>                  // std::assert
#include <boost/lexical_cast.hpp>   // boost::lexical_cast

using namespace std;

/**
 *  The {@code MaxPQ} class represents a priority queue of generic keys.
 *  It supports the usual insert and delete-the-maximum
 *  operations, along with methods for peeking at the maximum key,
 *  testing if the priority queue is empty, and iterating through
 *  the keys.
 *
 *  This implementation uses a binary heap.
 *  The insert and delete-the-maximum operations take
 *  Θ(log(n)) amortized time, where n is the number
 *  of elements in the priority queue. This is an amortized bound
 *  (and not a worst-case bound) because of array resizing operations.
 *  The min, size, and is-empty operations take
 *  Θ(1) time in the worst case.
 *  Construction takes time proportional to the specified capacity or the
 *  number of items used to initialize the data structure.
 *
 *  @author Benjamin Chan
 *
 *  Adapted from Algorithms, 4th edition, {@authors Robert Sedgewick and Kevin Wayne}
 *  and their booksite https://algs4.cs.princeton.edu/
 *
 *  The Java program from which this C++ code was adapted from is found at
 *  https://algs4.cs.princeton.edu/24pq/MaxPQ.java.html.
 *
 *  @param <T> the generic type of key on this priority queue
 */
template<typename T> requires Comparable<T>
class MaxPQ {
public:
    /**
     * Initializes an empty priority queue.
     */
    MaxPQ() {
        this->n = 0;
    }

    /**
     * Initializes a priority queue from the vector of keys.
     * Takes time proportional to the number of keys, using sink-based heap construction.
     *
     * @param keys, the vector of keys
     */
    explicit MaxPQ(vector<T> keys) {
        n = keys.size();
        pq = vector<T>(n + 1);
        for (int i = 0; i < n; i++)
            pq[i + 1] = keys[i];
        for (int k = n / 2; k >= 1; k--)
            sink(k);
    }

    /**
     * Returns true if this priority queue is empty.
     *
     * @return {@code true} if this priority queue is empty;
     *         {@code false} otherwise
     */
    bool isEmpty() {
        return n == 0;
    }

    /**
     * Returns the number of keys on this priority queue.
     *
     * @return the number of keys on this priority queue
     */
    int size() {
        return n;
    }

    /**
     * Returns a largest key on this priority queue.
     *
     * @return a largest key on this priority queue
     * @throws NoSuchElementException if this priority queue is empty
     */
    T max() {
        try {
            if (isEmpty()) throw NoSuchElementException();
            return pq[1];
        }
        catch (NoSuchElementException &e) {
            std::cout << "NoSuchElementException encountered: ";
            std::cout << e.what() << std::endl;
        }
    }

    /**
     * Adds a new key to this priority queue.
     *
     * @param  x the new key to add to this priority queue
     */
    void insert(T x) {
        // add x, and percolate it up to maintain heap invariant
        pq.push_back(x);
        swim(n);
    }

    /**
     * Removes and returns a largest key on this priority queue.
     *
     * @return a largest key on this priority queue
     * @throws NoSuchElementException if this priority queue is empty
     */
    T delMax() {
        try {
            if (isEmpty()) throw NoSuchElementException();

            T max = pq[1];
            exch(1, n--);
            sink(1);
            pq.erase(pq.begin() + n + 1); // to avoid loitering and help with garbage collection
            return max;
        }
        catch (NoSuchElementException &e) {
            std::cout << "NoSuchElementException encountered: ";
            std::cout << e.what() << std::endl;
        }
    }

    /**
      * Returns a string representation of this priority queue.
      *
      * @return the sequence of items in descending order, separated by spaces
      */
    [[nodiscard]] std::string toString() const;

private:
    vector<T> pq;               // store items at indices 1 to n
    int n{};                    // number of items on priority queue

    /**
     * @def the NoSuchElementException if there are no items in the priority queue after
     * using the max(), methods
     */
    struct NoSuchElementException : public std::exception {
        const char *what() {
            return "Priority Queue Underflow";
        }
    };

    /***************************************************************************
     * Helper functions to restore the heap invariant.
     ***************************************************************************/

    void swim(int k) {
        while (k > 1 && pq[k / 2] < k) {
            exch(k, k / 2);
            k = k / 2;
        }
    }

    void sink(int k) {
        while (2 * k <= n) {
            int j = 2 * k;
            if (j < n && pq[j] < pq[j + 1]) j++;
            if (pq[k] >= pq[j]) break;
            exch(k, j);
            k = j;
        }
    }


    /***************************************************************************
     * Helper functions for compares and swaps.
     ***************************************************************************/

    void exch(int i, int j) {
        T swap = pq[i];
        pq[i] = pq[j];
        pq[j] = swap;
    }

};

template<typename T>
requires Comparable<T>
std::string MaxPQ<T>::toString() const {
    std::stringstream ss;
    MaxPQ<T> copy{this->pq};
    while (!copy.isEmpty()) {
        ss << boost::lexical_cast<std::string>(copy.delMax()) << " ";
    }
    ss << endl;
    return ss.str();
}

/// Overloads the "<<" operator for a bag
template<typename T>
std::ostream &operator<<(std::ostream &os, const MaxPQ<T> &maxPQ) {
    return os << maxPQ.toString();
}

/// Uses type deduction for one of the constructors
template<typename T> requires Comparable<T>
MaxPQ(vector<T>) -> MaxPQ<T>;

#endif //ALGORITHMS_MAXPQ_HPP
