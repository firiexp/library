#define STANDALONE

#include <algorithm>
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

void check_levels(const FunctionalGraph &fg) {
    int depth = 0;
    for (int d : fg.dist_to_cycle) depth = max(depth, d);
    int levels = 1;
    while ((1LL << levels) <= depth) ++levels;
    assert((int)fg.up.size() == levels);
    for (const auto &row : fg.up) assert((int)row.size() == fg.n);
}

void check_distances(const FunctionalGraph &fg, const vector<int> &to) {
    check_levels(fg);
    int n = to.size();
    for (int s = 0; s < n; ++s) {
        vector<int> expected(n, -1);
        int cur = s, d = 0;
        while (expected[cur] == -1) {
            expected[cur] = d++;
            cur = to[cur];
        }
        for (int t = 0; t < n; ++t) assert(fg.distance(s, t) == expected[t]);
    }
}

void exhaustive_distance_check() {
    for (int n = 1; n <= 6; ++n) {
        int total = 1;
        for (int i = 0; i < n; ++i) total *= n;
        for (int mask = 0; mask < total; ++mask) {
            vector<int> to(n);
            int cur = mask;
            for (int &v : to) {
                v = cur % n;
                cur /= n;
            }
            check_distances(FunctionalGraph(to), to);
        }
    }
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
        check_distances(fg, to);
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

        for (int v = 0; v < n; ++v) {
            to[v] = rng() % n;
            fg.set_edge(v, to[v]);
        }
        fg.build();
        FunctionalGraph rebuilt(to);
        check_distances(fg, to);
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
    check_levels(empty);
    for (int n : {1, 2, 3, 7, 8, 9, 1023, 1024, 1025, 200000}) {
        vector<int> to(n);
        for (int v = 0; v < n; ++v) to[v] = min(v + 1, n - 1);
        FunctionalGraph fg(to);
        for (int v = 0; v < n; ++v) {
            assert(fg.distance(v, n - 1) == n - 1 - v);
            assert(fg.distance(v, v) == 0);
            assert(fg.distance(v, 0) == (v == 0 ? 0 : -1));
            int t = n / 2;
            assert(fg.distance(v, t) == (v <= t ? t - v : -1));
        }
        check_levels(fg);
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
        assert(fg.up.size() == 1);
        for (int v = 0; v < n; ++v) {
            assert(fg.distance(v, n / 2) == (n / 2 - v + n) % n);
        }
        for (int v : {0, n / 2, n - 1}) {
            assert(fg.in_cycle(v));
            for (long long k : {0LL, 1LL, (long long)n, LLONG_MAX}) {
                assert(fg.jump(v, k) == (v + k % n) % n);
            }
        }
        for (int shape = 0; shape < 3; ++shape) {
            for (int v = 0; v < n; ++v) {
                fg.set_edge(v, shape == 0 ? v : shape == 1 ? 0 : max(v - 1, 0));
            }
            fg.build();
            check_levels(fg);
            for (int v = 0; v < n; ++v) {
                assert(fg.jump(v, 0) == v);
                assert(fg.jump(v, LLONG_MAX) == (shape == 0 ? v : 0));
                int distance = shape == 0 ? (v == 0 ? 0 : -1) : shape == 1 ? (v != 0) : v;
                assert(fg.distance(v, 0) == distance);
                if (shape == 2 && v > 1) {
                    assert(fg.jump(v, v - 1) == 1);
                    assert(fg.distance(v, 1) == v - 1);
                }
            }
        }
    }
}

int main() {
    self_check();
    exhaustive_distance_check();

}
