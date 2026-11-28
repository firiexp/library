#define STANDALONE

#define main snippet_main
#include "../snippets/template.cpp"
#undef main
#include <unistd.h>

namespace library_io {
#include "../util/fastio.cpp"
}

template<class S, class P, class T>
void check_value(S &in, P &out, T expected) {
    T value{};
    in.read(value);
    if (value != expected) abort();
    out.print(value);
    out.print('\n');
}

template<class S, class P>
void check_values() {
    using I = __int128;
    using U = unsigned __int128;
    rewind(stdin);
    S in;
    P out;
    check_value(in, out, numeric_limits<I>::min());
    check_value(in, out, numeric_limits<I>::max());
    check_value(in, out, numeric_limits<U>::max());
    check_value(in, out, I(0));
    check_value(in, out, U(0));
    check_value(in, out, I(999999999999999LL));
    check_value(in, out, U(1000000000000000LL));
    check_value(in, out, I(-9999999999999999LL));
    check_value(in, out, U(10000000000000000LL));
    check_value(in, out, I(9999999999999999999ULL));
    check_value(in, out, -I(10000000000000000000ULL));
    check_value(in, out, (U(1) << 64) + 1);
    check_value(in, out, numeric_limits<long long>::min());
    check_value(in, out, numeric_limits<unsigned long long>::max());
    check_value(in, out, -42);
    check_value(in, out, true);
    check_value(in, out, 'Z');
}

int main() {
    const string values =
        "-170141183460469231731687303715884105728\n"
        "170141183460469231731687303715884105727\n"
        "340282366920938463463374607431768211455\n"
        "0\n0\n999999999999999\n1000000000000000\n"
        "-9999999999999999\n10000000000000000\n"
        "9999999999999999999\n-10000000000000000000\n18446744073709551617\n"
        "-9223372036854775808\n18446744073709551615\n-42\n1\nZ\n";
    FILE *output = tmpfile();
    if (!output || dup2(fileno(output), STDOUT_FILENO) < 0) abort();
    for (int padding : {0, 1024}) {
        FILE *input = tmpfile();
        string data = string(padding, ' ') + values;
        if (!input || fputs(data.c_str(), input) < 0 || fflush(input)) abort();
        if (dup2(fileno(input), STDIN_FILENO) < 0) abort();
        check_values<library_io::Scanner, library_io::Printer>();
        check_values<Scanner, Printer>();
        fclose(input);
    }
    if (fflush(stdout)) abort();
    rewind(output);
    for (int i = 0; i < 4; ++i) {
        for (char c : values) {
            if (fgetc(output) != c) abort();
        }
    }
    if (fgetc(output) != EOF) abort();
    fclose(output);
}
