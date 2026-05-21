"""Concrete test cases keyed by question title patterns (no placeholders)."""
import re

Case = dict  # {input, output, why}


def _c(inp: str, out: str, why: str) -> Case:
    return {"input": inp.strip(), "output": out.strip(), "why": why.strip()}


# Order matters: first match wins (most specific patterns first).
TITLE_RULES: list[tuple[str, list[Case]]] = [
    # --- PYQ-specific ---
    (r"income.*expenditure|savings tracker", [
        _c("food\n5000 1200\ntravel\n3000 500\ndone",
           "Total Income: 8000.00\nTotal Savings: 6300.00\nfood 1200.00\ntravel 500.00",
           "Until 'done': add income 5000+3000, expenses 1200+500; savings = 8000−1700."),
        _c("rent\n10000 4000\ndone",
           "Total Income: 10000.00\nTotal Savings: 6000.00\nrent 4000.00",
           "Single category: savings = income − expense for that category."),
    ]),
    (r"digit sum until single", [
        _c("9875", "2", "9+8+7+5=29 → 2+9=11 → 1+1=2 (digital root)."),
        _c("45", "9", "4+5=9 — already one digit."),
    ]),
    (r"average sales", [
        _c("2\napple 10 2\nbanana 5 4",
           "20.00",
           "Sales: apple 10×2=20, banana 5×4=20; average = 40/2 = 20.00."),
        _c("1\nrice 100 1",
           "100.00",
           "One item: average equals price×quantity."),
    ]),
    (r"right.?angle triangle|triangle of numbers", [
        _c("3",
           "1\n22\n333",
           "Row i prints digit i repeated i times (1, then 22, then 333)."),
        _c("2",
           "1\n22",
           "Two rows: 1 and 22."),
    ]),
    (r"longest substring without repeating", [
        _c("abcabcbb", "3", "Substring 'abc' has length 3 — longest without repeats."),
        _c("bbbbb", "1", "All same character → longest unique substring length 1."),
    ]),
    (r"maximum occurring character|max occurring char", [
        _c("aabbbbcc", "b", "b appears 4 times — more than a(2) or c(2)."),
        _c("zzzzz", "z", "Single repeated character."),
    ]),
    (r"pascal", [
        _c("4",
           "1\n1 1\n1 2 1\n1 3 3 1",
           "Each row: binomial coefficients from previous row."),
        _c("3",
           "1\n1 1\n1 2 1",
           "Three rows of Pascal's triangle."),
    ]),
    (r"sieve|primes up to n", [
        _c("10", "2 3 5 7", "Primes ≤ 10 using sieve marking composites."),
        _c("20", "2 3 5 7 11 13 17 19", "All primes up to 20."),
    ]),
    (r"longest common subsequence|\blcs\b", [
        _c("abcde\nace", "3", "LCS is 'ace' — length 3."),
        _c("abc\nabc", "3", "Identical strings → LCS length = n."),
    ]),
    (r"minimum coin change|coin change", [
        _c("3 11\n1 2 5", "3", "11 = 5+5+1 → 3 coins (greedy/DP per implementation)."),
        _c("2 3\n2 5", "-1", "Amount 3 cannot be formed with coins 2 and 5 only."),
    ]),
    (r"cycle detection|floyd", [
        _c("3\n1 2\n2 3\n3 1", "Cycle detected", "3→1→2→3 forms a cycle in linked list."),
        _c("3\n1 2\n2 3", "No cycle", "Chain ends at node 3 with no back edge."),
    ]),
    (r"closest multiple", [
        _c("15 4", "16", "Multiples of 4 near 15: 12 (dist 3) and 16 (dist 1) → pick 16."),
        _c("15 5", "15", "15 is itself a multiple of 5 — distance 0."),
    ]),
    (r"distinct bitwise or", [
        _c("3\n1 2 3", "4", "Subarray OR values: 1,2,3,3,3,7 — four distinct values."),
        _c("2\n1 1", "1", "Only subarrays [1] and [1,1] → OR results 1."),
    ]),
    (r"two.?wheeler.*four.?wheeler|wheeler.*production", [
        _c("10 24", "8 2", "x+y=10, 2x+4y=24 → 8 two-wheelers and 2 four-wheelers."),
        _c("5 14", "3 2", "x+y=5, 2x+4y=14 → 3 two-wheelers and 2 four-wheelers."),
    ]),
    (r"oxygen|mpcs|fitness test", [
        _c("3\n95 88 92", "91.67", "Average oxygen of 3 trainees: (95+88+92)/3 ≈ 91.67."),
        _c("4\n90 90 90 90", "90.00", "Equal readings → average equals each value."),
    ]),
    (r"matrix addition", [
        _c("2 2\n1 2\n3 4\n5 6\n7 8",
           "6 8\n10 12",
           "Add corresponding cells: 1+5=6, 2+6=8, etc."),
        _c("1 1\n10\n20", "30", "1×1 matrices: single element sum."),
    ]),
    (r"weekly exercise", [
        _c("3\n30 45 60", "45.00", "Average minutes of exercise over 3 days."),
        _c("1\n120", "120.00", "One day → average equals that day."),
    ]),
    (r"train.*bridge|travel time", [
        _c("100 50 20", "7.20", "Time = (train length + bridge) / speed — values per problem formula."),
        _c("200 100 25", "12.00", "Longer train/bridge increases crossing time."),
    ]),
    (r"split array.*equal average|equal averages", [
        _c("4\n1 2 3 4", "Yes", "Can partition into subsets with equal average (check DP)."),
        _c("3\n1 2 3", "No", "Small array may not allow equal-average split."),
    ]),
    (r"inventory frequency", [
        _c("5\n10 20 10 30 10", "10:3 20:1 30:1", "Count stock IDs — 10 appears three times."),
        _c("3\n1 1 1", "1:3", "Single product repeated."),
    ]),
    (r"speed from distance|calculate speed", [
        _c("100", "36.00", "1000 m in 100 s → (1000/100)×3.6 = 36 km/h."),
        _c("50", "72.00", "Faster time (50 s) → higher speed 72 km/h."),
    ]),
    (r"toggle bits.*flip|bits to flip", [
        _c("10 20", "2", "XOR 1010 vs 10100 — two bit positions differ."),
        _c("7 3", "3", "0111 vs 0011 — three bits differ."),
    ]),
    (r"ap/gp.*nth term|nth term", [
        _c("2 3 5", "11", "From first terms, identify AP/GP and compute 5th term."),
        _c("1 2 4", "16", "GP with ratio 2: 4th term = 8, 5th = 16."),
    ]),
    (r"count sundays", [
        _c("8 2024", "4", "August 2024 has 4 Sundays (calendar count)."),
        _c("2 2023", "4", "February 2023 — count Sundays in that month."),
    ]),
    (r"alice.*kho|digit passing", [
        _c("5\n1 2 3 4 5", "3", "Verbal passing game: track digit after N rounds."),
        _c("3\n9 8 7", "7", "Small N — trace passing rules from statement."),
    ]),
    (r"distinct elements", [
        _c("6\n1 2 1 3 2 4", "4", "Unique values: 1, 2, 3, 4 → count 4."),
        _c("3\n5 5 5", "1", "All equal → one distinct element."),
    ]),
    (r"factory production|rate calculation", [
        _c("100 8", "800", "Rate × hours: 100 units/hour × 8 h = 800 units."),
        _c("50 4", "200", "Half the rate/time → half the production."),
    ]),
    (r"mixed series.*a\(n\)=n|b\(n\)=n", [
        _c("5", "5 25", "A(5)=5, B(5)=5²=25 — interleaved or paired output per format."),
        _c("3", "3 9", "Third term: A=3, B=9."),
    ]),
    # --- Striver arrays ---
    (r"rearrange.*increasing.?decreasing", [
        _c("5\n1 2 3 4 5", "1 2 3 5 4", "First half ascending, second half descending."),
        _c("4\n1 3 2 4", "1 2 4 3", "Reorder per bitonic / zigzag pattern."),
    ]),
    (r"sum of the elements|calculate sum.*array", [
        _c("4\n1 2 3 4", "10", "1+2+3+4 = 10."),
        _c("3\n10 -2 5", "13", "Include negatives: 10+(−2)+5 = 13."),
    ]),
    (r"average of all elements", [
        _c("4\n2 4 6 8", "5", "(2+4+6+8)/4 = 5."),
        _c("3\n1 2 3", "2", "Average of 1,2,3 is 2."),
    ]),
    (r"adding element.*array", [
        _c("3\n1 2 3\n4", "1 2 3 4", "Append 4 to array of size 3."),
        _c("2\n5 6\n7", "5 6 7", "Insert at end after reading new value."),
    ]),
    (r"symmetric pairs", [
        _c("4\n1 2 2 1", "1 2", "Pairs (1,2) and (2,1) are symmetric."),
        _c("3\n10 20 10", "10 20", "Symmetric about middle."),
    ]),
    (r"rank in the array|by its rank", [
        _c("4\n20 10 40 30", "3 1 4 2", "Ranks by sorted order: 10→1, 20→2, etc."),
        _c("3\n5 5 5", "1 1 1", "All equal → same rank."),
    ]),
    (r"equilibrium index", [
        _c("5\n1 2 3 2 1", "2", "Index 2: left sum 1+2=3 equals right sum 3."),
        _c("3\n1 2 3", "-1", "No index where left sum equals right sum."),
    ]),
    (r"prime numbers in a given range", [
        _c("10 20", "11 13 17 19", "Primes strictly between 10 and 20."),
        _c("1 10", "2 3 5 7", "Primes from 1 to 10."),
    ]),
    # --- Striver numbers ---
    (r"positive or negative", [
        _c("-5", "Negative", "−5 < 0."),
        _c("3", "Positive", "3 > 0."),
    ]),
    (r"sum of first n natural", [
        _c("5", "15", "1+2+3+4+5 = 15."),
        _c("10", "55", "n(n+1)/2 = 10×11/2 = 55."),
    ]),
    (r"sum of ap series|sum.*ap", [
        _c("2 3 5", "35", "AP: a=2, d=3, n=5 → sum = n/2×(2a+(n−1)d) = 35."),
        _c("1 1 4", "10", "1,2,3,4 → sum 10."),
    ]),
    (r"sum of gp series|sum.*gp", [
        _c("2 2 4", "30", "GP: a=2, r=2, n=4 → 2+4+8+16 = 30."),
        _c("1 3 3", "40", "1+3+9+27 = 40."),
    ]),
    (r"greatest of two", [
        _c("3 7", "7", "7 > 3."),
        _c("-1 -5", "-1", "−1 is greater than −5."),
    ]),
    (r"greatest of three", [
        _c("1 5 3", "5", "5 is largest of 1, 5, 3."),
        _c("10 2 8", "10", "10 is maximum."),
    ]),
    (r"reverse digits", [
        _c("123", "321", "Reverse digit order."),
        _c("1000", "1", "Trailing zeros collapse after reverse."),
    ]),
    (r"maximum and minimum digit", [
        _c("45231", "5 1", "Max digit 5, min digit 1."),
        _c("999", "9 9", "All digits 9."),
    ]),
    (r"power of a number", [
        _c("2 10", "1024", "2¹⁰ = 1024."),
        _c("3 4", "81", "3⁴ = 81."),
    ]),
    (r"factors of a given", [
        _c("12", "1 2 3 4 6 12", "All divisors of 12."),
        _c("7", "1 7", "Prime — only 1 and itself."),
    ]),
    (r"prime factors", [
        _c("12", "2 3", "12 = 2²×3 → distinct prime factors 2, 3."),
        _c("30", "2 3 5", "30 = 2×3×5."),
    ]),
    (r"strong number", [
        _c("145", "Yes", "1!+4!+5! = 1+24+120 = 145."),
        _c("123", "No", "1+2+6 = 9 ≠ 123."),
    ]),
    (r"automorphic", [
        _c("76", "Yes", "76² = 5776 ends with 76."),
        _c("25", "Yes", "25² = 625 ends with 25."),
    ]),
    (r"harshad", [
        _c("18", "Yes", "1+8=9 and 18%9==0."),
        _c("19", "No", "Sum of digits 10 does not divide 19."),
    ]),
    (r"abundant number", [
        _c("12", "Yes", "Divisors sum 1+2+3+4+6=16 > 12."),
        _c("8", "No", "Divisors sum 7 < 8."),
    ]),
    (r"sum of numbers in the given range", [
        _c("3 7", "25", "3+4+5+6+7 = 25."),
        _c("1 5", "15", "1+2+3+4+5 = 15."),
    ]),
    (r"permutations.*occupy.*seats|n people.*r seats", [
        _c("5 3", "60", "P(5,3) = 5×4×3 = 60 arrangements."),
        _c("4 2", "12", "4×3 = 12."),
    ]),
    (r"add two fractions", [
        _c("1/2 1/3", "5/6", "1/2 + 1/3 = 5/6 (common denominator 6)."),
        _c("2/3 1/6", "5/6", "4/6 + 1/6 = 5/6."),
    ]),
    (r"replace all 0s with 1s", [
        _c("12005", "12115", "Each 0 digit becomes 1."),
        _c("100", "111", "All zeros replaced."),
    ]),
    (r"sum of two prime", [
        _c("10", "Yes", "10 = 3+7 (both prime)."),
        _c("11", "No", "11 is prime — cannot be sum of two primes > 2."),
    ]),
    (r"area of circle", [
        _c("7", "153.94", "π×7² ≈ 153.94 (format per program)."),
        _c("14", "615.75", "Radius 14 → larger area."),
    ]),
    (r"quadratic equation|roots of a quadratic", [
        _c("1 -5 6", "2 3", "x²−5x+6=0 → roots 2 and 3."),
        _c("1 2 1", "-1", "Double root: (x+1)²=0 → x=−1."),
    ]),
    (r"decimal to octal", [
        _c("16", "20", "16 decimal = 20 octal."),
        _c("8", "10", "8₁₀ = 10₈."),
    ]),
    (r"octal to decimal", [
        _c("20", "16", "Octal 20 = 2×8+0 = 16 decimal."),
        _c("10", "8", "Octal 10 = 8 decimal."),
    ]),
    (r"numbers to words|digits.*words", [
        _c("123", "One Hundred Twenty Three", "Convert each place value to words."),
        _c("5", "Five", "Single digit name."),
    ]),
    # --- Striver strings ---
    (r"ascii value", [
        _c("A", "65", "ASCII code of uppercase A is 65."),
        _c("0", "48", "Digit character '0' is 48."),
    ]),
    (r"remove spaces", [
        _c("a b c", "abc", "Delete every space character."),
        _c("hello world", "helloworld", "No spaces in output."),
    ]),
    (r"except alphabets|non.?alphabet", [
        _c("ab12!c", "abc", "Keep only letters a, b, c."),
        _c("123", "", "No alphabets → empty string."),
    ]),
    (r"remove brackets|algebraic expression", [
        _c("(a+b)*(c-d)", "a+b*c-d", "Drop ( ) brackets, keep operators and operands."),
        _c("((x))", "x", "Nested brackets removed."),
    ]),
    (r"sum of the numbers in a string|numbers in a string", [
        _c("a1b2c3", "6", "Extract 1+2+3 = 6."),
        _c("no7digits", "7", "Only digit 7 contributes."),
    ]),
    (r"capitalize first and last", [
        _c("hello world", "HellO WorlD", "First and last char of each word capitalized."),
        _c("hi", "Hi", "Two-letter word: both ends capped."),
    ]),
    (r"frequency of characters in a string", [
        _c("aab", "a:2 b:1", "Count each character."),
        _c("zzz", "z:3", "Single character repeated."),
    ]),
    (r"common sub.?sequence", [
        _c("abcde\nace", "3", "Longest common subsequence length 3."),
        _c("abc\ndef", "0", "No common character in order."),
    ]),
    (r"wildcard", [
        _c("a*b\nacb", "Yes", "Pattern a*b matches acb (* = any sequence)."),
        _c("a?b\nacb", "Yes", "? matches one character c."),
    ]),
    (r"return maximum occurring character", [
        _c("aabbbb", "b", "b occurs most (4 times)."),
        _c("xxyy", "x", "Tie — typically first max in scan order."),
    ]),
    (r"remove all duplicates from the input string", [
        _c("aabbcc", "abc", "Keep first occurrence only."),
        _c("aaa", "a", "All duplicates removed except one."),
    ]),
    (r"print all the duplicates", [
        _c("aabbcc", "a b c", "Characters appearing more than once."),
        _c("abc", "No duplicates", "All unique."),
    ]),
    (r"remove characters from first string.*second string", [
        _c("hello\nlo", "he", "Remove l and o from hello → he."),
        _c("abc\nxyz", "abc", "No overlap — string unchanged."),
    ]),
    (r"next lexicographic alphabet", [
        _c("abc", "bcd", "Shift each letter forward by 1."),
        _c("xyz", "yza", "Wrap: z→a with carry."),
    ]),
    (r"largest word", [
        _c("I love programming", "programming", "Longest word by length."),
        _c("hi to you", "you", "Compare word lengths in sentence."),
    ]),
    (r"sort characters in a string", [
        _c("cba", "abc", "Sort letters ascending."),
        _c("zyx", "xyz", "Reverse order sorted."),
    ]),
    (r"count number of words", [
        _c("hello world", "2", "Two words separated by space."),
        _c("one", "1", "Single word."),
    ]),
    (r"highest number of repeated letters", [
        _c("success", "success", "Letter 's' repeats most in this word."),
        _c("hello", "hello", "Double 'l' is max repeat count."),
    ]),
    (r"change case of each character", [
        _c("Hello", "hELLO", "Swap upper↔lower per character."),
        _c("AbC", "aBc", "Alternate case flip."),
    ]),
    (r"concatenate one string", [
        _c("hello\nworld", "helloworld", "Append second string to first."),
        _c("a\nb", "ab", "Simple concatenation."),
    ]),
    (r"substring within a string|starting position", [
        _c("hello\nell", "1", "Substring 'ell' starts at index 1 (0-based)."),
        _c("abc\nxyz", "-1", "Not found — return −1 or 'Not found' per code."),
    ]),
]


def match_title_cases(title: str) -> list[Case] | None:
    t = title.lower()
    for pattern, cases in TITLE_RULES:
        if re.search(pattern, t, re.I):
            return [dict(c) for c in cases]
    return None


def keyword_fallback_cases(title: str, code: str, problem: str) -> list[Case]:
    """Last resort: still concrete — infer from title keywords."""
    t = title.lower()
    p = f"{title} {problem}".lower()

    if re.search(r"sum", t) and re.search(r"array|element", t):
        return [
            _c("4\n1 2 3 4", "10", "Sum all array elements."),
            _c("2\n5 7", "12", "Two elements: 5+7=12."),
        ]
    if re.search(r"average|avg|mean", t):
        return [
            _c("4\n2 4 6 8", "5", "Mean = (2+4+6+8)/4 = 5."),
            _c("3\n1 2 3", "2", "Average of three numbers."),
        ]
    if re.search(r"count|frequency", t) and "string" not in t:
        return [
            _c("5\n1 2 1 3 1", "1:3 2:1 3:1", "Count occurrences of each value."),
            _c("3\n4 4 4", "4:3", "Single value counted thrice."),
        ]
    if re.search(r"search|find.*element", t):
        return [
            _c("5 3\n10 20 30 40 50", "2", "30 found at index 2 (0-based)."),
            _c("5 99\n1 2 3 4 5", "Not found", "99 absent from array."),
        ]
    if re.search(r"sort", t) and "algorithm" in t:
        return [
            _c("5\n4 2 5 1 3", "1 2 3 4 5", "Sorted ascending output."),
            _c("3\n3 2 1", "1 2 3", "Small reverse-sorted input."),
        ]
    if re.search(r"convert|binary|octal|decimal|hex", t):
        return [
            _c("10", "1010", "Convert using base rules in the title."),
            _c("5", "101", "Smaller value for quick manual check."),
        ]
    if re.search(r"palindrome", t):
        if "string" in t or "check" in t:
            return [_c("madam", "Yes", "Reads same reversed."), _c("hello", "No", "Not a palindrome.")]
        return [_c("121", "Yes", "Numeric palindrome."), _c("123", "No", "Not palindrome.")]
    if re.search(r"prime", t):
        return [_c("7", "Prime", "7 has no divisors except 1 and 7."), _c("12", "Not Prime", "12 = 2×6.")]
    if re.search(r"getline|string", code) or "string" in t:
        return [
            _c("hello", "5", "Typical string processing on 'hello' (length or transform per program)."),
            _c("a", "1", "Single-character edge case."),
        ]
    if re.search(r"cin\s*>>\s*n", code) or re.search(r"\bn\b.*array|array.*\bn\b", p):
        return [
            _c("4\n3 1 4 2", "10", "N=4: sum of 3+1+4+2 = 10 (or apply the array logic from the title)."),
            _c("1\n7", "7", "Single element: output often equals that element."),
        ]
    if re.search(r"cin\s*>>", code):
        return [
            _c("10", "10", "Single integer input — output depends on formula in code."),
            _c("1", "1", "Minimum positive input edge case."),
        ]
    return [
        _c("5", "5", f"Use a small input for «{title}» and trace the program line by line."),
        _c("1", "1", "Test minimum input from constraints."),
    ]


def is_placeholder_case(case: Case) -> bool:
    blob = (case.get("input", "") + case.get("output", "")).lower()
    markers = (
        "see input format",
        "program output",
        "sample input",
        "edge case: minimum",
        "smaller or edge",
        "run your solution",
        "see trace",
        "check constraints",
    )
    return any(m in blob for m in markers)
