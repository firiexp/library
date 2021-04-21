using Ar2 = array<int, 2>;
void argsort(vector<Ar2> &v){
    auto pos = [&](Ar2 &x) -> int { if(x[1]) return x[1] < 0 ? -1 : 1; else return x[0] > 0; };
    sort(v.begin(),v.end(), [&](Ar2 a, Ar2 b){
        if(pos(a) != pos(b)) return pos(a) < pos(b);
        return (ll)a[0]*b[1] > (ll)a[1]*b[0];
    });
}
