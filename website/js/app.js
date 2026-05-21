const state = {
  questions: [],
  filtered: [],
  edition: "pyq",
  activeId: null,
  copyRaw: "",
};

function editionQuestions(edition = state.edition) {
  return state.questions.filter((q) => q.edition === edition);
}

function findQuestion(edition, id) {
  return state.questions.find((q) => q.edition === edition && q.id === id);
}

function formatQNum(item) {
  const n = String(item.id).padStart(item.edition === "striver" ? 3 : 2, "0");
  return item.edition === "striver" ? n : n;
}

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

function buildTopicFilter() {
  const select = $("#topicFilter");
  const current = select.value;
  select.innerHTML = '<option value="">All topics</option>';
  const topics = new Set();
  editionQuestions().forEach((q) => q.topics.forEach((t) => topics.add(t)));
  [...topics].sort().forEach((t) => {
    const opt = document.createElement("option");
    opt.value = t;
    opt.textContent = t;
    select.appendChild(opt);
  });
  if ([...select.options].some((o) => o.value === current)) select.value = current;
}

function updateEditionCounts() {
  const pyq = editionQuestions("pyq").length;
  const striver = editionQuestions("striver").length;
  const elPyq = $("#countPyq");
  const elStriver = $("#countStriver");
  const welcome = $("#welcomeCount");
  if (elPyq) elPyq.textContent = pyq;
  if (elStriver) elStriver.textContent = striver;
  if (welcome) welcome.textContent = pyq + striver;
}

function renderStats() {
  const pool = editionQuestions();
  const easy = pool.filter((q) => q.difficulty === "Easy").length;
  const medium = pool.filter((q) => q.difficulty === "Medium").length;
  const hard = pool.filter((q) => q.difficulty === "Hard").length;
  const label = state.edition === "striver" ? "Striver" : "PYQ";
  $("#headerStats").innerHTML = `
    <div><strong>${pool.length}</strong><span>${label}</span></div>
    <div><strong>${easy}</strong><span>Easy</span></div>
    <div><strong>${medium}</strong><span>Med</span></div>
    <div><strong>${hard}</strong><span>Hard</span></div>
  `;
}

function setEdition(edition) {
  state.edition = edition;
  $$(".edition-btn").forEach((btn) => {
    btn.classList.toggle("active", btn.dataset.edition === edition);
  });
  const active = findQuestion(state.edition, state.activeId);
  if (!active) {
    state.activeId = null;
    goHome();
  }
  buildTopicFilter();
  applyFilters();
  renderStats();
}

function updateListCount() {
  const el = $("#listCount");
  if (el) el.textContent = state.filtered.length;
}

function getNavList() {
  return [...state.filtered].sort((a, b) => a.id - b.id);
}

function getNavIndex(id) {
  return getNavList().findIndex((q) => q.id === id && q.edition === state.edition);
}

function updateNav() {
  const prevBtns = $$(".js-nav-prev");
  const nextBtns = $$(".js-nav-next");
  const posEls = $$(".js-nav-position");
  const fills = $$(".js-nav-progress-fill");
  if (!prevBtns.length || !posEls.length) return;

  const setDisabled = (disabled) => {
    prevBtns.forEach((b) => (b.disabled = disabled));
    nextBtns.forEach((b) => (b.disabled = disabled));
  };

  const setPosition = (html) => posEls.forEach((el) => (el.innerHTML = html));
  const setProgress = (pct) => fills.forEach((el) => (el.style.width = `${pct}%`));

  if (state.activeId == null) {
    setDisabled(true);
    setPosition("—");
    setProgress(0);
    return;
  }

  const list = getNavList();
  const idx = getNavIndex(state.activeId);
  const total = list.length;
  const totalAll = editionQuestions().length;

  if (idx < 0) {
    setDisabled(true);
    setPosition("Not in current filter");
    setProgress(0);
    return;
  }

  prevBtns.forEach((b) => (b.disabled = idx <= 0));
  nextBtns.forEach((b) => (b.disabled = idx >= total - 1));

  const pct = total > 1 ? ((idx + 1) / total) * 100 : 100;
  setProgress(pct);

  const filteredNote =
    total < totalAll ? ` <span class="nav-filtered">(${total} shown)</span>` : "";
  const pad = state.edition === "striver" ? 3 : 2;
  const prefix = state.edition === "striver" ? "S" : "";
  setPosition(
    `<strong>${prefix}${String(state.activeId).padStart(pad, "0")}</strong> · ${idx + 1} / ${total}${filteredNote}`
  );
}

function goToAdjacent(direction) {
  if (state.activeId == null) return;
  const list = getNavList();
  const idx = getNavIndex(state.activeId);
  if (idx < 0) return;
  const nextIdx = idx + direction;
  if (nextIdx < 0 || nextIdx >= list.length) return;
  const next = list[nextIdx];
  showQuestion(next.edition, next.id);
  $("#mainContent")?.scrollTo({ top: 0, behavior: "smooth" });
}

function renderExplainedCode(item) {
  const container = $("#codeExplained");
  if (!container) return;

  const lines = item.codeLines?.length
    ? item.codeLines
    : (item.code || "").split("\n").map((text, i) => ({
        num: i + 1,
        text,
        note: "",
        important: false,
      }));

  const hl = typeof window.highlightCpp === "function" ? window.highlightCpp : (s) => escapeHtml(s);

  container.innerHTML = lines
    .map((row) => {
      const empty = !row.text.trim();
      const key = row.important && row.note;
      const codeHtml = row.text ? hl(row.text) : "&nbsp;";
      const noteHtml = row.note
        ? `<aside class="line-note">${escapeHtml(row.note)}</aside>`
        : `<aside class="line-note line-note--empty" aria-hidden="true"></aside>`;
      return `
        <div class="code-row ${key ? "code-row--key" : ""} ${empty ? "code-row--blank" : ""}">
          <span class="code-ln">${row.num}</span>
          <pre class="code-line"><code>${codeHtml}</code></pre>
          ${noteHtml}
        </div>`;
    })
    .join("");

  const tab = $("#codeTabName");
  if (tab) tab.textContent = item.filename || "solution.cpp";
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
    if (item.edition !== state.edition) return false;
    if (diff && item.difficulty !== diff) return false;
    if (topic && !item.topics.includes(topic)) return false;
    if (!q) return true;
    const hay = [
      item.edition,
      item.id,
      item.title,
      item.topics.join(" "),
      item.problemStatement,
      item.timeComplexity,
    ]
      .join(" ")
      .toLowerCase();
    const pad = item.edition === "striver" ? 3 : 2;
    return hay.includes(q) || String(item.id).padStart(pad, "0").includes(q);
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
    .map((item) => {
      const pad = item.edition === "striver" ? 3 : 2;
      const active = item.id === state.activeId && item.edition === state.edition;
      const edClass = item.edition === "striver" ? "q-item-edition--striver" : "q-item-edition--pyq";
      return `
    <button type="button" class="q-item ${active ? "active" : ""}"
      data-id="${item.id}" data-edition="${item.edition}" aria-current="${active ? "true" : "false"}">
      <span class="q-item-num">
        <span class="q-item-edition ${edClass}">${item.edition === "striver" ? "STR" : "PYQ"}</span>
        ${String(item.id).padStart(pad, "0")}
      </span>
      <span class="q-item-title">${escapeHtml(item.title)}</span>
      <span class="q-item-meta">
        <span class="${difficultyClass(item.difficulty)}">${item.difficulty}</span>
        <span class="pill">${escapeHtml(item.timeComplexity)}</span>
      </span>
    </button>`;
    })
    .join("");

  list.querySelectorAll(".q-item").forEach((btn) => {
    btn.addEventListener("click", () => {
      showQuestion(btn.dataset.edition, Number(btn.dataset.id));
      openSidebar(false);
    });
  });
}

function showQuestion(edition, id) {
  const item = findQuestion(edition, id);
  if (!item) return;

  if (state.edition !== edition) setEdition(edition);

  state.activeId = id;
  history.replaceState(null, "", `#${edition}-${id}`);

  $("#welcomePanel")?.classList.add("hidden");
  $("#questionDetail")?.classList.remove("hidden");

  const pad = item.edition === "striver" ? 3 : 2;
  $("#detailNumber").textContent = String(item.id).padStart(pad, "0");
  const pool = editionQuestions(item.edition);
  $("#detailEyebrow").textContent = `${item.editionLabel || item.edition} · ${item.id} of ${pool.length}`;
  $("#detailTitle").textContent = item.title;

  const diffKey = (item.difficulty || "medium").toLowerCase();
  const edBadge =
    item.edition === "striver"
      ? '<span class="badge edition-striver">Striver 100</span>'
      : '<span class="badge edition-pyq">PYQ</span>';
  const badges = [
    edBadge,
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

  state.copyRaw = item.code || "";
  renderExplainedCode(item);
  renderList();
  updateNav();

  const activeBtn = document.querySelector(
    `.q-item[data-id="${id}"][data-edition="${edition}"]`
  );
  activeBtn?.scrollIntoView({ block: "nearest", behavior: "smooth" });
}

function pickRandom() {
  const list = getNavList();
  if (!list.length) return;
  const item = list[Math.floor(Math.random() * list.length)];
  showQuestion(item.edition, item.id);
}

async function copyCode() {
  const raw = state.copyRaw;
  const btn = $("#copyCodeBtn");
  const orig = btn.innerHTML;
  try {
    await navigator.clipboard.writeText(raw);
    btn.innerHTML = orig.replace("Copy code", "Copied!");
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
  const m = location.hash.match(/^#(pyq|striver)-(\d+)$/);
  if (m) showQuestion(m[1], Number(m[2]));
  const legacy = location.hash.match(/^#q(\d+)$/);
  if (legacy) showQuestion("pyq", Number(legacy[1]));
}

function isTypingContext() {
  const tag = document.activeElement?.tagName;
  return tag === "INPUT" || tag === "SELECT" || tag === "TEXTAREA";
}

async function init() {
  const res = await fetch("data/questions.json");
  state.questions = await res.json();
  updateEditionCounts();
  buildTopicFilter();
  setEdition(state.edition);
  renderStats();
  renderList();
  updateListCount();

  $$(".edition-btn").forEach((btn) => {
    btn.addEventListener("click", () => setEdition(btn.dataset.edition));
  });

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

  $("#startBtn")?.addEventListener("click", () => {
    const first = getNavList()[0];
    if (first) showQuestion(first.edition, first.id);
  });
  $("#randomBtn")?.addEventListener("click", pickRandom);
  $("#brandHome")?.addEventListener("click", (e) => {
    e.preventDefault();
    goHome();
  });
  $("#copyCodeBtn")?.addEventListener("click", copyCode);

  $("#questionDetail")?.addEventListener("click", (e) => {
    if (e.target.closest(".js-nav-prev")) {
      e.preventDefault();
      goToAdjacent(-1);
    } else if (e.target.closest(".js-nav-next")) {
      e.preventDefault();
      goToAdjacent(1);
    }
  });
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
    } else if ((e.ctrlKey || e.metaKey) && e.shiftKey && e.key.toLowerCase() === "c") {
      e.preventDefault();
      copyCode();
    }
  });

  initFromHash();
}

init();
