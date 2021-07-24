#ifndef ALGORITHMS_QUEUE_H
#define ALGORITHMS_QUEUE_H

#include <iostream>
#include <exception>

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
 *  @author Ben Barani
 *
 *  @param <T> the generic type of an item in this queue
 */
template<typename T>
class Queue {
private:
    class Node;

    struct NoSuchElementException : public std::exception {
        const char *what() {
            return "Queue Underflow";
        }
    };

public:
    /// Initializes an empty queue
    Queue() : n(0), first(nullptr), last(nullptr) {};

    Queue(const Queue<T> &other) = delete;

    Queue(Queue<T> &&other) = delete;

    ~Queue() {
        while (first->next != nullptr) {
            Node *temp = first;
            first = first->next;
            delete temp;
        }
        delete first;
    };

    inline bool isEmpty() {
        return first == nullptr;
    };

    inline int size() {
        return n;
    }

    T peek();

    void enqueue(T item);

    T dequeue();

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
            Iterator temp = *this;
            nodePtr = nodePtr->next;
            return temp;
        }

        // Overload for the postincrement operator ++
        inline Iterator operator++(int) {
            Iterator temp = *this;
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
        friend class Queue;

        T item;
        Node *next;

        Node() : next(nullptr) {};

        explicit Node(const T &item, Node *ptr = nullptr) :
                item(item), next(ptr) {}
    };

    int n;

    Node *first;

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
    if (isEmpty()) first = last;
    else oldLast->next = last;
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


#endif //ALGORITHMS_QUEUE_H
