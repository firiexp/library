u64 Isqrt(u64 const &x){
    u64 ret = (u64)sqrtl(x);
    while(ret > 0 && ret*ret > x) --ret;
    while(x - ret*ret > 2*ret) ++ret;
    return ret;
}