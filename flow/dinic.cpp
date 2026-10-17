template<class T, bool directed>
class Dinic {
    static_assert(directed || numeric_limits<T>::is_signed,
                  "undirected flow requires a signed capacity type");
    struct input_edge {
        int from, index;
        T capacity;
    };
    vector<input_edge> positions;

    void bfs(int s, int t){
        fill(level.begin(),level.end(), -1);
        queue<int> Q;
        level[s] = 0;
        Q.emplace(s);
        while(!Q.empty()){
            int v = Q.front(); Q.pop();
            for (auto &&e : G[v]){
                if(e.cap > 0 && level[e.to] < 0){
                    level[e.to] = level[v] + 1;
                    if(e.to == t) return;
                    Q.emplace(e.to);
                }
            }
        }
    }
 
    T dfs(int v, int t, T f){
        if(v == t) return f;
        for(int &i = iter[v]; i < G[v].size(); i++){
            edge &e = G[v][i];
            if(e.cap > 0 && level[v] < level[e.to]){
                T d = dfs(e.to, t, min(f,  e.cap));
                if(d == 0) continue;
                e.cap -= d;
                G[e.to][e.rev].cap += d;
                return d;
            }
        }
        return 0;
    }
public:
    struct Edge {
        int from, to;
        T capacity, flow;
    };

    struct edge {
        int to{}; T cap; int rev{};
        edge() = default;
        edge(int to, T cap, int rev) : to(to), cap(cap), rev(rev) {}
    };
 
    vector<vector<edge>> G;
    vector<int> level, iter;
    Dinic() = default;
    explicit Dinic(int n) : G(n), level(n), iter(n) {}
 
    int add_edge(int from, int to, T cap){
        int from_id = G[from].size(), to_id = G[to].size();
        int id = positions.size();
        positions.push_back({from, from_id, cap});
        if(from == to) ++to_id;
        G[from].emplace_back(to, cap, to_id);
        G[to].emplace_back(from, directed ? 0 : cap, from_id);
        return id;
    }

    Edge get_edge(int id) const {
        const auto &p = positions[id];
        const auto &e = G[p.from][p.index];
        return {p.from, e.to, p.capacity, T(p.capacity - e.cap)};
    }

    vector<Edge> edges() const {
        vector<Edge> result;
        result.reserve(positions.size());
        for(int id = 0; id < int(positions.size()); ++id)
            result.push_back(get_edge(id));
        return result;
    }

    vector<char> min_cut(int s) const {
        vector<char> reachable(G.size(), false);
        queue<int> q;
        reachable[s] = true;
        q.emplace(s);
        while(!q.empty()) {
            int v = q.front(); q.pop();
            for(const auto &e : G[v]) {
                if(e.cap <= 0 || reachable[e.to]) continue;
                reachable[e.to] = true;
                q.emplace(e.to);
            }
        }
        return reachable;
    }
 
 
    T flow(int s, int t, T lim = INF<T>){
        T ret = 0;
        while(lim > 0) {
            bfs(s, t);
            if(level[t] < 0) break;
            fill(iter.begin(),iter.end(), 0);
            while(lim > 0){
                T f = dfs(s, t, lim);
                if(f == 0) break;
                ret += f;
                lim -= f;
            }
        }
        return ret;
    }
};

/**
 * @brief Dinic法(Dinic)
 */
