#include "./bipartite_matching.cpp"
class Bipartite_Matching_LexMin : public Bipartite_Matching {
public:
    using Bipartite_Matching::Bipartite_Matching;

    int solve_LexMin() {
        matching();
        int res = 0;
        for (int i = 0; i < l; ++i) res += match[i] != -1;
        int source = l + r, sink = source + 1;
        vector<vector<int>> reverse(sink + 1);
        vector<int> next(sink + 1), queue;
        vector<pair<int, int>> added;
        for (int i = 0; i < l; ++i) {
            if (match[i] == -1) continue;
            for (auto &edges : reverse) edges.clear();
            auto edge = [&](int u, int v) { reverse[v].push_back(u); };
            for (int u = i; u < l; ++u) {
                if (match[u] == -1) edge(source, u);
                else edge(u, source);
                for (int v : G[u]) {
                    int w = l + v;
                    if (match[u] == w) edge(w, u);
                    else edge(u, w);
                }
            }
            for (int v = l; v < l + r; ++v) {
                if (match[v] == -1) edge(v, sink);
                else edge(sink, v);
            }
            next.assign(sink + 1, -1);
            next[i] = i;
            queue.clear();
            queue.push_back(i);
            for (int k = 0; k < (int)queue.size(); ++k) {
                int v = queue[k];
                for (int u : reverse[v]) {
                    if (next[u] != -1) continue;
                    next[u] = v;
                    queue.push_back(u);
                }
            }
            int chosen = source;
            if (next[source] == -1) {
                chosen = match[i];
                for (int v : G[i]) {
                    int w = l + v;
                    if (w < chosen && next[w] != -1) chosen = w;
                }
            }
            if (chosen == match[i]) continue;
            added.clear();
            int u = i, v = chosen;
            do {
                if (u < l && l <= v && v < source) added.emplace_back(u, v);
                if (l <= u && u < source && v < l) match[u] = match[v] = -1;
                u = v;
                v = next[u];
            } while (u != i);
            for (auto [a, b] : added) {
                match[a] = b;
                match[b] = a;
            }
        }
        return res;
    }
};

/**
 * @brief 辞書順最小二部マッチング(Lexicographically Minimum Bipartite Matching)
 */
