#define PROBLEM "https://judge.yosupo.jp/problem/aplusb"

#include <bits/stdc++.h>
using namespace std;
using ll = long long;
#include "../util/fastio.cpp"
#include "../datastructure/radixheap.cpp"

struct Tracked {
    inline static int live = 0;
    int id;
    explicit Tracked(int id) : id(id) { ++live; }
    Tracked(const Tracked &other) : id(other.id) { ++live; }
    Tracked &operator=(const Tracked &) = default;
    ~Tracked() { --live; }
    bool operator<(const Tracked &other) const { return id < other.id; }
};

struct NonAssignable {
    inline static int live = 0;
    const int id;
    explicit NonAssignable(int id) : id(id) { ++live; }
    NonAssignable(const NonAssignable &other) : id(other.id) { ++live; }
    ~NonAssignable() { --live; }
    bool operator<(const NonAssignable &other) const { return id < other.id; }
};

template<class V>
void check_slide() {
    for (int width : {1, 2, 3, 31, 1024}) {
        RadixHeap<ll, V> q;
        for (int i = 0; i < width; ++i) q.emplace(0, V(i));
        for (int i = 0; i < 20000; ++i) {
            assert(q.top().first == 0 && q.top().second.id == i);
            q.pop();
            q.emplace(0, V(i + width));
            assert(q.size() == (size_t)width && !q.empty());
            assert(V::live <= 2 * width);
        }
        for (int i = 20000; i < 20000 + width; ++i) {
            assert(q.top().second.id == i);
            q.pop();
        }
        assert(q.empty() && q.size() == 0 && V::live == 0);
        for (ll key : {1LL, 2LL, 3LL, 1LL << 31, 1LL << 62, LLONG_MAX}) {
            q.emplace(key, V(7));
            assert(q.top().first == key && q.top().second.id == 7);
            q.pop();
            assert(q.empty() && V::live == 0);
        }
    }
}

template<class K>
void check_random() {
    mt19937_64 rng(74);
    RadixHeap<K, int> q;
    map<K, deque<int>> expected;
    K last = 0;
    int next_id = 0;
    size_t count = 0;
    auto pop = [&] {
        auto [key, id] = q.top();
        auto it = expected.begin();
        assert(key == it->first && id == it->second.front());
        assert(q.top() == make_pair(key, id));
        it->second.pop_front();
        if (it->second.empty()) expected.erase(it);
        last = key;
        q.pop();
        --count;
    };
    for (int step = 0; step < 100000; ++step) {
        if (expected.empty() || (count < 1024 && rng() % 2)) {
            K key = last + (rng() % 3 ? rng() % 10000 : 0);
            q.emplace(key, next_id);
            expected[key].push_back(next_id++);
            ++count;
        } else {
            pop();
        }
        assert(q.size() == count && q.empty() == expected.empty());
    }
    while (!q.empty()) pop();
    assert(count == 0 && expected.empty());
    q.emplace(numeric_limits<K>::max(), next_id);
    assert(q.top() == make_pair(numeric_limits<K>::max(), next_id));
    q.pop();
    assert(q.empty());
}

int main() {
    check_slide<Tracked>();
    check_slide<NonAssignable>();
    check_random<int>();
    check_random<ll>();
    Scanner sc;
    Printer pr;
    ll a, b;
    sc.read(a, b);
    pr.println(a + b);
}
