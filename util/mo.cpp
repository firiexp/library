const int B = 400;

struct Query {
    int l, r, no;
    Query(int l, int r, int no) : l(l), r(r), no(no) {}
    Query() : l(0), r(0), no(0) {}
    bool operator<(const Query &a) const {
        int ablock = this->l / B, bblock = a.l / B;
        if(ablock != bblock) return ablock < bblock;
        if(ablock & 1) return this->r < a.r;
        else return this->r > a.r;
    }
};
/*
for (auto &&X : query) {
    while(X.l < l) g(--l);
    while(r < X.r) f(r++);
    while(l < X.l) g(l++);
    while(X.r < r) f(--r);
    ans[X.no] = ans;
}
*/