#include <string>
#include <utility>
#include <vector>
using namespace std;

vector<pair<int, int>> lyndon_factorization(const string &s) {
    int n = (int)s.size();
    vector<pair<int, int>> res;
    for (int i = 0; i < n;) {
        int j = i + 1, k = i;
        while (j < n && s[k] <= s[j]) {
            if (s[k] < s[j]) k = i;
            else ++k;
            ++j;
        }
        int len = j - k;
        while (i <= k) {
            res.emplace_back(i, i + len);
            i += len;
        }
    }
    return res;
}

/**
 * @brief Lyndon分解(Lyndon Factorization)
 */
