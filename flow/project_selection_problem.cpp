#include "./dinic.cpp"

template<class T>
class ProjectSelectionProblem {
    int n;
    T base_score{};
    vector<T> weight;
    vector<tuple<int, int, T>> penalty;
    vector<int> selected;

public:
    ProjectSelectionProblem() : n(0) {}
    explicit ProjectSelectionProblem(int n) : n(n), base_score(0), weight(n, 0), selected(n, 0) {}

    int add_vertex() {
        weight.emplace_back(0);
        selected.emplace_back(0);
        return n++;
    }

    int size() const {
        return n;
    }

    void add_true_profit(int v, T x) {
        weight[v] += x;
    }

    void add_false_profit(int v, T x) {
        base_score += x;
        weight[v] -= x;
    }

    void add_penalty(int x, int y, T cost) {
        penalty.emplace_back(x, y, cost);
    }

    void add_if_then(int x, int y) {
        add_penalty(x, y, INF<T>);
    }

    void force_true(int v) {
        add_true_profit(v, INF<T>);
    }

    void force_false(int v) {
        add_false_profit(v, INF<T>);
    }

    T solve() {
        int s = n, t = n + 1;
        Dinic<T, true> mf(n + 2);
        T offset = base_score;
        for (int v = 0; v < n; ++v) {
            if (weight[v] >= 0) {
                offset += weight[v];
                mf.add_edge(s, v, weight[v]);
            } else {
                mf.add_edge(v, t, -weight[v]);
            }
        }
        for (auto&& [x, y, cost] : penalty) {
            mf.add_edge(x, y, cost);
        }
        T cut = mf.flow(s, t);

        fill(selected.begin(), selected.end(), 0);
        queue<int> q;
        q.emplace(s);
        vector<int> vis(n + 2, 0);
        vis[s] = 1;
        while (!q.empty()) {
            int v = q.front();
            q.pop();
            for (auto&& e : mf.G[v]) {
                if (e.cap <= 0 || vis[e.to]) continue;
                vis[e.to] = 1;
                q.emplace(e.to);
            }
        }
        for (int v = 0; v < n; ++v) {
            selected[v] = vis[v];
        }
        return offset - cut;
    }

    const vector<int>& get_selected() const {
        return selected;
    }
};

/**
 * @brief Project Selection Problem
 */
