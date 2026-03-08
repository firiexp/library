#include "./auxtree.cpp"

struct VirtualTree {
    int root;
    vector<int> vertices;
    vector<int> parent;
};

class VirtualTreeHelper {
    AuxTree aux;
    vector<int> mark, parent_buf;
    int stamp = 0;

public:
    explicit VirtualTreeHelper(int n) : aux(n), mark(n, 0), parent_buf(n, -1) {}

    void add_edge(int u, int v) {
        aux.add_edge(u, v);
    }

    void build(int root = 0) {
        aux.buildLCA(root);
    }

    int lca(int u, int v) {
        return aux.LCA(u, v);
    }

    int distance(int u, int v) {
        return aux.distance(u, v);
    }

    VirtualTree make(vector<int> vertices) {
        aux.make(vertices);
        sort(vertices.begin(), vertices.end(), [&](int a, int b) { return aux.fi[a] < aux.fi[b]; });
        vertices.erase(unique(vertices.begin(), vertices.end()), vertices.end());

        VirtualTree res;
        res.root = vertices.front();
        ++stamp;
        vector<int> st = {res.root};
        mark[res.root] = stamp;
        parent_buf[res.root] = -1;

        while (!st.empty()) {
            int v = st.back();
            st.pop_back();
            res.vertices.emplace_back(v);
            res.parent.emplace_back(parent_buf[v]);
            for (auto &&u : aux.out[v]) {
                if (mark[u] == stamp) continue;
                mark[u] = stamp;
                parent_buf[u] = v;
                st.emplace_back(u);
            }
        }

        aux.clear(vertices);
        return res;
    }
};

/**
 * @brief Virtual Tree Helper
 */
