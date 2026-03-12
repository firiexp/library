struct FunctionalGraph {
    static constexpr int LOG = 63;

    int n;
    vector<int> to;
    vector<vector<int>> up;
    vector<int> comp_id;
    vector<int> cycle_pos;
    vector<int> cycle_len;
    vector<int> dist_to_cycle;
    vector<int> cycle_entry;
    vector<vector<int>> cycles;

    explicit FunctionalGraph(int n)
        : n(n),
          to(n, -1),
          up(LOG, vector<int>(n, -1)),
          comp_id(n, -1),
          cycle_pos(n, -1),
          cycle_len(n, 0),
          dist_to_cycle(n, -1),
          cycle_entry(n, -1) {}

    explicit FunctionalGraph(const vector<int> &to)
        : FunctionalGraph((int)to.size()) {
        this->to = to;
        build();
    }

    void set_edge(int v, int nxt) {
        to[v] = nxt;
    }

    void build() {
        up.assign(LOG, vector<int>(n, -1));
        for (int v = 0; v < n; ++v) up[0][v] = to[v];
        for (int k = 0; k + 1 < LOG; ++k) {
            for (int v = 0; v < n; ++v) {
                up[k + 1][v] = up[k][up[k][v]];
            }
        }

        vector<int> indeg(n);
        for (int v = 0; v < n; ++v) ++indeg[to[v]];

        vector<int> que, order;
        que.reserve(n);
        order.reserve(n);
        for (int v = 0; v < n; ++v) {
            if (indeg[v] == 0) que.push_back(v);
        }
        for (int head = 0; head < (int)que.size(); ++head) {
            int v = que[head];
            order.push_back(v);
            int nxt = to[v];
            if (--indeg[nxt] == 0) que.push_back(nxt);
        }

        comp_id.assign(n, -1);
        cycle_pos.assign(n, -1);
        cycle_len.assign(n, 0);
        dist_to_cycle.assign(n, -1);
        cycle_entry.assign(n, -1);
        cycles.clear();

        vector<int> seen(n);
        for (int v = 0; v < n; ++v) {
            if (indeg[v] == 0 || seen[v]) continue;
            int cid = cycles.size();
            vector<int> cyc;
            int cur = v;
            do {
                seen[cur] = 1;
                comp_id[cur] = cid;
                cycle_pos[cur] = cyc.size();
                dist_to_cycle[cur] = 0;
                cycle_entry[cur] = cur;
                cyc.push_back(cur);
                cur = to[cur];
            } while (cur != v);
            for (int x : cyc) cycle_len[x] = cyc.size();
            cycles.push_back(cyc);
        }

        for (int i = (int)order.size() - 1; i >= 0; --i) {
            int v = order[i];
            int nxt = to[v];
            comp_id[v] = comp_id[nxt];
            cycle_pos[v] = cycle_pos[nxt];
            cycle_len[v] = cycle_len[nxt];
            dist_to_cycle[v] = dist_to_cycle[nxt] + 1;
            cycle_entry[v] = cycle_entry[nxt];
        }
    }

    int jump(int v, long long k) const {
        for (int i = 0; i < LOG; ++i) {
            if ((k >> i) & 1) v = up[i][v];
        }
        return v;
    }

    bool in_cycle(int v) const {
        return dist_to_cycle[v] == 0;
    }

    int cycle_id(int v) const {
        return comp_id[v];
    }

    int cycle_size(int v) const {
        return cycle_len[v];
    }

    int steps_to_cycle(int v) const {
        return dist_to_cycle[v];
    }

    int cycle_vertex(int v) const {
        return cycle_entry[v];
    }

    int cycle_index(int v) const {
        return cycle_pos[v];
    }

    const vector<int> &cycle(int id) const {
        return cycles[id];
    }
};

/**
 * @brief 関数グラフ(Functional Graph)
 */
