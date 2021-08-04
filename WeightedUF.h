//
// Created by Ben Chan on 7/24/21.
//

#ifndef ALGORITHMS_WEIGHTEDUF_H
#define ALGORITHMS_WEIGHTEDUF_H

#include <cstdint>
#include <string>
#include <vector>
#include <exception>

using namespace std;

/**
 *  The {@code WeightedUF} class represents a <em>union–find data type</em>
 *  (also known as the <em>disjoint-sets data type</em>).
 *  It supports the classic <em>union</em> and <em>find</em> operations,
 *  along with a <em>count</em> operation that returns the total number
 *  of sets.
 *  <p>
 *  The union–find data type models a collection of sets containing
 *  <em>n</em> elements, with each element in exactly one set.
 *  The elements are named 0 through <em>n</em>–1.
 *  Initially, there are <em>n</em> sets, with each element in its
 *  own set. The <em>canonical element</em> of a set
 *  (also known as the <em>root</em>, <em>identifier</em>,
 *  <em>leader</em>, or <em>set representative</em>)
 *  is one distinguished element in the set. Here is a summary of
 *  the operations:
 *  <ul>
 *  <li><em>find</em>(<em>p</em>) returns the canonical element
 *      of the set containing <em>p</em>. The <em>find</em> operation
 *      returns the same value for two elements if and only if
 *      they are in the same set.
 *  <li><em>union</em>(<em>p</em>, <em>q</em>) merges the set
 *      containing element <em>p</em> with the set containing
 *      element <em>q</em>. That is, if <em>p</em> and <em>q</em>
 *      are in different sets, replace these two sets
 *      with a new set that is the union of the two.
 *  <li><em>count</em>() returns the number of sets.
 *  </ul>
 *  <p>
 *  The canonical element of a set can change only when the set
 *  itself changes during a call to <em>union</em>&mdash;it cannot
 *  change during a call to either <em>find</em> or <em>count</em>.
 *  <p>
 *  This implementation uses <em>weighted quick union by rank</em>
 *  with <em>path compression by halving</em>.
 *  The constructor takes &Theta;(<em>n</em>) time, where
 *  <em>n</em> is the number of elements.
 *  The <em>union</em> and <em>find</em> operations take
 *  &Theta;(log <em>n</em>) time in the worst case.
 *  The <em>count</em> operation takes &Theta;(1) time.
 *  Moreover, starting from an empty data structure with <em>n</em> sites,
 *  any intermixed sequence of <em>m</em> <em>union</em> and <em>find</em>
 *  operations takes <em>O</em>(<em>m</em> &alpha;(<em>n</em>)) time,
 *  where &alpha;(<em>n</em>) is the inverse of
 *  <a href = "https://en.wikipedia.org/wiki/Ackermann_function#Inverse">Ackermann's function</a>.
 *  <p>
 *  For alternative implementations of the same API, see
 *  {@link QuickUnionUF}, {@link QuickFindUF}, and {@link WeightedQuickUnionUF}.
 *  For additional documentation, see
 *  <a href="https://algs4.cs.princeton.edu/15uf">Section 1.5</a> of
 *  <i>Algorithms, 4th Edition</i> by Robert Sedgewick and Kevin Wayne.
 *
 *  @author Robert Sedgewick
 *  @author Kevin Wayne
 *  @author Benjamin Chan
 *  @author Ben Barani
 */

class WeightedUF {
    vector<int> parent;
    vector<int8_t> rank;
    int thisCount;
public:
    /**
     * Initializes an empty union-find data structure with
     * {@code n} elements {@code 0} through {@code n-1}.
     * Initially, each elements is in its own set.
     *
     * @param  n the number of elements
     * @throws IllegalArgumentException if {@code n < 0}
     */
    explicit WeightedUF(int n);

    /**
     * Returns the canonical element of the set containing element {@code p}.
     *
     * @param  p an element
     * @return the canonical element of the set containing {@code p}
     * @throws IllegalArgumentException unless {@code 0 <= p < n}
     */
    int find(int p);

    /**
     * Returns the number of sets.
     *
     * @return the number of sets (between {@code 1} and {@code n})
     */
    inline int count() {
        return thisCount;
    }

    /**
     * Merges the set containing element {@code p} with the
     * the set containing element {@code q}.
     *
     * @param  p one element
     * @param  q the other element
     * @throws IllegalArgumentException unless
     *         both {@code 0 <= p < n} and {@code 0 <= q < n}
     */
    void weightedUnion(int p, int q);

    // validate that p is a valid index
    void validate(int p);
};

#endif //ALGORITHMS_WEIGHTEDUF_H
