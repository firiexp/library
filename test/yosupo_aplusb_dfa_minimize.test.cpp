#define PROBLEM "https://judge.yosupo.jp/problem/aplusb"
#include <bits/stdc++.h>
using namespace std;

#include "../string/dfa_minimize.cpp"
#include "../string/avoid_patterns.cpp"
#include "../math/digit_dfa.cpp"
#include "../util/fastio.cpp"

template<int W>
void equivalent(const DFA<W>& a, const DFA<W>& b) {
    set<pair<int, int>> seen;
    vector<pair<int, int>> queue{{a.initial, b.initial}};
    seen.insert(queue[0]);
    for (size_t i = 0; i < queue.size(); ++i) {
        auto [v, u] = queue[i];
        assert((v != -1 && a.accept[v]) == (u != -1 && b.accept[u]));
        for (int c = 0; c < W; ++c) {
            pair<int, int> to{v == -1 ? -1 : a.next[v][c], u == -1 ? -1 : b.next[u][c]};
            if (seen.insert(to).second) queue.push_back(to);
        }
    }
}

template<int W>
int oracle_size(const DFA<W>& a) {
    int n = a.next.size();
    vector<int> group(n + 1);
    for (int v = 0; v < n; ++v) group[v] = bool(a.accept[v]);
    while (true) {
        map<vector<int>, int> ids;
        vector<int> next(n + 1);
        for (int v = 0; v <= n; ++v) {
            vector<int> key{int(v != n && a.accept[v])};
            for (int c = 0; c < W; ++c) {
                int to = v == n ? -1 : a.next[v][c];
                key.push_back(group[to == -1 ? n : to]);
            }
            next[v] = ids.emplace(key, ids.size()).first->second;
        }
        if (next == group) break;
        group.swap(next);
    }
    vector<char> seen(n);
    vector<int> queue;
    if (a.initial != -1) queue.push_back(a.initial), seen[a.initial] = true;
    set<int> classes;
    for (size_t i = 0; i < queue.size(); ++i) {
        int v = queue[i];
        if (group[v] != group[n]) classes.insert(group[v]);
        for (int to : a.next[v]) if (to != -1 && !seen[to]) {
            seen[to] = true;
            queue.push_back(to);
        }
    }
    return classes.size();
}

template<int W>
void check(const DFA<W>& a) {
    auto b = minimize(a);
    equivalent(a, b);
    assert((int)b.next.size() == oracle_size(a));
    assert(b.accept.size() == b.next.size());
    assert(b.initial == (b.next.empty() ? -1 : 0));
    auto c = minimize(b);
    assert(c.next == b.next && c.accept == b.accept && c.initial == b.initial);
}

void self_check() {
    mt19937 rng(191);
    for (int tc = 0; tc < 4000; ++tc) {
        int n = 1 + rng() % 24;
        DFA<3> a{vector<array<int, 3>>(n), vector<char>(n), int(rng() % (n + 1)) - 1};
        for (int v = 0; v < n; ++v) {
            a.accept[v] = tc % 3 == 0 ? tc % 2 : rng() % 2;
            for (int& to : a.next[v]) to = int(rng() % (n + 1)) - 1;
        }
        check(a);
    }
    check(DFA<2>{});
    check(avoid_patterns<2, 'a'>({}));
    check(avoid_patterns<2, 'a'>({""}));
    check(avoid_patterns<2, 'a'>({"aa", "ba"}));
    check(avoid_patterns<10, '0'>({"404", "00"}));
    check(required_digits(1023));
    check(digit_value_mod(100));
    check(digit_sum_mod(100));
    check(intersect(digit_sum_exact(20), digit_value_mod(7)));
    assert(minimize(digit_value_mod(100)).next.size() == 3);
    assert(minimize(digit_sum_mod(100)).next.size() == 100);
    assert(minimize(required_digits(1023)).next.size() == 1024);
    DFA<2> unreachable{vector<array<int, 2>>(3), {false, true, false}, 0};
    unreachable.next = {{{0, 2}}, {{1, 1}}, {{2, 2}}};
    check(unreachable);
    assert(minimize(unreachable).initial == -1);
    auto chain = avoid_patterns<2, 'a'>({string(20000, 'a')});
    auto compact = minimize(chain);
    assert(compact.next.size() == 20000);
    equivalent(chain, compact);
}

int main() {
    self_check();
    Scanner sc;
    Printer pr;
    int a, b;
    sc.read(a, b);
    pr.println(a + b);
}
