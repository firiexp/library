#include "pow.cpp"
int primitive_root(int m) {
    if (m == 2) return 1;
    int divs[20] = {2};
    int cnt = 1;
    int x = (m-1)/2;
    while (x%2 == 0) x /= 2;
    for (ll i = 3; i*i <= x; i += 2) {
        if (x%i == 0) {
            divs[cnt++] = i;
            while (x%i == 0) x /= i;
        }
    }
    if (x > 1) divs[cnt++] = x;
    for (int g = 2;; g++) {
        bool ok = true;
        for (int i = 0; i < cnt && ok; i++) {
            ok |= pow_(g, (m-1)/divs[i], m) != 1;
        }
        if (ok) return g;
    }
}