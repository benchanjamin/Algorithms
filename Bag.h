#ifndef ALGORITHMS_BAG_H
#define ALGORITHMS_BAG_H

/**
 *  The {@code Bag} class represents a bag (or multiset) of
 *  generic items. It supports insertion and iterating over the
 *  items in arbitrary order.
 *
 *  This implementation uses a singly linked list with a nested class Node.
 *
 *  @author Benjamin Chan
 *  @author Ben Barani
 *
 *  @param <T> the generic type of an item in this bag
 */
template<typename T>
class Bag {
    class Node;

public:
    /// Initializes an empty bag
    Bag() : n(0), first(nullptr), last(nullptr) {};

    /// Prohibits construction from an lvalue Bag
    Bag(const Bag<T> &other) = delete;

    /// Prohibits construction from an rvalue Bag
    Bag(Bag<T> &&other) = delete;

    /// Destructor deletes all allocated items of Bag
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
        friend class Bag;

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

#endif //ALGORITHMS_BAG_H
