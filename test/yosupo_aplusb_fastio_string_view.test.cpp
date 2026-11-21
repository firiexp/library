#define STANDALONE

#include <unistd.h>
#define main snippet_main
#include "../snippets/template.cpp"
#undef main

namespace fastio {
#include "../util/fastio.cpp"
}

int main() {
    FILE *capture = tmpfile();
    if (!capture || dup2(fileno(capture), STDOUT_FILENO) < 0) return 1;

    const string_view bytes("!ab\0cd?", 7);
    const array<string_view, 3> views{"one", {}, bytes.substr(1, 5)};
    fastio::Printer out;
    out.println(string_view{}, string("plain"), string_view("hello"), views);
    out.flush();
    dout.puts(string_view{}, string("plain"), string_view("hello"), views);
    dout.flush();

    fflush(stdout);
    rewind(capture);
    const string line = " plain hello one  ab\0cd\n"s;
    const string expected = line + line;
    string actual(expected.size(), '\0');
    size_t n = fread(actual.data(), 1, actual.size(), capture);
    bool ok = n == expected.size() && actual == expected && fgetc(capture) == EOF;
    fclose(capture);
    return ok ? 0 : 1;
}
