#ifndef FIRIEXP_LIBRARY_MATH_PRIME_TWO_SQUARE_SUM_CPP
#define FIRIEXP_LIBRARY_MATH_PRIME_TWO_SQUARE_SUM_CPP

#include "primefactor_ll.cpp"
#include "../modular/mod_sqrt.cpp"
#include "../isqrt.cpp"
#include "../../util/rle.cpp"

namespace two_square_sum_detail {

using Gaussian = pair<long long, long long>;

Gaussian multiply(Gaussian a, Gaussian b) {
    auto [x, y] = a;
    auto [u, v] = b;
    return {(__int128)x * u - (__int128)y * v, (__int128)x * v + (__int128)y * u};
}

Gaussian split_prime(long long p) {
    long long a = p, b = mod_sqrt(-1, p);
    while ((__int128)b * b > p) {
        long long r = a % b;
        a = b;
        b = r;
    }
    return {b, Isqrt(p - b * b)};
}

}

vector<pair<long long, long long>> two_square_sum(long long n) {
    using two_square_sum_detail::Gaussian;
    using two_square_sum_detail::multiply;
    assert(n >= 0);
    if (n == 0) return {{0, 0}};

    auto factors = RLE(prime_factor(n));
    long long scale = 1;
    bool diagonal = false;
    for (auto [p, e] : factors) {
        if (p % 4 == 1) continue;
        if (p % 4 == 3 && e % 2) return {};
        if (p == 2) diagonal = e % 2;
        for (int i = 0; i < e / 2; ++i) scale *= p;
    }

    vector<Gaussian> products{{scale, diagonal ? scale : 0}};
    for (auto [p, e] : factors) {
        if (p % 4 != 1) continue;
        Gaussian prime = two_square_sum_detail::split_prime(p);
        vector<Gaussian> powers{{1, 0}};
        for (int i = 0; i < e; ++i) powers.push_back(multiply(powers.back(), prime));
        vector<Gaussian> next;
        next.reserve(products.size() * (e + 1));
        for (int i = 0; i <= e; ++i) {
            auto [u, v] = powers[e - i];
            Gaussian factor = multiply(powers[i], {u, -v});
            for (Gaussian z : products) next.push_back(multiply(z, factor));
        }
        products.swap(next);
    }

    vector<Gaussian> result;
    result.reserve(products.size() + 1);
    for (auto [x, y] : products) {
        while (x <= 0 || y < 0) tie(x, y) = Gaussian{-y, x};
        result.emplace_back(x, y);
        if (y == 0) result.emplace_back(0, x);
    }
    return result;
}

#endif

/**
 * @brief 二平方和表現の列挙
 */
