vector<int> Z_algorithm(const string &s){
    vector<int> res(s.size());
    res.front() = s.size();
    for (int i = 1, j = 0; i < s.size(); ++i) {
        if(i + res[i-j] < j + res[j]) res[i] = res[i-j];
        else {
            int k = max(0, j + res[j]-i);
            while(i + k < s.size() && s[k] == s[i+k]) ++k;
            res[i] = k;
            j = i;
        }
    }
    return res;
}
