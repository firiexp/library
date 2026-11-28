#include "centroid_decomposition_query_helper.cpp"

class RangeContourSum {
    vector<vector<int>> path, dist;
    vector<size_t> offset;
    vector<long long> bit;

    template<class F>
    void for_each_row(int v, F f) const {
        for (int i = 0; i < (int)path[v].size(); ++i) {
            size_t all_row = 2 * size_t(path[v][i]);
            f(all_row, dist[v][i]);
            if (i > 0) {
                size_t branch_row = 2 * size_t(path[v][i - 1]) + 1;
                f(branch_row, dist[v][i]);
            }
        }
    }

public:
    RangeContourSum(const vector<vector<int>> &g, const vector<long long> &values)
        : offset(2 * g.size() + 1) {
        {
            CentroidDecompositionQueryHelper cd(g.size());
            cd.G = g;
            cd.build();
            path = move(cd.path);
            dist = move(cd.dist);
        }
        for (int v = 0; v < (int)g.size(); ++v)
            for_each_row(v, [&](size_t row, int d) {
                offset[row + 1] = max(offset[row + 1], size_t(d) + 1);
            });
        partial_sum(offset.begin(), offset.end(), offset.begin());
        bit.resize(offset.back());
        for (int v = 0; v < (int)g.size(); ++v)
            for_each_row(v, [&](size_t row, int d) { bit[offset[row] + d] += values[v]; });
        for (size_t row = 0; row + 1 < offset.size(); ++row) {
            size_t begin = offset[row], size = offset[row + 1] - begin;
            for (size_t i = 0; i < size; ++i) {
                size_t parent = i | (i + 1);
                if (parent < size) bit[begin + parent] += bit[begin + i];
            }
        }
    }

    void add(int v, long long x) {
        for_each_row(v, [&](size_t row, int d) {
            size_t begin = offset[row], size = offset[row + 1] - begin;
            for (size_t i = d; i < size; i |= i + 1) bit[begin + i] += x;
        });
    }

    long long query(int v, int l, int r) {
        if (l >= r) return 0;
        long long answer = 0;
        for_each_row(v, [&](size_t row, int d) {
            size_t begin = offset[row];
            long long size = offset[row + 1] - begin;
            long long left = max(0LL, (long long)l - d);
            long long right = min(size, (long long)r - d);
            if (left >= right) return;
            long long positive = 0, negative = 0;
            for (; right > 0; right &= right - 1) positive += bit[begin + right - 1];
            for (; left > 0; left &= left - 1) negative += bit[begin + left - 1];
            if (row & 1) answer -= positive - negative;
            else answer += positive - negative;
        });
        return answer;
    }
};

/**
 * @brief 木の頂点加算・距離区間和
 */
