#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/problems/ALDS1_9_C"

#include <bits/stdc++.h>
using namespace std;

#include "../util/fastio.cpp"
#include "../datastructure/leftist_heap.cpp"

int main() {
    Scanner in;
    Printer out;
    LeftistHeap<long long> heap(1);
    while (true) {
        string operation;
        in.read(operation);
        if (operation == "end") break;
        if (operation == "insert") {
            long long x;
            in.read(x);
            heap.push(0, -x);
        } else {
            out.println(-heap.top(0));
            heap.pop(0);
        }
    }
}
