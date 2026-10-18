from __future__ import annotations

import json
import pathlib
import resource
import subprocess
import sys
import time
import threading


def main():
    phase, directory, timeout, *args = sys.argv[1:]
    directory = pathlib.Path(directory)
    directory.mkdir(parents=True, exist_ok=True)
    started = time.perf_counter()
    process = subprocess.Popen(args)
    timed_out = threading.Event()

    def expire():
        if process.poll() is None:
            timed_out.set()
            process.kill()

    timer = threading.Timer(float(timeout), expire) if float(timeout) else None
    if timer:
        timer.start()
    try:
        code = process.wait()
    finally:
        if timer:
            timer.cancel()
    if timed_out.is_set():
        print(f'TLE: exceeded {timeout} seconds', file=sys.stderr)
        code = 124
    report = {'elapsed': time.perf_counter() - started, 'returncode': code,
              'memory': resource.getrusage(resource.RUSAGE_CHILDREN).ru_maxrss / 1024}
    (directory / f'{phase}.json').write_text(json.dumps(report) + '\n')
    return code if code >= 0 else 128 - code


if __name__ == '__main__':
    raise SystemExit(main())
