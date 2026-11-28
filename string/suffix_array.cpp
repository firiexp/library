#ifndef FIRIEXP_LIBRARY_STRING_SUFFIX_ARRAY_CPP
#define FIRIEXP_LIBRARY_STRING_SUFFIX_ARRAY_CPP

vector<int> convert(string const& s){
    int n = s.size();
    std::vector<int> s2(n);
    for (int i = 0; i < n; i++) s2[i] = static_cast<unsigned char>(s[i]);
    return s2;
}

vector<int> suffix_array(const vector<int> &s, int upper){
    int n = s.size();
    if (n <= 1) return vector<int>(n, 0);
    if (n == 2) return s[0] < s[1] ? vector<int>{0, 1} : vector<int>{1, 0};
    vector<int> sa(n);
    vector<bool> ls(n);
    for (int i = n-2; i >= 0; --i) ls[i] = (s[i] == s[i+1]) ? ls[i+1] : (s[i] < s[i+1]);
    vector<int> sum_l(upper+1), sum_s(upper+1);
    for (int i = 0; i < n; ++i) (ls[i] ? sum_l[s[i]+1] : sum_s[s[i]])++;
    for (int i = 0; i <= upper; ++i) {
        sum_s[i] += sum_l[i];
        if(i < upper) sum_l[i+1] += sum_s[i];
    }

    auto induce = [&](vector<int> const& lms){
        fill(sa.begin(),sa.end(), -1);
        vector<int> buf(upper+1);
        copy(sum_s.begin(),sum_s.end(), buf.begin());
        for (auto &&i : lms) if(i != n) sa[buf[s[i]]++] = i;
        copy(sum_l.begin(),sum_l.end(), buf.begin());
        sa[buf[s.back()]++] = n-1;
        for (int i = 0; i < n; ++i) {
            int v = sa[i];
            if(v >= 1 && !ls[v-1]) sa[buf[s[v-1]]++] = v-1;
        }
        copy(sum_l.begin(),sum_l.end(), buf.begin());
        for (int i = n - 1; i >= 0; --i) {
            int v = sa[i];
            if(v >= 1 && ls[v-1]) sa[--buf[s[v-1]+1]] = v-1;
        }
    };
    vector<int> lms_map(n+1, -1);
    int m = 0;
    for (int i = 1; i < n; ++i) if(!ls[i-1] && ls[i]) lms_map[i] = m++;
    vector<int> lms;
    lms.reserve(m);
    for (int i = 1; i < n; ++i) if(!ls[i-1] && ls[i]) lms.emplace_back(i);
    induce(lms);
    if(m){
        vector<int> sorted_lms;
        sorted_lms.reserve(m);
        for (auto &&i : sa) if(~lms_map[i]) sorted_lms.emplace_back(i);
        vector<int> rec_s(m);
        int rec_upper = 0;
        rec_s[lms_map[sorted_lms.front()]] = 0;
        for (int i = 1; i < m; ++i) {
            int l = sorted_lms[i-1], r = sorted_lms[i];
            int end_l = (lms_map[l]+1) < m ? lms[lms_map[l]+1] : n;
            int end_r = (lms_map[r]+1) < m ? lms[lms_map[r]+1] : n;
            bool same = true;
            if(end_l-l != end_r-r) same = false;
            else {
                while(l < end_l && s[l] == s[r]) l++, r++;
                if(l == n || s[l] != s[r]) same = false;
            }
            rec_upper += !same;
            rec_s[lms_map[sorted_lms[i]]] = rec_upper;
        }
        vector<int> rec_sa;
        if (rec_upper + 1 == m) {
            rec_sa.resize(m);
            for (int i = 0; i < m; ++i) rec_sa[rec_s[i]] = i;
        } else {
            rec_sa = suffix_array(rec_s, rec_upper);
        }
        for (int i = 0; i < m; ++i) sorted_lms[i] = lms[rec_sa[i]];
        induce(sorted_lms);
    }
    return sa;
}

template<class T> vector<int> suffix_array(vector<T> const& s){
    int n = s.size();
    vector<int> idx(n);
    iota(idx.begin(),idx.end(), 0);
    sort(idx.begin(),idx.end(), [&](int l, int r){ return s[l] < s[r]; });
    vector<int> z(n);
    int now = 0;
    for (int i = 0; i < n; ++i) {
        if(i && s[idx[i-1]] != s[idx[i]]) now++;
        z[idx[i]] = now;
    }
    return suffix_array(z, now);
}

vector<int> suffix_array(const string& s){
    return suffix_array(convert(s), 255);
}

namespace suffix_array_detail {

template<class Sequence>
vector<int> lcp_with_rank(const Sequence& s, const vector<int>& sa, const vector<int>& rank) {
    int n = s.size();
    if (n <= 1) return {};
    vector<int> lcp(n-1);
    int h = 0;
    for (int i = 0; i < n; ++i) {
        if(h > 0) h--;
        if(!rank[i]) continue;
        int j = sa[rank[i]-1];
        while(j+h < n && i+h < n && s[j+h] == s[i+h]) h++;
        lcp[rank[i]-1] = h;
    }
    return lcp;
}

template<class Sequence>
vector<int> build_lcp(const Sequence& s, const vector<int>& sa) {
    int n = s.size();
    if (n <= 1) return {};
    vector<int> rank(n);
    for (int i = 0; i < n; ++i) rank[sa[i]] = i;
    return lcp_with_rank(s, sa, rank);
}

}

template<class T>
vector<int> lcp(const vector<T>& s, const vector<int>& sa) {
    return suffix_array_detail::build_lcp(s, sa);
}

vector<int> lcp(string const& s, vector<int> const& sa){
    return suffix_array_detail::build_lcp(s, sa);
}

template<class Sequence = string>
class SuffixArray {
    Sequence text;
    vector<int> sa;
    mutable vector<long long> distinct_prefix_sum;
    using Pattern = conditional_t<is_same_v<Sequence, string>, string_view, const Sequence&>;

public:
    explicit SuffixArray(Sequence s) : text(move(s)), sa(suffix_array(text)) {}

    int size() const { return sa.size(); }
    int operator[](int i) const { return sa[i]; }
    const vector<int>& array() const { return sa; }
    vector<int> lcp() const { return ::lcp(text, sa); }

    pair<int, int> kth_substring(long long k) const {
        if (k < 0 || sa.empty()) return {-1, -1};
        if (distinct_prefix_sum.empty()) {
            auto common = lcp();
            distinct_prefix_sum.reserve(size());
            long long total = 0;
            for (int i = 0; i < size(); ++i) {
                int shared = i == 0 ? 0 : common[i - 1];
                total += size() - sa[i] - shared;
                distinct_prefix_sum.push_back(total);
            }
        }
        auto it = upper_bound(distinct_prefix_sum.begin(), distinct_prefix_sum.end(), k);
        if (it == distinct_prefix_sum.end()) return {-1, -1};
        int start = sa[it - distinct_prefix_sum.begin()];
        int shorter_by = int(*it - 1 - k);
        return {start, size() - shorter_by};
    }

    pair<int, int> equal_range(Pattern pattern) const {
        int n = size();
        if (pattern.empty() || !n) return {0, n};
        auto less = [](const auto& a, const auto& b) {
            if constexpr (is_same_v<Sequence, string>) return (unsigned char)a < (unsigned char)b;
            else return a < b;
        };
        if (pattern.size() == 1) {
            auto l = lower_bound(sa.begin(), sa.end(), pattern[0], [&](int pos, const auto& c) {
                return less(text[pos], c);
            });
            auto r = upper_bound(l, sa.end(), pattern[0], [&](const auto& c, int pos) {
                return less(c, text[pos]);
            });
            return {int(l - sa.begin()), int(r - sa.begin())};
        }
        auto match = [&](int pos, int common) {
            int limit = min<size_t>(n - pos, pattern.size());
            for (; common < limit; ++common) {
                const auto& a = text[pos + common];
                const auto& b = pattern[common];
                if (less(a, b) || less(b, a)) break;
            }
            return common;
        };
        auto compare = [&](int pos, int& common) {
            common = match(pos, common);
            if (size_t(common) == pattern.size()) return 0;
            if (pos + common == n || less(text[pos + common], pattern[common])) return -1;
            return 1;
        };
        auto bound = [&](int l, int r, int common, bool upper) {
            while (l < r) {
                int m = l + (r - l) / 2;
                int matched = match(sa[m], common);
                bool full = size_t(matched) == pattern.size();
                if (!full) common = matched;
                if (full == upper) l = m + 1;
                else r = m;
            }
            return l;
        };
        int left_lcp = 0, right_lcp = 0;
        int first = compare(sa.front(), left_lcp);
        if (first > 0) return {0, 0};
        int last = compare(sa.back(), right_lcp);
        if (last < 0) return {n, n};
        if (first == 0) return {0, last == 0 ? n : bound(1, n - 1, right_lcp, true)};
        if (last == 0) return {bound(1, n - 1, left_lcp, false), n};

        int l = 1, r = n - 1;
        while (l < r) {
            int m = l + (r - l) / 2;
            int common = min(left_lcp, right_lcp);
            int order = compare(sa[m], common);
            if (order < 0) {
                l = m + 1;
                left_lcp = common;
            } else if (order > 0) {
                r = m;
                right_lcp = common;
            } else {
                return {bound(l, m, left_lcp, false), bound(m + 1, r, right_lcp, true)};
            }
        }
        return {l, l};
    }
};

SuffixArray(const char*) -> SuffixArray<string>;

/**
 * @brief Suffix Array
 */

#endif
