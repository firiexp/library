from __future__ import annotations

import contextlib
import os
import pathlib
import sys
import shutil
import subprocess
import tempfile
import unittest
from unittest.mock import patch

import verification_impl as verifier
from competitive_verifier.verify.verifier import content_hash
from competitive_verifier.models import VerificationInput
from generate_verify_dashboard_impl import parse_verification_result


class VerifierIntegrationTest(unittest.TestCase):
    def setUp(self):
        self.temporary = tempfile.TemporaryDirectory(prefix='library-verifier-test-')
        self.addCleanup(self.temporary.cleanup)
        self.root = pathlib.Path(self.temporary.name)
        self.previous_cwd = pathlib.Path.cwd()
        self.addCleanup(os.chdir, self.previous_cwd)
        self.state = self.root / '.competitive-verifier'
        self.state.mkdir()
        (self.root / 'test').mkdir()
        (self.root / '.scripts').mkdir()
        for name in verifier.VERIFY_INPUTS:
            destination = self.root / name
            destination.parent.mkdir(parents=True, exist_ok=True)
            shutil.copyfile(verifier.ROOT / name, destination)
        self.context = contextlib.ExitStack()
        self.addCleanup(self.context.close)
        for name, value in [('ROOT', self.root), ('STATE', self.state), ('CONFIG', self.state / 'config.toml'), ('SOURCE_DIRS', ('test',))]:
            self.context.enter_context(patch.object(verifier, name, value))
        os.chdir(self.root)
        (self.root / 'test/value.cpp').write_text('constexpr int value = 0;\n')
        (self.root / 'test/a.test.cpp').write_text('#define STANDALONE\n#include "value.cpp"\nint main() { return value; }\n')
        (self.root / 'test/b.test.cpp').write_text('#define STANDALONE\nint main() { return 0; }\n')

    def test_untracked_dependency_hash_skip_and_parallel_failure(self):
        resolved = verifier.resolve(jobs=2)
        self.assertEqual(verifier.test_paths(resolved), ['test/a.test.cpp', 'test/b.test.cpp'])
        output = self.state / 'result.json'
        self.assertEqual(verifier.verify(resolved, output=output, jobs=2, no_download=True), 0)
        self.assertEqual(verifier.verify(resolved, output=output, previous=output, jobs=2, no_download=True), 0)
        unchanged = verifier.read_json(output)
        self.assertTrue(all(not result['newest'] for result in unchanged['files'].values()))
        (self.root / 'test/value.cpp').write_text('constexpr int value = 1;\n')
        self.assertEqual(verifier.verify(resolved, output=output, previous=output, jobs=2, no_download=True), 1)
        failed = verifier.read_json(output)
        self.assertEqual(failed['files']['test/a.test.cpp']['verifications'][0]['status'], 'failure')
        self.assertFalse(failed['files']['test/b.test.cpp']['newest'])
        before = verifier.read_json(output)['files']['test/b.test.cpp']['verifications'][0]['last_execution_time']
        self.assertEqual(verifier.verify(verifier.select(resolved, ['test/b.test.cpp']), output=output, previous=output,
                                         force=True, jobs=1, no_download=True), 0)
        forced = verifier.read_json(output)
        self.assertEqual(forced['files']['test/a.test.cpp']['verifications'][0]['status'], 'failure')
        self.assertNotEqual(forced['files']['test/b.test.cpp']['verifications'][0]['last_execution_time'], before)
        (self.root / 'test/value.cpp').write_text('constexpr int value = 0;\n')
        self.assertEqual(verifier.verify(resolved, output=output, previous=output, jobs=2, no_download=True), 0)
        self.assertEqual(verifier.read_json(output)['files']['test/a.test.cpp']['verifications'][0]['status'], 'success')

    def test_docs_reject_missing_and_config_changes(self):
        resolved = verifier.resolve(jobs=2)
        model = VerificationInput.model_validate(resolved)
        result = {'total_seconds': 0, 'files': {p: {'content_hash': content_hash(model.transitive_depends_on[pathlib.Path(p)]),
                  'verifications': [{'status': 'success', 'elapsed': 0}]} for p in verifier.test_paths(resolved)}}
        verifier.docs_results(resolved, result, require_success=True)
        with (self.state / 'config.toml').open('a') as stream:
            stream.write('\n')
        with self.assertRaises(ValueError):
            verifier.docs_results(resolved, result, require_success=True)
        missing = verifier.docs_results(resolved, {})
        self.assertTrue(all(v['verifications'][0]['status'] == 'skipped' for v in missing['files'].values()))

    def test_docs_include_untracked_sources_and_markdown(self):
        import build_verify_docs_impl as docs
        from competitive_verifier.models import VerifyCommandResult
        subprocess.run(['git', 'init', '-q', str(self.root)], check=True)
        subprocess.run(['git', '-c', 'user.name=Verifier Test', '-c', 'user.email=verifier@example.invalid',
                        'commit', '--allow-empty', '-qm', 'fixture'], check=True)
        markdown = self.root / '_md/value.md'
        markdown.parent.mkdir()
        markdown.write_text('---\ndocumentation_of: //test/value.cpp\n---\nFixture explanation.\n')
        resolved = verifier.resolve(jobs=2)
        result = verifier.docs_results(resolved, {})
        with patch.object(docs, 'ROOT', self.root):
            builder = docs.WorkingTreeDocumentBuilder(verifications=VerificationInput.model_validate(resolved),
                result=VerifyCommandResult.model_validate(result), docs_dir=self.state / 'docs',
                destination_dir=self.state / '_jekyll', include=None, exclude=None)
            self.assertTrue(builder.build())
        self.assertTrue((self.state / '_jekyll/test/a.test.cpp.md').is_file())
        self.assertIn('Fixture explanation.', (self.state / '_jekyll/test/value.cpp.md').read_text())

    def test_measurement_exits_nonzero_for_failed_test_and_compilation(self):
        import generate_verify_dashboard_impl as dashboard
        for source, phase in [('int main() { return 1; }', 'done'), ('int main() { invalid; }', 'error')]:
            with self.subTest(phase=phase):
                (self.root / 'test/a.test.cpp').write_text('#define STANDALONE\n' + source + '\n')
                argv = ['measure', '--no-download', '--keep-going', '--json', str(self.state / 'report.json'),
                        '--html', str(self.state / 'report.html'), 'test/a.test.cpp']
                with patch.object(dashboard, 'ROOT', self.root), patch.object(dashboard, 'STATE', self.state), patch.object(sys, 'argv', argv):
                    self.assertEqual(dashboard.main(), 1)
                report = verifier.read_json(self.state / 'report.json')
                self.assertEqual(report['tests'][0]['phase'], phase)
                self.assertFalse(report['tests'][0]['run']['ok'])
        dashboard.get_environment_info.cache_clear()

    def test_standalone_timeout(self):
        completed = subprocess.run(['python3', '.scripts/verify_command_impl.py', 'run', str(self.state / 'timeout'), '0.05',
                                    'python3', '-c', 'import time; time.sleep(10)'], capture_output=True, text=True)
        self.assertEqual(completed.returncode, 124)
        result = verifier.read_json(self.state / 'timeout/run.json')
        self.assertEqual(parse_verification_result({'status': 'failure'}, result)['cases'][0]['status'], 'TLE')


class DashboardResultTest(unittest.TestCase):
    def test_native_case_results_preserve_failure_and_memory(self):
        parsed = parse_verification_result({'status': 'failure', 'testcases': [
            {'name': 'example', 'status': 'AC', 'elapsed': .1, 'memory': 2},
            {'name': 'large', 'status': 'WA', 'elapsed': .5, 'memory': 8},
        ]})
        self.assertEqual(parsed['passedCaseCount'], 1)
        self.assertEqual(parsed['slowestCase'], 'large')
        self.assertEqual(parsed['maxMemoryMb'], 8)
        self.assertEqual(parsed['averageSec'], .3)
