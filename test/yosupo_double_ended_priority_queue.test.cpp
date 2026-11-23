#define PROBLEM "https://judge.yosupo.jp/problem/double_ended_priority_queue"

#include <bits/stdc++.h>
using namespace std;

#include "../util/fastio.cpp"
#include "../datastructure/heap/double_ended_priority_queue.cpp"

int main() {
    Scanner in;
    Printer out;
    int n, q;
    in.read(n, q);
    vector<int> values(n);
    in.read(values);
    DoubleEndedPriorityQueue<int> heap(std::move(values));
    while (q--) {
        int type;
        in.read(type);
        if (type == 0) {
            int x;
            in.read(x);
            heap.push(x);
        } else if (type == 1) {
            out.println(heap.pop_min());
        } else {
            out.println(heap.pop_max());
        }
    }
}
