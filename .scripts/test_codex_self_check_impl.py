import tempfile
import unittest
from pathlib import Path
from unittest.mock import patch

import codex_self_check_impl as self_check


class MarkdownLiquidTest(unittest.TestCase):
    def check_document(self, text: str) -> list[str]:
        with tempfile.TemporaryDirectory() as directory:
            root = Path(directory)
            path = root / "_md" / "geometry" / "sample.md"
            path.parent.mkdir(parents=True)
            path.write_text(text)
            with patch.object(self_check, "ROOT", root):
                return self_check.check_markdown_files()

    def test_initializer_in_code_fence(self):
        text = (
            "---\ntitle: example\n---\n\n```cpp\n"
            "vector<pair<long long, long long>> points = {{1, 2}, {3, 6}, {2, 1}};\n"
            "```\n"
        )
        problems = self.check_document(text)
        self.assertEqual(len(problems), 1)
        self.assertIn("_md/geometry/sample.md:6: unsafe Liquid opener '{{'", problems[0])
        self.assertIn("separate the characters with a space", problems[0])
        self.assertEqual(self.check_document(text.replace("{{1", "{ {1")), [])

    def test_liquid_openers_in_markdown(self):
        for literal in ("{{0}}", "{{ unterminated", "{% unknown %}", "{% unterminated"):
            for wrapper in ("{}", "`{}`", "${}$", "```cpp\n{}\n```", "~~~cpp\n{}\n~~~"):
                with self.subTest(literal=literal, wrapper=wrapper):
                    problems = self.check_document(wrapper.format(literal))
                    self.assertEqual(len(problems), 1)
                    self.assertIn("unsafe Liquid opener", problems[0])

    def test_line_numbers_after_code_fences(self):
        problems = self.check_document("```cpp\nint x = 0;\n```\n\n`{{0}}`\n{% bad %}\n")
        self.assertEqual(len(problems), 2)
        self.assertIn("sample.md:5:", problems[0])
        self.assertIn("sample.md:6:", problems[1])

    def test_raw_blocks(self):
        for start, end in (
            ("{% raw %}", "{% endraw %}"),
            ("{%- raw -%}", "{%- endraw -%}"),
        ):
            with self.subTest(start=start):
                text = start + "\n```cpp\nauto x = {{0}};\n{% unknown %}\n```\n" + end
                self.assertEqual(self.check_document(text + "\n" + text), [])
                problems = self.check_document(text + "\n{{0}}")
                self.assertEqual(len(problems), 1)
                self.assertIn("sample.md:7: unsafe Liquid opener", problems[0])

    def test_unbalanced_raw_blocks(self):
        for text, message in (
            ("\n{% raw %}\n{{0}}", "raw block is missing endraw"),
            ("\n{% endraw %}", "endraw without raw"),
            ("\n{% raw %}\n{% endraw", "raw block is missing endraw"),
        ):
            with self.subTest(text=text):
                problems = self.check_document(text)
                self.assertEqual(problems, [f"_md/geometry/sample.md:2: Liquid {message}"])

    def test_ordinary_braces_and_existing_complexity_rule(self):
        self.assertEqual(self.check_document("```cpp\nauto x = { {1, 2}, {3, 4}};\n```\n$O(N)$"), [])
        problems = self.check_document("`O(N)`")
        self.assertEqual(problems, ["_md/geometry/sample.md:1: complexity should use MathJax, not backticks"])


if __name__ == "__main__":
    unittest.main()
