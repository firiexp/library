template<class T>
class SegmentTreeBeats {
    void add_(int x, T val){
        if(!val) return;
        auto& now = seg[x];
        now.sum += val*now.len;
        now.mn += val; now.mx += val; now.add += val;
        if(now.mn2 != INF<T>) now.mn2 += val;
        if(now.mx2 != -INF<T>) now.mx2 += val;
    }
    void chmin_(int x, T val){
        if(val >= seg[x].mx) return;
        auto& now = seg[x];
        now.sum += now.mxc*(val-now.mx);
        if(now.mn == now.mx) now.mn = val;
        else if(now.mn2 == now.mx) now.mn2 = val;
        now.mx = val;
    }
    void chmax_(int x, T val){
        if(val <= seg[x].mn) return;
        auto& now = seg[x];
        now.sum += now.mnc*(val-now.mn);
        if(now.mx == now.mn) now.mx = val;
        else if(now.mx2 == now.mn) now.mx2 = val;
        now.mn = val;
    }
    void get(int x){
        M& now = seg[x], &l = seg[(x<<1)|0], &r = seg[(x<<1)|1];
        now.sum = l.sum + r.sum;
        now.mn = min(l.mn, r.mn);
        now.mx = max(l.mx, r.mx);
        now.len = l.len + r.len;
        if(l.mn < r.mn) now.mnc = l.mnc, now.mn2 = min(l.mn2, r.mn);
        else if(r.mn < l.mn) now.mnc = r.mnc, now.mn2 = min(r.mn2, l.mn);
        else now.mnc = l.mnc + r.mnc, now.mn2 = min(l.mn2, r.mn2);
        if(l.mx > r.mx) now.mxc = l.mxc, now.mx2 = max(l.mx2, r.mx);
        else if(r.mx > l.mx) now.mxc = r.mxc, now.mx2 = max(r.mx2, l.mx);
        else now.mxc = l.mxc + r.mxc, now.mx2 = max(l.mx2, r.mx2);
    }
    void eval(int x){
        auto &now = seg[x];
        for (int i = 0; x < n && i < 2; ++i) {
            add_((x<<1)|i, now.add);
            chmin_((x<<1)|i, now.mx);
            chmax_((x<<1)|i, now.mn);
        }
        now.add = 0;
    }
    void thrust(int k){ for (int i = height-1; i >= 1; --i) eval(k>>i); }
    void recalc(int k) { k = k >> __builtin_ctz(k); while(k >>= 1) get(k);}

    void in_chmin(int x, T val) {
        if(seg[x].mx2 < val) chmin_(x, val);
        else {
            eval(x);
            in_chmin((x<<1)|0, val);
            in_chmin((x<<1)|1, val);
            get(x);
        }
    }
    void in_chmax(int x, T val) {
        if(seg[x].mn2 > val) chmax_(x, val);
        else {
            eval(x);
            in_chmax((x<<1)|0, val);
            in_chmax((x<<1)|1, val);
            get(x);
        }
    }
public:
#define RANGEX(NAME, INFUNC) \
void NAME(int a, int b, T val) { \
    thrust(a += n); \
    thrust(b += n); \
    for(int l = a, r = b; l < r; l >>=1, r>>=1) { \
        if (l & 1) INFUNC(l++, val); \
        if (r & 1) INFUNC(--r, val); \
    } \
    recalc(a); \
    recalc(b); \
}
    RANGEX(chmin, in_chmin)
    RANGEX(chmax, in_chmax)
    RANGEX(add, add_)
#undef RANGEX
    T sum(int a, int b) {
        thrust(a += n);
        thrust(b += n);
        T res = 0;
        for(int l = a, r = b; l < r; l >>=1, r>>=1) {
            if (l & 1) res += seg[l++].sum;
            if (r & 1) res += seg[--r].sum;
        }
        return res;
    }
    struct M {
        T sum, mx, mx2, mxc, mn, mn2, mnc, len, add;
        M() : mx2(-INF<T>), mxc(1), mn2(INF<T>), mnc(1), add(0) {};
    };
    vector<M> seg;
    int n, height;
    SegmentTreeBeats() = default;
    SegmentTreeBeats(const vector<T>& v){
        n = 1, height = 1;
        while(n < v.size()) n <<= 1, height++;
        seg.resize(2*n);
        for (int i = 0; i < v.size(); ++i) {
            seg[i+n].sum = seg[i+n].mx = seg[i+n].mn = v[i];
            seg[i+n].len = 1;
        }
        for (int i = n-1; i >= 1; --i) get(i);
    }
};
