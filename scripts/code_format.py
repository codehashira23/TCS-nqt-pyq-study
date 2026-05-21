"""Format C++ for study: one statement per line (at ;), light spacing, word wrap."""
import re
import textwrap

INDENT = "    "
WRAP_WIDTH = 88


def _light_spacing(line: str) -> str:
    """Minimal prettier — safe for --, ::, and >> in templates."""
    if not line.strip():
        return line
    s = line.strip()
    s = re.sub(r"#include\s*<", "#include <", s)
    s = re.sub(r"\bcin\s*>>", "cin >>", s)
    s = re.sub(r"\bcout\s*<<", "cout <<", s)
    s = re.sub(r",(?=\S)", ", ", s)
    s = re.sub(r"(?<![=!<>+\-*/%])=(?!=)", " = ", s)
    s = re.sub(r"\s*==\s*", " == ", s)
    s = re.sub(r"\s*!=\s*", " != ", s)
    s = re.sub(r"\s*<=\s*", " <= ", s)
    s = re.sub(r"\s*>=\s*", " >= ", s)
    s = re.sub(r"\s*&&\s*", " && ", s)
    s = re.sub(r"\s*\|\|\s*", " || ", s)
    # Only space << / >> when used as stream operators (after cin/cout or closing paren)
    s = re.sub(r"(?<=cin)\s*>>\s*", " >> ", s)
    s = re.sub(r"(?<=cout)\s*<<\s*", " << ", s)
    s = re.sub(r"\s+", " ", s).strip()
    return s


def _split_at_semicolons(text: str) -> list[str]:
    """Split text on ; outside strings. Each part is one statement (no trailing ;)."""
    parts = []
    buf = []
    i = 0
    n = len(text)
    in_str = None
    esc = False

    while i < n:
        c = text[i]
        if in_str:
            buf.append(c)
            if esc:
                esc = False
            elif c == "\\":
                esc = True
            elif c == in_str:
                in_str = None
            i += 1
            continue
        if c in "\"'":
            in_str = c
            buf.append(c)
            i += 1
            continue
        if c == ";":
            stmt = "".join(buf).strip()
            if stmt:
                parts.append(stmt)
            buf = []
            i += 1
            continue
        buf.append(c)
        i += 1
    tail = "".join(buf).strip()
    if tail:
        parts.append(tail)
    return parts


def _wrap_line(line: str, width: int = WRAP_WIDTH) -> list[str]:
    if len(line) <= width:
        return [line]
    return textwrap.wrap(
        line,
        width=width,
        break_long_words=False,
        break_on_hyphens=False,
    )


def format_cpp(code: str) -> str:
    """Pretty-print: braces on own lines; each ; ends a statement on its own line."""
    code = code.strip()
    if not code:
        return code

    if "/*" in code and "*/" in code:
        end = code.find("*/")
        code = code[end + 2 :].strip()

    # Normalize braces onto separate tokens/lines
    code = re.sub(r"\s*\{\s*", " {\n", code)
    code = re.sub(r"\s*\}\s*", "\n}\n", code)
    raw_lines = [ln.strip() for ln in code.splitlines() if ln.strip()]

    out_lines = []
    depth = 0

    for raw in raw_lines:
        if raw == "{":
            out_lines.append(INDENT * depth + "{")
            depth += 1
            continue
        if raw == "}":
            depth = max(0, depth - 1)
            out_lines.append(INDENT * depth + "}")
            continue

        # Split compound lines at semicolons
        stmts = _split_at_semicolons(raw)
        for stmt in stmts:
            stmt = _light_spacing(stmt)
            if not stmt:
                continue

            # Control header ending with {
            if stmt.endswith("{"):
                body = stmt[:-1].strip()
                out_lines.append(INDENT * depth + body + " {")
                depth += 1
                continue

            # for (a; b; c) — put each clause on its own indented line
            m = re.match(r"^(for|while)\s*\((.+)\)$", stmt, re.I | re.S)
            if m and m.group(1).lower() == "for" and ";" in m.group(2):
                inner = m.group(2)
                clauses = [c.strip() for c in inner.split(";")]
                out_lines.append(INDENT * depth + f"for ({clauses[0]};")
                for c in clauses[1:-1]:
                    out_lines.append(INDENT * depth + "     " + c + ";")
                out_lines.append(INDENT * depth + "     " + clauses[-1] + ")")
                continue

            if stmt.startswith("#include"):
                out_lines.append(_light_spacing(stmt))
            elif stmt.startswith("using namespace"):
                out_lines.append(_light_spacing(stmt) + (";" if not stmt.endswith(";") else ""))
            else:
                line = INDENT * depth + stmt + ";"
                for wrapped in _wrap_line(line):
                    out_lines.append(wrapped)

    return "\n".join(out_lines)


# --- Line notes ---
NOTE_RULES = [
    (r"#include\s*<bits/stdc", "Master header: I/O, vectors, algorithms in one include."),
    (r"#include", "Brings in libraries needed for this program."),
    (r"using\s+namespace\s+std", "So we can write cin/cout without std:: prefix."),
    (r"sync_with_stdio\s*\(\s*false\s*\)", "Disables C/C++ stream sync — faster input."),
    (r"cin\.tie\s*\(\s*nullptr\s*\)", "Unties cin from cout — faster input."),
    (r"vector\s*<", "STL vector — dynamic array."),
    (r"cin\s*>>\s*n\b", "Read N (size or count)."),
    (r"getline\s*\(\s*cin", "Read a full line (may contain spaces)."),
    (r"for\s*\(", "Loop — core logic often here."),
    (r"while\s*\(", "Loop until condition becomes false."),
    (r"if\s*\(", "Branch based on a condition."),
    (r"cout\s*<<", "Print the answer."),
    (r"return\s+", "Return value / exit function."),
    (r"\(n\s*\*\s*\(\s*n\s*-\s*1\)\)\s*/\s*2", "nC2 handshake formula."),
    (r"sort\s*\(", "Sort data in ascending/descending order."),
    (r"reverse\s*\(", "Reverse order of elements."),
    (r"max\s*\(|min\s*\(", "Track best value seen so far."),
]


def _split_inline_comment(line: str) -> tuple[str, str]:
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
    stripped = line.strip().rstrip(";")
    if not stripped or stripped in ("{", "}"):
        return ""
    if stripped.startswith("//"):
        return stripped[2:].strip()
    blob = f"{title} {topics}"
    for pat, note in NOTE_RULES:
        if re.search(pat, stripped, re.I):
            return note
    if re.search(r"cin\s*>>", stripped):
        return "Reads input from stdin."
    if re.search(r"cout\s*<<", stripped):
        return "Writes output — match problem format."
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
        lines.append({"num": i, "text": text, "note": note, "important": important})
    return lines, formatted


def annotate_cpp(code: str, title: str, topics: str) -> str:
    lines, formatted = build_code_lines(code, title, topics)
    out = []
    for row in lines:
        text = row["text"]
        if row["note"] and row["important"] and text.strip():
            out.append(f"{text}  // {row['note']}")
        elif text.strip() or row["note"]:
            out.append(text if text.strip() else f"// {row['note']}")
        else:
            out.append("")
    return "\n".join(out)
