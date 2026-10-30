#define STANDALONE

#include <bits/stdc++.h>
using namespace std;
#include "../util/parse.cpp"

void check(const string& s, int expected) {
    const string original = s;
    assert(parse_expression(s) == expected);
    assert(parse_expression(string(s)) == expected);
    string wrapped = "999" + s + "999";
    assert(parse_expression(string_view(wrapped).substr(3, s.size())) == expected);
    vector<char> buffer(s.begin(), s.end());
    assert(parse_expression(string_view(buffer.data(), buffer.size())) == expected);
    assert(s == original);
    assert(wrapped == "999" + s + "999");
    assert(string(buffer.begin(), buffer.end()) == original);
    string terminated = s;
    terminated.push_back('\0');
    state cur = terminated.cbegin();
    assert(expr(cur) == expected);
    assert(cur == terminated.cbegin() + s.size());
}

pair<string, int> generate(mt19937& rng, int depth) {
    if (!depth || rng() % 4 == 0) {
        int value = rng() % 100;
        return {to_string(value), value};
    }
    auto [left, a] = generate(rng, depth - 1);
    auto [right, b] = generate(rng, depth - 1);
    char op = string("+-*/")[rng() % 4];
    if (op == '/' && b == 0) op = '+';
    long long value;
    if (op == '+') value = (long long)a + b;
    else if (op == '-') value = (long long)a - b;
    else if (op == '*') value = (long long)a * b;
    else value = a / b;
    if (abs(value) > 1000000) return {left, a};
    return {"(" + left + op + right + ")", int(value)};
}

int main() {
    assert(parse_expression("2*(3+4)") == 14);
    for (auto [s, value] : vector<pair<string, int>>{
             {"0", 0}, {"12345", 12345}, {"000123", 123}, {"(42)", 42},
             {"2*(3+4)", 14}, {"2+3*4", 14}, {"20-6-3", 11},
             {"100/5/2", 10}, {"20/3*2", 12}, {"7/(0-3)", -2},
             {"(0-7)/3", -2}, {"(0-7)/(0-3)", 2}, {"1-2*3+4/2", -3},
             {"2147483647", INT_MAX}, {"0-2147483647-1", INT_MIN},
             {"((1+2)*(3+4)-(8/2))", 17}}) check(s, value);
    mt19937 rng(314);
    for (int trial = 0; trial < 5000; ++trial) {
        auto [s, value] = generate(rng, 6);
        check(s, value);
    }
    string long_expression = "1";
    for (int i = 1; i < 100000; ++i) long_expression += "+1";
    check(long_expression, 100000);
    check(string(200, '(') + "1" + string(200, ')'), 1);
}
