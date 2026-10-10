#include "centroid_decomposition_query_helper.cpp"
#include "../datastructure/binaryindexedtree.cpp"

class RangeContourSum {
    CentroidDecompositionQueryHelper cd;
    vector<BIT<long long>> all, branch;
    vector<int> all_size, branch_size;

    long long sum(BIT<long long> &bit, int size, long long l, long long r) {
        int left = (int)max(0LL, min((long long)size, l));
        int right = (int)max(0LL, min((long long)size, r));
        return bit.sum(right) - bit.sum(left);
    }

public:
    RangeContourSum(const vector<vector<int>> &g, const vector<long long> &values)
        : cd((int)g.size()), all_size(g.size()), branch_size(g.size()) {
        cd.G = g;
        cd.build();
        int n = g.size();
        vector<vector<long long>> a(n), b(n);
        for (int v = 0; v < n; ++v) {
            for (int i = 0; i < (int)cd.path[v].size(); ++i) {
                int c = cd.path[v][i], d = cd.dist[v][i];
                if ((int)a[c].size() <= d) a[c].resize(d + 1);
                a[c][d] += values[v];
                if (i == 0) continue;
                int child = cd.path[v][i - 1];
                if ((int)b[child].size() <= d) b[child].resize(d + 1);
                b[child][d] += values[v];
            }
        }
        all.reserve(n);
        branch.reserve(n);
        for (int c = 0; c < n; ++c) {
            all_size[c] = a[c].size();
            branch_size[c] = b[c].size();
            all.emplace_back(a[c]);
            branch.emplace_back(b[c]);
        }
    }

    void add(int v, long long x) {
        for (int i = 0; i < (int)cd.path[v].size(); ++i) {
            all[cd.path[v][i]].add(cd.dist[v][i], x);
            if (i > 0) branch[cd.path[v][i - 1]].add(cd.dist[v][i], x);
        }
    }

    long long query(int v, int l, int r) {
        if (l >= r) return 0;
        long long answer = 0;
        for (int i = 0; i < (int)cd.path[v].size(); ++i) {
            int c = cd.path[v][i], d = cd.dist[v][i];
            answer += sum(all[c], all_size[c], (long long)l - d, (long long)r - d);
            if (i == 0) continue;
            int child = cd.path[v][i - 1];
            answer -= sum(branch[child], branch_size[child], (long long)l - d, (long long)r - d);
        }
        return answer;
    }
};

/**
 * @brief 木の頂点加算・距離区間和
 */
