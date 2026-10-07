vector<int> manacher(const string &s){
    vector<int> res(s.size());
    int i = 0, j = 0;
    while(i < s.size()){
        while(i >= j && i + j < s.size() && s[i-j] == s[i+j]) ++j;
        res[i] = j;
        int k = 1;
        while(i >= k && i + k < s.size() && k + res[i-k] < j) res[i+k] = res[i-k], ++k;
        i += k; j -= k;
    }
    return res;
}

struct PalindromeRadii {
    vector<int> odd, even;

    explicit PalindromeRadii(const string &s): odd(manacher(s)), even(s.size()) {
        int n = s.size(), l = 0, r = -1;
        for (int i = 0; i < n; ++i) {
            int k = i > r ? 0 : min(even[l + r - i + 1], r - i + 1);
            while (i - k - 1 >= 0 && i + k < n && s[i - k - 1] == s[i + k]) ++k;
            even[i] = k;
            if (i + k - 1 > r) {
                l = i - k;
                r = i + k - 1;
            }
        }
    }

    bool is_palindrome(int l, int r) const {
        int length = r - l;
        if (!length) return true;
        int center = l + length / 2;
        return length & 1 ? odd[center] >= length / 2 + 1 : even[center] >= length / 2;
    }
};
