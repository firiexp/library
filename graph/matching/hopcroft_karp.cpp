#ifndef FIRIEXP_LIBRARY_GRAPH_HOPCROFT_KARP_CPP
#define FIRIEXP_LIBRARY_GRAPH_HOPCROFT_KARP_CPP

class HopcroftKarp {
    int l, r;
    vector<pair<int, int>> edges;
    vector<int> start, elist;
    vector<int> dist, bfs_order;
    int terminal_depth;
    bool dirty = true;

    void build_graph() {
        start.assign(l + 1, 0);
        elist.assign(edges.size(), 0);
        for (auto &&[a, b] : edges) ++start[a + 1];
        for (int i = 0; i < l; ++i) start[i + 1] += start[i];
        auto counter = start;
        for (auto &&[a, b] : edges) {
            elist[counter[a]++] = b;
        }
    }

    int collect_free_roots() {
        int count = 0;
        for (int v = 0; v < l; ++v) {
            if (match_left[v] == -1 && start[v] < start[v + 1]) bfs_order[count++] = v;
        }
        return count;
    }

    bool build_layers(int root_count) {
        int head = 0, tail = root_count;
        fill(dist.begin(), dist.end(), -1);
        for (int i = 0; i < root_count; ++i) dist[bfs_order[i]] = 0;
        terminal_depth = l + 1;
        while (head < tail) {
            int v = bfs_order[head++];
            for (int ei = start[v]; ei < start[v + 1]; ++ei) {
                int to = elist[ei];
                int u = match_right[to];
                if (u == -1) {
                    terminal_depth = dist[v] + 1;
                    return true;
                }
                if (dist[u] != -1) continue;
                dist[u] = dist[v] + 1;
                bfs_order[tail++] = u;
            }
        }
        return false;
    }

public:
    vector<int> match_left, match_right;

    explicit HopcroftKarp(int l, int r) : l(l), r(r), start(l + 1), dist(l), bfs_order(l), match_left(l, -1), match_right(r, -1) {}

    void add_edge(int a, int b) {
        edges.emplace_back(a, b);
        dirty = true;
    }

    bool bfs() { return build_layers(collect_free_roots()); }

    bool dfs(int v) {
        for (int ei = start[v]; ei < start[v + 1]; ++ei) {
            int to = elist[ei];
            int u = match_right[to];
            if (u == -1 && dist[v] + 1 != terminal_depth) continue;
            if (u != -1 && (dist[u] != dist[v] + 1 || dist[u] >= terminal_depth || !dfs(u))) continue;
            match_left[v] = to;
            match_right[to] = v;
            return true;
        }
        dist[v] = -1;
        return false;
    }

    int max_matching() {
        int ret = 0;
        for (int v : match_left) if (v != -1) ++ret;
        if (!dirty) return ret;
        build_graph();
        if (ret == 0) {
            for (int v = 0; v < l; ++v) {
                for (int ei = start[v]; ei < start[v + 1]; ++ei) {
                    int to = elist[ei];
                    if (match_right[to] != -1) continue;
                    match_left[v] = to;
                    match_right[to] = v;
                    ++ret;
                    break;
                }
            }
        }
        int root_count = collect_free_roots();
        while (root_count && build_layers(root_count)) {
            int remaining = 0;
            for (int i = 0; i < root_count; ++i) {
                int v = bfs_order[i];
                if (dfs(v)) ++ret;
                else bfs_order[remaining++] = v;
            }
            root_count = remaining;
        }
        dirty = false;
        return ret;
    }

    pair<vector<int>, vector<int>> minimum_vertex_cover() {
        max_matching();
        vector<char> seen_left(l), seen_right(r);
        queue<int> q;
        for (int i = 0; i < l; ++i) {
            if (match_left[i] != -1) continue;
            seen_left[i] = true;
            q.push(i);
        }
        while (!q.empty()) {
            int v = q.front();
            q.pop();
            for (int ei = start[v]; ei < start[v + 1]; ++ei) {
                int to = elist[ei];
                if (to == match_left[v] || seen_right[to]) continue;
                seen_right[to] = true;
                int u = match_right[to];
                if (u != -1 && !seen_left[u]) {
                    seen_left[u] = true;
                    q.push(u);
                }
            }
        }
        vector<int> left, right;
        for (int i = 0; i < l; ++i) if (!seen_left[i]) left.push_back(i);
        for (int i = 0; i < r; ++i) if (seen_right[i]) right.push_back(i);
        return {move(left), move(right)};
    }

    vector<pair<int, int>> get_pairs() const {
        vector<pair<int, int>> ret;
        for (int i = 0; i < l; ++i) {
            if (match_left[i] != -1) ret.emplace_back(i, match_left[i]);
        }
        return ret;
    }
};

#endif

/**
 * @brief Hopcroft-Karp法
 */
