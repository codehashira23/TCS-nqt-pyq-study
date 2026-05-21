# Deploy TCS NQT Study Site (GitHub Pages)

Your site lives in the `website/` folder. GitHub Actions builds `questions.json` and publishes automatically on every push to `main`.

## Step 1 — Create a GitHub repository

1. Open [https://github.com/new](https://github.com/new)
2. Repository name: e.g. `tcs-nqt-pyq-study` (any name works)
3. Set visibility to **Public** (required for free GitHub Pages on personal accounts)
4. **Do not** add README, .gitignore, or license (this project already has them)
5. Click **Create repository**

## Step 2 — Push this project

Replace `YOUR_USERNAME` and `YOUR_REPO` with your GitHub username and repo name.

```powershell
cd "c:\Users\divya\Desktop\tcsnqt\tcs nqt\tcs_pyq_cpp_files"

git remote add origin https://github.com/YOUR_USERNAME/YOUR_REPO.git
git push -u origin main
```

If Git asks you to sign in, use a [Personal Access Token](https://github.com/settings/tokens) as the password (scope: `repo`).

## Step 3 — Enable GitHub Pages

1. On GitHub, open your repo → **Settings** → **Pages**
2. Under **Build and deployment** → **Source**, choose **GitHub Actions**
3. Wait 1–2 minutes for the workflow **Deploy to GitHub Pages** to finish (tab **Actions**)
4. Your live URL will look like:

   `https://YOUR_USERNAME.github.io/YOUR_REPO/`

## Step 4 — Update the site later

After editing `.cpp` files or the website:

```powershell
python scripts/build_questions.py   # optional locally; CI runs this too
git add .
git commit -m "Update questions or site"
git push
```

The site redeploys automatically within a few minutes.

---

## Alternative: Netlify (no Git required)

1. Go to [https://app.netlify.com/drop](https://app.netlify.com/drop)
2. Drag the **`website`** folder onto the page
3. Netlify gives you a random URL instantly; you can rename it in site settings

Run `python scripts/build_questions.py` before dragging if you changed any `.cpp` files.

---

## Custom domain (`tcsnqt.io`)

GitHub repo: **codehashira23/TCS-nqt-pyq-study**

### A) Get the default site working first

1. **Settings → Pages → Build and deployment → Source** → choose **GitHub Actions** (not Jekyll, not “Static HTML” buttons on that screen).
2. **Actions** tab → run **Deploy to GitHub Pages** (or push any commit).
3. When green, open: **https://codehashira23.github.io/TCS-nqt-pyq-study/**

Only after that works, configure the custom domain below.

### B) DNS at your domain registrar (where you bought tcsnqt.io)

Log in to GoDaddy / Namecheap / Cloudflare / etc. and add:

**For root domain `tcsnqt.io` (recommended):**

| Type | Host / Name | Value |
|------|-------------|--------|
| A | `@` | `185.199.108.153` |
| A | `@` | `185.199.109.153` |
| A | `@` | `185.199.110.153` |
| A | `@` | `185.199.111.153` |

**Optional — also support `www.tcsnqt.io`:**

| Type | Host / Name | Value |
|------|-------------|--------|
| CNAME | `www` | `codehashira23.github.io` |

Remove any old A/CNAME records that conflict. Save and wait **15 minutes – 48 hours** for DNS to propagate.

### C) GitHub Pages custom domain field

1. **Settings → Pages → Custom domain** → enter `tcsnqt.io` → **Save**
2. Wait until **DNS check** turns green.
3. Then enable **Enforce HTTPS** (only available after DNS is valid).

The file `website/CNAME` in this repo tells GitHub to use `tcsnqt.io` on each deploy.

---

## Troubleshooting

| Issue | Fix |
|-------|-----|
| Pages workflow failed | Repo → **Actions** → open the failed run and read the error |
| Blank page / 404 | Ensure Pages source is **GitHub Actions**, not “Deploy from branch” with wrong folder |
| `questions.json` missing | Workflow runs `build_questions.py`; push all `.cpp` files to the repo |
| Site shows old content | Hard refresh (Ctrl+Shift+R) or wait for CDN cache |
