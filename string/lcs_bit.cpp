int LCS_bit(string &s, string &t){
    const int n = s.size(), m = t.size(), bit_sz = (m+63)>>6;
    vector<vector<ull>> p(256, vector<ull>(bit_sz, 0));
    for (int i = 0; i < m; ++i) {
        p[t[i]][i>>6] |= (1ULL << (i&63));
    }
    vector<ull> dp(bit_sz);
    for (int i = 0; i < m; ++i) {
        if(s[0] == t[i]) {
            dp[i>>6] |= (1ULL << (i&63));
            break;
        }
    }
    for (int i = 1; i < n; ++i) {
        ull shift = 1, sub = 0, tmp_sub = 0;
        for (int j = 0; j < bit_sz; ++j) {
            ull x = dp[j] | p[s[i]][j], y = (dp[j] << 1)|shift, z = x;
            shift = dp[j] >> 63;
            tmp_sub = z < sub;
            z -= sub;
            sub = tmp_sub;
            sub += z < y;
            z -= y;
            dp[j] = (z^x)&x;
        }
        dp[m>>6] &= (1LLU << (m&63))-1;
    }
    int ans = 0;
    for (int i = 0; i < bit_sz; ++i) {
        ans += __builtin_popcountll(dp[i]);
    }
    return ans;
}