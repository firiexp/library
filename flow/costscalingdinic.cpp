template<class T, bool directed>
class CostScalingDinic {
    void bfs(int s, T x){
        fill(level.begin(),level.end(), -1);
        queue<int> Q;
        level[s] = 0;
        Q.emplace(s);
        while(!Q.empty()){
            int v = Q.front(); Q.pop();
            for (auto &&e : G[v]){
                if(e.cap >= x && level[e.to] < 0){
                    level[e.to] = level[v] + 1;
                    Q.emplace(e.to);
                }
            }
        }
    }

    T dfs(int v, int t, T x, T f){
        if(v == t) return f;
        T res = 0;
        for(int &i = iter[v]; i < G[v].size(); i++){
            edge &e = G[v][i];
            if(e.cap >= x && level[v] < level[e.to]){
                T d = dfs(e.to, t, x, min(f-res,  e.cap));
                if(d == 0) continue;
                e.cap -= d;
                G[e.to][e.rev].cap += d;
                res += d;
                if(f - res < x) break;
            }
        }
        return res;
    }
public:
    struct edge {
        int to{}; T cap; int rev{};
        edge() = default;
        edge(int to, T cap, int rev) : to(to), cap(cap), rev(rev) {}
    };

    vector<vector<edge>> G;
    vector<int> level, iter;
    CostScalingDinic() = default;
    explicit CostScalingDinic(int n) : G(n), level(n), iter(n) {}

    void add_edge(int from, int to, int cap){
        if(!cap) return;
        G[from].emplace_back(to, cap, G[to].size());
        G[to].emplace_back(from, directed ? 0 : cap,  G[from].size()-1);
    }

    T flow(int s, int t, T lim = INF<T>){
        T ret = 0;
        T cap = 1; while(cap<<1 <= lim) cap <<= 1;
        while(cap) {
            bfs(s, cap);
            if(level[t] < 0){
                cap >>= 1;
                continue;
            }
            fill(iter.begin(),iter.end(), 0);
            ret += dfs(s, t, cap, INF<T>);
        }
        return ret;
    }
};
