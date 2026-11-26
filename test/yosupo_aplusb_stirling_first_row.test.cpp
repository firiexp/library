#define STANDALONE

#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using uint = unsigned;
using ull = unsigned long long;
#include "../fps/taylor_shift.cpp"
#include "../math/combinatorics/stirling_first_row.cpp"

int main() {
    vector<mint> signed_row = {1}, unsigned_row = {1};
    for (int n = 0; n <= 256; ++n) {
        assert(stirling_first_row(n) == signed_row);
        assert(stirling_first_row_unsigned(n) == unsigned_row);
        vector<mint> next_signed(n + 2), next_unsigned(n + 2);
        for (int k = 0; k <= n; ++k) {
            next_signed[k] -= n * signed_row[k];
            next_signed[k + 1] += signed_row[k];
            next_unsigned[k] += n * unsigned_row[k];
            next_unsigned[k + 1] += unsigned_row[k];
        }
        signed_row.swap(next_signed);
        unsigned_row.swap(next_unsigned);
    }
}
