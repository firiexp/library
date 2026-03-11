vector<int> Z_algorithm(const string &s){
    int n = (int)s.size();
    vector<int> res(n);
    if (n == 0) return res;
    res[0] = n;
    for (int i = 1, l = 0, r = 0; i < n; ++i) {
        if (i < r) res[i] = min(r - i, res[i - l]);
        while (i + res[i] < n && s[res[i]] == s[i + res[i]]) ++res[i];
        if (r < i + res[i]) {
            l = i;
            r = i + res[i];
        }
    }
    return res;
}

/**
 * @brief Z-Algorithm
 */
