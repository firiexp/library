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


# :warning: library/independentset.cpp

<a href="../../index.html">Back to top page</a>

* category: <a href="../../index.html#d521f765a49c72507257a2620612ee96">library</a>
* <a href="{{ site.github.repository_url }}/blob/master/library/independentset.cpp">View this file on GitHub</a>
    - Last commit date: 2020-04-26 16:08:15+09:00




## Code

<a id="unbundled"></a>
{% raw %}
```cpp
class IndependentSet {
    int n;
    vector<vector<int>> G;
    void dfs(int x, vector<bool> &visited, vector<bool> &gcan, vector<bool> &alive){
        stack<int> s;
        s.emplace(x);
        while(!s.empty()){
            int y = s.top();
            visited[y] = true;
            gcan[y] = true;
            s.pop();
            for (auto &&i : G[y]) {
                if(!visited[i] && alive[i]) s.emplace(i);
            }
        }
    }

    int ConnectedCase(vector<bool> can) {
        int pMax = -1, pMin = -1, Max = -1, Min = n+1, num = 0;
        for (int i = 0; i < n; ++i) {
            if(!can[i]) continue;
            ++num;
            int tnum = 0;
            for (auto &&j : G[i]) if(can[j]) ++tnum;
            if(Max < tnum) Max = tnum, pMax = i;
            if(Min > tnum) Min = tnum, pMin = i;
        }
        if(num == 1) return 1;
        if(Max <= 2){
            if(Min == 1) return (num+1)/2;
            else return num/2;
        }
        int ans = 0;
        vector<bool> ncan = can;
        if(Min < 2){
            ncan[pMin] = false;
            for (auto &&i : G[pMin]) ncan[i] = false;
            ans = max(ans, GeneralCase(ncan) + 1);
        }else {
            ncan[pMax] = false;
            for (auto &&i : G[pMax]) ncan[i] = false;
            int temp = GeneralCase(ncan);
            ans = max(ans, temp+1);
            ncan = can;
            ncan[pMax] = false;
            ans = max(ans, GeneralCase(ncan));
        }
        return ans;
    }

    int GeneralCase(vector<bool> alive) {
        if(n <= 1) return n;
        vector<bool> visited(n, 0);
        int res = 0;
        for (int i = 0; i < n; ++i) {
            if(!visited[i] && alive[i]){
                vector<bool> gcan(n, false);
                dfs(i, visited, gcan, alive);
                res += ConnectedCase(gcan);
            }
        }
        return res;
    }
public:
    explicit IndependentSet(int n): n(n), G(n) {}
    void add_edge(int u, int v){
        G[u].emplace_back(v);
        G[v].emplace_back(u);
    }
    int stable_set() {
        vector<bool> alive(n, true);
        return GeneralCase(alive);
    }
};
```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 1 "library/independentset.cpp"
class IndependentSet {
    int n;
    vector<vector<int>> G;
    void dfs(int x, vector<bool> &visited, vector<bool> &gcan, vector<bool> &alive){
        stack<int> s;
        s.emplace(x);
        while(!s.empty()){
            int y = s.top();
            visited[y] = true;
            gcan[y] = true;
            s.pop();
            for (auto &&i : G[y]) {
                if(!visited[i] && alive[i]) s.emplace(i);
            }
        }
    }

    int ConnectedCase(vector<bool> can) {
        int pMax = -1, pMin = -1, Max = -1, Min = n+1, num = 0;
        for (int i = 0; i < n; ++i) {
            if(!can[i]) continue;
            ++num;
            int tnum = 0;
            for (auto &&j : G[i]) if(can[j]) ++tnum;
            if(Max < tnum) Max = tnum, pMax = i;
            if(Min > tnum) Min = tnum, pMin = i;
        }
        if(num == 1) return 1;
        if(Max <= 2){
            if(Min == 1) return (num+1)/2;
            else return num/2;
        }
        int ans = 0;
        vector<bool> ncan = can;
        if(Min < 2){
            ncan[pMin] = false;
            for (auto &&i : G[pMin]) ncan[i] = false;
            ans = max(ans, GeneralCase(ncan) + 1);
        }else {
            ncan[pMax] = false;
            for (auto &&i : G[pMax]) ncan[i] = false;
            int temp = GeneralCase(ncan);
            ans = max(ans, temp+1);
            ncan = can;
            ncan[pMax] = false;
            ans = max(ans, GeneralCase(ncan));
        }
        return ans;
    }

    int GeneralCase(vector<bool> alive) {
        if(n <= 1) return n;
        vector<bool> visited(n, 0);
        int res = 0;
        for (int i = 0; i < n; ++i) {
            if(!visited[i] && alive[i]){
                vector<bool> gcan(n, false);
                dfs(i, visited, gcan, alive);
                res += ConnectedCase(gcan);
            }
        }
        return res;
    }
public:
    explicit IndependentSet(int n): n(n), G(n) {}
    void add_edge(int u, int v){
        G[u].emplace_back(v);
        G[v].emplace_back(u);
    }
    int stable_set() {
        vector<bool> alive(n, true);
        return GeneralCase(alive);
    }
};

```
{% endraw %}

<a href="../../index.html">Back to top page</a>

