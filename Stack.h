#ifndef ALGORITHMS_STACK_H
#define ALGORITHMS_STACK_H

#include <string>                   // std::string
#include <sstream>                  // std::stringstream
#include <iostream>                 // std::cout
#include <exception>                // std::exception
#include <boost/lexical_cast.hpp>   // boost::lexical_cast

/**
 *  The {@code Stack} class represents a last-in-first-out (LIFO) stack of generic items.
 *  It supports the usual push and pop operations, along with methods
 *  for peeking at the top item, testing if the stack is empty, and iterating through
 *  the items in LIFO order.
 *
 *  This implementation uses a singly linked list with a nested class Node.
 *
 *  @author Benjamin Chan
 *
 *  Adapted from Algorithms, 4th edition, {@authors Robert Sedgewick and Kevin Wayne}
 *  and their booksite https://algs4.cs.princeton.edu/
 *
 *  The Java program from which this C++ code was adapted from is found at
 *  https://algs4.cs.princeton.edu/13stacks/Stack.java.html.
 *
 *  @param <T> the generic type of an item in this stack
 */
template<typename T>
class Stack {
private:
    /**
     * @def the helper inner linked list class for a queue
     */
    class Node;

    /**
     * @def the NoSuchElementException if there are no items in a stack after
     * using the pop() and peek() methods
     */
    struct NoSuchElementException : public std::exception {
        const char *what() {
            return "Stack Underflow";
        }
    };

public:
    /// Initializes an empty stack
    Stack() : n(0), first(nullptr), last(nullptr) {};

    /// Prevents the invocation of the constructor with an lvalue stack
    Stack(const Stack<T> &other) = delete;

    /// Prevents the invocation of the constructor with an rvalue stack
    Stack(Stack<T> &&other) = delete;

    /// Destructor deletes all allocated items of a stack
    ~Stack() {
        while (first->next != nullptr) {
            Node *temp = first;
            first = first->next;
            delete temp;
        }
        delete first;
    };

    /**
     * Returns true if this stack is empty.
     *
     * @return true if this stack is empty; false otherwise
     */
    inline bool isEmpty() {
        return first == nullptr;
    };

    /**
     * Returns the number of items in this stack.
     *
     * @return the number of items in this stack
     */
    inline int size() {
        return n;
    }

    /**
     * Returns (but does not remove) the item most recently added to this stack.
     *
     * @return the item most recently added to this stack
     * @throws NoSuchElementException if this stack is empty
     */
    T peek();

    /**
      * Adds the item to this stack.
      *
      * @param  item the item to add
      */
    void push(T item);

    /**
     * Removes and returns the item most recently added to this stack.
     *
     * @return the item most recently added
     * @throws NoSuchElementException if this stack is empty
     */
    T pop();

    /**
     * Returns a string representation of this stack.
     *
     * @return the sequence of items in LIFO order, separated by spaces
     */
    [[nodiscard]] std::string toString() const;

    /// Nested iterator class
    class Iterator {
        friend class Stack<T>;

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

    inline Iterator begin() const {
        return Iterator(first);
    }

    inline Iterator end() const {
        return Iterator(last->next);
    }

private:

    class Node {
        friend class Stack;

        T item;
        Node *next;

        Node() : next(nullptr) {};

        explicit Node(const T &item, Node *ptr = nullptr) :
                item(item), next(ptr) {}
    };

    /// the number of nodes in a stack
    int n;

    /// the first node of a stack
    Node *first;

    /// the last node of a stack
    Node *last;

};


template<typename T>
T Stack<T>::peek() {
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
void Stack<T>::push(T item) {
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
T Stack<T>::pop() {
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
        return nullptr;
    }
}

template<typename T>
std::string Stack<T>::toString() const {
    std::stringstream ss;
    for (const auto &item: *this) {
        ss << boost::lexical_cast<std::string>(item) << " ";
    }
    ss << std::endl;
    return ss.str();
}

/// Overloads the "<<" operator for a stack
template<typename T>
std::ostream &operator<<(std::ostream &os, const Stack<T> &stack) {
    return os << stack.toString();
}

#endif //ALGORITHMS_STACK_H
