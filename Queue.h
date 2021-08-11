#ifndef ALGORITHMS_QUEUE_H
#define ALGORITHMS_QUEUE_H

#include <string>                   // std::string
#include <sstream>                  // std::stringstream
#include <iostream>                 // std::cout
#include <exception>                // std::exception
#include <boost/lexical_cast.hpp>   // boost::lexical_cast

/**
 *  The {@code Queue} class represents a first-in-first-out (FIFO)
 *  queue of generic items.
 *  It supports the usual enqueue and dequeue
 *  operations, along with methods for peeking at the first item,
 *  testing if the queue is empty, and iterating through
 *  the items in FIFO order.
 *
 *  This implementation uses a singly linked list with a nested class Node.
 *
 *  @author Benjamin Chan
 *
 *  Adapted from Algorithms, 4th edition, {@authors Robert Sedgewick and Kevin Wayne}
 *  and their booksite https://algs4.cs.princeton.edu/
 *
 *  The Java program from which this C++ code was adapted from is found at
 *  https://algs4.cs.princeton.edu/41graph/Queue.java.html.
 *
 *  @param <T> the generic type of an item in this queue
 */
template<typename T>
class Queue {
private:
    /**
     * @def the helper inner linked list class for a queue
     */
    class Node;

    /**
     * @def the NoSuchElementException if there are no items in a queue after
     * using the dequeue() and peek() methods
     */
    struct NoSuchElementException : public std::exception {
        const char *what() {
            return "Queue Underflow";
        }
    };

public:
    /// Initializes an empty queue
    Queue() : n(0), first(nullptr), last(nullptr) {};

    /// Prevents the invocation of the constructor with an lvalue queue
    Queue(const Queue<T> &other) = delete;

    /// Prevents the invocation of the constructor with an rvalue queue
    Queue(Queue<T> &&other) = delete;

    /// Destructor deletes all allocated items of a queue
    ~Queue() {
        while (first->next != nullptr) {
            Node *temp = first;
            first = first->next;
            delete temp;
        }
        delete first;
    };

    /**
     * Returns true if this queue is empty.
     *
     * @return {@code true} if this queue is empty; {@code false} otherwise
     */
    inline bool isEmpty() {
        return first == nullptr;
    };

    /**
     * Returns the number of items in this queue.
     *
     * @return the number of items in this queue
     */
    inline int size() {
        return n;
    }

    /**
     * Returns the item least recently added to this queue.
     *
     * @return the item least recently added to this queue
     * @throws NoSuchElementException if this queue is empty
     */
    T peek();

    /**
     * Adds the item to this queue.
     *
     * @param  item the item to add
     */
    void enqueue(T item);

    /**
     * Removes and returns the item on this queue that was least recently added.
     *
     * @return the item on this queue that was least recently added
     * @throws NoSuchElementException if this queue is empty
     */
    T dequeue();

    /**
     * Returns a string representation of this queue.
     *
     * @return the sequence of items in FIFO order, separated by spaces
     */
    [[nodiscard]] std::string toString() const;

    /// Nested iterator class
    class Iterator {
        friend class Queue<T>;

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
            Iterator temp(*this);
            operator++();
            return temp;
        }
    }; // End of inner class iterator

    /**
     * Returns an iterator that points to the first node of the queue.
     *
     * @return an iterator that points to the first node of the queue
     */
    inline Iterator begin() const {
        return Iterator(first);
    }

    /**
     * Returns an iterator that points to the past-the-end node after the last node of the queue.
     *
     * @return an iterator that points to the past-the-end node after the last node of the queue
     */
    inline Iterator end() const {
        return Iterator(last->next);
    }

private:
    // helper linked list class
    class Node {
        friend class Queue;

        T item;
        Node *next;

        Node() : next(nullptr) {};

        explicit Node(const T &item, Node *ptr = nullptr) :
                item(item), next(ptr) {}
    };

    /// the number of nodes in a queue
    int n;

    /// the first node in a queue
    Node *first;

    /// the last node in a queue
    Node *last;
};


template<typename T>
T Queue<T>::peek() {
    try {
        if (isEmpty()) throw NoSuchElementException();
        return this->first.item;
    }
    catch (NoSuchElementException &e) {
        std::cout << "NoSuchElementException encountered: ";
        std::cout << e.what() << std::endl;
    }
}

template<typename T>
void Queue<T>::enqueue(T item) {
    Node *oldLast = last;
    last = new Node(item);
    if (isEmpty()) {
        first = last;
    } else
        oldLast->next = last;
    n++;
}

template<typename T>
T Queue<T>::dequeue() {
    try {
        if (isEmpty()) throw NoSuchElementException();
        Node *oldFirst = first;
        T item = first->item;
        first = first->next;
        delete oldFirst;
        n--;
        return item;
    }
    catch (NoSuchElementException &e) {
        std::cout << "NoSuchElementException encountered: ";
        std::cout << e.what() << std::endl;
        return 0;
    }
}

template<typename T>
std::string Queue<T>::toString() const {
    std::stringstream ss;
    for (const auto &item: *this) {
        ss << boost::lexical_cast<std::string>(item) << " ";
    }
    ss << std::endl;
    return ss.str();
}

/// Overloads the "<<" operator for a queue
template<typename T>
std::ostream &operator<<(std::ostream &os, const Queue<T> &queue) {
    return os << queue.toString();
}

#endif //ALGORITHMS_QUEUE_H
