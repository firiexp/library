#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/problems/ALDS1_9_C"

#include <algorithm>
#include <string>
#include <vector>
using namespace std;

using ll = long long;

#include "../util/fastio.cpp"
#include "../datastructure/binaryheap.cpp"

int main() {
    Scanner sc;
    Printer pr;

    binary_heap<int> pq;
    string op;
    while (true) {
        sc.read(op);
        if (op == "end") break;
        if (op == "insert") {
            int x;
            sc.read(x);
            pq.emplace(x);
        } else {
            pr.writeln(pq.top());
            pq.pop();
        }
    }
    return 0;
}
