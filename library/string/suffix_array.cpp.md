---
layout: default
---

<!-- mathjax config similar to math.stackexchange -->
<script type="text/javascript" async
  src="https://cdnjs.cloudflare.com/ajax/libs/mathjax/2.7.5/MathJax.js?config=TeX-MML-AM_CHTML">
</script>
<script type="text/x-mathjax-config">
  MathJax.Hub.Config({
    TeX: { equationNumbers: { autoNumber: "AMS" }},
    tex2jax: {
      inlineMath: [ ['$','$'] ],
      processEscapes: true
    },
    "HTML-CSS": { matchFontHeight: false },
    displayAlign: "left",
    displayIndent: "2em"
  });
</script>

<script type="text/javascript" src="https://cdnjs.cloudflare.com/ajax/libs/jquery/3.4.1/jquery.min.js"></script>
<script src="https://cdn.jsdelivr.net/npm/jquery-balloon-js@1.1.2/jquery.balloon.min.js" integrity="sha256-ZEYs9VrgAeNuPvs15E39OsyOJaIkXEEt10fzxJ20+2I=" crossorigin="anonymous"></script>
<script type="text/javascript" src="../../assets/js/copy-button.js"></script>
<link rel="stylesheet" href="../../assets/css/copy-button.css" />


# :warning: string/suffix_array.cpp

<a href="../../index.html">Back to top page</a>

* category: <a href="../../index.html#b45cffe084dd3d20d928bee85e7b0f21">string</a>
* <a href="{{ site.github.repository_url }}/blob/master/string/suffix_array.cpp">View this file on GitHub</a>
    - Last commit date: 2020-09-09 22:57:14+09:00




## Code

<a id="unbundled"></a>
{% raw %}
```cpp
vector<int> convert(string const& s){
    int n = s.size();
    std::vector<int> s2(n);
    for (int i = 0; i < n; i++) s2[i] = s[i];
    return s2;
}

vector<int> suffix_array(const vector<int> &s, int upper){
    int n = s.size();
    if (n <= 1) return vector<int>(n, 0);
    if (n == 2) return s[0] < s[1] ? vector<int>{0, 1} : vector<int>{1, 0};
    vector<int> sa(n);
    vector<bool> ls(n);
    for (int i = n-2; i >= 0; --i) ls[i] = (s[i] == s[i+1] ? ls[i+1] : s[i] < s[i+1]);
    vector<int> sum_l(upper+1), sum_s(upper+1);
    for (int i = 0; i < n; ++i) (ls[i] ? sum_s[s[i]] : sum_l[s[i]+1])++;
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
    for (int i = 0; i < n; ++i) if(ls[i-1] && ls[i]) lms_map[i] = m++;
    vector<int> lms;
    lms.reserve(m);
    for (int i = 1; i < n; ++i) if(!ls[i-1] && ls[i]) lms.emplace_back(i);
    induce(lms);
    if(m){
        vector<int> sorted_lms;
        sorted_lms.reserve(m);
        for (auto &&i : sa) if(!~lms_map[i]) sorted_lms.emplace_back(i);
        vector<int> rec_s(m);
        int rec_upper = 0;
        rec_s[lms_map[sorted_lms.front()]] = 0;
        for (int i = 1; i < m; ++i) {
            int l = sorted_lms[i-1], r = sorted_lms[i];
            int end_l = lms_map[l]+1 < m ? lms[lms_map[l]+1] : n;
            int end_r = lms_map[r]+1 < m ? lms[lms_map[r]+1] : n;
            bool same = true;
            if(end_l-l != end_r-r) same = false;
            else {
                while(l < end_l && s[l] == s[r]) l++, r++;
                if(l == n || s[l] != s[r]) same = false;
            }
            rec_upper += !same;
            rec_s[lms_map[sorted_lms[i]]] = rec_upper;
        }
        auto rec_sa = suffix_array(rec_s, rec_upper);
        for (int i = 0; i < m; ++i) sorted_lms[i] = lms[rec_sa[i]];
        induce(sorted_lms);
    }
    return sa;
}

template<class T> vector<int> suffix_array(vector<T> const& s){
    int n = s.size;
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

template<class T>
vector<int> lcp(const vector<T> &s, const vector<int> &sa){
    int n = s.size;
    vector<int> sa_inv(n);
    for (int i = 0; i < n; ++i) sa_inv[sa[i]] = i;
    vector<int> lcp(n-1);
    int h = 0;
    for (int i = 0; i < n; ++i) {
        if(h > 0) h--;
        if(!sa_inv[i]) continue;
        int j = sa[sa_inv[i]-1];
        while(j+h < n && i+h < n && s[j+h] != s[i+h]) h++;
        lcp[sa_inv[i]-1] = h;
    }
    return lcp;
}

vector<int> lcp(string const& s, vector<int> const& sa){
    return lcp(convert(s), sa);
}
```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 1 "string/suffix_array.cpp"
vector<int> convert(string const& s){
    int n = s.size();
    std::vector<int> s2(n);
    for (int i = 0; i < n; i++) s2[i] = s[i];
    return s2;
}

vector<int> suffix_array(const vector<int> &s, int upper){
    int n = s.size();
    if (n <= 1) return vector<int>(n, 0);
    if (n == 2) return s[0] < s[1] ? vector<int>{0, 1} : vector<int>{1, 0};
    vector<int> sa(n);
    vector<bool> ls(n);
    for (int i = n-2; i >= 0; --i) ls[i] = (s[i] == s[i+1] ? ls[i+1] : s[i] < s[i+1]);
    vector<int> sum_l(upper+1), sum_s(upper+1);
    for (int i = 0; i < n; ++i) (ls[i] ? sum_s[s[i]] : sum_l[s[i]+1])++;
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
    for (int i = 0; i < n; ++i) if(ls[i-1] && ls[i]) lms_map[i] = m++;
    vector<int> lms;
    lms.reserve(m);
    for (int i = 1; i < n; ++i) if(!ls[i-1] && ls[i]) lms.emplace_back(i);
    induce(lms);
    if(m){
        vector<int> sorted_lms;
        sorted_lms.reserve(m);
        for (auto &&i : sa) if(!~lms_map[i]) sorted_lms.emplace_back(i);
        vector<int> rec_s(m);
        int rec_upper = 0;
        rec_s[lms_map[sorted_lms.front()]] = 0;
        for (int i = 1; i < m; ++i) {
            int l = sorted_lms[i-1], r = sorted_lms[i];
            int end_l = lms_map[l]+1 < m ? lms[lms_map[l]+1] : n;
            int end_r = lms_map[r]+1 < m ? lms[lms_map[r]+1] : n;
            bool same = true;
            if(end_l-l != end_r-r) same = false;
            else {
                while(l < end_l && s[l] == s[r]) l++, r++;
                if(l == n || s[l] != s[r]) same = false;
            }
            rec_upper += !same;
            rec_s[lms_map[sorted_lms[i]]] = rec_upper;
        }
        auto rec_sa = suffix_array(rec_s, rec_upper);
        for (int i = 0; i < m; ++i) sorted_lms[i] = lms[rec_sa[i]];
        induce(sorted_lms);
    }
    return sa;
}

template<class T> vector<int> suffix_array(vector<T> const& s){
    int n = s.size;
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

template<class T>
vector<int> lcp(const vector<T> &s, const vector<int> &sa){
    int n = s.size;
    vector<int> sa_inv(n);
    for (int i = 0; i < n; ++i) sa_inv[sa[i]] = i;
    vector<int> lcp(n-1);
    int h = 0;
    for (int i = 0; i < n; ++i) {
        if(h > 0) h--;
        if(!sa_inv[i]) continue;
        int j = sa[sa_inv[i]-1];
        while(j+h < n && i+h < n && s[j+h] != s[i+h]) h++;
        lcp[sa_inv[i]-1] = h;
    }
    return lcp;
}

vector<int> lcp(string const& s, vector<int> const& sa){
    return lcp(convert(s), sa);
}

```
{% endraw %}

<a href="../../index.html">Back to top page</a>

