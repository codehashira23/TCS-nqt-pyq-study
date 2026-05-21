"""Format compact C++ and attach study notes per important line."""
import re

INDENT = "    "


def _split_outside_strings(code: str) -> list[str]:
    """Split code into tokens preserving strings."""
    tokens = []
    i = 0
    n = len(code)
    buf = ""
    while i < n:
        c = code[i]
        if c in "\"'":
            q = c
            buf += c
            i += 1
            while i < n:
                if code[i] == "\\":
                    buf += code[i : i + 2]
                    i += 2
                    continue
                buf += code[i]
                if code[i] == q:
                    i += 1
                    break
                i += 1
            continue
        if c in "{}":
            if buf.strip():
                tokens.append(buf.strip())
                buf = ""
            tokens.append(c)
            i += 1
            continue
        if c == ";":
            # Don't split for(;;) headers — only statement-ending semicolons
            depth = 0
            for ch in buf:
                if ch == "(":
                    depth += 1
                elif ch == ")":
                    depth = max(0, depth - 1)
            if depth == 0:
                if buf.strip():
                    tokens.append(buf.strip())
                    buf = ""
                tokens.append(";")
                i += 1
                continue
            buf += c
            i += 1
            continue
        buf += c
        i += 1
    if buf.strip():
        tokens.append(buf.strip())
    return tokens


def format_cpp(code: str) -> str:
    """Expand one-liner solutions into readable multi-line C++."""
    code = code.strip()
    if not code:
        return code

    # Already multi-line and readable
    lines = code.split("\n")
    if len(lines) >= 6 and any(len(l) > 80 for l in lines[:8]):
        return _normalize_indent(code)

    tokens = _split_outside_strings(code)
    out = []
    depth = 0
    line_parts = []

    def flush_line():
        nonlocal line_parts
        if line_parts:
            text = " ".join(line_parts)
            out.append(INDENT * depth + text)
            line_parts = []

    for tok in tokens:
        if tok == "{":
            if line_parts:
                out.append(INDENT * depth + " ".join(line_parts) + " {")
                line_parts = []
            else:
                if out and not out[-1].rstrip().endswith("{"):
                    out[-1] = out[-1] + " {"
                else:
                    out.append(INDENT * depth + "{")
            depth += 1
        elif tok == "}":
            flush_line()
            depth = max(0, depth - 1)
            out.append(INDENT * depth + "}")
        elif tok == ";":
            line_parts.append(";")
            flush_line()
        else:
            line_parts.append(tok)

    flush_line()

    # Rebuild includes / using at column 0
    result = []
    for ln in out:
        stripped = ln.strip()
        if stripped.startswith("#include") or stripped.startswith("using "):
            result.append(stripped)
        elif stripped == "}" and depth == 0:
            result.append(stripped)
        else:
            result.append(ln if ln.startswith(INDENT) or not stripped else INDENT * max(0, depth) + stripped)

    formatted = "\n".join(result)
    formatted = _clean_semicolons(formatted) if formatted else code
    return _normalize_indent(formatted) if formatted else code


def _clean_semicolons(code: str) -> str:
    """Remove stray space before semicolons."""
    return re.sub(r"\s+;", ";", code)


def _normalize_indent(code: str) -> str:
    lines = code.split("\n")
    fixed = []
    depth = 0
    for raw in lines:
        s = raw.strip()
        if not s:
            fixed.append("")
            continue
        if s.startswith("#include") or s.startswith("using "):
            fixed.append(s)
            continue
        if s == "}":
            depth = max(0, depth - 1)
            fixed.append(INDENT * depth + "}")
            continue
        if s.endswith("{") and s != "{":
            fixed.append(INDENT * depth + s)
            depth += 1
            continue
        if s == "{":
            fixed.append(INDENT * depth + "{")
            depth += 1
            continue
        fixed.append(INDENT * depth + s)
    text = "\n".join(fixed)
    return _clean_semicolons(text)


# (pattern, note) — first match wins; order = most specific first
NOTE_RULES = [
    (r"#include\s*<bits/stdc", "Master header: I/O, vectors, algorithms in one include."),
    (r"#include", "Brings in libraries needed for this program."),
    (r"using\s+namespace\s+std", "So we can write cin/cout without std:: prefix."),
    (r"sync_with_stdio\s*\(\s*false\s*\)", "Disables C/ C++ stream sync → faster input."),
    (r"cin\.tie\s*\(\s*nullptr\s*\)", "Unties cin from cout → faster input."),
    (r"vector\s*<\s*int\s*>", "Dynamic integer array of size N."),
    (r"vector\s*<\s*long\s+long", "64-bit array — avoids overflow on large sums."),
    (r"vector\s*<", "STL container to store input data."),
    (r"unordered_map|map\s*<", "Hash map / map for frequency or lookups."),
    (r"queue\s*<|stack\s*<", "Queue/stack for BFS, DFS, or simulations."),
    (r"priority_queue", "Heap for greedy / Dijkstra style problems."),
    (r"stringstream", "Parse a full line into words."),
    (r"cin\s*>>\s*n\b", "Read N — usually array length or count."),
    (r"cin\s*>>\s*s\b", "Read target sum S (or similar parameter)."),
    (r"cin\s*>>\s*k\b", "Read K — window size, rotations, or threshold."),
    (r"for\s*\(\s*auto\s*&?\s*\w+\s*:\s*\w+\s*\)", "Range-for: visit every element once."),
    (r"for\s*\(\s*int\s+\w+\s*=\s*0", "Classic for-loop over indices 0 … n-1."),
    (r"for\s*\(\s*int\s+\w+\s*=\s*\w+;\s*\w+\s*>=", "Reverse loop — often for DP backwards."),
    (r"while\s*\(\s*l\s*<\s*r", "Binary search: shrink [l, r] until one element remains."),
    (r"while\s*\(\s*l\s*<=\s*r", "Binary search variant on index range."),
    (r"while\s*\(\s*\w+\s*--\s*\)|while\s*\(\s*n\s*--", "Read/process exactly N values."),
    (r"while\s*\(\s*\w+\s*<\s*\w+\s*\)", "Two pointers or sliding window loop."),
    (r"\(r\s*-\s*l\)\s*/\s*2", "Mid index without overflow (binary search)."),
    (r"m\s*%\s*2", "Align mid to even index — paired array trick."),
    (r"a\[m\]\s*==\s*a\[m\s*\+\s*1\]", "Pair found at mid → answer lies to the right."),
    (r"l\s*=\s*m\s*\+\s*2", "Skip the pair; search right half."),
    (r"r\s*=\s*m\b", "No pair at mid → odd element is at m or left."),
    (r"dp\[", "DP table: stores best answer for sub-states."),
    (r"dp\[0\]\s*=", "Base case: empty subset / zero sum."),
    (r"MOD\s*=|%\s*MOD|1e9\s*\+\s*7", "Modulo 10^9+7 — count problems on TCS."),
    (r"\^=|\^\s*\w", "XOR — cancels pairs; finds odd occurrence."),
    (r"sort\s*\(", "Sort input — enables two pointers or binary search."),
    (r"reverse\s*\(", "Reverse string or in-place word order."),
    (r"max\s*\(|min\s*\(", "Keep running best value (greedy / Kadane)."),
    (r"LLONG_MIN|INT_MIN", "Initialize to smallest value before max scan."),
    (r"cur\s*=\s*max|best\s*=\s*max", "Kadane: extend subarray or start fresh."),
    (r"pos\s*\+\+|pos\s*=\s*0", "Write index — Dutch flag / move zeros."),
    (r"if\s*\(\s*\w+\s*!=\s*0\)", "Skip zeros; keep relative order of non-zeros."),
    (r"cout\s*<<", "Print the required answer."),
    (r"return\s+0", "Exit main successfully."),
    (r"int\s+main\s*\(", "Program entry point."),
    (r"\(n\s*\*\s*\(n\s*-\s*1\)\)\s*/\s*2", "nC2 — handshakes / pairs formula."),
    (r"sqrt\s*\(|cbrt\s*\(", "Root check — primes, perfect numbers."),
    (r"isalpha|isdigit|tolower", "Character classification / case fold."),
    (r"getline\s*\(\s*cin", "Read a full line (may contain spaces)."),
    (r"adj\[|vector\s*<\s*vector", "Graph adjacency list."),
    (r"visited|vis\[", "Mark nodes/ cells already processed."),
]


def _split_inline_comment(line: str) -> tuple[str, str]:
    """Return (code_part, note) from a line that may end with // comment."""
    stripped = line.strip()
    if not stripped:
        return line, ""
    if stripped.startswith("//"):
        return "", stripped[2:].strip()
    idx = line.find("//")
    if idx > 0:
        before = line[:idx].rstrip()
        after = line[idx + 2 :].strip()
        if before and after:
            return before, after
    return line, ""


def _line_note(line: str, title: str, topics: str) -> str:
    stripped = line.strip()
    if not stripped or stripped in ("{", "}"):
        return ""
    if stripped.startswith("//"):
        return stripped[2:].strip()

    blob = f"{title} {topics}"
    for pat, note in NOTE_RULES:
        if re.search(pat, stripped, re.I):
            return note

    # Fallbacks by structure
    if re.search(r"cin\s*>>", stripped):
        return "Reads input values from stdin."
    if re.search(r"cout\s*<<", stripped):
        return "Writes output — match the format in the problem."
    if re.search(r"for\s*\(", stripped):
        return "Loop over data — core logic often lives here."
    if re.search(r"if\s*\(", stripped):
        return "Branch on a condition from the problem rules."
    if re.search(r"while\s*\(", stripped):
        return "Repeat until pointers/indices meet the stop condition."
    if "=" in stripped and "==" not in stripped and "<<" not in stripped:
        return "Assign/update a variable used in the answer."

    return ""


def build_code_lines(code: str, title: str, topics: str) -> tuple[list[dict], str]:
    formatted = format_cpp(code)
    lines = []
    for i, raw in enumerate(formatted.split("\n"), start=1):
        code_part, inline_note = _split_inline_comment(raw.rstrip())
        text = code_part if code_part else raw.rstrip()
        note = inline_note or _line_note(text, title, topics)
        if not code_part and inline_note:
            text = ""
        important = bool(note) and bool(text.strip() or inline_note)
        lines.append(
            {
                "num": i,
                "text": text,
                "note": note,
                "important": important,
            }
        )
    return lines, formatted


def annotate_cpp(code: str, title: str, topics: str) -> str:
    """Formatted code with inline // notes on important lines (for copy view)."""
    lines, formatted = build_code_lines(code, title, topics)
    out = []
    for row in lines:
        text = row["text"]
        if row["note"] and row["important"] and not text.strip().startswith("//"):
            pad = max(2, 52 - len(text))
            out.append(f"{text}{' ' * pad}// {row['note']}")
        else:
            out.append(text)
    return "\n".join(out)
