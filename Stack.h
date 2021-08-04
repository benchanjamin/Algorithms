#ifndef ALGORITHMS_STACK_H
#define ALGORITHMS_STACK_H

#include <iostream>
#include <exception>

template<typename T>
class Stack {
private:
    class Node;

    struct NoSuchElementException : public std::exception {
        const char *what() {
            return "Stack Underflow";
        }
    };

public:
    Stack() : n(0), first(nullptr), last(nullptr) {};

    Stack(const Stack<T> &other) = delete;

    Stack(Stack<T> &&other) = delete;

    ~Stack() {
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

    void push(T item);

    T pop();

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
        friend class Stack;

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
    if (isEmpty())
        first = last;
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


#endif //ALGORITHMS_STACK_H
