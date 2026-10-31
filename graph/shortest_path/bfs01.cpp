#include "../edge.cpp"

template <typename T>
vector<T> bfs01(int s, vector<vector<edge<T>>> &G) {
    int n = G.size();
    vector<T> d(n, INF<T>);
    vector<char> settled(n);
    deque<int> q;
    d[s] = 0;
    q.push_front(s);
    while (!q.empty()) {
        int v = q.front();
        q.pop_front();
        if (settled[v]) continue;
        settled[v] = true;
        for (auto &&e : G[v]) {
            T nd = d[v] + e.cost;
            if (d[e.to] <= nd) continue;
            d[e.to] = nd;
            if (e.cost == T(0)) {
                q.push_front(e.to);
            } else {
                assert(e.cost == T(1));
                q.push_back(e.to);
            }
        }
    }
    return d;
}

/**
 * @brief 01-BFS
 */
