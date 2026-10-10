#include "SCC.cpp"

vector<char> offline_reachability(int n, const vector<pair<int, int>> &edges,
                                  const vector<pair<int, int>> &queries) {
    vector<char> answer(queries.size());
    if (queries.empty()) return answer;
    SCC scc(n);
    for (auto [u, v] : edges) scc.add_edge(u, v);
    int count = scc.build();
    vector<int> sources(count, -1), targets(count, -1);
    int ns = 0, nt = 0;
    for (int i = 0; i < (int)queries.size(); ++i) {
        auto [u, v] = queries[i];
        int s = scc[u], t = scc[v];
        if (s == t) answer[i] = 1;
        if (s >= t) continue;
        if (sources[s] == -1) sources[s] = ns++;
        if (targets[t] == -1) targets[t] = nt++;
    }
    bool forward = ns <= nt;
    auto &group = forward ? sources : targets;
    int k = forward ? ns : nt;
    vector<int> component(k), head(k, -1), next(queries.size());
    for (int v = 0; v < count; ++v)
        if (group[v] != -1) component[group[v]] = v;
    for (int i = 0; i < (int)queries.size(); ++i) {
        auto [u, v] = queries[i];
        int s = scc[u], t = scc[v];
        if (s >= t) continue;
        int id = group[forward ? s : t];
        next[i] = head[id];
        head[id] = i;
    }
    vector<unsigned long long> mask(count);
    for (int begin = 0; begin < k; begin += 64) {
        int end = min(begin + 64, k);
        fill(mask.begin(), mask.end(), 0);
        for (int id = begin; id < end; ++id)
            mask[component[id]] = 1ULL << (id - begin);
        if (forward) {
            for (int v = 0; v < count; ++v)
                for (int u : scc.G_out[v]) mask[u] |= mask[v];
        } else {
            for (int v = count - 1; v >= 0; --v)
                for (int u : scc.G_out[v]) mask[v] |= mask[u];
        }
        for (int id = begin; id < end; ++id) {
            for (int i = head[id]; i != -1; i = next[i]) {
                auto [u, v] = queries[i];
                answer[i] = (mask[scc[forward ? v : u]] >> (id - begin)) & 1;
            }
        }
    }
    return answer;
}

/**
 * @brief 有向グラフの一括到達判定
 */
