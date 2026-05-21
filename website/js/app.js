const state = {
  questions: [],
  filtered: [],
  activeId: null,
};

const $ = (sel) => document.querySelector(sel);

function escapeHtml(text) {
  const d = document.createElement("div");
  d.textContent = text;
  return d.innerHTML;
}

function formatProse(text) {
  return escapeHtml(text)
    .replace(/\*\*(.+?)\*\*/g, "<strong>$1</strong>")
    .replace(/\n/g, "<br>");
}

function difficultyClass(d) {
  const k = (d || "medium").toLowerCase();
  return `pill pill-${k}`;
}

function buildTopicFilter(questions) {
  const topics = new Set();
  questions.forEach((q) => q.topics.forEach((t) => topics.add(t)));
  const select = $("#topicFilter");
  [...topics].sort().forEach((t) => {
    const opt = document.createElement("option");
    opt.value = t;
    opt.textContent = t;
    select.appendChild(opt);
  });
}

function renderStats(questions) {
  const easy = questions.filter((q) => q.difficulty === "Easy").length;
  const medium = questions.filter((q) => q.difficulty === "Medium").length;
  const hard = questions.filter((q) => q.difficulty === "Hard").length;
  $("#headerStats").innerHTML = `
    <div><strong>${questions.length}</strong><span>Total</span></div>
    <div><strong>${easy}</strong><span>Easy</span></div>
    <div><strong>${medium}</strong><span>Med</span></div>
    <div><strong>${hard}</strong><span>Hard</span></div>
  `;
}

function updateListCount() {
  const el = document.getElementById("listCount");
  if (el) el.textContent = state.filtered.length;
}

function getNavList() {
  return [...state.filtered].sort((a, b) => a.id - b.id);
}

function getNavIndex(id) {
  return getNavList().findIndex((q) => q.id === id);
}

function updateNav() {
  const prevBtn = $("#prevBtn");
  const nextBtn = $("#nextBtn");
  const posEl = $("#navPosition");
  if (!prevBtn || !nextBtn || !posEl) return;

  if (state.activeId == null) {
    prevBtn.disabled = true;
    nextBtn.disabled = true;
    posEl.textContent = "—";
    return;
  }

  const list = getNavList();
  const idx = getNavIndex(state.activeId);
  const total = list.length;
  const totalAll = state.questions.length;

  if (idx < 0) {
    prevBtn.disabled = true;
    nextBtn.disabled = true;
    posEl.textContent = "Not in current filter";
    return;
  }

  prevBtn.disabled = idx <= 0;
  nextBtn.disabled = idx >= total - 1;

  const filteredNote =
    total < totalAll ? ` <span class="nav-filtered">(${total} filtered)</span>` : "";
  posEl.innerHTML = `Question <strong>${String(state.activeId).padStart(2, "0")}</strong> · ${idx + 1} of ${total}${filteredNote}`;
}

function goToAdjacent(direction) {
  if (state.activeId == null) return;
  const list = getNavList();
  const idx = getNavIndex(state.activeId);
  if (idx < 0) return;

  const nextIdx = idx + direction;
  if (nextIdx < 0 || nextIdx >= list.length) return;

  showQuestion(list[nextIdx].id);
  window.scrollTo({ top: 0, behavior: "smooth" });
}

function applyFilters() {
  const q = $("#searchInput").value.trim().toLowerCase();
  const diff = $("#difficultyFilter").value;
  const topic = $("#topicFilter").value;

  state.filtered = state.questions.filter((item) => {
    if (diff && item.difficulty !== diff) return false;
    if (topic && !item.topics.includes(topic)) return false;
    if (!q) return true;
    const hay = [
      item.id,
      item.title,
      item.topics.join(" "),
      item.problemStatement,
      item.timeComplexity,
    ]
      .join(" ")
      .toLowerCase();
    return hay.includes(q) || String(item.id).padStart(2, "0").includes(q);
  });

  renderList();
  updateListCount();
  updateNav();
}

function renderList() {
  const list = $("#questionList");
  if (!state.filtered.length) {
    list.innerHTML = '<p class="empty-list">No questions match your filters.</p>';
    return;
  }

  list.innerHTML = state.filtered
    .map(
      (item) => `
    <button type="button" class="q-item ${item.id === state.activeId ? "active" : ""}"
      data-id="${item.id}" aria-current="${item.id === state.activeId ? "true" : "false"}">
      <span class="q-item-num">#${String(item.id).padStart(2, "0")}</span>
      <span class="q-item-title">${escapeHtml(item.title)}</span>
      <span class="q-item-meta">
        <span class="${difficultyClass(item.difficulty)}">${item.difficulty}</span>
        <span class="pill">${escapeHtml(item.timeComplexity)}</span>
      </span>
    </button>
  `
    )
    .join("");

  list.querySelectorAll(".q-item").forEach((btn) => {
    btn.addEventListener("click", () => showQuestion(Number(btn.dataset.id)));
  });
}

function showQuestion(id) {
  const item = state.questions.find((q) => q.id === id);
  if (!item) return;

  state.activeId = id;
  history.replaceState(null, "", `#q${id}`);

  $("#welcomePanel").classList.add("hidden");
  $("#questionDetail").classList.remove("hidden");

  $("#detailNumber").textContent = String(item.id).padStart(2, "0");
  $("#detailTitle").textContent = item.title;

  const diffKey = (item.difficulty || "medium").toLowerCase();
  const badges = [
    `<span class="badge ${diffKey}">${item.difficulty}</span>`,
    `<span class="badge">${escapeHtml(item.timeComplexity)} time</span>`,
    ...item.topics.map((t) => `<span class="badge topic">${escapeHtml(t)}</span>`),
  ];
  if (item.source) badges.push(`<span class="badge">${escapeHtml(item.source)}</span>`);
  if (item.exam) badges.push(`<span class="badge">${escapeHtml(item.exam)}</span>`);
  $("#detailBadges").innerHTML = badges.join("");

  $("#detailProblem").innerHTML = formatProse(item.problemStatement);
  $("#detailExplanation").innerHTML = formatProse(item.explanation);
  $("#detailTime").textContent = item.timeComplexity;
  $("#detailSpace").textContent = item.spaceComplexity;
  $("#detailCxNote").textContent = item.complexityNote;
  const codeEl = $("#detailCode");
  codeEl.textContent = item.code;
  codeEl.dataset.raw = item.code;

  if (typeof highlightCppCode === "function") {
    highlightCppCode(
      codeEl,
      document.getElementById("codeGutter"),
      item.filename || "solution.cpp"
    );
  }

  renderList();
  updateNav();

  const activeBtn = document.querySelector(`.q-item[data-id="${id}"]`);
  if (activeBtn) activeBtn.scrollIntoView({ block: "nearest", behavior: "smooth" });
}

async function copyCode() {
  const codeEl = $("#detailCode");
  const raw = codeEl.dataset.raw || codeEl.textContent;
  const btn = $("#copyCodeBtn");
  const orig = btn.innerHTML;
  try {
    await navigator.clipboard.writeText(raw);
    btn.innerHTML = orig.replace("Copy", "Copied!");
    btn.classList.add("copied");
    setTimeout(() => {
      btn.innerHTML = orig;
      btn.classList.remove("copied");
    }, 2000);
  } catch {
    btn.classList.add("copied");
  }
}

function initFromHash() {
  const m = location.hash.match(/^#q(\d+)$/);
  if (m) showQuestion(Number(m[1]));
}

async function init() {
  const res = await fetch("data/questions.json");
  state.questions = await res.json();
  state.filtered = [...state.questions];

  buildTopicFilter(state.questions);
  renderStats(state.questions);
  renderList();
  updateListCount();

  $("#searchInput").addEventListener("input", applyFilters);
  $("#difficultyFilter").addEventListener("change", applyFilters);
  $("#topicFilter").addEventListener("change", applyFilters);
  $("#copyCodeBtn").addEventListener("click", copyCode);
  $("#prevBtn").addEventListener("click", () => goToAdjacent(-1));
  $("#nextBtn").addEventListener("click", () => goToAdjacent(1));
  window.addEventListener("hashchange", initFromHash);

  document.addEventListener("keydown", (e) => {
    if (!$("#questionDetail") || $("#questionDetail").classList.contains("hidden")) return;
    const tag = document.activeElement?.tagName;
    if (tag === "INPUT" || tag === "SELECT" || tag === "TEXTAREA") return;

    if (e.key === "ArrowLeft") {
      e.preventDefault();
      goToAdjacent(-1);
    } else if (e.key === "ArrowRight") {
      e.preventDefault();
      goToAdjacent(1);
    }
  });

  initFromHash();
}

init();
