from __future__ import annotations

import concurrent.futures
import copy
import hashlib
import json
import pathlib
import resource
import shlex
import subprocess
import sys
import tempfile

from competitive_verifier.models import VerificationInput
from competitive_verifier.oj.languages import VerificationConfig
from competitive_verifier.oj.resolver import OjResolver
from competitive_verifier.verify.verifier import content_hash

ROOT = pathlib.Path(__file__).resolve().parent.parent
STATE = ROOT / '.competitive-verifier'
CONFIG = STATE / 'config.toml'
SOURCE_DIRS = ('datastructure', 'flow', 'fps', 'geometry', 'graph', 'math', 'string', 'tree', 'util', 'snippets', 'test')
VERIFY_INPUTS = ('.competitive-verifier/config.toml', 'requirements-dev.txt', '.scripts/verification_impl.py', '.scripts/verify_command_impl.py')


def write_json(path, value):
    path = pathlib.Path(path)
    path.parent.mkdir(parents=True, exist_ok=True)
    with tempfile.NamedTemporaryFile(mode='w', dir=path.parent, prefix=path.name + '.', suffix='.tmp', delete=False) as stream:
        stream.write(json.dumps(value, ensure_ascii=False, indent=2) + '\n')
        temporary = pathlib.Path(stream.name)
    temporary.replace(path)


def read_json(path, default=None):
    path = pathlib.Path(path)
    return json.loads(path.read_text()) if path.exists() else default


def command(args, *, capture=False):
    return subprocess.run(args, cwd=ROOT, text=True, check=False,
                          stdout=subprocess.PIPE if capture else None,
                          stderr=subprocess.STDOUT if capture else None)


def unlimited_stack():
    _, hard = resource.getrlimit(resource.RLIMIT_STACK)
    resource.setrlimit(resource.RLIMIT_STACK, (hard, hard))


def resolve(jobs=8, *, bundle=False, tle=60.0):
    with CONFIG.open('rb') as stream:
        language = VerificationConfig.load(stream).get_dict()['.cpp']
    paths = sorted(p.relative_to(ROOT) for directory in SOURCE_DIRS for p in (ROOT / directory).rglob('*.cpp'))

    def resolve_one(path):
        attributes = language.list_attributes(path, basedir=ROOT)
        dependencies = {p.resolve().relative_to(ROOT).as_posix() for p in language.list_dependencies(path, basedir=ROOT)}
        verifications = []
        for environment in language.list_environments(path, basedir=ROOT):
            for verification in OjResolver.env_to_verifications(environment, attr=attributes, path=path, basedir=ROOT):
                value = verification.model_dump(mode='json', exclude_none=True)
                if value['type'] not in ('problem', 'command'):
                    raise ValueError(f"unsupported verification: {path}: {value['type']}")
                directory = pathlib.Path('.competitive-verifier/build') / hashlib.sha256(f'{path}:{environment.name}'.encode()).hexdigest()[:20]
                compiler = environment.get_compile_command(path, basedir=ROOT, tempdir=directory)
                execute = environment.get_execute_command(path, basedir=ROOT, tempdir=directory)
                execute = shlex.split(execute) if isinstance(execute, str) else execute
                value['compile'] = ['python3', '.scripts/verify_command_impl.py', 'compile', str(directory), '0', *map(str, compiler)]
                value['command'] = list(map(str, execute))
                if value['type'] == 'command':
                    value['command'] = ['python3', '.scripts/verify_command_impl.py', 'run', str(directory), str(tle), *map(str, execute)]
                    value['tempdir'] = str(directory)
                else:
                    value['tle'] = float(attributes.get('TLE', tle))
                verifications.append(value)
        if path.name.endswith('.test.cpp') and len(verifications) != 1:
            raise ValueError(f'expected one verification for {path}, got {len(verifications)}')
        if verifications:
            dependencies.update(VERIFY_INPUTS)
            dependencies.add('.competitive-verifier/runtime.json')
        sources = []
        if bundle:
            bundled = language.bundle(path, basedir=ROOT)
            if bundled:
                destination = pathlib.Path('.competitive-verifier/bundled') / path
                (ROOT / destination).parent.mkdir(parents=True, exist_ok=True)
                (ROOT / destination).write_bytes(bundled)
                sources.append({'name': 'bundled', 'path': str(destination)})
        return str(path), {'dependencies': sorted(dependencies), 'verification': verifications,
                           'document_attributes': attributes, 'additonal_sources': sources}

    compiler = command(['g++', '--version'], capture=True)
    compiler.check_returncode()
    write_json(STATE / 'runtime.json', {'compiler': compiler.stdout, 'platform': sys.platform, 'tle': float(tle)})
    with concurrent.futures.ThreadPoolExecutor(max_workers=jobs) as executor:
        files = dict(executor.map(resolve_one, paths))
    for name in (*VERIFY_INPUTS, '.competitive-verifier/runtime.json'):
        files[name] = {'dependencies': [], 'document_attributes': {'DISPLAY': 'never'}}
    result = {'files': files}
    VerificationInput.model_validate(result)
    return result


def test_paths(resolved):
    return sorted(path for path, value in resolved['files'].items() if value.get('verification'))


def select(resolved, paths):
    selected = set(paths)
    result = copy.deepcopy(resolved)
    for path, value in result['files'].items():
        if path not in selected:
            value['verification'] = []
    return result


def verify(resolved, *, output, jobs=8, previous=None, no_download=False, force=False):
    unlimited_stack()
    STATE.mkdir(exist_ok=True)
    selected = set(test_paths(resolved))
    prior = read_json(previous, {'total_seconds': 0, 'files': {}}) if previous else {'total_seconds': 0, 'files': {}}
    model = VerificationInput.model_validate(resolved)
    reusable = {}
    if not force:
        for path in selected:
            value = prior['files'].get(path, {})
            if not value.get('verifications') or any(v['status'] != 'success' for v in value['verifications']):
                continue
            current_hash = content_hash(model.transitive_depends_on[pathlib.Path(path)])
            if current_hash and value.get('content_hash') == current_hash:
                reusable[path] = value
    pending = selected - reusable.keys()
    print(f'verification plan: {len(pending)} to run, {len(reusable)} cached', flush=True)
    with tempfile.TemporaryDirectory(prefix='run-', dir=STATE) as directory:
        directory = pathlib.Path(directory)
        input_path = directory / 'input.json'
        write_json(input_path, select(resolved, pending))
        if pending and not no_download:
            downloaded = command(['competitive-verifier', 'download', '--verify-json', str(input_path)])
            if downloaded.returncode:
                return downloaded.returncode
        count = min(jobs, len(pending))

        def run_shard(index):
            result_path = directory / f'result-{index}.json'
            args = ['competitive-verifier', 'verify', '--verify-json', str(input_path), '--output', str(result_path),
                    '--check-error', '--no-download', '--change-detection', 'hash', '--split', str(count), '--split-index', str(index)]
            completed = subprocess.run(args, cwd=ROOT, stdout=subprocess.DEVNULL, check=False)
            return completed.returncode, read_json(result_path, {'total_seconds': 0, 'files': {}})

        results = []
        if pending:
            with concurrent.futures.ThreadPoolExecutor(max_workers=count) as executor:
                results = list(executor.map(run_shard, range(count)))
        merged = prior
        for value in merged['files'].values():
            value['newest'] = False
        for path in pending:
            merged['files'].pop(path, None)
        for _, result in results:
            for path, value in result["files"].items():
                if path in pending:
                    current = merged["files"].get(path)
                    if value.get("newest", True) or current is None or not current.get("newest", True):
                        merged["files"][path] = value
        merged['total_seconds'] = sum(result['total_seconds'] for _, result in results)
        write_json(output, merged)
        missing = selected - merged['files'].keys()
        if missing:
            print(f'error: missing verification results: {sorted(missing)}', file=sys.stderr)
        unsuccessful = [path for path in selected if not merged["files"].get(path, {}).get("verifications") or
                        any(v["status"] != "success" for v in merged["files"].get(path, {}).get("verifications", []))]
        print(f"verified: {len(selected) - len(unsuccessful)}/{len(selected)} successful", flush=True)
        return int(bool(unsuccessful) or any(code for code, _ in results))


def docs_results(resolved, result, *, require_success=False):
    model = VerificationInput.model_validate(resolved)
    files = {}
    for path in test_paths(resolved):
        value = result.get('files', {}).get(path)
        current_hash = content_hash(model.transitive_depends_on[pathlib.Path(path)])
        if not value or not current_hash or value.get('content_hash') != current_hash:
            value = {'verifications': [{'status': 'skipped', 'elapsed': 0}], 'newest': False}
        if require_success and (not value['verifications'] or any(v['status'] != 'success' for v in value['verifications'])):
            raise ValueError(f'missing, stale or unsuccessful verification: {path}')
        files[path] = value
    return {'total_seconds': result.get('total_seconds', 0), 'files': files}
