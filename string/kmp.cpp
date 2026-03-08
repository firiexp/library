vector<int> kmp_table(const string &s){
    int n = s.size();
    vector<int> table(n + 1);
    table[0] = -1;
    for (int i = 0, j = -1; i < n;) {
        while(j >= 0 && s[i] != s[j]) j = table[j];
        i++, j++;
        table[i] = j;
    }
    return table;
}

vector<int> kmp_search(const string &text, const string &pattern){
    int n = text.size(), m = pattern.size();
    vector<int> res;
    if(pattern.empty()){
        res.resize(n + 1);
        iota(res.begin(), res.end(), 0);
        return res;
    }
    auto table = kmp_table(pattern);
    for (int i = 0, j = 0; i < n;) {
        while(j >= 0 && text[i] != pattern[j]) j = table[j];
        i++, j++;
        if(j == m){
            res.emplace_back(i - j);
            j = table[j];
        }
    }
    return res;
}

/**
 * @brief KMP法
 * @docs _md/kmp.md
 */
