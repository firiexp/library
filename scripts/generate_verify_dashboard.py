#!/usr/bin/env python3

IMPL = __file__.rsplit("/", 2)[0] + "/.scripts/generate_verify_dashboard_impl.py"


with open(IMPL, "rb") as fh:
    code = compile(fh.read(), IMPL, "exec")
__file__ = IMPL
exec(code, globals())
