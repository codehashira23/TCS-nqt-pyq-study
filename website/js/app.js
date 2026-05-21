const state = {
  questions: [],
  filtered: [],
  activeId: null,
  activeSection: "problem",
};

const $ = (sel) => document.querySelector(sel);
const $$ = (sel) => document.querySelectorAll(sel);

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
  return `pill pill-${(d || "medium").toLowerCase()}`;
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
  const el = $("#listCount");
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
  const fill = $("#navProgressFill");
  if (!prevBtn || !nextBtn || !posEl) return;

  if (state.activeId == null) {
    prevBtn.disabled = true;
    nextBtn.disabled = true;
    posEl.textContent = "—";
    if (fill) fill.style.width = "0%";
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
    if (fill) fill.style.width = "0%";
    return;
  }

  prevBtn.disabled = idx <= 0;
  nextBtn.disabled = idx >= total - 1;

  const pct = total > 1 ? ((idx + 1) / total) * 100 : 100;
  if (fill) fill.style.width = `${pct}%`;

  const filteredNote =
    total < totalAll ? ` <span class="nav-filtered">(${total} shown)</span>` : "";
  posEl.innerHTML = `<strong>#${String(state.activeId).padStart(2, "0")}</strong> · ${idx + 1} / ${total}${filteredNote}`;
}

function goToAdjacent(direction) {
  if (state.activeId == null) return;
  const list = getNavList();
  const idx = getNavIndex(state.activeId);
  if (idx < 0) return;
  const nextIdx = idx + direction;
  if (nextIdx < 0 || nextIdx >= list.length) return;
  showQuestion(list[nextIdx].id);
  $("#mainContent")?.scrollTo({ top: 0, behavior: "smooth" });
}

function setActiveSection(section) {
  state.activeSection = section;
  $$(".section-tab").forEach((tab) => {
    const on = tab.dataset.section === section;
    tab.classList.toggle("active", on);
    tab.setAttribute("aria-selected", on ? "true" : "false");
  });
  $$("[data-panel]").forEach((panel) => {
    const on = panel.dataset.panel === section;
    panel.classList.toggle("hidden-panel", !on);
    panel.hidden = !on;
  });
}

function openSidebar(open) {
  const sidebar = $("#sidebar");
  const backdrop = $("#sidebarBackdrop");
  const toggle = $("#menuToggle");
  if (!sidebar) return;
  sidebar.classList.toggle("open", open);
  backdrop?.classList.toggle("visible", open);
  if (backdrop) backdrop.hidden = !open;
  toggle?.setAttribute("aria-expanded", open ? "true" : "false");
}

function goHome() {
  state.activeId = null;
  history.replaceState(null, "", location.pathname);
  $("#welcomePanel")?.classList.remove("hidden");
  $("#questionDetail")?.classList.add("hidden");
  updateNav();
  $("#readProgress").style.width = "0%";
}

function updateReadProgress() {
  const main = $("#mainContent");
  const bar = $("#readProgress");
  if (!main || !bar || $("#questionDetail")?.classList.contains("hidden")) {
    bar.style.width = "0%";
    return;
  }
  const max = main.scrollHeight - main.clientHeight;
  const pct = max > 0 ? (main.scrollTop / max) * 100 : 0;
  bar.style.width = `${pct}%`;
}

function applyFilters() {
  const q = $("#searchInput").value.trim().toLowerCase();
  const diff = $("#difficultyFilter").value;
  const topic = $("#topicFilter").value;

  state.filtered = state.questions.filter((item) => {
    if (diff && item.difficulty !== diff) return false;
    if (topic && !item.topics.includes(topic)) return false;
    if (!q) return true;
    const hay = [item.id, item.title, item.topics.join(" "), item.problemStatement, item.timeComplexity]
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
    list.innerHTML = '<p class="empty-list">No questions match.<br>Try clearing filters.</p>';
    return;
  }

  list.innerHTML = state.filtered
    .map(
      (item) => `
    <button type="button" class="q-item ${item.id === state.activeId ? "active" : ""}"
      data-id="${item.id}" aria-current="${item.id === state.activeId ? "true" : "false"}">
      <span class="q-item-num">${String(item.id).padStart(2, "0")}</span>
      <span class="q-item-title">${escapeHtml(item.title)}</span>
      <span class="q-item-meta">
        <span class="${difficultyClass(item.difficulty)}">${item.difficulty}</span>
        <span class="pill">${escapeHtml(item.timeComplexity)}</span>
      </span>
    </button>`
    )
    .join("");

  list.querySelectorAll(".q-item").forEach((btn) => {
    btn.addEventListener("click", () => {
      showQuestion(Number(btn.dataset.id));
      openSidebar(false);
    });
  });
}

function showQuestion(id) {
  const item = state.questions.find((q) => q.id === id);
  if (!item) return;

  state.activeId = id;
  history.replaceState(null, "", `#q${id}`);

  $("#welcomePanel")?.classList.add("hidden");
  $("#questionDetail")?.classList.remove("hidden");

  $("#detailNumber").textContent = String(item.id).padStart(2, "0");
  $("#detailEyebrow").textContent = `Question ${item.id} of ${state.questions.length}`;
  $("#detailTitle").textContent = item.title;

  const diffKey = (item.difficulty || "medium").toLowerCase();
  const badges = [
    `<span class="badge ${diffKey}">${item.difficulty}</span>`,
    `<span class="badge">${escapeHtml(item.timeComplexity)}</span>`,
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
    highlightCppCode(codeEl, $("#codeGutter"), item.filename || "solution.cpp");
  }

  setActiveSection(state.activeSection);
  renderList();
  updateNav();

  const activeBtn = document.querySelector(`.q-item[data-id="${id}"]`);
  activeBtn?.scrollIntoView({ block: "nearest", behavior: "smooth" });
}

function pickRandom() {
  const list = getNavList();
  if (!list.length) return;
  const item = list[Math.floor(Math.random() * list.length)];
  showQuestion(item.id);
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

function syncDifficultyChips() {
  const val = $("#difficultyFilter").value;
  $$(".chip[data-diff]").forEach((chip) => {
    chip.classList.toggle("active", chip.dataset.diff === val);
  });
}

function initFromHash() {
  const m = location.hash.match(/^#q(\d+)$/);
  if (m) showQuestion(Number(m[1]));
}

function isTypingContext() {
  const tag = document.activeElement?.tagName;
  return tag === "INPUT" || tag === "SELECT" || tag === "TEXTAREA";
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
  $("#topicFilter").addEventListener("change", applyFilters);
  $("#difficultyFilter").addEventListener("change", () => {
    syncDifficultyChips();
    applyFilters();
  });

  $$(".chip[data-diff]").forEach((chip) => {
    chip.addEventListener("click", () => {
      $("#difficultyFilter").value = chip.dataset.diff;
      syncDifficultyChips();
      applyFilters();
    });
  });

  $$(".section-tab").forEach((tab) => {
    tab.addEventListener("click", () => setActiveSection(tab.dataset.section));
  });

  $("#startBtn")?.addEventListener("click", () => {
    const first = getNavList()[0];
    if (first) showQuestion(first.id);
  });
  $("#randomBtn")?.addEventListener("click", pickRandom);
  $("#brandHome")?.addEventListener("click", (e) => {
    e.preventDefault();
    goHome();
  });
  $("#copyCodeBtn")?.addEventListener("click", copyCode);
  $("#prevBtn")?.addEventListener("click", () => goToAdjacent(-1));
  $("#nextBtn")?.addEventListener("click", () => goToAdjacent(1));
  $("#menuToggle")?.addEventListener("click", () => {
    const open = !$("#sidebar")?.classList.contains("open");
    openSidebar(open);
  });
  $("#sidebarClose")?.addEventListener("click", () => openSidebar(false));
  $("#sidebarBackdrop")?.addEventListener("click", () => openSidebar(false));

  $("#mainContent")?.addEventListener("scroll", updateReadProgress);
  window.addEventListener("hashchange", initFromHash);
  window.addEventListener("resize", () => {
    if (window.innerWidth > 1024) openSidebar(false);
  });

  document.addEventListener("keydown", (e) => {
    if (e.key === "/" && !isTypingContext()) {
      e.preventDefault();
      $("#searchInput")?.focus();
      openSidebar(true);
      return;
    }

    if ($("#questionDetail")?.classList.contains("hidden") || isTypingContext()) return;

    if (e.key === "ArrowLeft") {
      e.preventDefault();
      goToAdjacent(-1);
    } else if (e.key === "ArrowRight") {
      e.preventDefault();
      goToAdjacent(1);
    } else if (e.key === "1") setActiveSection("problem");
    else if (e.key === "2") setActiveSection("complexity");
    else if (e.key === "3") setActiveSection("explanation");
    else if (e.key === "4") setActiveSection("code");
    else if ((e.ctrlKey || e.metaKey) && e.shiftKey && e.key.toLowerCase() === "c") {
      e.preventDefault();
      copyCode();
    }
  });

  initFromHash();
}

init();
