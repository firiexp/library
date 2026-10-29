#define PROBLEM "https://judge.yosupo.jp/problem/product_of_polynomial_sequence"

#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using uint = unsigned;
using ull = unsigned long long;
#include "../util/fastio.cpp"
#include "../fps/product_polynomials.cpp"

int main() {
    Scanner sc;
    Printer pr;
    int n;
    sc.read(n);
    vector<poly> factors(n);
    for (auto& factor : factors) {
        int degree;
        sc.read(degree);
        factor.v.resize(degree + 1);
        for (auto& x : factor.v) {
            int value;
            sc.read(value);
            x = value;
        }
    }
    auto product = product_polynomials(move(factors));
    for (int i = 0; i < product.size(); ++i) {
        pr.print(product[i].val);
        pr.print(i + 1 == product.size() ? '\n' : ' ');
    }
}
