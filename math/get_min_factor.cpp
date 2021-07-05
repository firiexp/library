vector<int> get_min_factor(int n) {
    if(n <= 1) return vector<int>{0, 1};
    vector<bool> prime(n+1, true);
    vector<int> min_factor(n+1, 0);
    min_factor[0] = 0, min_factor[1] = 1;
    prime[0] = false; prime[1] = false;
    for(ll i = 2; i <= n; i++){
        if(prime[i]) {
            min_factor[i] = i;
            for(ll j = i << 1; j <= n; j += i) {
                prime[j] = false;
                if(min_factor[j] == 0) min_factor[j] = i;
            }
        }
    }
    return min_factor;
}
