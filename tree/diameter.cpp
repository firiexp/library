int diameter(vector<vector<int>> &G){
    vector<int> dist(G.size());
    int s = 0;
    auto dfs = [&](int x, int par, auto &&f) -> void {
        for (auto &&i : G[x]) {
            if(i != par){
                dist[i] = dist[x] + 1;
                if(dist[s] < dist[i]) s = i;
                f(i, x, f);
            }
        }
    };
    dist[s] = 0;
    dfs(s, -1, dfs);
    dist[s] = 0;
    dfs(s, -1, dfs);
    return dist[s];
}