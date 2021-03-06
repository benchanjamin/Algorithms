#ifndef ALGORITHMS_BAG_HPP
#define ALGORITHMS_BAG_HPP

#include <string>                   // std::string
#include <sstream>                  // std::stringstream
#include <boost/lexical_cast.hpp>   // boost::lexical_cast

/**
 *  The {@code Bag} class represents a bag (or multiset) of
 *  generic items. It supports insertion and iterating over the
 *  items in arbitrary order.
 *
 *  This implementation uses a singly linked list with a nested class Node.
 *
 *  @author Benjamin Chan
 *
 *  Adapted from Algorithms, 4th edition, {@authors Robert Sedgewick and Kevin Wayne}
 *  and their booksite https://algs4.cs.princeton.edu/
 *
 *  The Java program from which this C++ code was adapted from is found at
 *  https://algs4.cs.princeton.edu/13stacks/Bag.java.html
 *
 *  @param <T> the generic type of an item in this bag
 */
template<typename T>
class Bag {
    /**
     * @def the helper inner linked list class for a queue
     */
    class Node;

public:
    /// Initializes an empty bag
    Bag() : n(0), first(nullptr), last(nullptr) {};

    /// Prohibits construction from an lvalue bag
    Bag(const Bag<T> &other) = delete;

    /// Prohibits construction from an rvalue bag
    Bag(Bag<T> &&other) = delete;

    /// Destructor deletes all allocated items of a bag
    ~Bag() {
        while (first->next != nullptr) {
            Node *temp = first;
            first = first->next;
            delete temp;
        }
        delete first;
    };

    /**
     * Returns true if this bag is empty.
     *
     * @return {@code true} if this bag is empty;
     *         {@code false} otherwise
     */
    inline bool isEmpty() {
        return first == nullptr;
    };

    /**
     * Returns the number of items in this bag.
     *
     * @return the number of items in this bag
     */
    inline int size() {
        return n;
    }

    /**
    * Adds the item to this bag.
    *
    * @param the item to add to this bag
    */
    void add(T item);

    /**
     * Returns a string representation of this bag.
     *
     * @return the sequence of items in random order, separated by spaces
     */
    [[nodiscard]] std::string toString() const;

    /// Nested iterator class
    class Iterator {
        friend class Bag<T>;

    private:
        Node *nodePtr;

        // The constructor is private, so only our friends
        // can create instances of iterators.
        explicit Iterator(Node *newPtr) : nodePtr(newPtr) {};

    public:
        Iterator() : nodePtr(nullptr) {}

        // Overload for the comparison operator !=
        inline bool operator!=(const Iterator &itr) const {
            return nodePtr != itr.nodePtr;
        }

        // Overload for the dereference operator *
        inline T &operator*() const {
            return nodePtr->item;
        }

        // Overload for the preincrement operator ++
        inline Iterator &operator++() {
            this->nodePtr = this->nodePtr->next;
            return *this;
        }

        // Overload for the postincrement operator ++
        inline Iterator operator++(int) {
            Iterator temp = *this;
            operator++();
            return temp;
        }
    }; // End of inner class iterator

    /**
     * Returns an iterator that points to the first node of the bag.
     *
     * @return an iterator that points to the first node of the bag
     */
    inline Iterator begin() const {
        return Iterator(first);
    }

    /**
     * Returns an iterator that points to the past-the-end node after the last node of the bag.
     *
     * @return an iterator that points to the past-the-end node after the last node of the bag
     */
    inline Iterator end() const {
        return Iterator(last->next);
    }

private:
    class Node {
        friend class Bag;


        T item;
        Node *next;

        Node() : next(nullptr) {};

        explicit Node(const T &item, Node *ptr = nullptr) :
                item(item), next(ptr) {}
    };

    /// the number of nodes in a bag
    int n;

    /// the first node in a bag
    Node *first;

    /// the last node in a bag
    Node *last;
};

template<typename T>
void Bag<T>::add(T item) {
    if (isEmpty()) {
        last = new Node();
        first = last;
        first->item = item;
        n++;
        return;
    }
    Node *oldFirst = first;
    first = new Node(item, oldFirst);
    n++;
}

template<typename T>
std::string Bag<T>::toString() const {
    std::stringstream ss;
    for (const auto &item: *this) {
        ss << boost::lexical_cast<std::string>(item) << " ";
    }
    ss << std::endl;
    return ss.str();
}

/// Overloads the "<<" operator for a bag
template<typename T>
std::ostream &operator<<(std::ostream &os, const Bag<T> &bag) {
    return os << bag.toString();
}

#endif //ALGORITHMS_BAG_HPP
