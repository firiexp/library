using namespace std;

template <typename M>
class ReRooting {
public:
    using T = typename M::T;
    using U = typename M::U;

    struct Node {
        int to, rev;
        U val;

        Node(int to, int rev, U val) : to(to), rev(rev), val(val) {}
    };

    int n;
    vector<vector<Node>> G;
    vector<T> dpl, dpr;
    vector<int> offset, l, r;

    explicit ReRooting(int n) : n(n), G(n), offset(n + 1), l(n), r(n) {}

    void add_edge(int u, int v, const U &x) {
        G[u].emplace_back(v, (int)G[v].size(), x);
        G[v].emplace_back(u, (int)G[u].size() - 1, x);
    }

    void add_edge(int u, int v, const U &x, const U &y) {
        G[u].emplace_back(v, (int)G[v].size(), x);
        G[v].emplace_back(u, (int)G[u].size() - 1, y);
    }

    T dfs(int i, int par) {
        int base = offset[i];
        while (l[i] != par && l[i] < (int)G[i].size()) {
            auto &e = G[i][l[i]];
            dpl[base + l[i] + 1] = M::f(dpl[base + l[i]], M::g(dfs(e.to, e.rev), e.val));
            ++l[i];
        }
        while (r[i] != par && r[i] >= 0) {
            auto &e = G[i][r[i]];
            dpr[base + r[i]] = M::f(M::g(dfs(e.to, e.rev), e.val), dpr[base + r[i] + 1]);
            --r[i];
        }
        if (par < 0) return dpr[base];
        return M::f(dpl[base + par], dpr[base + par + 1]);
    }

    vector<T> solve() {
        for (int i = 0; i < n; ++i) {
            offset[i + 1] = offset[i] + (int)G[i].size() + 1;
            l[i] = 0;
            r[i] = (int)G[i].size() - 1;
        }
        dpl.assign(offset[n], M::e());
        dpr.assign(offset[n], M::e());
        vector<T> ans(n);
        for (int i = 0; i < n; ++i) ans[i] = dfs(i, -1);
        return ans;
    }
};

/**
 * @brief ReRooting(全方位木DP)
 */
