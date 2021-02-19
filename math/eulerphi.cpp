int eulerphi(int x){
    int phi = x, xx = x;
    for (int i = 2; i * i <= x; ++i) {
        if (xx % i == 0) {
            phi -= phi / i;
            while(xx % i == 0) xx /= i;
        }
    }
    if(xx > 1) phi -= phi/xx;
    return phi;
}
