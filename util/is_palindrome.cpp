bool is_parindrome(const string &s, char c = '?'){
    auto n = s.length();
    for (int i = 0; i < (n+1)/2; ++i) {
        if(s[i] == c || s[n-i-1] == c) continue;
        if(s[i] != s[n-i-1]) return false;
    }
    return true;
}