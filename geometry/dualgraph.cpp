#include "../geometry/geometry.cpp"

class DualGraph {
    struct P {
        int to, nxt, id, id2, rev;
        P(int to = 0, int nxt = 0, int id = 0, int rev = 0) : to(to), nxt(nxt), id(id), rev(rev), id2(0) {};
        bool operator!=(P x){ return to != x.to || nxt != x.nxt || id != x.id || rev != x.rev; }
    };
public:
    int n, m;
    Polygon v;
    vector<vector<P>> G_;
    vector<vector<int>> G;
    vector<vector<Point>> A;
    DualGraph(Polygon v) : v(v), n(v.size()), G_(n), m(0) {}

    void add_point(Point P){ v.emplace_back(P); n++; G_.emplace_back(); }
    void add_edge(int a, int b){
        G_[a].emplace_back(b, 0, m, 0);
        G_[b].emplace_back(a, 0, m++, 0);
    }

    void build(){
        vector<int> l(m), r(m);
        for (int i = 0; i < n; ++i) {
            sort(G_[i].begin(), G_[i].end(), [&](P &a, P &b){ return arg(v[a.to]-v[i]) < arg(v[b.to]-v[i]); });
            for (int j = 0; j < G_[i].size(); ++j) {
                G_[i][j].nxt = (j + 1) % G_[i].size();
                if(i < G_[i][j].to) l[G_[i][j].id] = j;
                else r[G_[i][j].id] = j;
            }
        }
        for (int i = 0; i < n; ++i) {
            for (auto &&e : G_[i]) {
                e.rev = (i < e.to ? r[e.id] : l[e.id]);
            }
        }
        int cur = 1;
        A = move(vector<vector<Point>>());
        for (int i = 0; i < n; ++i) {
            for (auto &&x : G_[i]) {
                if(x.id2) continue;
                x.id2 = cur;
                A.emplace_back();
                A.back().emplace_back(v[i]);
                auto e = &x;
                while(e->to != i){
                    A.back().emplace_back(v[e->to]);
                    e = &G_[e->to][G_[e->to][e->rev].nxt];
                    e->id2 = cur;
                }
                cur++;
            }
        }
        for (int i = 0; i < n; ++i) {
            for (auto &&e : G_[i]) {
                (i < e.to ? l[e.id] : r[e.id]) = e.id2-1;
            }
        }
        G = move(vector<vector<int>>(A.size()));
        for (int i = 0; i < m; ++i) {
            G[l[i]].emplace_back(r[i]);
            G[r[i]].emplace_back(l[i]);
        }
    }
};