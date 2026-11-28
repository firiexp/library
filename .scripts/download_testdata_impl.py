from __future__ import annotations

import logging
import pathlib
import sys
import time

from competitive_verifier.download.download import parse_urls
from competitive_verifier.log import configure_stderr_logging, group
from competitive_verifier.models import VerificationInput
from competitive_verifier.oj import problem_from_url
from requests.exceptions import ConnectionError, Timeout


def download_problem(url):
    problem = problem_from_url(url)
    if problem is None:
        raise ValueError(f'unsupported problem URL: {url}')
    for attempt in range(1, 4):
        try:
            if not problem.download_system_cases():
                raise RuntimeError(f'no test data for {url}')
            return
        except (ConnectionError, Timeout) as error:
            if attempt == 3:
                raise
            delay = 2 ** attempt
            print(f'{url}: {error}; retrying in {delay}s', file=sys.stderr, flush=True)
            time.sleep(delay)


def download_testdata(urls_or_files):
    success = True
    for url in sorted(parse_urls(urls_or_files)):
        with group(f'download: {url}'):
            try:
                download_problem(url)
            except Exception:
                logging.exception('failed to download %s', url)
                success = False
    return success


if __name__ == '__main__':
    configure_stderr_logging(logging.INFO)
    resolved = VerificationInput.parse_file_relative(pathlib.Path(sys.argv[1]))
    raise SystemExit(0 if download_testdata(resolved.files.values()) else 1)
