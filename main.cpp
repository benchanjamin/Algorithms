#include <chrono>
#include <fstream>
#include <cassert>
#include "Bag.hpp"
#include "Queue.hpp"
#include "Stack.hpp"
#include "WeightedQuickUnionUF.hpp"
#include "SelectionSort.hpp"
#include "InsertionSort.hpp"
#include "ShellSort.hpp"
#include "MergeSort.hpp"
#include "MergeSortBU.hpp"
#include "QuickSort.hpp"
#include "QuickSort3way.hpp"
#include "BinarySearch.hpp"
#include "QuickSelect.hpp"
#include "MaxPQ.hpp"


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

    // Tests the merge sort algorithm on strings
    testFile.clear();
    testFile.open("./Test Files/random_strings.txt");
    vector<string> stringVector7;
    if (testFile.is_open()) {
        string str;
        while (testFile >> str) {
            stringVector7.emplace_back(str);
        }
        testFile.close();
        t0 = high_resolution_clock::now();
        MergeSort{stringVector7};
    }
    t1 = high_resolution_clock::now();
    for (const auto &x: stringVector7) {
        cout << x << " ";
    }
    cout << endl;

    cout << "Finished Merge Sort: " << duration_cast<milliseconds>(t1 - t0).count() << " msecs\n" << endl;

    // Tests the merge sort algorithm on ints
    testFile.clear();
    testFile.open("./Test Files/random_numbers.txt");
    vector<int> intVector7;
    if (testFile.is_open()) {
        int number;
        while (testFile >> number) {
            intVector7.emplace_back(number);
        }
        testFile.close();
        t0 = high_resolution_clock::now();
        MergeSort{intVector7, true};
    }
    t1 = high_resolution_clock::now();
    for (const auto &x: intVector7) {
        cout << x << " ";
    }
    cout << endl;

    cout << "Finished Merge Sort: " << duration_cast<milliseconds>(t1 - t0).count() << " msecs\n" << endl;

    // Tests the merge reverse sort algorithm on strings
    testFile.clear();
    testFile.open("./Test Files/random_strings.txt");
    vector<string> stringVector8;
    if (testFile.is_open()) {
        string str;
        while (testFile >> str) {
            stringVector8.emplace_back(str);
        }
        testFile.close();
        t0 = high_resolution_clock::now();
        MergeSort{stringVector8, true};
    }
    t1 = high_resolution_clock::now();
    for (const auto &x: stringVector8) {
        cout << x << " ";
    }
    cout << endl;

    cout << "Finished Merge Reverse Sort: " << duration_cast<milliseconds>(t1 - t0).count() << " msecs\n" << endl;

    // Tests the merge reverse sort algorithm on ints
    testFile.clear();
    testFile.open("./Test Files/random_numbers.txt");
    vector<int> intVector8;
    if (testFile.is_open()) {
        int number;
        while (testFile >> number) {
            intVector8.emplace_back(number);
        }
        testFile.close();
        t0 = high_resolution_clock::now();
        MergeSort{intVector8, true};
    }
    t1 = high_resolution_clock::now();
    for (const auto &x: intVector8) {
        cout << x << " ";
    }
    cout << endl;

    cout << "Finished Merge Reverse Sort: " << duration_cast<milliseconds>(t1 - t0).count() << " msecs\n" << endl;

    // Tests the merge sort bottom-up algorithm on strings
    testFile.clear();
    testFile.open("./Test Files/random_strings.txt");
    vector<string> stringVector9;
    if (testFile.is_open()) {
        string str;
        while (testFile >> str) {
            stringVector9.emplace_back(str);
        }
        testFile.close();
        t0 = high_resolution_clock::now();
        MergeSortBU{stringVector9};
    }
    t1 = high_resolution_clock::now();
    for (const auto &x: stringVector9) {
        cout << x << " ";
    }
    cout << endl;

    cout << "Finished Merge Sort Bottom-Up: " << duration_cast<milliseconds>(t1 - t0).count() << " msecs\n" << endl;

    // Tests the merge sort bottom-up algorithm on ints
    testFile.clear();
    testFile.open("./Test Files/random_numbers.txt");
    vector<int> intVector9;
    if (testFile.is_open()) {
        int number;
        while (testFile >> number) {
            intVector9.emplace_back(number);
        }
        testFile.close();
        t0 = high_resolution_clock::now();
        MergeSortBU{intVector9};
    }
    t1 = high_resolution_clock::now();
    for (const auto &x: intVector9) {
        cout << x << " ";
    }
    cout << endl;

    cout << "Finished Merge Sort Bottom-Up: " << duration_cast<milliseconds>(t1 - t0).count() << " msecs\n" << endl;

    // Tests the merge reverse sort bottom-up algorithm on strings
    testFile.clear();
    testFile.open("./Test Files/random_strings.txt");
    vector<string> stringVector10;
    if (testFile.is_open()) {
        string str;
        while (testFile >> str) {
            stringVector10.emplace_back(str);
        }
        testFile.close();
        t0 = high_resolution_clock::now();
        MergeSortBU{stringVector10, true};
    }
    t1 = high_resolution_clock::now();
    for (const auto &x: stringVector10) {
        cout << x << " ";
    }
    cout << endl;

    cout << "Finished Merge Sort Bottom-Up: " << duration_cast<milliseconds>(t1 - t0).count() << " msecs\n" << endl;

    // Tests the merge reverse sort bottom-up algorithm on ints
    testFile.clear();
    testFile.open("./Test Files/random_numbers.txt");
    vector<int> intVector10;
    if (testFile.is_open()) {
        int number;
        while (testFile >> number) {
            intVector10.emplace_back(number);
        }
        testFile.close();
        t0 = high_resolution_clock::now();
        MergeSortBU{intVector10, true};
    }
    t1 = high_resolution_clock::now();
    for (const auto &x: intVector10) {
        cout << x << " ";
    }
    cout << endl;

    cout << "Finished Merge Sort Bottom-Up: " << duration_cast<milliseconds>(t1 - t0).count() << " msecs\n" << endl;

    // Tests the quick sort algorithm on strings
    testFile.clear();
    testFile.open("./Test Files/random_strings.txt");
    vector<string> stringVector11;
    if (testFile.is_open()) {
        string str;
        while (testFile >> str) {
            stringVector11.emplace_back(str);
        }
        testFile.close();
        t0 = high_resolution_clock::now();
        QuickSort{stringVector11};
    }
    t1 = high_resolution_clock::now();
    for (const auto &x: stringVector11) {
        cout << x << " ";
    }
    cout << endl;

    cout << "Finished Quick Sort: " << duration_cast<milliseconds>(t1 - t0).count() << " msecs\n" << endl;

    // Tests the quick sort algorithm on ints
    testFile.clear();
    testFile.open("./Test Files/random_numbers.txt");
    vector<int> intVector11;
    if (testFile.is_open()) {
        int number;
        while (testFile >> number) {
            intVector11.emplace_back(number);
        }
        testFile.close();
        t0 = high_resolution_clock::now();
        QuickSort{intVector11};
    }
    t1 = high_resolution_clock::now();
    for (const auto &x: intVector11) {
        cout << x << " ";
    }
    cout << endl;

    cout << "Finished Quick Sort: " << duration_cast<milliseconds>(t1 - t0).count() << " msecs\n" << endl;

    // Tests the quick reverse sort algorithm on strings
    testFile.clear();
    testFile.open("./Test Files/random_strings.txt");
    vector<string> stringVector12;
    if (testFile.is_open()) {
        string str;
        while (testFile >> str) {
            stringVector12.emplace_back(str);
        }
        testFile.close();
        t0 = high_resolution_clock::now();
        QuickSort{stringVector12, true};
    }
    t1 = high_resolution_clock::now();
    for (const auto &x: stringVector12) {
        cout << x << " ";
    }
    cout << endl;

    cout << "Finished Quick Reverse Sort: " << duration_cast<milliseconds>(t1 - t0).count() << " msecs\n" << endl;

    // Tests the quick reverse sort algorithm on ints
    testFile.clear();
    testFile.open("./Test Files/random_numbers.txt");
    vector<int> intVector12;
    if (testFile.is_open()) {
        int number;
        while (testFile >> number) {
            intVector12.emplace_back(number);
        }
        testFile.close();
        t0 = high_resolution_clock::now();
        QuickSort{intVector12, true};
    }
    t1 = high_resolution_clock::now();
    for (const auto &x: intVector12) {
        cout << x << " ";
    }
    cout << endl;

    cout << "Finished Quick Reverse Sort: " << duration_cast<milliseconds>(t1 - t0).count() << " msecs\n" << endl;

    // Tests the quick 3-way sort algorithm on strings
    testFile.clear();
    testFile.open("./Test Files/random_strings.txt");
    vector<string> stringVector13;
    if (testFile.is_open()) {
        string str;
        while (testFile >> str) {
            stringVector13.emplace_back(str);
        }
        testFile.close();
        t0 = high_resolution_clock::now();
        QuickSort3way{stringVector13};
    }
    t1 = high_resolution_clock::now();
    for (const auto &x: stringVector13) {
        cout << x << " ";
    }
    cout << endl;

    cout << "Finished Quick 3-way Sort: " << duration_cast<milliseconds>(t1 - t0).count() << " msecs\n" << endl;

    // Tests the quick 3-way sort algorithm on ints
    testFile.clear();
    testFile.open("./Test Files/random_numbers.txt");
    vector<int> intVector13;
    if (testFile.is_open()) {
        int number;
        while (testFile >> number) {
            intVector13.emplace_back(number);
        }
        testFile.close();
        t0 = high_resolution_clock::now();
        QuickSort3way{intVector13};
    }
    t1 = high_resolution_clock::now();
    for (const auto &x: intVector13) {
        cout << x << " ";
    }
    cout << endl;

    cout << "Finished Quick 3-way Sort: " << duration_cast<milliseconds>(t1 - t0).count() << " msecs\n" << endl;

    // Tests the quick 3-way reverse sort algorithm on strings
    testFile.clear();
    testFile.open("./Test Files/random_strings.txt");
    vector<string> stringVector14;
    if (testFile.is_open()) {
        string str;
        while (testFile >> str) {
            stringVector14.emplace_back(str);
        }
        testFile.close();
        t0 = high_resolution_clock::now();
        QuickSort3way{stringVector14, true};
    }
    t1 = high_resolution_clock::now();
    for (const auto &x: stringVector14) {
        cout << x << " ";
    }
    cout << endl;

    cout << "Finished Quick 3-way Reverse Sort: " << duration_cast<milliseconds>(t1 - t0).count() << " msecs\n" << endl;

    // Tests the quick 3-way reverse sort algorithm on ints
    testFile.clear();
    testFile.open("./Test Files/random_numbers.txt");
    vector<int> intVector14;
    if (testFile.is_open()) {
        int number;
        while (testFile >> number) {
            intVector14.emplace_back(number);
        }
        testFile.close();
        t0 = high_resolution_clock::now();
        QuickSort3way{intVector14, true};
    }
    t1 = high_resolution_clock::now();
    for (const auto &x: intVector14) {
        cout << x << " ";
    }
    cout << endl;

    cout << "Finished Quick 3-way Reverse Sort: " << duration_cast<milliseconds>(t1 - t0).count() << " msecs\n" << endl;

    // Tests binary search algorithm for int vector
    int result1 = BinarySearch::indexOf(intVector13, 5, false);
    // finding 5 should return the index of 4
    assert(result1 == 4);

    // Tests binary search algorithm for reverse int vector
    int result2 = BinarySearch::indexOf(intVector14, 8, true);
    // finding 8 should return the index of 2
    assert(result2 == 2);

    // Tests binary search algorithm for basic int array of length 5
    int testVector[5] = {1, 2, 3, 4, 5};
    int result3 = BinarySearch::indexOf(testVector, 5, 3, false);
    // finding 3 should return the index of 2
    assert(result3 == 2);

    // Tests binary search algorithm for basic int array of length 5 that is in reverse order
    SelectionSort{testVector, true};
    int result4 = BinarySearch::indexOf(testVector, 5, 3, false);
    // finding 3 should return the index of 2
    assert(result4 == 2);

    // Tests quick select algorithm to determine the element in the basic array of rank 5
    // (aka the 6th highest element in the container)
    int testVector2[15] = {50, 21, 28, 65, 39, 59, 56, 22, 95, 12, 90, 53, 32, 77, 33};
    QuickSelect quickselect = QuickSelect(testVector2);
    int result5 = quickselect.rankOf(5);
    // finding a rank of 5 should return 33 of testVector
    assert(result5 == 33);

    // Tests quick select algorithm to determine the element in the basic array of rank 5 if it
    // were sorted in reverse order (aka the 6th lowest element in the container)
    QuickSelect quickselect2 = QuickSelect(testVector2);
    int result6 = quickselect2.rankOf(5);
    // finding a rank of 5 should return 33 of testVector
    assert(result6 == 33);

    // Tests the max priority queue data structure on ints
    MaxPQ<int> maxPQ = MaxPQ<int>();
    testFile.clear();
    testFile.open("./Test Files/random_numbers.txt");
    if (testFile.is_open()) {
        int number;
        t0 = high_resolution_clock::now();
        while (testFile >> number) {
            maxPQ.insert(number);
        }
    }
    t1 = high_resolution_clock::now();
    testFile.close();
    cout << maxPQ;

    cout << "Finished Testing Max Priority Queue: " << duration_cast<milliseconds>(t1 - t0).count() << " msecs\n"
         << endl;

}

