ull Isqrt(ull const &x){
    ull ret = (ull)sqrtl(x);
    while(ret > 0 && ret*ret > x) --ret;
    while(x - ret*ret > 2*ret) ++ret;
    return ret;
}