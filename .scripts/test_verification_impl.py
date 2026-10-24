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
from run_verify_impl import shard_paths
from competitive_verifier.verify.verifier import content_hash
from competitive_verifier.models import VerificationInput
from competitive_verifier.models.problem import TestCaseData
from competitive_verifier.oj import problem_from_url
from competitive_verifier.oj.problem import save_testcases
from generate_verify_dashboard_impl import parse_verification_result


class TemplateAssertionTest(unittest.TestCase):
    def test_local_controls_assertions(self):
        template = verifier.ROOT / 'snippets/template.cpp'
        with tempfile.TemporaryDirectory(prefix='library-template-test-') as temporary:
            source = pathlib.Path(temporary) / 'main.cpp'
            executable = pathlib.Path(temporary) / 'main'
            source.write_text(f'#define main template_main\n#include "{template}"\n#undef main\n'
                              'int main() { int calls = 0; assert(++calls); return calls; }\n')
            for flags, expected in [([], 0), (['-DLOCAL'], 1), (['-DNDEBUG'], 0), (['-DLOCAL', '-DNDEBUG'], 1)]:
                with self.subTest(flags=flags):
                    subprocess.run(['g++', '-std=c++17', '-O2', *flags, str(source), '-o', str(executable)], check=True)
                    self.assertEqual(subprocess.run([str(executable)]).returncode, expected)


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
        with patch.object(verifier, 'command') as download, patch.object(verifier.subprocess, 'run') as run:
            self.assertEqual(verifier.verify(resolved, output=output, previous=output, jobs=2), 0)
            download.assert_not_called()
            run.assert_not_called()
        unchanged = verifier.read_json(output)
        self.assertTrue(all(not result['newest'] for result in unchanged['files'].values()))
        verifier.docs_results(resolved, unchanged, require_success=True)
        (self.root / 'test/value.cpp').write_text('constexpr int value = 1;\n')
        self.assertEqual(verifier.verify(resolved, output=output, previous=output, jobs=2, no_download=True), 1)
        failed = verifier.read_json(output)
        self.assertEqual(failed['files']['test/a.test.cpp']['verifications'][0]['status'], 'failure')
        self.assertFalse(failed['files']['test/b.test.cpp']['newest'])
        before_failure = failed['files']['test/a.test.cpp']['verifications'][0]['last_execution_time']
        self.assertEqual(verifier.verify(resolved, output=output, previous=output, jobs=2, no_download=True), 1)
        retried = verifier.read_json(output)
        self.assertNotEqual(retried['files']['test/a.test.cpp']['verifications'][0]['last_execution_time'], before_failure)
        before = verifier.read_json(output)['files']['test/b.test.cpp']['verifications'][0]['last_execution_time']
        self.assertEqual(verifier.verify(verifier.select(resolved, ['test/b.test.cpp']), output=output, previous=output,
                                         force=True, jobs=1, no_download=True), 0)
        forced = verifier.read_json(output)
        self.assertEqual(forced['files']['test/a.test.cpp']['verifications'][0]['status'], 'failure')
        self.assertNotEqual(forced['files']['test/b.test.cpp']['verifications'][0]['last_execution_time'], before)
        (self.root / 'test/value.cpp').write_text('constexpr int value = 0;\n')
        self.assertEqual(verifier.verify(resolved, output=output, previous=output, jobs=2, no_download=True), 0)
        self.assertEqual(verifier.read_json(output)['files']['test/a.test.cpp']['verifications'][0]['status'], 'success')

    def successful_results(self, resolved):
        model = VerificationInput.model_validate(resolved)
        return {'total_seconds': 0, 'files': {
            path: {'content_hash': content_hash(model.transitive_depends_on[pathlib.Path(path)]),
                   'verifications': [{'status': 'success', 'elapsed': 0}], 'newest': True}
            for path in verifier.test_paths(resolved)}}

    def test_cached_problem_needs_no_testdata(self):
        (self.root / 'test/a.test.cpp').write_text('#define PROBLEM "https://judge.yosupo.jp/problem/aplusb"\nint main() { return 0; }\n')
        resolved = verifier.resolve(jobs=2)
        output = self.state / 'result.json'
        verifier.write_json(output, self.successful_results(resolved))
        with patch.object(verifier, 'command') as download, patch.object(verifier.subprocess, 'run') as run:
            self.assertEqual(verifier.verify(resolved, output=output, previous=output), 0)
            download.assert_not_called()
            run.assert_not_called()
        verifier.docs_results(resolved, verifier.read_json(output), require_success=True)

    def test_download_and_execution_only_for_changed_test(self):
        resolved = verifier.resolve(jobs=2)
        output = self.state / 'result.json'
        verifier.write_json(output, self.successful_results(resolved))
        (self.root / 'test/value.cpp').write_text('constexpr int value = 0;\n\n')
        downloaded = []

        def download(args):
            self.assertEqual(args[:3], ['competitive-verifier', 'download', '--verify-json'])
            downloaded.extend(verifier.test_paths(verifier.read_json(args[3])))
            return subprocess.CompletedProcess(args, 0)

        with patch.object(verifier, 'command', side_effect=download):
            self.assertEqual(verifier.verify(resolved, output=output, previous=output, jobs=2), 0)
        self.assertEqual(downloaded, ['test/a.test.cpp'])
        result = verifier.read_json(output)
        self.assertTrue(result['files']['test/a.test.cpp']['newest'])
        self.assertFalse(result['files']['test/b.test.cpp']['newest'])
        verifier.docs_results(resolved, result, require_success=True)

    def test_configuration_changes_and_force_download_all_tests(self):
        resolved = verifier.resolve(jobs=2)
        output = self.state / 'result.json'
        verifier.write_json(output, self.successful_results(resolved))
        downloaded = []

        def download(args):
            downloaded.append(verifier.test_paths(verifier.read_json(args[3])))
            return subprocess.CompletedProcess(args, 17)

        for name in (*verifier.VERIFY_INPUTS, '.competitive-verifier/runtime.json'):
            with self.subTest(name=name):
                path = self.root / name
                original = path.read_text()
                path.write_text(original + '\n')
                with patch.object(verifier, 'command', side_effect=download):
                    self.assertEqual(verifier.verify(resolved, output=output, previous=output), 17)
                self.assertEqual(downloaded[-1], verifier.test_paths(resolved))
                path.write_text(original)
        with patch.object(verifier, 'command', side_effect=download):
            self.assertEqual(verifier.verify(resolved, output=output, previous=output, force=True), 17)
        self.assertEqual(downloaded[-1], verifier.test_paths(resolved))

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
        self.addCleanup(dashboard.get_environment_info.cache_clear)
        url = 'https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=ITP1_1_A'
        save_testcases([TestCaseData('sample', b'', b'Hello World\n')], directory=problem_from_url(url).test_directory)
        for source, phase in [('int main() { return 1; }', 'done'), ('int main() { invalid; }', 'error')]:
            with self.subTest(phase=phase):
                (self.root / 'test/a.test.cpp').write_text(f'#define PROBLEM "{url}"\n' + source + '\n')
                argv = ['measure', '--no-download', '--keep-going', '--json', str(self.state / 'report.json'),
                        '--html', str(self.state / 'report.html'), 'test/a.test.cpp']
                with patch.object(dashboard, 'ROOT', self.root), patch.object(dashboard, 'STATE', self.state), patch.object(sys, 'argv', argv):
                    self.assertEqual(dashboard.main(), 1)
                report = verifier.read_json(self.state / 'report.json')
                self.assertEqual(report['tests'][0]['phase'], phase)
                self.assertFalse(report['tests'][0]['run']['ok'])

    def test_measurement_disables_assertions_and_skips_standalone(self):
        import generate_verify_dashboard_impl as dashboard
        self.addCleanup(dashboard.get_environment_info.cache_clear)
        url = 'https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=ITP1_1_A'
        save_testcases([TestCaseData('sample', b'', b'Hello World\n')], directory=problem_from_url(url).test_directory)
        (self.root / 'test/a.test.cpp').write_text(
            f'#define PROBLEM "{url}"\n#include <cassert>\n#include <cstdio>\n'
            '#ifdef LOCAL\n#error LOCAL must be disabled for measurement\n#endif\n'
            'int main() { assert(false); puts("Hello World"); }\n')
        (self.root / 'test/b.test.cpp').write_text('#define STANDALONE\nint main() { invalid; }\n')
        argv = ['measure', '--no-download', '--json', str(self.state / 'report.json'), '--html', str(self.state / 'report.html'),
                'test/a.test.cpp', 'test/b.test.cpp']
        with patch.object(dashboard, 'ROOT', self.root), patch.object(dashboard, 'STATE', self.state), patch.object(sys, 'argv', argv):
            self.assertEqual(dashboard.main(), 0)
            self.assertEqual(dashboard.list_test_paths([]), [self.root / 'test/a.test.cpp'])
        report = verifier.read_json(self.state / 'report.json')
        self.assertEqual(len(report['tests']), 1)
        self.assertTrue(report['tests'][0]['run']['ok'])
        self.assertEqual(report['tests'][0]['run']['parsed']['passedCaseCount'], 1)
        self.assertEqual(report['inventory']['currentTestCount'], 1)

    def test_release_dependencies_and_debug_cache_remain_separate(self):
        (self.root / 'test/debug.cpp').write_text('constexpr int expected = 1;\n')
        (self.root / 'test/release.cpp').write_text('constexpr int expected = 0;\n')
        (self.root / 'test/a.test.cpp').write_text(
            '#define STANDALONE\n#include <cassert>\n#ifdef LOCAL\n#include "debug.cpp"\n'
            '#else\n#include "release.cpp"\n#endif\n'
            'int main() { int calls = 0; assert(++calls); return calls != expected; }\n')
        debug = verifier.resolve(jobs=2)
        output = self.state / 'result.json'
        self.assertEqual(verifier.verify(debug, output=output, jobs=2, no_download=True), 0)
        debug_runtime = (self.state / 'runtime.json').read_text()
        release = verifier.resolve(jobs=2, release=True)
        self.assertEqual((self.state / 'runtime.json').read_text(), debug_runtime)
        debug_file = debug['files']['test/a.test.cpp']
        release_file = release['files']['test/a.test.cpp']
        self.assertIn('test/debug.cpp', debug_file['dependencies'])
        self.assertNotIn('test/release.cpp', debug_file['dependencies'])
        self.assertIn('test/release.cpp', release_file['dependencies'])
        self.assertNotIn('test/debug.cpp', release_file['dependencies'])
        self.assertNotEqual(debug_file['verification'][0]['command'], release_file['verification'][0]['command'])
        release_model = VerificationInput.model_validate(release)
        self.assertNotEqual(verifier.read_json(output)['files']['test/a.test.cpp']['content_hash'],
                            content_hash(release_model.transitive_depends_on[pathlib.Path('test/a.test.cpp')]))
        self.assertEqual(verifier.verify(release, output=self.state / 'release-result.json', jobs=2, no_download=True), 0)
        with patch.object(verifier, 'command') as download, patch.object(verifier.subprocess, 'run') as run:
            self.assertEqual(verifier.verify(debug, output=output, previous=output, jobs=2), 0)
            download.assert_not_called()
            run.assert_not_called()

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


class ShardTest(unittest.TestCase):
    def test_shards_cover_tests_once_and_keep_assignments_when_tests_change(self):
        paths = [f'test/{i}.test.cpp' for i in range(40)]
        for split in (1, 4, 7):
            shards = [shard_paths(paths, split, index) for index in range(split)]
            self.assertEqual(sorted(path for shard in shards for path in shard), sorted(paths))
            updated = sorted(paths[1:] + ['test/new.test.cpp'])
            for index, shard in enumerate(shards):
                self.assertEqual(set(shard_paths(updated, split, index)) & set(paths), set(shard) - {paths[0]})
