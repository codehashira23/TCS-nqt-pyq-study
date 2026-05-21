"""Parse TCS NQT C++ PYQ files and generate website/data/questions.json."""
import json
import re
import sys
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parent))
from code_format import annotate_cpp, build_code_lines, format_cpp

ROOT = Path(__file__).resolve().parent.parent
OUT = ROOT / "website" / "data" / "questions.json"

SECTIONS = [
    "QUESTION",
    "CONSTRAINTS",
    "INPUT FORMAT",
    "OUTPUT FORMAT",
    "EXPLANATION",
    "TEACHING NOTE",
]

# Topic/keyword -> (time, space, study note for complexity)
COMPLEXITY_HINTS = [
    (r"O\(log\s*N\)|O_log_N|Binary Search", "O(log N)", "O(1)", "Halve search space each step."),
    (r"Count Subsets|Subset Sum|Coin Change|Minimum_Coin", "O(N * S)", "O(S)", "DP over target sum S."),
    (r"BFS|Breadth.?First", "O(V + E)", "O(V)", "Visit each vertex and edge once."),
    (r"DFS|Depth.?First", "O(V + E)", "O(V)", "Stack/recursion over graph."),
    (r"Dijkstra", "O((V+E) log V)", "O(V)", "Priority queue relaxes edges."),
    (r"Sieve|Eratosthenes", "O(N log log N)", "O(N)", "Mark multiples of each prime."),
    (r"LCS|Longest Common Subsequence", "O(N*M)", "O(N*M)", "2D DP over both strings."),
    (r"Kadane|Maximum Subarray", "O(N)", "O(1)", "Single pass tracking best subarray."),
    (r"Dutch National Flag|Sort.*0s.*1s.*2s|Move.*Zero|Empty.*Packet|Chocolate", "O(N)", "O(1)", "Single pass reordering (two pointers)."),
    (r"Floyd|Cycle Detection", "O(N)", "O(1)", "Slow/fast pointers meet if cycle exists."),
    (r"Handshake|Derangement|Factorial|Combinatorics", "O(1)", "O(1)", "Closed-form combinatorics."),
    (r"Count Subarrays|Subarray.*Sum|Prefix", "O(N)", "O(N)", "Prefix sum or sliding window."),
    (r"Two Pointer", "O(N)", "O(1)", "Two indices scan the array once."),
    (r"Hash|Frequency|Distinct|Anagram|Non.?Repeating", "O(N)", "O(N)", "Hash map/set for counts or lookup."),
    (r"Bubble Sort|Sorting Algorithm", "O(N^2)", "O(1)", "Adjacent swaps until sorted."),
    (r"Matrix", "O(N*M)", "O(N*M)", "Visit each matrix cell once."),
    (r"Fibonacci|AP_GP|Series|Pattern", "O(N)", "O(1)", "Iterate terms or use closed form."),
    (r"Palindrome|Reverse|Caesar|Cipher", "O(N)", "O(N)", "Linear scan or in-place reversal."),
    (r"Prime|Perfect|Armstrong|Digit|GCD|LCM|Leap", "O(sqrt N) or O(log N)", "O(1)", "Math checks per number."),
    (r"Jump Game", "O(N)", "O(1)", "Track farthest reachable index."),
    (r"\bXOR\b|Toggle.*Bit|Bitwise OR", "O(N) or O(log N)", "O(1)", "Bit manipulation on integers."),
    (r"Graph", "O(V + E)", "O(V)", "Adjacency traversal."),
    (r"Dynamic Programming|\bDP\b", "O(N * K)", "O(K)", "State over items and parameter K."),
]


def infer_complexity(title: str, topics: str, code: str, question: str, filename: str) -> dict:
    blob = f"{title} {topics} {filename} {question}"
    code_blob = code
    for pattern, time_c, space_c, note in COMPLEXITY_HINTS:
        if re.search(pattern, blob, re.I) or re.search(pattern, code_blob, re.I):
            return {"time": time_c, "space": space_c, "note": note}

    if re.search(r"O\(N\^2\)", blob, re.I):
        return {"time": "O(N^2)", "space": "O(1)", "note": "Nested loops over input."}
    if re.search(r"for\s*\([^)]*for\s*\(", code):
        return {"time": "O(N^2)", "space": "O(1)", "note": "Nested loops detected in code."}
    if re.search(r"while\s*\(.*<.*\)|for\s*\(.*n", code, re.I):
        return {"time": "O(N)", "space": "O(1)", "note": "Linear iteration over input size."}

    return {"time": "O(N)", "space": "O(1)", "note": "Default linear scan unless proven otherwise."}


def parse_cpp(path: Path) -> dict:
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
        m = re.search(pat, header, re.S)
        return m.group(1).strip() if m else ""

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

    topics = ""
    tm = re.search(r"Topics:\s*(.+)", header)
    if tm:
        topics = tm.group(1).strip()

    source = ""
    sm = re.search(r"Source:\s*(.+)", header)
    if sm:
        source = sm.group(1).strip()

    exam = ""
    em = re.search(r"Exam/Shift:\s*(.+)", header)
    if em:
        exam = em.group(1).strip()

    o_match = re.search(r"O\([^)]+\)|O_[A-Za-z0-9_]+", header + " " + path.name)
    explicit_o = o_match.group(0).replace("_", " ") if o_match else ""

    cx = infer_complexity(title, topics, code, question, path.name)
    if explicit_o and "log" in explicit_o.lower():
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

    slug = re.sub(r"[^a-z0-9]+", "-", path.stem.lower()).strip("-")
    topics_str = ", ".join(t.strip() for t in topics.split(",") if t.strip())
    formatted = format_cpp(code)
    code_lines, _ = build_code_lines(code, title, topics_str)
    annotated = annotate_cpp(code, title, topics_str)

    return {
        "id": num,
        "slug": slug,
        "title": title,
        "filename": path.name,
        "difficulty": difficulty or "Medium",
        "topics": [t.strip() for t in topics.split(",") if t.strip()],
        "source": source,
        "exam": exam,
        "problemStatement": problem_statement.strip(),
        "explanation": full_explanation.strip(),
        "code": formatted,
        "codeAnnotated": annotated,
        "codeLines": code_lines,
        "timeComplexity": cx["time"],
        "spaceComplexity": cx["space"],
        "complexityNote": cx["note"],
    }


def main():
    files = sorted(ROOT.glob("*.cpp"), key=lambda p: int(re.match(r"(\d+)", p.name).group(1)))
    questions = [parse_cpp(f) for f in files]
    OUT.parent.mkdir(parents=True, exist_ok=True)
    OUT.write_text(json.dumps(questions, indent=2, ensure_ascii=False), encoding="utf-8")
    print(f"Wrote {len(questions)} questions to {OUT}")


if __name__ == "__main__":
    main()
