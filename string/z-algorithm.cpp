vector<int> Z_algorithm(const string &s){
    int n = (int)s.size();
    vector<int> res(n);
    if (n == 0) return res;
    res[0] = n;
    for (int i = 1, j = 0; i < n; ++i) {
        int &k = res[i];
        if (j + res[j] > i) k = min(res[i - j], j + res[j] - i);
        while (i + k < n && s[k] == s[i + k]) ++k;
        if (i + k > j + res[j]) j = i;
    }
    return res;
}
