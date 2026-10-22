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
    if (k == 0) return answer;
    vector<int> component(k), head(k, -1), next(queries.size());
    int index = 0;
    for (int v = 0; v < count; ++v)
        if (group[v] != -1) component[group[v] = index++] = v;
    vector<int> boundary((k + 63) / 64, forward ? 0 : count);
    for (int i = 0; i < (int)queries.size(); ++i) {
        auto [u, v] = queries[i];
        int s = scc[u], t = scc[v];
        if (s >= t) continue;
        int id = group[forward ? s : t];
        next[i] = head[id];
        head[id] = i;
        if (forward) boundary[id / 64] = max(boundary[id / 64], t);
        else boundary[id / 64] = min(boundary[id / 64], s);
    }
    vector<unsigned long long> mask(count);
    for (int begin = 0; begin < k; begin += 64) {
        int end = min(begin + 64, k);
        int lo = forward ? component[begin] : boundary[begin / 64];
        int hi = forward ? boundary[begin / 64] : component[end - 1];
        fill(mask.begin() + lo, mask.begin() + hi + 1, 0);
        for (int id = begin; id < end; ++id)
            mask[component[id]] = 1ULL << (id - begin);
        if (forward) {
            for (int v = lo; v <= hi; ++v) {
                if (mask[v] == 0) continue;
                for (int u : scc.G_out[v]) {
                    if (u > hi) break;
                    mask[u] |= mask[v];
                }
            }
        } else {
            for (int v = hi; v >= lo; --v) {
                for (int u : scc.G_out[v]) {
                    if (u > hi) break;
                    mask[v] |= mask[u];
                }
            }
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
