#define PROBLEM "https://judge.yosupo.jp/problem/aplusb"

#include <cassert>
#include <climits>
#include <random>
#include <tuple>
#include <vector>
using namespace std;

using ll = long long;

#include <cstdio>
#include <cstring>
#include <string>
#include <type_traits>

#include <charconv>
#include "../util/fastio.cpp"
#include "../graph/functional_graph.cpp"

tuple<vector<int>, int, int> walk_info(const vector<int> &to, int start) {
    int n = to.size();
    vector<int> pos(n, -1), ord;
    int cur = start;
    while (pos[cur] == -1) {
        pos[cur] = ord.size();
        ord.push_back(cur);
        cur = to[cur];
    }
    return {ord, pos[cur], (int)ord.size() - pos[cur]};
}

int brute_jump(const vector<int> &to, int start, long long k) {
    auto [ord, offset, len] = walk_info(to, start);
    if (k < (int)ord.size()) return ord[k];
    return ord[offset + (k - offset) % len];
}

void self_check() {
    mt19937 rng(0);
    for (int tc = 0; tc < 500; ++tc) {
        int n = rng() % 30 + 1;
        vector<int> to(n);
        for (int v = 0; v < n; ++v) to[v] = rng() % n;

        FunctionalGraph fg(n);
        for (int v = 0; v < n; ++v) fg.set_edge(v, to[v]);
        fg.build();

        FunctionalGraph fg2(to);
        for (int v = 0; v < n; ++v) {
            assert(fg.jump(v, 0) == v);
            assert(fg.jump(v, 1) == to[v]);
            assert(fg.jump(v, 37) == fg2.jump(v, 37));

            auto [ord, offset, len] = walk_info(to, v);
            int entry = ord[offset];
            assert(fg.steps_to_cycle(v) == offset);
            assert(fg.cycle_vertex(v) == entry);
            assert(fg.cycle_size(v) == len);
            assert(fg.in_cycle(v) == (offset == 0));
            assert(fg.cycle_id(v) == fg.cycle_id(entry));

            const auto &cyc = fg.cycle(fg.cycle_id(v));
            assert((int)cyc.size() == len);
            assert(cyc[fg.cycle_index(v)] == entry);

            for (long long k : {0LL, (long long)offset, (long long)offset + len,
                                LLONG_MAX - 1, LLONG_MAX}) {
                assert(fg.jump(v, k) == brute_jump(to, v, k));
            }

            for (long long k = 0; k <= 100; ++k) {
                assert(fg.jump(v, k) == brute_jump(to, v, k));
            }
            for (int rep = 0; rep < 20; ++rep) {
                long long k = (long long)(rng() % 1000000) * (rng() % 1000000);
                assert(fg.jump(v, k) == brute_jump(to, v, k));
            }
        }

        vector<int> seen_cycle(fg.cycles.size());
        for (int cid = 0; cid < (int)fg.cycles.size(); ++cid) {
            const auto &cyc = fg.cycle(cid);
            for (int i = 0; i < (int)cyc.size(); ++i) {
                int v = cyc[i];
                assert(fg.in_cycle(v));
                assert(to[v] == cyc[(i + 1) % cyc.size()]);
                ++seen_cycle[cid];
            }
        }
        for (int cid = 0; cid < (int)fg.cycles.size(); ++cid) {
            assert(seen_cycle[cid] == (int)fg.cycle(cid).size());
        }

        // Rebuild all cycle metadata after changing edges.
        for (int v = 0; v < n; ++v) {
            to[v] = rng() % n;
            fg.set_edge(v, to[v]);
        }
        fg.build();
        FunctionalGraph rebuilt(to);
        assert(fg.comp_id == rebuilt.comp_id);
        assert(fg.cycle_pos == rebuilt.cycle_pos);
        assert(fg.cycle_len == rebuilt.cycle_len);
        assert(fg.dist_to_cycle == rebuilt.dist_to_cycle);
        assert(fg.cycle_entry == rebuilt.cycle_entry);
        assert(fg.cycles == rebuilt.cycles);
        for (int v = 0; v < n; ++v) {
            assert(fg.jump(v, LLONG_MAX) == brute_jump(to, v, LLONG_MAX));
        }
    }

    FunctionalGraph empty(vector<int>{});
    empty.build();
    assert(empty.cycles.empty());
    for (int n : {1, 2, 3, 7, 8, 9, 1023, 1024, 1025, 200000}) {
        vector<int> to(n);
        for (int v = 0; v < n; ++v) to[v] = min(v + 1, n - 1);
        FunctionalGraph fg(to);
        int levels = 1;
        while ((1LL << levels) < n) ++levels;
        assert((int)fg.up.size() == levels);
        for (int v : {0, n / 2, n - 1}) {
            for (long long k : {0LL, 1LL, (long long)n - v - 1,
                                (long long)n - v, LLONG_MAX}) {
                int expected = k >= n - v - 1 ? n - 1 : v + (int)k;
                assert(fg.jump(v, k) == expected);
            }
            for (int k = 1; k < n - v - 1; k *= 2) {
                assert(fg.jump(v, k) == v + k);
            }
        }
        fg.set_edge(n - 1, 0);
        fg.build();
        for (int v : {0, n / 2, n - 1}) {
            assert(fg.in_cycle(v));
            for (long long k : {0LL, 1LL, (long long)n, LLONG_MAX}) {
                assert(fg.jump(v, k) == (v + k % n) % n);
            }
        }
    }
}

int main() {
    self_check();

    Scanner sc;
    Printer pr;
    ll a, b;
    sc.read(a, b);
    pr.println(a + b);
    return 0;
}
