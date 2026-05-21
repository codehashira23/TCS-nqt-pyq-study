/**
 * Global visit counter — fixed bottom-right.
 * Uses Page Views API (https://page-views-api.ratneshc.com).
 */
(function () {
  const API = "https://page-views-api.ratneshc.com/api/v1";
  const PATH = "/";
  const SESSION_FLAG = "tcsnqt_pv_tracked";

  const countEl = document.getElementById("visitCount");
  const widget = document.getElementById("visitCounter");
  if (!countEl || !widget) return;

  function siteId() {
    const h = location.hostname.replace(/^www\./, "").toLowerCase();
    if (!h || h === "localhost" || h === "127.0.0.1") return "tcsnqt-dev";
    return h;
  }

  function formatCount(n) {
    if (typeof n !== "number" || Number.isNaN(n)) return "—";
    return n.toLocaleString("en-IN");
  }

  function setCount(value) {
    countEl.textContent = formatCount(value);
    countEl.removeAttribute("data-loading");
    widget.classList.add("visit-counter--ready");
  }

  function qs(params) {
    return new URLSearchParams(params).toString();
  }

  async function fetchViews(site) {
    const res = await fetch(`${API}/views?${qs({ site, path: PATH })}`, {
      cache: "no-store",
    });
    if (!res.ok) throw new Error(`views HTTP ${res.status}`);
    const data = await res.json();
    if (typeof data.views !== "number") throw new Error("invalid views payload");
    return data.views;
  }

  async function trackVisit(site) {
    await fetch(`${API}/track?${qs({ site, path: PATH })}`, {
      method: "GET",
      keepalive: true,
      cache: "no-store",
    });
  }

  function shouldTrack() {
    try {
      if (sessionStorage.getItem(SESSION_FLAG)) return false;
      sessionStorage.setItem(SESSION_FLAG, "1");
      return true;
    } catch {
      return true;
    }
  }

  function localFallback(increment) {
    const key = `tcsnqt_visits_${siteId()}`;
    let n = 0;
    try {
      n = parseInt(localStorage.getItem(key) || "0", 10) || 0;
      if (increment) {
        n += 1;
        localStorage.setItem(key, String(n));
      }
    } catch {
      n = increment ? 1 : 0;
    }
    return n;
  }

  async function init() {
    const site = siteId();
    const increment = shouldTrack();

    try {
      if (increment) await trackVisit(site);
      setCount(await fetchViews(site));
      return;
    } catch {
      /* API unavailable */
    }

    const local = localFallback(increment);
    setCount(local);
    widget.setAttribute(
      "title",
      "Offline mode — visit count is estimated for this browser only"
    );
  }

  init();
})();
