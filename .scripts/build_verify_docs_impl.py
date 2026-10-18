#!/usr/bin/env python3

from __future__ import annotations

import argparse
import pathlib
import re
import sys

ROOT = pathlib.Path(__file__).resolve().parent.parent
sys.path.insert(0, str(ROOT / '.scripts'))
from verification_impl import STATE, docs_results, read_json, resolve, write_json
from competitive_verifier.documents.builder import DocumentBuilder
from competitive_verifier.documents.render import RenderJob
from competitive_verifier.models import VerificationInput, VerifyCommandResult


class WorkingTreeDocumentBuilder(DocumentBuilder):
    def write_code_docs(self, *, config_yml, index_md, static_dir):
        sources = {path for path in self.verifications.files if path.suffix == '.cpp' and path.is_file()}
        sources.update(path.relative_to(ROOT) for path in (ROOT / '_md').rglob('*.md'))
        for job in RenderJob.enumerate_jobs(sources=sources, verifications=self.verifications,
                                          result=self.result, config=config_yml, index_md=index_md):
            destination = self.destination_dir / job.destination_name
            destination.parent.mkdir(parents=True, exist_ok=True)
            with destination.open('wb') as stream:
                job.write_to(stream)


def main():
    parser = argparse.ArgumentParser(description='Generate Jekyll sources from competitive-verifier results.')
    parser.add_argument('--result', type=pathlib.Path, default=STATE / 'result.json')
    parser.add_argument('--destination', type=pathlib.Path, default=STATE / '_jekyll')
    parser.add_argument('--require-success', action='store_true', help='reject missing, stale or failed verification results')
    parser.add_argument('-j', '--jobs', type=int, default=8)
    args = parser.parse_args()
    if args.jobs < 1:
        parser.error('jobs must be positive')
    resolved = resolve(args.jobs, bundle=True)
    for value in resolved["files"].values():
        for source in value.get("additonal_sources", []):
            path = ROOT / source["path"]
            path.write_bytes(re.sub(rb'^#line\s+\d+\s+"(?:[^"\\]|\\.)*"\s*\n', b"", path.read_bytes(), flags=re.MULTILINE))
    write_json(STATE / 'verify-files.json', resolved)
    result = docs_results(resolved, read_json(args.result, {}), require_success=args.require_success)
    write_json(STATE / 'docs-result.json', result)
    builder = WorkingTreeDocumentBuilder(verifications=VerificationInput.model_validate(resolved),
                                        result=VerifyCommandResult.model_validate(result),
                                        docs_dir=STATE / 'docs', destination_dir=args.destination,
                                        include=None, exclude=None)
    return int(not builder.build())


if __name__ == '__main__':
    raise SystemExit(main())
