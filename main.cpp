#include <chrono>
#include <fstream>
#include <string>
#include <vector>
#include "Bag.h"
#include "Queue.h"
#include "Stack.h"
#include "WeightedUF.h"
#include "Selection.h"

using namespace std;
using namespace std::chrono;

int main() {
    // Test the bag
    cout << "Testing Bag: ";
    Bag<string> bag;

    auto t0 = high_resolution_clock::now();
    ifstream testFile("./Test Files/testCollections.txt");
    if (testFile.is_open()) {
        string input;
        while (testFile >> input) {
            bag.add(input);
        }
        cout << "size of bag = " << bag.size() << endl;
        testFile.close();
    }
    auto t1 = high_resolution_clock::now();

    cout << "Finished Testing Bag: " << duration_cast<milliseconds>(t1 - t0).count() << " msecs\n" << endl;

    // Tests the queue
    cout << "Testing Queue: ";
    Queue<string> queue;

    t0 = high_resolution_clock::now();
    testFile.clear();
    testFile.open("./Test Files/testCollections.txt");
    if (testFile.is_open()) {
        string input;
        while (testFile >> input) {
            if (!(input == "-"))
                queue.enqueue(input);
            else if (!queue.isEmpty())
                cout << queue.dequeue() + " ";
        }
        testFile.close();
    }

    cout << endl;
    t1 = high_resolution_clock::now();

    cout << "Finished Testing Queue: " << duration_cast<milliseconds>(t1 - t0).count() << " msecs\n" << endl;

    // Tests the stack
    cout << "Testing Stack: ";
    Stack<string> stack;

    t0 = high_resolution_clock::now();
    testFile.clear();
    testFile.open("./Test Files/testCollections.txt");
    if (testFile.is_open()) {
        string input;
        while (testFile >> input) {
            if (!(input == "-"))
                stack.push(input);
            else if (!stack.isEmpty())
                cout << stack.pop() + " ";
        }
        testFile.close();
    }

    cout << endl;
    t1 = high_resolution_clock::now();

    cout << "Finished Stack: " << duration_cast<milliseconds>(t1 - t0).count() << " msecs\n" << endl;

    // Test the union-find (weighted)
    t0 = high_resolution_clock::now();

    testFile.clear();
    testFile.open("./Test Files/tinyUF.txt");
    if (testFile.is_open()) {
        int size;
        testFile >> size;
        WeightedUF uf = WeightedUF(size);
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

    cout << "Finished WeightedUF: " << duration_cast<milliseconds>(t1 - t0).count() << " msecs\n" << endl;

    vector<string> a{"dasd", "dsd", "Add", "bing"};
    sort(a.begin(), a.end());
    Selection::sort<string>(a);
}

