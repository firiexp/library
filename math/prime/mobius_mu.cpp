int mobius_mu(ll n) {
	int res = 0;
	for(ll d = 2; d*d <= n; d++) {
		if(n % (d*d) == 0) return 0;
		else if(n % d == 0) n /= d, res++;
	}
	if(n != 1) res++;
	return res&1 ? -1 : 1;
}