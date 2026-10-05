#!/usr/bin/env python3

from __future__ import annotations

import argparse
import os
from pathlib import Path
import pty
import resource
import select
import shlex
import subprocess
import tempfile
import time
import tty


ROOT = Path(__file__).resolve().parents[1]
DRIVER = r'''
struct AssignedToken {
    string text;
    bool assign(const string &s) { text = s; return true; }
};

int main(int argc, char **argv) {
    Scanner in;
    string mode = argv[1];
    if (mode == "output") {
        Printer out;
        string method = argv[2];
        string s(stoi(argv[3]), 'x');
        if (method == "println") {
            out.FASTIO_PRINTLN(s);
        } else {
            s += "\nTAIL";
            if (method == "literal") out.print("READY\n");
            else if (method == "cstr") out.print(s.c_str());
            else if (method == "string") out.print(s);
            else if (method == "stream") out << s;
            else if (method == "char") {
                for (char c : s) out.print(c);
            }
        }
        int ack;
        in.read(ack);
        if (ack != 7) return 1;
    } else if (mode == "char") {
        char c;
        in.read(c);
        putchar(c);
    } else if (mode == "string") {
        string s;
        in.read(s);
        fwrite(s.data(), 1, s.size(), stdout);
    } else if (mode == "assign") {
        AssignedToken s;
        in.read(s);
        fwrite(s.text.data(), 1, s.text.size(), stdout);
    } else if (mode == "double") {
        double x;
        in.read(x);
        printf("%.17g", x);
    } else if (mode == "integer") {
        long long x;
        in.read(x);
        printf("%lld", x);
    }
}
'''


def pipe_cases():
    for length in (3, 131072, 131073, 262161):
        token = (b"abcXYZ09" * ((length + 7) // 8))[:length]
        for leading in (b"", b" \n\t"):
            for trailing in (b"", b" \n"):
                name = f"string-{length}-leading{len(leading)}-trailing{len(trailing)}"
                yield name, "string", leading + token + trailing, token
    for mode, tokens in (
        ("double", (b"1.25", b"-0.5", b"2.5e+10")),
        ("assign", (b"123456789012345678901234567890",)),
        ("integer", (b"0", b"7", b"-9223372036854775808", b"9223372036854775807")),
    ):
        for token in tokens:
            expected = b"25000000000" if token == b"2.5e+10" else token
            for leading in (b"", b" \n\t"):
                for trailing in (b"", b" \n"):
                    name = f"{mode}-{token.decode()}-leading{len(leading)}-trailing{len(trailing)}"
                    yield name, mode, leading + token + trailing, expected


def compile_driver(directory: Path, variant: str, cxx: str, sanitize: bool) -> Path:
    source = directory / f"{variant}.cpp"
    binary = directory / variant
    if variant == "util":
        prefix = '#include <bits/stdc++.h>\n#include "util/fastio.cpp"\n#define FASTIO_PRINTLN println\n'
    else:
        prefix = '#define main snippet_main\n#include "snippets/template.cpp"\n#undef main\n#define FASTIO_PRINTLN puts\n'
    source.write_text(prefix + DRIVER)
    flags = ["-std=c++17", "-O2"]
    if sanitize:
        flags += ["-g", "-fsanitize=address,undefined", "-fno-omit-frame-pointer", "-fno-pie", "-no-pie"]
    subprocess.run(shlex.split(cxx) + flags + ["-I", str(ROOT), str(source), "-o", str(binary)], check=True)
    return binary


def check_pipes(binary: Path) -> int:
    count = 0
    for name, mode, data, expected in pipe_cases():
        try:
            result = subprocess.run([str(binary), mode], input=data, capture_output=True, timeout=5, check=True)
        except (subprocess.TimeoutExpired, subprocess.CalledProcessError) as error:
            detail = (error.stderr or b"").decode(errors="replace")
            raise RuntimeError(f"{binary.name}: {name}: {error}\n{detail}") from error
        if result.stdout != expected:
            raise RuntimeError(f"{binary.name}: {name}: output mismatch")
        count += 1
    return count


def output_cases():
    yield "output-literal", "literal", 0, b"READY\n"
    for method in ("cstr", "string", "stream", "char", "println"):
        for length in (0, 4, 131071, 131072, 131073, 262161):
            tail = b"" if method == "println" else b"TAIL"
            yield f"output-{method}-{length}", method, length, b"x" * length + b"\n" + tail


def tty_input_cases():
    for mode, token in (("integer", b"7"), ("char", b"z"), ("string", b"abc"), ("double", b"1.25"), ("assign", b"12345678901234567890")):
        for leading in (b"", b"\n", b" \n\t \n\n"):
            yield f"tty-input-{mode}-leading{len(leading)}", mode, leading + token + b"\n", token


def read_exact(fd: int, size: int) -> bytes:
    result = bytearray()
    deadline = time.monotonic() + 5
    while len(result) < size:
        remaining = deadline - time.monotonic()
        if remaining <= 0 or not select.select([fd], [], [], remaining)[0]:
            raise RuntimeError(f"TTY output timed out after {len(result)} of {size} bytes")
        chunk = os.read(fd, size - len(result))
        if not chunk:
            raise RuntimeError("unexpected TTY EOF")
        result.extend(chunk)
    return bytes(result)


def check_outputs(binary: Path) -> int:
    count = 0
    for name, method, length, expected in output_cases():
        command = [str(binary), "output", method, str(length)]
        result = subprocess.run(command, input=b"7\n", capture_output=True, timeout=5, check=True)
        if result.stdout != expected:
            raise RuntimeError(f"{binary.name}: pipe-{name}: output mismatch")
        master, slave = pty.openpty()
        try:
            tty.setraw(slave)
            with subprocess.Popen(command, stdin=subprocess.PIPE, stdout=slave, stderr=subprocess.PIPE) as process:
                try:
                    prefix_size = expected.index(b"\n") + 1
                    actual = read_exact(master, prefix_size)
                    _, error = process.communicate(b"7\n", timeout=5)
                    if process.returncode:
                        raise RuntimeError(error.decode(errors="replace"))
                    actual += read_exact(master, len(expected) - prefix_size)
                    if actual != expected:
                        raise RuntimeError("output mismatch")
                except Exception as error:
                    process.kill()
                    process.communicate()
                    raise RuntimeError(f"{binary.name}: tty-{name}: {error}") from error
        finally:
            os.close(master)
            os.close(slave)
        count += 2
    return count


def check_tty_inputs(binary: Path) -> int:
    count = 0
    for name, mode, data, expected in tty_input_cases():
        master, slave = pty.openpty()
        try:
            tty.setraw(slave)
            with subprocess.Popen([str(binary), mode], stdin=slave, stdout=subprocess.PIPE, stderr=subprocess.PIPE) as process:
                try:
                    os.write(master, data)
                    actual, error = process.communicate(timeout=5)
                    if process.returncode:
                        raise RuntimeError(error.decode(errors="replace"))
                    if actual != expected:
                        raise RuntimeError(f"expected {expected!r}, got {actual!r}")
                except Exception as error:
                    process.kill()
                    process.communicate()
                    raise RuntimeError(f"{binary.name}: {name}: {error}") from error
        finally:
            os.close(master)
            os.close(slave)
        count += 1
    return count


def main() -> int:
    parser = argparse.ArgumentParser(description="Check util and snippet fastio EOF boundaries and TTY input/output.")
    parser.add_argument("--cxx", default=os.environ.get("CXX", "g++"), help="C++ compiler command")
    parser.add_argument("--variant", choices=("util", "snippet", "all"), default="all")
    parser.add_argument("--sanitize", action="store_true", help="enable ASan and UBSan")
    parser.add_argument("--list", action="store_true", help="list cases without compiling or running")
    args = parser.parse_args()
    variants = ("util", "snippet") if args.variant == "all" else (args.variant,)
    if args.list:
        for variant in variants:
            for name, *_ in pipe_cases():
                print(f"{variant}: {name}")
            for name, *_ in output_cases():
                print(f"{variant}: pipe-{name}")
                print(f"{variant}: tty-{name}")
            for name, *_ in tty_input_cases():
                print(f"{variant}: {name}")
        return 0
    if args.sanitize:
        soft, hard = resource.getrlimit(resource.RLIMIT_STACK)
        if soft == resource.RLIM_INFINITY:
            resource.setrlimit(resource.RLIMIT_STACK, (8 * 1024 * 1024, hard))
    with tempfile.TemporaryDirectory(prefix="check-fastio-") as directory:
        for variant in variants:
            binary = compile_driver(Path(directory), variant, args.cxx, args.sanitize)
            count = check_pipes(binary) + check_tty_inputs(binary) + check_outputs(binary)
            print(f"ok: {variant} fastio ({count} pipe/TTY cases)", flush=True)
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
