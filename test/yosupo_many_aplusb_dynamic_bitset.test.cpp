#define PROBLEM "https://judge.yosupo.jp/problem/many_aplusb"

#include <algorithm>
#include <random>
#include <vector>
using namespace std;

#include "../util/fastio.cpp"
#include "../datastructure/dynamic_bitset.cpp"

int brute_find_first(const vector<int> &v) {
    for (int i = 0; i < (int)v.size(); ++i) if (v[i]) return i;
    return -1;
}

int brute_find_next(const vector<int> &v, int k) {
    for (int i = k + 1; i < (int)v.size(); ++i) if (v[i]) return i;
    return -1;
}

int brute_count(const vector<int> &v) {
    int res = 0;
    for (int x : v) res += x;
    return res;
}

vector<int> brute_shift_left(const vector<int> &v, int s) {
    vector<int> res(v.size());
    for (int i = 0; i < (int)v.size(); ++i) {
        if (i - s >= 0) res[i] = v[i - s];
    }
    return res;
}

vector<int> brute_shift_right(const vector<int> &v, int s) {
    vector<int> res(v.size());
    for (int i = 0; i < (int)v.size(); ++i) {
        if (i + s < (int)v.size()) res[i] = v[i + s];
    }
    return res;
}

bool same(const DynamicBitset &bs, const vector<int> &v) {
    if (bs.size() != (int)v.size()) return false;
    for (int i = 0; i < (int)v.size(); ++i) {
        if (bs.test(i) != (bool)v[i]) return false;
    }
    if (bs.count() != brute_count(v)) return false;
    if (bs.any() != (brute_count(v) > 0)) return false;
    if (bs.none() != (brute_count(v) == 0)) return false;
    if (bs.all() != (brute_count(v) == (int)v.size())) return false;
    if (bs.find_first() != brute_find_first(v)) return false;
    int cur = bs.find_first();
    int want = brute_find_first(v);
    if (cur != want) return false;
    while (cur != -1) {
        cur = bs.find_next(cur);
        want = brute_find_next(v, want);
        if (cur != want) return false;
    }
    return true;
}

int main() {
    {
        mt19937 rng(123456789);
        for (int n = 0; n <= 130; ++n) {
            for (int trial = 0; trial < 200; ++trial) {
                DynamicBitset bs(n);
                vector<int> v(n, 0);
                for (int step = 0; step < 200; ++step) {
                    int op = uniform_int_distribution<int>(0, 12)(rng);
                    int k = n == 0 ? 0 : uniform_int_distribution<int>(0, n - 1)(rng);
                    int s = n == 0 ? 0 : uniform_int_distribution<int>(0, n + 5)(rng);
                    if (op == 0 && n) {
                        bs.set(k);
                        v[k] = 1;
                    } else if (op == 1 && n) {
                        bs.reset(k);
                        v[k] = 0;
                    } else if (op == 2 && n) {
                        bs.flip(k);
                        v[k] ^= 1;
                    } else if (op == 3 && n) {
                        int x = uniform_int_distribution<int>(0, 1)(rng);
                        bs.assign(k, x);
                        v[k] = x;
                    } else if (op == 4) {
                        bs.set();
                        fill(v.begin(), v.end(), 1);
                    } else if (op == 5) {
                        bs.reset();
                        fill(v.begin(), v.end(), 0);
                    } else if (op == 6) {
                        bs.flip();
                        for (int &x : v) x ^= 1;
                    } else if (op == 7) {
                        bs <<= s;
                        v = brute_shift_left(v, s);
                    } else if (op == 8) {
                        bs >>= s;
                        v = brute_shift_right(v, s);
                    } else {
                        DynamicBitset other(n);
                        vector<int> w(n);
                        for (int i = 0; i < n; ++i) {
                            w[i] = uniform_int_distribution<int>(0, 1)(rng);
                            if (w[i]) other.set(i);
                        }
                        if (op == 9) {
                            bs &= other;
                            for (int i = 0; i < n; ++i) v[i] &= w[i];
                        } else if (op == 10) {
                            bs |= other;
                            for (int i = 0; i < n; ++i) v[i] |= w[i];
                        } else if (op == 11) {
                            bs ^= other;
                            for (int i = 0; i < n; ++i) v[i] ^= w[i];
                        } else {
                            if ((bs << s).count() != brute_count(brute_shift_left(v, s))) return 1;
                            if ((bs >> s).count() != brute_count(brute_shift_right(v, s))) return 1;
                        }
                    }
                    if (!same(bs, v)) return 1;
                }
            }
        }
    }

    Scanner sc;
    Printer pr;
    int t;
    sc.read(t);
    while (t--) {
        long long a, b;
        sc.read(a, b);
        pr.writeln(a + b);
    }
    return 0;
}
