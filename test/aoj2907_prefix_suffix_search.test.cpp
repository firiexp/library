#define PROBLEM "https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=2907"

#include <array>
#include <algorithm>
#include <string>
#include <utility>
#include <vector>
using namespace std;

#include <cstdio>
#include <cstring>
#include <type_traits>

#include "../util/fastio.cpp"
#include "../datastructure/trie.cpp"

struct Fenwick {
    int n;
    vector<int> bit;
    explicit Fenwick(int n) : n(n), bit(n + 1, 0) {}
    void add(int i, int x) {
        for (++i; i <= n; i += i & -i) bit[i] += x;
    }
    int sum(int r) const {
        int res = 0;
        for (; r > 0; r -= r & -r) res += bit[r];
        return res;
    }
};

template<class T>
void build_ranges(const T &trie, vector<int> &word_pos, vector<int> &l, vector<int> &r) {
    const int n = trie.v.size();
    l.assign(n, 0);
    r.assign(n, 0);
    vector<int> it(n, 0);
    vector<char> entered(n, 0);
    int order = 0;

    struct Frame {
        int v;
    };
    vector<Frame> st;
    st.push_back({0});
    while (!st.empty()) {
        int v = st.back().v;
        if (!entered[v]) {
            entered[v] = 1;
            l[v] = order;
            for (int id : trie.v[v].idxs) word_pos[id] = order++;
        }
        while (it[v] < 26 && trie.v[v].nxt[it[v]] == -1) ++it[v];
        if (it[v] == 26) {
            r[v] = order;
            st.pop_back();
            continue;
        }
        st.push_back({trie.v[v].nxt[it[v]++]});
    }
}

int main() {
    Scanner sc;
    Printer pr;

    int n, q;
    sc.read(n, q);
    vector<string> words(n);
    auto f = [](char c) { return c - 'a'; };
    Trie<26, decltype(f)> pref(f), suff(f);

    for (int i = 0; i < n; ++i) {
        sc.read(words[i]);
        pref.add(words[i], i);
        reverse(words[i].begin(), words[i].end());
        suff.add(words[i], i);
        reverse(words[i].begin(), words[i].end());
    }

    vector<int> pref_pos(n), suff_pos(n), lp, rp, ls, rs;
    build_ranges(pref, pref_pos, lp, rp);
    build_ranges(suff, suff_pos, ls, rs);

    struct Point {
        int x, y;
    };
    vector<Point> pts(n);
    for (int i = 0; i < n; ++i) pts[i] = {pref_pos[i], suff_pos[i]};
    sort(pts.begin(), pts.end(), [](const Point &a, const Point &b) {
        if (a.x != b.x) return a.x < b.x;
        return a.y < b.y;
    });

    struct Event {
        int x, y, id, sign;
    };
    vector<Event> ev;
    ev.reserve(4 * q);
    vector<long long> ans(q);

    for (int i = 0; i < q; ++i) {
        string p, s;
        sc.read(p, s);
        int pv = pref.find(p);
        int sv = -1;
        reverse(s.begin(), s.end());
        sv = suff.find(s);
        if (pv == -1 || sv == -1) {
            continue;
        }
        ev.push_back({rp[pv], rs[sv], i, +1});
        ev.push_back({lp[pv], rs[sv], i, -1});
        ev.push_back({rp[pv], ls[sv], i, -1});
        ev.push_back({lp[pv], ls[sv], i, +1});
    }

    sort(ev.begin(), ev.end(), [](const Event &a, const Event &b) {
        return a.x < b.x;
    });

    Fenwick bit(n);
    int p = 0;
    for (const auto &e : ev) {
        while (p < n && pts[p].x < e.x) {
            bit.add(pts[p].y, 1);
            ++p;
        }
        ans[e.id] += 1LL * e.sign * bit.sum(e.y);
    }

    for (int i = 0; i < q; ++i) pr.writeln(ans[i]);
    return 0;
}
