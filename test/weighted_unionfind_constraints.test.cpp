#define STANDALONE

#include <bits/stdc++.h>
using namespace std;
#include "../datastructure/unionfind/weightedunionfind.cpp"

struct AddGroup {
    using T = long long;
    static T e() { return 0; }
    static T op(T a, T b) { return a + b; }
    static T inv(T a) { return -a; }
    static T random(mt19937 &rng) { return int(rng() % 21) - 10; }
};

struct PermutationGroup {
    using T = array<int, 4>;
    static T e() { return {0, 1, 2, 3}; }
    static T op(T a, T b) {
        T c;
        for (int i = 0; i < 4; ++i) c[i] = a[b[i]];
        return c;
    }
    static T inv(T a) {
        T b;
        for (int i = 0; i < 4; ++i) b[a[i]] = i;
        return b;
    }
    static T random(mt19937 &rng) {
        T a = e();
        shuffle(a.begin(), a.end(), rng);
        return a;
    }
};

template<class G>
void check() {
    using T = typename G::T;
    mt19937 rng(320);
    WeightedUnionFind<G> empty(0);
    for (int n = 1; n <= 10; ++n) {
        for (int tc = 0; tc < 100; ++tc) {
            WeightedUnionFind<G> uf(n);
            vector<vector<pair<int, T>>> graph(n);
            auto differences = [&](int source) {
                vector<optional<T>> distance(n);
                vector<int> queue{source};
                distance[source] = G::e();
                for (int i = 0; i < (int)queue.size(); ++i) {
                    int v = queue[i];
                    for (auto [to, w] : graph[v]) {
                        if (distance[to]) continue;
                        distance[to] = G::op(*distance[v], w);
                        queue.push_back(to);
                    }
                }
                return distance;
            };
            for (int step = 0; step < 80; ++step) {
                int u = rng() % n, v = step % 11 == 0 ? u : rng() % n;
                if (n >= 3 && step == 0) u = 1, v = 2;
                if (n >= 3 && step == 1) u = 0, v = 1;
                auto distance = differences(u);
                T w = distance[v] && step % 2 ? *distance[v] : G::random(rng);
                bool expected_merged = !distance[v];
                bool expected_ok = expected_merged || *distance[v] == w;
                auto result = uf.unite(u, v, w);
                assert(result.ok == expected_ok);
                assert(result.merged == expected_merged);
                assert(!result == !expected_ok);
                if (result && result.merged) {
                    graph[u].emplace_back(v, w);
                    graph[v].emplace_back(u, G::inv(w));
                }
                auto repeated = uf.unite(u, v, w);
                assert(bool(repeated) == expected_ok && !repeated.merged);
                auto reversed = uf.unite(v, u, G::inv(w));
                assert(bool(reversed) == expected_ok && !reversed.merged);
                for (int a = 0; a < n; ++a) {
                    auto oracle = differences(a);
                    int count = 0;
                    for (int b = 0; b < n; ++b) {
                        assert(uf.same(a, b) == oracle[b].has_value());
                        if (oracle[b]) {
                            ++count;
                            assert(uf.diff(a, b) == *oracle[b]);
                        }
                    }
                    assert(uf.size(a) == count);
                }
            }
        }
    }
}

int main() {
    check<AddGroup>();
    check<PermutationGroup>();
}
