vector<vector<mint>> comb_table(int n, int m){
    vector<vector<mint>> res(n+1, vector<mint>(m+1, 0));
    for (int i = 0; i <= n; ++i){
        res[i][0] = 1;
        for(int j = 1; j <= i; j ++){
			res[i][j] = res[i-1][j-1] + res[i-1][j];
        }
    }
    return res;
}