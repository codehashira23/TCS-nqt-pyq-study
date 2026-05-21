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

## Troubleshooting

| Issue | Fix |
|-------|-----|
| Pages workflow failed | Repo → **Actions** → open the failed run and read the error |
| Blank page / 404 | Ensure Pages source is **GitHub Actions**, not “Deploy from branch” with wrong folder |
| `questions.json` missing | Workflow runs `build_questions.py`; push all `.cpp` files to the repo |
| Site shows old content | Hard refresh (Ctrl+Shift+R) or wait for CDN cache |
