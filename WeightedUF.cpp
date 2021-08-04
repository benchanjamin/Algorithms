//
// Created by Ben Chan on 7/31/21.
//
#include "WeightedUF.h"

int WeightedUF::find(int p) {
    validate(p);
    while (p != parent[p]) {
        parent[p] = parent[parent[p]];
        p = parent[p];
    }
    return p;
}


void WeightedUF::validate(int p) {
    int n = (int) parent.size();
    if (p < 0 || p >= n)
        throw invalid_argument("index " + to_string(p) + " is not between 0 and " + to_string(n - 1));
}

void WeightedUF::weightedUnion(int p, int q) {
    int rootP = find(p);
    int rootQ = find(q);
    if (rootP == rootQ) return;

    // make root of smaller rank point to root of larger rank
    if (rank[rootP] < rank[rootQ]) parent[rootP] = rootQ;
    else if (rank[rootP] > rank[rootQ]) parent[rootQ] = rootP;
    else {
        parent[rootQ] = rootP;
        rank[rootP]++;
    }
    thisCount--;
}

WeightedUF::WeightedUF(int n) : thisCount(n) {
    parent.resize(n);
    rank.resize(n);
    for (int i = 0; i < n; i++) {
        parent[i] = i;
        rank[i] = 0;
    }
}
