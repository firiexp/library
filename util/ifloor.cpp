template<class T>T ifloor(T x, T y){
    return x/y-(x%y ? (x < 0)^(y < 0) : 0);
}

template<class T>inline T iceil(T x, T y){
    return x/y+(x%y ? (x >= 0)^(y < 0) : 0);
}
