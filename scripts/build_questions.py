"""Parse PYQ + Striver C++ files → website/data/questions.json."""
import json
import re
import sys
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parent))
from code_format import annotate_cpp, build_code_lines, format_cpp

ROOT = Path(__file__).resolve().parent.parent
STRIVER_ROOT = ROOT / "100 q by striver for tcsnqt"
OUT = ROOT / "website" / "data" / "questions.json"

SECTIONS = [
    "QUESTION",
    "CONSTRAINTS",
    "INPUT FORMAT",
    "OUTPUT FORMAT",
    "EXPLANATION",
    "TEACHING NOTE",
]

COMPLEXITY_HINTS = [
    (r"O\(log\s*N\)|O_log_N|Binary Search", "O(log N)", "O(1)", "Halve search space each step."),
    (r"Count Subsets|Subset Sum|Coin Change|Minimum_Coin", "O(N * S)", "O(S)", "DP over target sum S."),
    (r"BFS|Breadth.?First", "O(V + E)", "O(V)", "Visit each vertex and edge once."),
    (r"Merge sort|Quick Sort|Insertion Sort|Selection Sort|Bubble Sort", "O(N log N) or O(N^2)", "O(1) or O(N)", "Classic sorting algorithms."),
    (r"Bubble Sort|Sorting Algorithm", "O(N^2)", "O(1)", "Adjacent swaps until sorted."),
    (r"Kadane|Maximum Subarray|Maximum product subarray", "O(N)", "O(1)", "Single pass tracking best subarray."),
    (r"Dutch National Flag|Sort.*0s.*1s.*2s|Move.*Zero|Empty.*Packet|Chocolate", "O(N)", "O(1)", "Single pass reordering (two pointers)."),
    (r"Floyd|Cycle Detection", "O(N)", "O(1)", "Slow/fast pointers meet if cycle exists."),
    (r"Handshake|Derangement|Factorial|Combinatorics|permutations", "O(1) or O(N)", "O(1)", "Math / combinatorics formula."),
    (r"Count Subarrays|Subarray.*Sum|Prefix", "O(N)", "O(N)", "Prefix sum or sliding window."),
    (r"Two Pointer|Block Swap|Rotate", "O(N)", "O(1)", "In-place array manipulation."),
    (r"Hash|Frequency|Distinct|Anagram|Non.?Repeating|duplicate", "O(N)", "O(N)", "Hash map/set for counts or lookup."),
    (r"Matrix", "O(N*M)", "O(N*M)", "Visit each matrix cell once."),
    (r"Fibonacci|AP_GP|Series|Pattern|Sieve|Prime", "O(N) or O(N log log N)", "O(1) or O(N)", "Number theory / series iteration."),
    (r"Palindrome|Reverse|Caesar|Cipher|String|substring", "O(N)", "O(N)", "Linear scan on string."),
    (r"Prime|Perfect|Armstrong|Digit|GCD|LCM|Leap|Quadratic", "O(sqrt N) or O(log N)", "O(1)", "Math checks per number."),
    (r"Graph", "O(V + E)", "O(V)", "Adjacency traversal."),
    (r"Dynamic Programming|\bDP\b", "O(N * K)", "O(K)", "State over items and parameter K."),
]


def infer_complexity(title: str, topics: str, code: str, question: str, filename: str) -> dict:
    blob = f"{title} {topics} {filename} {question}"
    for pattern, time_c, space_c, note in COMPLEXITY_HINTS:
        if re.search(pattern, blob, re.I) or re.search(pattern, code, re.I):
            return {"time": time_c, "space": space_c, "note": note}
    if re.search(r"for\s*\([^)]*for\s*\(", code):
        return {"time": "O(N^2)", "space": "O(1)", "note": "Nested loops detected in code."}
    if re.search(r"while\s*\(|for\s*\(", code, re.I):
        return {"time": "O(N)", "space": "O(1)", "note": "Linear iteration over input size."}
    return {"time": "O(N)", "space": "O(1)", "note": "Linear scan unless proven otherwise."}


def infer_striver_difficulty(title: str, category: str) -> str:
    t = f"{title} {category}".lower()
    if re.search(r"sort|merge|quick|rotation|equilibrium|median|subset|product subarray", t):
        return "Medium"
    if re.search(r"sort|block swap|symmetric|frequency|duplicate|wildcard", t):
        return "Medium"
    return "Easy"


def _pack_question(
    *,
    edition: str,
    num: int,
    title: str,
    filename: str,
    difficulty: str,
    topics: list[str],
    source: str,
    exam: str,
    problem_statement: str,
    explanation: str,
    code: str,
    cx: dict,
) -> dict:
    topics_str = ", ".join(topics)
    formatted = format_cpp(code)
    code_lines, _ = build_code_lines(code, title, topics_str)
    annotated = annotate_cpp(code, title, topics_str)
    slug = re.sub(r"[^a-z0-9]+", "-", f"{edition}-{num}-{title}".lower()).strip("-")

    return {
        "edition": edition,
        "editionLabel": "TCS NQT PYQ" if edition == "pyq" else "Striver's 100 Q for TCS NQT",
        "id": num,
        "slug": slug,
        "title": title,
        "filename": filename,
        "difficulty": difficulty,
        "topics": topics,
        "source": source,
        "exam": exam,
        "problemStatement": problem_statement.strip(),
        "explanation": explanation.strip(),
        "code": formatted,
        "codeAnnotated": annotated,
        "codeLines": code_lines,
        "timeComplexity": cx["time"],
        "spaceComplexity": cx["space"],
        "complexityNote": cx["note"],
    }


def parse_pyq_cpp(path: Path) -> dict:
    text = path.read_text(encoding="utf-8")
    m = re.match(r"(\d+)_", path.name)
    num = int(m.group(1)) if m else 0

    header = ""
    code = text
    if "/*" in text:
        end = text.find("*/")
        if end != -1:
            header = text[2:end].strip()
            code = text[end + 2 :].strip()

    title_m = re.search(r"TCS NQT PYQ\s*\d+:\s*(.+)", header)
    title = title_m.group(1).strip() if title_m else path.stem.replace("_", " ")

    def field(name: str) -> str:
        pat = rf"{name}\s*\n(.*?)(?=\n\s*(?:{'|'.join(SECTIONS)})|\Z)"
        fm = re.search(pat, header, re.S)
        return fm.group(1).strip() if fm else ""

    question = field("QUESTION")
    constraints = field("CONSTRAINTS")
    input_fmt = field("INPUT FORMAT")
    output_fmt = field("OUTPUT FORMAT")
    explanation = field("EXPLANATION")
    teaching = field("TEACHING NOTE")

    difficulty = ""
    dm = re.search(r"Difficulty:\s*(\w+)", header)
    if dm:
        difficulty = dm.group(1)

    topics_raw = ""
    tm = re.search(r"Topics:\s*(.+)", header)
    if tm:
        topics_raw = tm.group(1).strip()

    source = ""
    sm = re.search(r"Source:\s*(.+)", header)
    if sm:
        source = sm.group(1).strip()

    exam = ""
    em = re.search(r"Exam/Shift:\s*(.+)", header)
    if em:
        exam = em.group(1).strip()

    cx = infer_complexity(title, topics_raw, code, question, path.name)
    o_match = re.search(r"O\([^)]+\)|O_[A-Za-z0-9_]+", header + " " + path.name)
    if o_match and "log" in o_match.group(0).lower():
        cx["time"] = "O(log N)"
        cx["note"] = "Required by problem statement."

    full_explanation = explanation
    if teaching:
        full_explanation += "\n\n**How to approach:**\n" + teaching.replace("\n   ", "\n")
    if input_fmt or output_fmt:
        full_explanation += "\n\n**I/O:**\n"
        if input_fmt:
            full_explanation += f"- Input: {input_fmt}\n"
        if output_fmt:
            full_explanation += f"- Output: {output_fmt}\n"

    problem_statement = question
    if constraints:
        problem_statement += "\n\n**Constraints:**\n" + constraints

    return _pack_question(
        edition="pyq",
        num=num,
        title=title,
        filename=path.name,
        difficulty=difficulty or "Medium",
        topics=[t.strip() for t in topics_raw.split(",") if t.strip()],
        source=source or "Verified PYQ",
        exam=exam,
        problem_statement=problem_statement,
        explanation=full_explanation,
        code=code,
        cx=cx,
    )


def parse_striver_cpp(path: Path) -> dict:
    text = path.read_text(encoding="utf-8")
    lines = text.splitlines()

    m = re.match(r"(\d+)_", path.name)
    num = int(m.group(1)) if m else 0

    header_comments = []
    code_lines = []
    in_code = False
    for line in lines:
        if not in_code and line.strip().startswith("#include"):
            in_code = True
        if in_code:
            code_lines.append(line)
        elif line.strip().startswith("//"):
            header_comments.append(line.strip()[2:].strip())

    code = "\n".join(code_lines).strip()
    header_blob = "\n".join(header_comments)

    title_m = re.search(r"Problem\s*\d+:\s*(.+)", header_blob, re.I)
    title = title_m.group(1).strip() if title_m else path.stem.replace("_", " ")

    topic_m = re.search(r"Topic:\s*(.+)", header_blob, re.I)
    topic_label = topic_m.group(1).strip() if topic_m else ""

    parent = path.parent.name.replace("_", " ")
    category = re.sub(r"^\d+\s*", "", parent).strip() or "General"

    study = []
    capture = False
    for hc in header_comments:
        if "how to study" in hc.lower():
            capture = True
            continue
        if capture:
            if hc.startswith("-") or hc.lower().startswith("all code"):
                study.append(hc)
            elif not hc:
                continue
            else:
                capture = False

    explanation = (
        "**Striver's TCS NQT 100 — study guide**\n"
        + (f"**Category:** {category}\n" if category else "")
        + (f"**Sheet topic:** {topic_label}\n\n" if topic_label else "\n")
        + "**How to study this solution:**\n"
        + "\n".join(f"- {s.lstrip('- ')}" for s in study if s)
        + "\n\nRead the code on the right — important lines include comments from the original sheet."
    )

    problem_statement = f"**{title}**\n\n"
    if topic_label:
        problem_statement += f"**Topic:** {topic_label} ({category})\n\n"
    problem_statement += (
        "Practice problem from **Striver's 100 Questions for TCS NQT** — "
        "focused on building fundamentals (not a previous-year exam question)."
    )

    topics = [category]
    if topic_label and topic_label not in topics:
        topics.append(topic_label)

    difficulty = infer_striver_difficulty(title, category)
    cx = infer_complexity(title, ", ".join(topics), code, title, path.name)

    return _pack_question(
        edition="striver",
        num=num,
        title=title,
        filename=path.name,
        difficulty=difficulty,
        topics=topics,
        source="Striver · TCS NQT 100",
        exam="",
        problem_statement=problem_statement,
        explanation=explanation,
        code=code,
        cx=cx,
    )


def main():
    pyq_files = sorted(ROOT.glob("*.cpp"), key=lambda p: int(re.match(r"(\d+)", p.name).group(1)))
    striver_files = sorted(
        STRIVER_ROOT.rglob("*.cpp"),
        key=lambda p: int(re.match(r"(\d+)", p.name).group(1)),
    )

    questions = [parse_pyq_cpp(f) for f in pyq_files] + [parse_striver_cpp(f) for f in striver_files]

    OUT.parent.mkdir(parents=True, exist_ok=True)
    OUT.write_text(json.dumps(questions, indent=2, ensure_ascii=False), encoding="utf-8")
    print(f"Wrote {len(questions)} questions to {OUT}")
    print(f"  PYQ: {len(pyq_files)}  |  Striver: {len(striver_files)}")


if __name__ == "__main__":
    main()
