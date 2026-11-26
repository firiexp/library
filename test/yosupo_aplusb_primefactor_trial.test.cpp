#define STANDALONE

#include <bits/stdc++.h>
#include <sys/resource.h>
#include <sys/wait.h>
#include <unistd.h>
using namespace std;
using uint = unsigned;

#include "../math/prime/primefactor.cpp"

void require(bool ok) {
    if (!ok) std::abort();
}

template<class T>
void check_invalid(T n) {
    pid_t child = fork();
    require(child >= 0);
    if (child == 0) {
        const rlimit no_core{0, 0};
        if (setrlimit(RLIMIT_CORE, &no_core) != 0) _exit(1);
        alarm(2);
        prime_factor_trial(n);
        _exit(0);
    }
    int status;
    require(waitpid(child, &status, 0) == child);
    require(WIFSIGNALED(status) && WTERMSIG(status) == SIGABRT);
}

vector<uint> trial_factor(uint n) {
    vector<uint> result;
    for (uint p = 2; p <= n / p; ++p) {
        while (n % p == 0) {
            result.push_back(p);
            n /= p;
        }
    }
    if (n != 1) result.push_back(n);
    return result;
}

void check(uint n) {
    const auto expected = trial_factor(n);
    require(prime_factor_trial(n) == expected);
    require(prime_factor_trial(static_cast<int>(n)) == vector<int>(expected.begin(), expected.end()));
    require(prime_factor_trial(static_cast<long long>(n)) == vector<long long>(expected.begin(), expected.end()));
    unsigned long long product = 1;
    for (uint p : expected) product *= p;
    require(product == n);
}

int main() {
    check_invalid(-1);
    check_invalid(0);
    check_invalid(LLONG_MIN);
    check_invalid(1U << 31);
    check_invalid(INT_MAX + 1LL);
    check_invalid((1LL << 32) + 3);
    check_invalid(ULLONG_MAX);
    for (uint n = 1; n <= 100000; ++n) check(n);
    for (uint n = 1; n <= (1U << 30); n *= 2) check(n);
    for (uint p = 2; p * p <= INT_MAX; ++p) {
        if (trial_factor(p).size() == 1) {
            require(prime_factor_trial(p * p) == vector<uint>({p, p}));
        }
    }
    for (uint n : {3U, 17U, 30030U, 59049U, 387420489U, 1000000000U, 1000000007U,
                   2U * 499999993U, 31991U * 31991U, 31991U * 31981U, 32000U * 32000U,
                   32003U * 32003U, 46337U * 46327U, 46337U * 46337U,
                   static_cast<uint>(INT_MAX - 1), static_cast<uint>(INT_MAX)}) {
        check(n);
    }
    mt19937 random(271);
    for (int tc = 0; tc < 3000; ++tc) check(1 + random() % INT_MAX);
}
