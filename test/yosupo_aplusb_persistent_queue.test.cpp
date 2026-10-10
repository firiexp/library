#define PROBLEM "https://judge.yosupo.jp/problem/aplusb"

#include <bits/stdc++.h>
using namespace std;

#include "../util/fastio.cpp"
#include "../datastructure/persistent_queue.cpp"

void self_check() {
    mt19937 rng(103);
    for (int trial = 0; trial < 100; ++trial) {
        PersistentQueue<int> q;
        vector<deque<int>> states(1);
        assert(q.empty(0) && q.size(0) == 0);
        for (int step = 0; step < 1000; ++step) {
            int version = rng() % states.size();
            auto expected = states[version];
            int next;
            if (expected.empty() || rng() % 3) {
                int x = int(rng() % 101) - 50;
                next = q.push(version, x);
                expected.push_back(x);
            } else {
                assert(q.front(version) == expected.front());
                next = q.pop(version);
                expected.pop_front();
            }
            assert(next == (int)states.size());
            states.push_back(expected);
            for (int t : {version, next, int(rng() % states.size())}) {
                assert(q.size(t) == (int)states[t].size());
                assert(q.empty(t) == states[t].empty());
                if (!q.empty(t)) assert(q.front(t) == states[t].front());
            }
        }
    }
    PersistentQueue<int> q;
    int version = 0;
    for (int i = 0; i < 65537; ++i) {
        version = q.push(version, i);
        assert(q.front(version) == 0);
    }
    for (int i = 0; i < 65536; ++i) {
        int branch = q.pop(version);
        assert(q.front(branch) == 1 && q.front(version) == 0);
        int tail = q.push(branch, -i);
        assert(q.size(tail) == q.size(version));
    }
    for (int i = 0; i < 65537; ++i) {
        assert(q.front(version) == i);
        version = q.pop(version);
    }
    assert(q.empty(version));
    assert(q.front(q.push(version, -1)) == -1);
    PersistentQueue<string> strings;
    int a = strings.push(0, "a"), b = strings.push(a, "b");
    assert(strings.front(b) == "a");
    auto copy = strings;
    assert(copy.front(copy.pop(b)) == "b");
    assert(strings.front(b) == "a");
}

int main() {
    self_check();
    Scanner in;
    Printer out;
    int a, b;
    in.read(a, b);
    out.println(a + b);
}
