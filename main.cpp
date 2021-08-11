#include <chrono>
#include <fstream>
#include "Bag.h"
#include "Queue.h"
#include "Stack.h"
#include "WeightedQuickUnionUF.h"
#include "SelectionSort.h"
#include "InsertionSort.h"
#include "ShellSort.h"


using namespace std;
using namespace std::chrono;

int main() {
    // Tests the bag
    cout << "Testing Bag: ";
    Bag<string> bag;

    time_point<high_resolution_clock> t0;

    ifstream testFile("./Test Files/to_be.txt");
    if (testFile.is_open()) {
        t0 = high_resolution_clock::now();
        string input;
        while (testFile >> input) {
            bag.add(input);
        }
        testFile.close();
        cout << "size of bag = " << bag.size() << endl;
        cout << "Items in the bag: " << bag;
    }
    auto t1 = high_resolution_clock::now();

    cout << "Finished Testing Bag: " << duration_cast<milliseconds>(t1 - t0).count() << " msecs\n" << endl;

    // Tests the queue
    cout << "Testing Queue: ";
    Queue<string> queue;

    testFile.clear();
    testFile.open("./Test Files/to_be.txt");
    if (testFile.is_open()) {
        t0 = high_resolution_clock::now();
        string input;
        while (testFile >> input) {
            if (!(input == "-"))
                queue.enqueue(input);
            else if (!queue.isEmpty())
                cout << queue.dequeue() + " ";
        }
        testFile.close();
        cout << endl;
    }

    cout << "Remaining Items in the Queue: " << queue;

    t1 = high_resolution_clock::now();

    cout << "Finished Testing Queue: " << duration_cast<milliseconds>(t1 - t0).count() << " msecs\n" << endl;

    // Tests the stack
    cout << "Testing Stack: ";
    Stack<string> stack;

    testFile.clear();
    testFile.open("./Test Files/to_be.txt");
    if (testFile.is_open()) {
        t0 = high_resolution_clock::now();
        string input;
        while (testFile >> input) {
            if (!(input == "-"))
                stack.push(input);
            else if (!stack.isEmpty())
                cout << stack.pop() + " ";
        }
        cout << endl;
        testFile.close();
    }

    cout << "Remaining Items in the Stack: " << stack;

    t1 = high_resolution_clock::now();

    cout << "Finished Stack: " << duration_cast<milliseconds>(t1 - t0).count() << " msecs\n" << endl;

    // Tests the union-find (weighted)
    testFile.clear();
    testFile.open("./Test Files/tiny_UF.txt");
    if (testFile.is_open()) {
        t0 = high_resolution_clock::now();
        int size;
        testFile >> size;
        WeightedQuickUnionUF uf = WeightedQuickUnionUF(size);
        int p;
        int q;
        while (testFile >> p && testFile >> q) {
            if (uf.find(p) == uf.find(q)) {
                continue;
            }
            uf.weightedUnion(p, q);
            cout << to_string(p) << " " << to_string(q) << endl;
        }
        cout << to_string(uf.count()) + " components" << endl;
        testFile.close();
    }
    t1 = high_resolution_clock::now();

    cout << "Finished WeightedQuickUnionUF: " << duration_cast<milliseconds>(t1 - t0).count() << " msecs\n" << endl;

    // Tests the selection sort algorithm on strings
    testFile.clear();
    testFile.open("./Test Files/random_strings.txt");
    vector<string> stringVector;
    if (testFile.is_open()) {
        string str;
        while (testFile >> str) {
            stringVector.emplace_back(str);
        }
        testFile.close();
        t0 = high_resolution_clock::now();
        SelectionSort{stringVector};
    }
    t1 = high_resolution_clock::now();
    for (const auto &x: stringVector) {
        cout << x << " ";
    }
    cout << endl;

    cout << "Finished Selection Sort: " << duration_cast<milliseconds>(t1 - t0).count() << " msecs\n" << endl;

    // Tests the selection sort algorithm on ints
    testFile.clear();
    testFile.open("./Test Files/random_numbers.txt");
    vector<int> intVector;
    if (testFile.is_open()) {
        int number;
        while (testFile >> number) {
            intVector.emplace_back(number);
        }
        testFile.close();
        t0 = high_resolution_clock::now();
        SelectionSort{intVector};
    }
    t1 = high_resolution_clock::now();
    for (const auto &x: intVector) {
        cout << x << " ";
    }
    cout << endl;

    cout << "Finished Selection Sort: " << duration_cast<milliseconds>(t1 - t0).count() << " msecs\n" << endl;

    // Tests the selection reverse sort algorithm on strings
    testFile.clear();
    testFile.open("./Test Files/random_strings.txt");
    vector<string> stringVector2;
    if (testFile.is_open()) {
        string str;
        while (testFile >> str) {
            stringVector2.emplace_back(str);
        }
        testFile.close();
        t0 = high_resolution_clock::now();
        SelectionSort{stringVector2, true};
    }
    t1 = high_resolution_clock::now();
    for (const auto &x: stringVector2) {
        cout << x << " ";
    }
    cout << endl;

    cout << "Finished Selection Reverse Sort: " << duration_cast<milliseconds>(t1 - t0).count() << " msecs\n" << endl;

    // Tests the selection reverse sort algorithm on ints
    testFile.clear();
    testFile.open("./Test Files/random_numbers.txt");
    vector<int> intVector2;
    if (testFile.is_open()) {
        int number;
        while (testFile >> number) {
            intVector2.emplace_back(number);
        }
        testFile.close();
        t0 = high_resolution_clock::now();
        SelectionSort{intVector2, true};
    }
    t1 = high_resolution_clock::now();
    for (const auto &x: intVector2) {
        cout << x << " ";
    }
    cout << endl;

    cout << "Finished Selection Reverse Sort: " << duration_cast<milliseconds>(t1 - t0).count() << " msecs\n" << endl;

    // Tests the insertion sort algorithm on strings
    testFile.clear();
    testFile.open("./Test Files/random_strings.txt");
    vector<string> stringVector3;
    if (testFile.is_open()) {
        string str;
        while (testFile >> str) {
            stringVector3.emplace_back(str);
        }
        testFile.close();
        t0 = high_resolution_clock::now();
        InsertionSort{stringVector3};
    }
    t1 = high_resolution_clock::now();
    for (const auto &x: stringVector3) {
        cout << x << " ";
    }
    cout << endl;

    cout << "Finished Insertion Sort: " << duration_cast<milliseconds>(t1 - t0).count() << " msecs\n" << endl;

    // Tests the insertion sort algorithm on ints
    testFile.clear();
    testFile.open("./Test Files/random_numbers.txt");
    vector<int> intVector3;
    if (testFile.is_open()) {
        int number;
        while (testFile >> number) {
            intVector3.emplace_back(number);
        }
        testFile.close();
        t0 = high_resolution_clock::now();
        SelectionSort{intVector3};
    }
    t1 = high_resolution_clock::now();
    for (const auto &x: intVector3) {
        cout << x << " ";
    }
    cout << endl;

    cout << "Finished Insertion Sort: " << duration_cast<milliseconds>(t1 - t0).count() << " msecs\n" << endl;

    // Tests the insertion reverse sort algorithm on strings
    testFile.clear();
    testFile.open("./Test Files/random_strings.txt");
    vector<string> stringVector4;
    if (testFile.is_open()) {
        string str;
        while (testFile >> str) {
            stringVector4.emplace_back(str);
        }
        testFile.close();
        t0 = high_resolution_clock::now();
        InsertionSort{stringVector4, true};
    }
    t1 = high_resolution_clock::now();
    for (const auto &x: stringVector4) {
        cout << x << " ";
    }
    cout << endl;

    cout << "Finished Insertion Reverse Sort: " << duration_cast<milliseconds>(t1 - t0).count() << " msecs\n" << endl;

    // Tests the insertion reverse sort algorithm on ints
    testFile.clear();
    testFile.open("./Test Files/random_numbers.txt");
    vector<int> intVector4;
    if (testFile.is_open()) {
        int number;
        while (testFile >> number) {
            intVector4.emplace_back(number);
        }
        testFile.close();
        t0 = high_resolution_clock::now();
        SelectionSort{intVector4, true};
    }
    t1 = high_resolution_clock::now();
    for (const auto &x: intVector4) {
        cout << x << " ";
    }
    cout << endl;

    cout << "Finished Insertion Reverse Sort: " << duration_cast<milliseconds>(t1 - t0).count() << " msecs\n" << endl;

    // Tests the shell sort algorithm on strings
    testFile.clear();
    testFile.open("./Test Files/random_strings.txt");
    vector<string> stringVector5;
    if (testFile.is_open()) {
        string str;
        while (testFile >> str) {
            stringVector5.emplace_back(str);
        }
        testFile.close();
        t0 = high_resolution_clock::now();
        ShellSort{stringVector5};
    }
    t1 = high_resolution_clock::now();
    for (const auto &x: stringVector5) {
        cout << x << " ";
    }
    cout << endl;

    cout << "Finished Shell Sort: " << duration_cast<milliseconds>(t1 - t0).count() << " msecs\n" << endl;

    // Tests the shell sort algorithm on ints
    testFile.clear();
    testFile.open("./Test Files/random_numbers.txt");
    vector<int> intVector5;
    if (testFile.is_open()) {
        int number;
        while (testFile >> number) {
            intVector5.emplace_back(number);
        }
        testFile.close();
        t0 = high_resolution_clock::now();
        ShellSort{intVector5};
    }
    t1 = high_resolution_clock::now();
    for (const auto &x: intVector5) {
        cout << x << " ";
    }
    cout << endl;

    cout << "Finished Shell Sort: " << duration_cast<milliseconds>(t1 - t0).count() << " msecs\n" << endl;

    // Tests the shell reverse sort algorithm on strings
    testFile.clear();
    testFile.open("./Test Files/random_strings.txt");
    vector<string> stringVector6;
    if (testFile.is_open()) {
        string str;
        while (testFile >> str) {
            stringVector6.emplace_back(str);
        }
        testFile.close();
        t0 = high_resolution_clock::now();
        ShellSort{stringVector6, true};
    }
    t1 = high_resolution_clock::now();
    for (const auto &x: stringVector6) {
        cout << x << " ";
    }
    cout << endl;

    cout << "Finished Shell Reverse Sort: " << duration_cast<milliseconds>(t1 - t0).count() << " msecs\n" << endl;

    // Tests the shell reverse sort algorithm on ints
    testFile.clear();
    testFile.open("./Test Files/random_numbers.txt");
    vector<int> intVector6;
    if (testFile.is_open()) {
        int number;
        while (testFile >> number) {
            intVector6.emplace_back(number);
        }
        testFile.close();
        t0 = high_resolution_clock::now();
        ShellSort{intVector6, true};
    }
    t1 = high_resolution_clock::now();
    for (const auto &x: intVector6) {
        cout << x << " ";
    }
    cout << endl;

    cout << "Finished Shell Reverse Sort: " << duration_cast<milliseconds>(t1 - t0).count() << " msecs\n" << endl;
}

