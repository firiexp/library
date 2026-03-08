#!/usr/bin/env python3

IMPL = __file__.rsplit("/", 2)[0] + "/.scripts/sync_doc_titles_impl.py"


if __name__ == "__main__":
    with open(IMPL, "rb") as fh:
        code = compile(fh.read(), IMPL, "exec")
    exec(code, {"__name__": "__main__", "__file__": IMPL})
