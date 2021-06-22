class IndependentSet {
    int n;
    vector<ull> G;
    pair<int, ull> dfs(ull R, ull P, ull X){
        if(!P && !X){
            return {__builtin_popcountll(R), R};
        }
        if(!P) return {-1, 0};
        pair<int, ull> res = {-1, 0};
        int pivot = __builtin_ctzll(P|X);
        ull z = P & ~G[pivot];
        for (int i = 0; i < n; ++i) {
            if(z & (1ull << i)){
                res = max(res, dfs(R|(1ull << i), P&G[i], X&G[i]));
                P ^= 1ull << i;
                X |= 1ull << i;
            }
        }
        return res;
    }


public:
    explicit IndependentSet(int n): n(n), G(n) {
        for (int i = 0; i < n; ++i) {
            G[i] = ((1ull << n)-1)^(1ull << i);
        }
    }
    void add_edge(int u, int v){
        G[u] &= ~(1ull << v);
        G[v] &= ~(1ull << u);
    }
    pair<int, ull> maximum_independent_set() {
        return dfs(0, (1ull << n)-1, 0);
    }
};