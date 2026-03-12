#!/usr/bin/env python3

from __future__ import annotations

import argparse
import json
import subprocess
from importlib import util as importlib_util
from pathlib import Path


ROOT = Path(__file__).resolve().parent.parent
DEFAULT_FIXTURE_PATH = ROOT / "scripts" / "measure_dashboard_assets" / "measure-dashboard-regression.json"
DEFAULT_OUTPUT_DIR = ROOT / ".verify-helper" / "measure-dashboard-regression"
SCENARIOS = (
    {
        "name": "desktop-top",
        "width": 1440,
        "height": 900,
        "mode": "default",
        "required_tokens": (
            'data-scenario-ready="desktop-top"',
            "displaying 8 / 8 tests",
            'data-entry-path="test/yosupo_point_add_range_sum_segtree.test.cpp"',
        ),
    },
    {
        "name": "desktop-scroll",
        "width": 1440,
        "height": 900,
        "mode": "default",
        "required_tokens": (
            'data-scenario-ready="desktop-scroll"',
            "sort: slowest / desc",
            'data-entry-path="test/yosupo_dynamic_graph_vertex_add_component_sum.test.cpp"',
        ),
    },
    {
        "name": "mobile-top",
        "width": 430,
        "height": 1200,
        "mode": "default",
        "required_tokens": (
            'data-scenario-ready="mobile-top"',
            'data-entry-path="test/yosupo_convolution_ntt.test.cpp"',
        ),
    },
    {
        "name": "skeleton-top",
        "width": 1440,
        "height": 900,
        "mode": "skeleton",
        "required_tokens": (
            'data-scenario-ready="skeleton-top"',
            'class="skeleton-row"',
            "visible: loading",
        ),
    },
)
SCENARIO_HELPER = """
<script>
window.addEventListener("load", () => {
    const params = new URLSearchParams(window.location.search);
    const view = params.get("view");
    const applyScenario = () => {
        if (view === "desktop-scroll") {
            window.scrollTo(0, 640);
        }
        document.body.dataset.scenarioReady = view ?? "default";
    };
    setTimeout(applyScenario, 1200);
}, { once: true });
</script>
""".strip()


def parse_args() -> argparse.Namespace:
    parser = argparse.ArgumentParser(
        description="Render the measurement dashboard from a fixture JSON and capture reference screenshots.",
        formatter_class=argparse.ArgumentDefaultsHelpFormatter,
    )
    parser.add_argument("--fixture", type=Path, default=DEFAULT_FIXTURE_PATH, help="fixture json path")
    parser.add_argument("--output-dir", type=Path, default=DEFAULT_OUTPUT_DIR, help="output directory")
    parser.add_argument("--virtual-time-budget", type=int, default=4000, help="chromium virtual time budget in ms")
    return parser.parse_args()


def load_dashboard_module():
    module_path = ROOT / "scripts" / "generate_verify_dashboard.py"
    spec = importlib_util.spec_from_file_location("generate_verify_dashboard", module_path)
    if spec is None or spec.loader is None:
        raise RuntimeError(f"failed to load module spec: {module_path}")
    module = importlib_util.module_from_spec(spec)
    spec.loader.exec_module(module)
    return module


def inject_scenario_helper(html_text: str) -> str:
    return html_text.replace("</body>", f"{SCENARIO_HELPER}\n</body>")


def prepare_output_dir(output_dir: Path) -> None:
    output_dir.mkdir(parents=True, exist_ok=True)
    for path in (ROOT / ".verify-helper").glob("measure-dashboard-*.png"):
        path.unlink()
    for path in output_dir.glob("*.png"):
        path.unlink()


def make_scenario_report(base_report: dict, mode: str) -> dict:
    report = json.loads(json.dumps(base_report))
    if mode == "skeleton":
        report["tests"] = []
    elif mode != "default":
        raise ValueError(f"unknown scenario mode: {mode}")
    return report


def run_screenshot(url: str, output_path: Path, *, width: int, height: int, virtual_time_budget: int) -> None:
    command = [
        "chromium-browser",
        "--headless",
        "--disable-gpu",
        "--hide-scrollbars",
        "--run-all-compositor-stages-before-draw",
        "--force-device-scale-factor=1",
        f"--window-size={width},{height}",
        f"--virtual-time-budget={virtual_time_budget}",
        f"--screenshot={output_path}",
        url,
    ]
    completed = subprocess.run(command, cwd=ROOT, capture_output=True, text=True, check=False)
    if completed.returncode != 0:
        raise RuntimeError(
            f"chromium failed for {output_path.name}\nstdout:\n{completed.stdout}\nstderr:\n{completed.stderr}"
        )
    if not output_path.exists():
        raise RuntimeError(f"screenshot was not created: {output_path}")


def run_dump_dom(url: str, *, virtual_time_budget: int) -> str:
    command = [
        "chromium-browser",
        "--headless",
        "--disable-gpu",
        f"--virtual-time-budget={virtual_time_budget}",
        "--dump-dom",
        url,
    ]
    completed = subprocess.run(command, cwd=ROOT, capture_output=True, text=True, check=False)
    if completed.returncode != 0:
        raise RuntimeError(f"chromium dump-dom failed\nstdout:\n{completed.stdout}\nstderr:\n{completed.stderr}")
    return completed.stdout


def verify_dom_tokens(dom_text: str, required_tokens: tuple[str, ...], *, scenario_name: str) -> None:
    missing = [token for token in required_tokens if token not in dom_text]
    if missing:
        joined = ", ".join(missing)
        raise RuntimeError(f"scenario {scenario_name}: missing tokens in dumped DOM: {joined}")


def main() -> int:
    args = parse_args()
    fixture_path = args.fixture.resolve()
    output_dir = args.output_dir.resolve()
    module = load_dashboard_module()
    base_report = json.loads(fixture_path.read_text())

    prepare_output_dir(output_dir)

    for scenario in SCENARIOS:
        report = make_scenario_report(base_report, scenario["mode"])
        html_path = output_dir / f"{scenario['name']}.html"
        html_text = module.render_html(report, json_path=html_path.with_suffix(".json"), bootstrap_full_report=True)
        html_path.write_text(inject_scenario_helper(html_text))

        url = f"{html_path.resolve().as_uri()}?view={scenario['name']}"
        output_path = output_dir / f"{scenario['name']}.png"
        run_screenshot(
            url,
            output_path,
            width=scenario["width"],
            height=scenario["height"],
            virtual_time_budget=args.virtual_time_budget,
        )
        dom_text = run_dump_dom(url, virtual_time_budget=args.virtual_time_budget)
        verify_dom_tokens(dom_text, scenario["required_tokens"], scenario_name=scenario["name"])
        print(output_path.relative_to(ROOT))
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
