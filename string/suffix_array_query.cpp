#ifndef FIRIEXP_LIBRARY_STRING_SUFFIX_ARRAY_QUERY_CPP
#define FIRIEXP_LIBRARY_STRING_SUFFIX_ARRAY_QUERY_CPP

#include "suffix_array.cpp"
#include "../datastructure/sparsetable.cpp"

class SuffixArrayQuery {
    struct Minimum {
        using T = int;
        static int f(int a, int b) { return min(a, b); }
    };
    int n;
    vector<int> rank;
    SparseTable<Minimum> rmq;

    template<class Sequence>
    void initialize(const Sequence& s) {
        n = (int)s.size();
        auto sa = suffix_array(s);
        rank.resize(n);
        for (int i = 0; i < n; ++i) rank[sa[i]] = i;
        rmq.build(suffix_array_detail::lcp_with_rank(s, sa, rank));
    }

public:
    explicit SuffixArrayQuery(const string& s) { initialize(s); }

    template<class T>
    explicit SuffixArrayQuery(const vector<T>& s) { initialize(s); }

    int suffix_rank(int i) const { return rank[i]; }

    int lce(int i, int j) const {
        if (i == j) return n - i;
        if (i == n || j == n) return 0;
        int a = rank[i], b = rank[j];
        if (a > b) swap(a, b);
        return rmq.query(a, b);
    }

    int compare(int l1, int r1, int l2, int r2) const {
        int len1 = r1 - l1, len2 = r2 - l2;
        if (lce(l1, l2) >= min(len1, len2))
            return (len1 > len2) - (len1 < len2);
        return rank[l1] < rank[l2] ? -1 : 1;
    }
};

#endif

/**
 * @brief 最長共通接頭辞・部分文字列の辞書順比較
 */
