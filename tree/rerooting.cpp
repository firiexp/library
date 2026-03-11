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
    vector<vector<T>> dpl, dpr;
    vector<int> l, r;

    explicit ReRooting(int n) : n(n), G(n), dpl(n), dpr(n), l(n), r(n) {}

    void add_edge(int u, int v, const U &x) {
        G[u].emplace_back(v, (int)G[v].size(), x);
        G[v].emplace_back(u, (int)G[u].size() - 1, x);
    }

    void add_edge(int u, int v, const U &x, const U &y) {
        G[u].emplace_back(v, (int)G[v].size(), x);
        G[v].emplace_back(u, (int)G[u].size() - 1, y);
    }

    T dfs(int i, int par) {
        while (l[i] != par && l[i] < (int)G[i].size()) {
            auto &e = G[i][l[i]];
            dpl[i][l[i] + 1] = M::f(dpl[i][l[i]], M::g(dfs(e.to, e.rev), e.val));
            ++l[i];
        }
        while (r[i] != par && r[i] >= 0) {
            auto &e = G[i][r[i]];
            dpr[i][r[i]] = M::f(dpr[i][r[i] + 1], M::g(dfs(e.to, e.rev), e.val));
            --r[i];
        }
        if (par < 0) return dpr[i].front();
        return M::f(dpl[i][par], dpr[i][par + 1]);
    }

    vector<T> solve() {
        for (int i = 0; i < n; ++i) {
            dpl[i].assign(G[i].size() + 1, M::e());
            dpr[i].assign(G[i].size() + 1, M::e());
            l[i] = 0;
            r[i] = (int)G[i].size() - 1;
        }
        vector<T> ans(n);
        for (int i = 0; i < n; ++i) ans[i] = dfs(i, -1);
        return ans;
    }
};

/**
 * @brief ReRooting(全方位木DP)
 */
