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
    vector<int> offset;

    explicit ReRooting(int n) : n(n), G(n), offset(n + 1) {}

    void add_edge(int u, int v, const U &x) {
        G[u].emplace_back(v, (int)G[v].size(), x);
        G[v].emplace_back(u, (int)G[u].size() - 1, x);
    }

    void add_edge(int u, int v, const U &x, const U &y) {
        G[u].emplace_back(v, (int)G[v].size(), x);
        G[v].emplace_back(u, (int)G[u].size() - 1, y);
    }

    vector<T> solve() {
        for (int i = 0; i < n; ++i) {
            offset[i + 1] = offset[i] + (int)G[i].size() + 1;
        }
        dpl.assign(offset[n], M::e());
        dpr.assign(offset[n], M::e());
        vector<int> parent(n, -1), order;
        order.reserve(n);
        if (n) order.push_back(0);
        for (int i = 0; i < (int)order.size(); ++i) {
            int v = order[i];
            for (int j = 0; j < (int)G[v].size(); ++j) if (j != parent[v]) {
                auto &e = G[v][j];
                parent[e.to] = e.rev;
                order.push_back(e.to);
            }
        }
        vector<T> ans(n);
        for (int i = n - 1; i >= 0; --i) {
            int v = order[i], base = offset[v];
            T value = M::e();
            for (int j = 0; j < (int)G[v].size(); ++j) if (j != parent[v]) {
                auto &e = G[v][j];
                dpl[base + j + 1] = M::g(ans[e.to], e.val);
                value = M::f(value, dpl[base + j + 1]);
            }
            ans[v] = move(value);
        }
        for (int v : order) {
            int base = offset[v], degree = G[v].size();
            for (int j = degree - 1; j >= 0; --j)
                dpr[base + j] = M::f(dpl[base + j + 1], dpr[base + j + 1]);
            for (int j = 0; j < degree; ++j) {
                dpl[base + j + 1] = M::f(dpl[base + j], dpl[base + j + 1]);
                if (j == parent[v]) continue;
                auto &e = G[v][j];
                T value = M::f(dpl[base + j], dpr[base + j + 1]);
                dpl[offset[e.to] + e.rev + 1] = M::g(value, G[e.to][e.rev].val);
            }
            ans[v] = dpr[base];
        }
        return ans;
    }
};

/**
 * @brief ReRooting(全方位木DP)
 */
