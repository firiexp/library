#define PROBLEM "https://judge.yosupo.jp/problem/many_aplusb"

#include <cctype>
#include <random>
#include <stack>
#include <string>
#include <vector>
using namespace std;

#include "../util/fastio.cpp"
#include "../util/parse.cpp"

namespace {

int precedence(char op) {
    if (op == '+' || op == '-') return 1;
    if (op == '*' || op == '/') return 2;
    return -1;
}

bool apply_top(stack<int> &values, stack<char> &ops) {
    if (values.size() < 2 || ops.empty()) return false;
    int rhs = values.top();
    values.pop();
    int lhs = values.top();
    values.pop();
    char op = ops.top();
    ops.pop();
    if (op == '+') values.push(lhs + rhs);
    else if (op == '-') values.push(lhs - rhs);
    else if (op == '*') values.push(lhs * rhs);
    else {
        if (rhs == 0) return false;
        values.push(lhs / rhs);
    }
    return true;
}

bool eval_bruteforce(const string &s, int &res) {
    stack<int> values;
    stack<char> ops;
    int n = (int)s.size();
    for (int i = 0; i < n; ) {
        if (isdigit(s[i])) {
            int x = 0;
            while (i < n && isdigit(s[i])) {
                x = x * 10 + (s[i] - '0');
                ++i;
            }
            values.push(x);
            continue;
        }
        if (s[i] == '(') {
            ops.push(s[i]);
            ++i;
            continue;
        }
        if (s[i] == ')') {
            while (!ops.empty() && ops.top() != '(') {
                if (!apply_top(values, ops)) return false;
            }
            if (ops.empty() || ops.top() != '(') return false;
            ops.pop();
            ++i;
            continue;
        }
        while (!ops.empty() && precedence(ops.top()) >= precedence(s[i])) {
            if (!apply_top(values, ops)) return false;
        }
        ops.push(s[i]);
        ++i;
    }
    while (!ops.empty()) {
        if (ops.top() == '(') return false;
        if (!apply_top(values, ops)) return false;
    }
    if (values.size() != 1) return false;
    res = values.top();
    return true;
}

string gen_expr(mt19937 &rng, int depth);

string gen_number(mt19937 &rng) {
    return to_string(uniform_int_distribution<int>(0, 30)(rng));
}

string gen_factor(mt19937 &rng, int depth) {
    if (depth == 0 || uniform_int_distribution<int>(0, 3)(rng) == 0) {
        return gen_number(rng);
    }
    return "(" + gen_expr(rng, depth - 1) + ")";
}

string gen_muldiv(mt19937 &rng, int depth) {
    int cnt = uniform_int_distribution<int>(1, 3)(rng);
    string s = gen_factor(rng, depth);
    for (int i = 1; i < cnt; ++i) {
        char op = uniform_int_distribution<int>(0, 1)(rng) ? '*' : '/';
        s += op;
        s += gen_factor(rng, depth);
    }
    return s;
}

string gen_expr(mt19937 &rng, int depth) {
    int cnt = uniform_int_distribution<int>(1, 3)(rng);
    string s = gen_muldiv(rng, depth);
    for (int i = 1; i < cnt; ++i) {
        char op = uniform_int_distribution<int>(0, 1)(rng) ? '+' : '-';
        s += op;
        s += gen_muldiv(rng, depth);
    }
    return s;
}

bool check_parse(const string &s) {
    int expected;
    if (!eval_bruteforce(s, expected)) return true;
    string t = s;
    t.push_back('\0');
    state cur = t.begin();
    int actual = expr(cur);
    return actual == expected && *cur == '\0';
}

}  // namespace

int main() {
    {
        mt19937 rng(123456789);
        vector<string> samples = {
            "0",
            "1+2*3",
            "(1+2)*3",
            "8/3",
            "18/(2+1)",
            "30-4*5+6",
            "2*(3+(4*5))",
            "24/(3*2)-7"
        };
        for (const string &s : samples) {
            if (!check_parse(s)) return 1;
        }
        for (int depth = 0; depth <= 4; ++depth) {
            for (int trial = 0; trial < 600; ++trial) {
                string s = gen_expr(rng, depth);
                if (!check_parse(s)) return 1;
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
