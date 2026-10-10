#define PROBLEM "https://judge.yosupo.jp/problem/persistent_queue"

#include <bits/stdc++.h>
using namespace std;

#include "../util/fastio.cpp"
#include "../datastructure/persistent_queue.cpp"

int main() {
    Scanner in;
    Printer out;
    int q;
    in.read(q);
    PersistentQueue<int> queue;
    for (int i = 0; i < q; ++i) {
        int type, version;
        in.read(type, version);
        ++version;
        if (type == 0) {
            int x;
            in.read(x);
            queue.push(version, x);
        } else {
            out.println(queue.front(version));
            queue.pop(version);
        }
    }
}
