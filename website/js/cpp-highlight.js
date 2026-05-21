/**
 * Lightweight C++ highlighter using VS Code Dracula token colors.
 * https://draculatheme.com
 */
const DRACULA = {
  keyword: "#ff79c6",
  type: "#8be9fd",
  string: "#f1fa8c",
  number: "#bd93f9",
  comment: "#6272a4",
  function: "#50fa7b",
  preprocessor: "#ff79c6",
  operator: "#ff79c6",
  punctuation: "#f8f8f2",
  plain: "#f8f8f2",
};

const CPP_KEYWORDS = new Set([
  "alignas", "alignof", "and", "and_eq", "asm", "auto", "bitand", "bitor",
  "break", "case", "catch", "class", "compl", "const", "constexpr",
  "const_cast", "continue", "decltype", "default", "delete", "do", "dynamic_cast",
  "else", "enum", "explicit", "export", "extern", "false", "for", "friend",
  "goto", "if", "inline", "mutable", "namespace", "new", "noexcept", "not",
  "not_eq", "nullptr", "operator", "or", "or_eq", "private", "protected",
  "public", "register", "reinterpret_cast", "return", "sizeof", "static",
  "static_assert", "static_cast", "struct", "switch", "template", "this",
  "thread_local", "throw", "true", "try", "typedef", "typeid", "typename",
  "union", "using", "virtual", "void", "volatile", "while", "xor", "xor_eq",
  "int", "long", "short", "char", "bool", "float", "double", "signed", "unsigned",
  "vector", "string", "map", "set", "queue", "stack", "pair", "array", "list",
  "cin", "cout", "cerr", "endl", "ios", "std", "namespace",
]);

const CPP_TYPES = new Set([
  "std", "string", "vector", "map", "set", "queue", "stack", "pair",
  "stringstream", "priority_queue", "unordered_map", "unordered_set",
]);

function span(cls, text) {
  const color = DRACULA[cls] || DRACULA.plain;
  return `<span class="hl-${cls}" style="color:${color}">${escapeHl(text)}</span>`;
}

function escapeHl(s) {
  return s
    .replace(/&/g, "&amp;")
    .replace(/</g, "&lt;")
    .replace(/>/g, "&gt;");
}

function highlightCpp(code) {
  let out = "";
  let i = 0;
  const n = code.length;

  while (i < n) {
    // Line comment
    if (code[i] === "/" && code[i + 1] === "/") {
      let j = i + 2;
      while (j < n && code[j] !== "\n") j++;
      out += span("comment", code.slice(i, j));
      i = j;
      continue;
    }
    // Block comment
    if (code[i] === "/" && code[i + 1] === "*") {
      let j = i + 2;
      while (j < n - 1 && !(code[j] === "*" && code[j + 1] === "/")) j++;
      j = Math.min(j + 2, n);
      out += span("comment", code.slice(i, j));
      i = j;
      continue;
    }
    // Preprocessor line
    if (code[i] === "#") {
      let j = i;
      while (j < n && code[j] !== "\n") j++;
      out += span("preprocessor", code.slice(i, j));
      i = j;
      continue;
    }
    // String / char
    if (code[i] === '"' || code[i] === "'") {
      const q = code[i];
      let j = i + 1;
      while (j < n) {
        if (code[j] === "\\") { j += 2; continue; }
        if (code[j] === q) { j++; break; }
        j++;
      }
      out += span("string", code.slice(i, j));
      i = j;
      continue;
    }
    // Number
    if (/[0-9]/.test(code[i]) || (code[i] === "." && /[0-9]/.test(code[i + 1]))) {
      let j = i;
      while (j < n && /[0-9.xXa-fA-FlLuU]/.test(code[j])) j++;
      out += span("number", code.slice(i, j));
      i = j;
      continue;
    }
    // Identifier
    if (/[a-zA-Z_]/.test(code[i])) {
      let j = i;
      while (j < n && /[a-zA-Z0-9_]/.test(code[j])) j++;
      const word = code.slice(i, j);
      let k = j;
      while (k < n && /\s/.test(code[k])) k++;
      const isFunc = k < n && code[k] === "(";
      if (CPP_KEYWORDS.has(word)) out += span("keyword", word);
      else if (isFunc || word === "main") out += span("function", word);
      else if (CPP_TYPES.has(word) || /^[A-Z]/.test(word) || word.endsWith("_t"))
        out += span("type", word);
      else out += span("plain", word);
      i = j;
      continue;
    }
    // Operators
    if (/[+\-*/%=<>!&|^~?:]/.test(code[i])) {
      let j = i;
      while (j < n && /[+\-*/%=<>!&|^~?:]/.test(code[j])) j++;
      out += span("operator", code.slice(i, j));
      i = j;
      continue;
    }
    // Brackets
    if (/[{}()[\];,.]/.test(code[i])) {
      out += span("punctuation", code[i]);
      i++;
      continue;
    }
    out += escapeHl(code[i]);
    i++;
  }
  return out;
}

function buildLineNumbers(code) {
  const lines = code.split("\n");
  return lines.map((_, idx) => `<span>${idx + 1}</span>`).join("");
}

window.highlightCpp = highlightCpp;

window.highlightCppCode = function (codeEl, gutterEl, filename) {
  const raw = codeEl.textContent || "";
  codeEl.innerHTML = highlightCpp(raw);
  if (gutterEl) gutterEl.innerHTML = buildLineNumbers(raw);
  const tab = document.getElementById("codeTabName");
  if (tab && filename) tab.textContent = filename;
};
