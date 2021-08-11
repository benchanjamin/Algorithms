//
// Created by Ben Chan on 7/24/21.
//

#ifndef ALGORITHMS_WEIGHTEDQUICKUNIONUF_H
#define ALGORITHMS_WEIGHTEDQUICKUNIONUF_H

#include <cstdint>
#include <string>
#include <vector>
#include <exception>

using namespace std;

/**
 *  The {@code WeightedQuickUnionUF} class represents a union–find data type
 *  (also known as the disjoint-sets data type).
 *  It supports the classic union and find operations,
 *  along with a count operation that returns the total number
 *  of sets.
 *
 *  The union–find data type models a collection of sets containing
 *  n elements, with each element in exactly one set.
 *  The elements are named 0 through n–1.
 *  Initially, there are n sets, with each element in its
 *  own set. The canonical element of a set
 *  (also known as the root, identifier,
 *  leader, or set representative)
 *  is one distinguished element in the set. Here is a summary of
 *  the operations:
 *
 *  -   find(p) returns the canonical element
 *      of the set containing p. The find operation
 *      returns the same value for two elements if and only if
 *      they are in the same set.
 *
 *  -   union(p, q) merges the set
 *      containing element p with the set containing
 *      element q. That is, if <em>p</em> and <em>q</em>
 *      are in different sets, replace these two sets
 *      with a new set that is the union of the two.
 *
 *  -   count</em>() returns the number of sets.
 *
 *  The canonical element of a set can change only when the set
 *  itself changes during a call to union;it cannot
 *  change during a call to either find or count.
 *
 *  This implementation uses weighted quick union by rank
 *  with path compression by halving.
 *  The constructor takes Θ(n) time, where
 *  n is the number of elements.
 *  The union and find operations take
 *  Θ(log(n)) time in the worst case.
 *  The count operation takes Θ(1) time.
 *
 *  @author Benjamin Chan
 *
 *  Adapted from Algorithms, 4th edition, {@authors Robert Sedgewick and Kevin Wayne}
 *  and their booksite https://algs4.cs.princeton.edu/
 *
 *  The Java program from which this C++ code was adapted from is found at
 *  https://algs4.cs.princeton.edu/15uf/WeightedQuickUnionUF.java.html.
 */

class WeightedQuickUnionUF {
    // parent[i] = parent of i
    vector<int> parent;
    // size[i] = number of elements in subtree rooted at i
    vector<int8_t> rank;
    // number of components
    int thisCount;
public:
    /**
     * Initializes an empty union-find data structure with
     * {@code n} elements {@code 0} through {@code n-1}.
     * Initially, each elements is in its own set.
     *
     * @param  n the number of elements
     * @throws invalid_argument if {@code n < 0}
     */
    explicit WeightedQuickUnionUF(int n);

    /**
     * Returns the canonical element of the set containing element {@code p}.
     *
     * @param  p an element
     * @return the canonical element of the set containing {@code p}
     * @throws invalid_argument unless {@code 0 <= p < n}
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
     * @throws invalid_argument unless
     *         both {@code 0 <= p < n} and {@code 0 <= q < n}
     */
    void weightedUnion(int p, int q);

private:
    /// validates that p is a valid index
    void validate(int p);
};

#endif //ALGORITHMS_WEIGHTEDQUICKUNIONUF_H
