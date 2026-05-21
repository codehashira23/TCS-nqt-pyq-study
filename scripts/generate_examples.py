"""Generate question-specific examples (test cases + walkthrough) for each problem."""

import re



from title_cases import is_placeholder_case, keyword_fallback_cases, match_title_cases





def _case(input_text: str, output_text: str, why: str) -> dict:

    return {"input": input_text.strip(), "output": output_text.strip(), "why": why.strip()}





def _format_examples_text(cases: list[dict]) -> str:

    parts = []

    for i, c in enumerate(cases, 1):

        parts.append(f"**Example {i}**")

        parts.append(f"**Input:**\n{c['input']}")

        parts.append(f"**Output:**\n{c['output']}")

        parts.append(f"**Why this output?**\n{c['why']}")

        parts.append("")

    return "\n".join(parts).strip()





def _ensure_two_cases(cases: list[dict], title: str, code: str, problem: str) -> list[dict]:

    if len(cases) >= 2:

        return cases

    extra = keyword_fallback_cases(title, code, problem)

    for c in extra:

        if c not in cases and not is_placeholder_case(c):

            cases.append(c)

        if len(cases) >= 2:

            break

    return cases





def generate_examples(

    title: str,

    problem_statement: str,

    code: str,

    topics: list[str],

    edition: str,

) -> tuple[str, list[dict]]:

    blob = f"{title} {problem_statement} {code} {' '.join(topics)}".lower()

    cases: list[dict] = []



    # Title-specific rules first (most reliable)

    title_cases = match_title_cases(title)

    if title_cases:

        cases = title_cases



    # --- Combinatorics / math ---

    if not cases and re.search(r"handshake|n\s*\*\s*\(\s*n\s*-\s*1\s*\)", blob):

        cases = [

            _case("5", "10", "5 people → each shakes 4 others → 5×4/2 = 10 unique handshakes."),

            _case("3", "3", "3 people → 3×2/2 = 3 handshakes (triangle)."),

        ]

    elif not cases and re.search(r"derangement|book exchange", blob):

        cases = [

            _case("3", "2", "3 people swap books so nobody keeps their own → 2 derangements."),

            _case("4", "9", "4 people → 9 valid derangements (subfactorial pattern)."),

        ]

    elif not cases and re.search(r"gcd|hcf", blob) and re.search(r"lcm", blob):

        cases = [

            _case("12 18", "6 36", "GCD(12,18)=6; LCM = 12×18/6 = 36."),

            _case("8 20", "4 40", "GCD=4; LCM = 8×20/4 = 40."),

        ]

    elif not cases and re.search(r"\bgcd\b", blob):

        cases = [

            _case("48 18", "6", "Largest number dividing both 48 and 18 is 6."),

            _case("7 13", "1", "7 and 13 are coprime → GCD is 1."),

        ]

    elif not cases and re.search(r"\blcm\b", blob):

        cases = [

            _case("4 6", "12", "Smallest common multiple of 4 and 6 is 12."),

            _case("5 7", "35", "5 and 7 are coprime → LCM = 35."),

        ]

    elif not cases and re.search(r"factorial", blob) and "sum" not in blob:

        cases = [

            _case("5", "120", "5! = 5×4×3×2×1 = 120."),

            _case("0", "1", "0! is defined as 1 by convention."),

        ]

    elif not cases and re.search(r"fibonacci|fib ", blob):

        cases = [

            _case("6", "8", "Fibonacci: 0,1,1,2,3,5,8 → 6th term (1-indexed style) is 8."),

            _case("10", "55", "Building the series up to the 10th term gives 55."),

        ]

    elif not cases and re.search(r"ap_gp|nth term|series", blob) and "pattern" in blob:

        cases = [

            _case("2 3 5", "11", "Apply the AP/GP formula from the first terms to get the nth term."),

            _case("1 2 4", "16", "Identify ratio or difference from the sample series, then extend."),

        ]



    # --- Prime / number theory ---

    elif not cases and re.search(r"prime", blob) and re.search(r"check|is prime|prime or not", blob):

        cases = [

            _case("7", "Prime", "7 has no divisors except 1 and 7."),

            _case("12", "Not Prime", "12 = 2×6, so it is composite."),

        ]

    elif not cases and re.search(r"armstrong", blob):

        cases = [

            _case("153", "Yes", "1³+5³+3³ = 153 → Armstrong number."),

            _case("123", "No", "1³+2³+3³ = 36 ≠ 123."),

        ]

    elif not cases and re.search(r"perfect number", blob):

        cases = [

            _case("6", "Yes", "Divisors 1,2,3 sum to 6."),

            _case("12", "No", "Divisors sum to 16, not 12."),

        ]

    elif not cases and re.search(r"palindrome", blob) and "number" in blob:

        cases = [

            _case("121", "Yes", "Reads same forwards and backwards."),

            _case("123", "No", "Reverse is 321."),

        ]

    elif not cases and re.search(r"leap year", blob):

        cases = [

            _case("2024", "Leap Year", "Divisible by 4 and not a century exception."),

            _case("1900", "Not Leap Year", "Century year not divisible by 400."),

        ]

    elif not cases and re.search(r"odd occurring|odd number of times|appears an odd", blob):

        cases = [

            _case("5\n1 1 2 2 3", "3", "3 appears once; pairs cancel — binary search finds the odd one."),

            _case("7\n4 4 7 8 8 9 9", "7", "Only 7 has odd frequency in sorted pair layout."),

        ]

    elif not cases and re.search(r"even or odd|check.*even", blob) and "array" not in blob:

        cases = [

            _case("14", "Even", "14 % 2 == 0."),

            _case("7", "Odd", "7 % 2 == 1."),

        ]

    elif not cases and re.search(r"sum of digits", blob):

        cases = [

            _case("123", "6", "1+2+3 = 6."),

            _case("9999", "36", "9+9+9+9 = 36."),

        ]

    elif not cases and re.search(r"binary|decimal.*binary|binary.*decimal", blob):

        cases = [

            _case("10", "1010", "10 in decimal is 1010 in binary."),

            _case("5", "101", "5 = 4+1 → binary 101."),

        ]

    elif not cases and re.search(r"xor", blob) and "coin" in blob:

        cases = [

            _case("3\n1 2 3", "0", "XOR of 1,2,3 is 0; minimum coins uses that value."),

            _case("2\n5 7", "2", "XOR of 5,7 is 2."),

        ]



    # --- Arrays ---

    elif not cases and re.search(r"maximum subarray|kadane", blob):

        cases = [

            _case("5\n-2 1 -3 4 -1", "4", "Best contiguous subarray is [4] with sum 4."),

            _case("3\n2 3 -1", "5", "Whole array sums to 5."),

        ]

    elif not cases and re.search(r"move zero|empty packet|chocolate", blob):

        cases = [

            _case("5\n1 0 2 0 3", "1 2 3 0 0", "Non-zeros keep order; zeros shift right."),

            _case("4\n0 4 0 1", "4 1 0 0", "Same rule for any arrangement."),

        ]

    elif not cases and re.search(r"dutch|0s.*1s.*2s|sort.*0.*1.*2", blob):

        cases = [

            _case("6\n2 0 2 1 0 1", "0 0 1 1 2 2", "Three-way partition: 0s, then 1s, then 2s."),

            _case("3\n2 2 0", "0 2 2", "Sort only three categories in one pass."),

        ]

    elif not cases and re.search(r"reverse.*array|reverse a given array", blob):

        cases = [

            _case("4\n1 2 3 4", "4 3 2 1", "Swap ends inward until reversed."),

            _case("3\n9 8 7", "7 8 9", "Three elements reversed."),

        ]

    elif not cases and re.search(r"smallest|minimum", blob) and "array" in blob:

        cases = [

            _case("5\n3 1 4 1 5", "1", "Scan and keep the minimum value."),

            _case("4\n10 -2 8 -2", "-2", "Negative values allowed; -2 is smallest."),

        ]

    elif not cases and re.search(r"largest|maximum", blob) and "array" in blob:

        cases = [

            _case("5\n3 1 4 1 5", "5", "Maximum in the array is 5."),

            _case("4\n-5 -1 -9", "-1", "-1 is largest among negatives."),

        ]

    elif not cases and re.search(r"second (smallest|largest)", blob):

        cases = [

            _case("5\n3 1 4 1 5", "3", "Distinct sorted values → second smallest is 3."),

            _case("4\n10 20 30 40", "30", "Second largest is 30."),

        ]

    elif not cases and re.search(r"missing number", blob):

        cases = [

            _case("3\n1 2 4", "3", "Numbers 1..4 expected; 3 is missing."),

            _case("5\n1 2 3 5 6", "4", "One value from 1..6 is absent."),

        ]

    elif not cases and re.search(r"rotate.*k|rotation", blob):

        cases = [

            _case("5 2\n1 2 3 4 5", "3 4 5 1 2", "Left rotate by 2 moves first two elements to the end."),

            _case("4 1\n10 20 30 40", "20 30 40 10", "Rotate left by 1."),

        ]

    elif not cases and re.search(r"\bxor\b", blob) and "array" in blob:

        cases = [

            _case("5\n1 1 2 2 3", "3", "XOR of all elements leaves the single odd-occurring value."),

            _case("7\n4 4 7 8 8 9 9", "7", "Only 7 has odd frequency."),

        ]

    elif not cases and re.search(r"subset sum|count subsets", blob):

        cases = [

            _case("3 6\n1 2 3", "1", "Only subset {1,2,3} sums to 6 (or count per problem)."),

            _case("4 5\n2 2 1 3", "2", "Two subsets may sum to 5 depending on duplicates."),

        ]

    elif not cases and re.search(r"subarray.*sum|sum equal to k", blob):

        cases = [

            _case("5 5\n1 2 3 -2 5", "2", "Two subarrays sum to 5 (e.g. [2,3] and [5])."),

            _case("4 0\n1 -1 1 -1", "4", "Many zero-sum subarrays when sum target is 0."),

        ]

    elif not cases and re.search(r"frequency|repeating|duplicate", blob) and "array" in blob:

        cases = [

            _case("6\n1 2 1 3 2 1", "1:3 2:2 3:1", "Count how many times each value appears."),

            _case("4\n5 5 5 5", "5:4", "Single value repeated four times."),

        ]

    elif not cases and re.search(r"search an element", blob):

        cases = [

            _case("5 3\n10 20 30 40 50", "Found at index 2", "30 is at index 2 (0-based)."),

            _case("5 7\n1 2 3 4 5", "Not found", "7 is absent."),

        ]

    elif not cases and re.search(r"median", blob):

        cases = [

            _case("5\n3 1 4 1 5", "3", "Sorted: 1,1,3,4,5 → median is 3."),

            _case("4\n10 1 5 2", "3", "Sorted: 1,2,5,10 → average of middle two."),

        ]



    # --- Strings ---

    elif not cases and re.search(r"reverse.*string|reverse words", blob):

        if "word" in blob:

            cases = [

                _case("hello world", "world hello", "Reverse order of words, not characters."),

                _case("I love code", "code love I", "Each word token reversed in position."),

            ]

        else:

            cases = [

                _case("hello", "olleh", "Reverse full string character-wise."),

                _case("abc", "cba", "Three characters reversed."),

            ]

    elif not cases and re.search(r"palindrome", blob) and "string" in blob:

        cases = [

            _case("Madam", "Yes", "Case-insensitive → still reads same reversed."),

            _case("hello", "No", "Reverse is olleh."),

        ]

    elif not cases and re.search(r"anagram", blob):

        cases = [

            _case("listen silent", "Yes", "Same letter counts → anagrams."),

            _case("hello world", "No", "Different letters and lengths."),

        ]

    elif not cases and re.search(r"vowel|consonant", blob):

        cases = [

            _case("Hello!", "Vowels:2 Consonants:3", "Count a,e,i,o,u (case-insensitive)."),

            _case("xyz", "Vowels:0 Consonants:3", "No vowels in xyz."),

        ]

    elif not cases and re.search(r"caesar|cipher", blob):

        cases = [

            _case("abc 1", "bcd", "Shift each letter by 1 → a→b, b→c, c→d."),

            _case("xyz 3", "abc", "Wrap around alphabet after z."),

        ]

    elif not cases and re.search(r"first non.?repeating|non.?repeating char", blob):

        cases = [

            _case("aabbc", "c", "a and b repeat; c is first unique."),

            _case("aabb", "No repeating", "Every character repeats."),

        ]



    # --- Sorting algorithms (Striver) ---

    elif not cases and re.search(r"bubble sort", blob):

        cases = [

            _case("5\n4 2 5 1 3", "1 2 3 4 5", "Adjacent swaps until array sorted ascending."),

            _case("3\n3 2 1", "1 2 3", "Smallest bubble-sort trace on three elements."),

        ]

    elif not cases and re.search(r"selection sort", blob):

        cases = [

            _case("4\n64 25 12 22", "12 22 25 64", "Repeatedly pick minimum from unsorted part."),

            _case("3\n2 1 3", "1 2 3", "Swap minimum into front each pass."),

        ]

    elif not cases and re.search(r"insertion sort", blob):

        cases = [

            _case("5\n5 2 4 6 1", "1 2 4 5 6", "Insert each element into sorted left part."),

            _case("3\n3 1 2", "1 2 3", "Classic insertion sort dry run."),

        ]

    elif not cases and re.search(r"merge sort|quick sort", blob):

        cases = [

            _case("6\n38 27 43 3 9 82", "3 9 27 38 43 82", "Divide, sort halves, merge (or partition for quick sort)."),

            _case("4\n10 7 8 9", "7 8 9 10", "Smaller example to trace recursion."),

        ]



    # --- Graph / BFS ---

    elif not cases and re.search(r"bfs|breadth", blob):

        cases = [

            _case("4 4\n0 1\n1 2\n2 3\n0", "0 1 2 3", "BFS from node 0 visits in level order."),

            _case("3 2\n0 1\n0 2", "0 1 2", "Queue explores neighbors layer by layer."),

        ]



    if not cases:

        cases = keyword_fallback_cases(title, code, problem_statement)



    cases = _ensure_two_cases(cases, title, code, problem_statement)



    # Strip any placeholder that slipped through

    cases = [c for c in cases if not is_placeholder_case(c)]

    if len(cases) < 2:

        cases = keyword_fallback_cases(title, code, problem_statement)[:2]



    text = _format_examples_text(cases[:3])

    return text, cases[:3]


