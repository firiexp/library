template<class T>
pair<T, vector<int>> stoer_wagner(vector<vector<T>> graph) {
    int n = graph.size();
    vector<int> order(n);
    iota(order.begin(), order.end(), 0);
    vector<vector<int>> members(n);
    for (int u = 0; u < n; ++u) {
        assert(int(graph[u].size()) == n);
        for (int v = 0; v < u; ++v)
            assert(graph[u][v] >= T{} && graph[u][v] == graph[v][u]);
        members[u].push_back(u);
    }

    pair<T, vector<int>> best{};
    for (int count = n; count >= 2; --count) {
        vector<T> connection(n);
        for (int i = 1; i < count; ++i) {
            int prev = order[i - 1], next = i;
            for (int j = i; j < count; ++j) {
                int v = order[j];
                connection[v] += graph[prev][v];
                if (connection[v] > connection[order[next]]) next = j;
            }
            swap(order[i], order[next]);
        }

        int s = order[count - 2], t = order[count - 1];
        if (best.second.empty() || connection[t] < best.first) {
            best = {connection[t], members[t]};
            if (best.first == T{}) break;
        }
        for (int i = 0; i < count - 2; ++i) {
            int v = order[i];
            graph[s][v] += graph[t][v];
            graph[v][s] = graph[s][v];
        }
        members[s].insert(members[s].end(), members[t].begin(), members[t].end());
    }
    return best;
}

/**
 * @brief 無向グラフの全域最小カット(Stoer–Wagner法)
 */
