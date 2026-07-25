#!/usr/bin/env python3

IMPL = __file__.rsplit("/", 2)[0] + "/.scripts/measure_verify_impl.py"


with open(IMPL, "rb") as fh:
    code = compile(fh.read(), IMPL, "exec")
__file__ = IMPL
exec(code, globals())
