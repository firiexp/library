#define PROBLEM "https://judge.yosupo.jp/problem/aplusb"

#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using uint = unsigned;
using ull = unsigned long long;
#include "../util/fastio.cpp"
#include "../fps/polynomial_interpolation.cpp"

mint horner(const vector<mint> &coefficients, mint x) {
    mint result = 0;
    for (int i = (int)coefficients.size() - 1; i >= 0; --i) result = result * x + coefficients[i];
    return result;
}

void self_check() {
    assert(polynomial_interpolation({}, {}).v.empty());
    mt19937 random(64);
    const int sizes[] = {1, 2, 3, 31, 32, 33, 63, 64, 65, 127, 128, 129, 149};
    for (int tc = 0; tc < 1000; ++tc) {
        int n = tc < 13 ? sizes[tc] : 1 + random() % 149;
        vector<mint> coefficients(n), xs(n), ys(n);
        for (auto &c : coefficients) c = random() % 998244353;
        if (tc % 7 == 0) fill(coefficients.begin(), coefficients.end(), mint(0));
        else if (tc % 5 == 0) fill(coefficients.begin() + n / 2, coefficients.end(), mint(0));
        mint offset = random() % 998244353, step = 1 + random() % 998244352;
        for (int i = 0; i < n; ++i) xs[i] = offset + step * mint(i);
        shuffle(xs.begin(), xs.end(), random);
        for (int i = 0; i < n; ++i) ys[i] = horner(coefficients, xs[i]);
        auto original_xs = xs, original_ys = ys;
        auto result = polynomial_interpolation(xs, ys);
        assert(result.v == coefficients);
        assert(xs == original_xs && ys == original_ys);
        assert(result.multipoint_eval(xs) == ys);

        int count = tc % 9 == 0 ? 0 : random() % 150;
        vector<mint> points(count), expected(count);
        for (int i = 0; i < count; ++i) {
            points[i] = tc % 3 == 0 ? mint(0) : mint(random() % 998244353);
            expected[i] = horner(coefficients, points[i]);
        }
        assert(result.multipoint_eval(points) == expected);
        assert(poly().multipoint_eval(points) == vector<mint>(count));
    }
}

int main() {
    self_check();
    Scanner sc;
    Printer pr;
    int a, b;
    sc.read(a, b);
    pr.println(a + b);
}
