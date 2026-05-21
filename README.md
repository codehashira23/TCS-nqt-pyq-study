# TCS NQT PYQ — Self Study Website

A static study site for all **72** TCS NQT previous-year C++ questions. Each question includes:

- Problem statement & constraints
- Full C++ solution (copy button)
- Explanation & approach notes
- Time & space complexity

## Quick start

1. Regenerate data after editing any `.cpp` file:

   ```bash
   python scripts/build_questions.py
   ```

2. Serve the website (needs a local server for `fetch`):

   ```bash
   cd website
   python -m http.server 8080
   ```

3. Open [http://localhost:8080](http://localhost:8080)

## Project layout

| Path | Purpose |
|------|---------|
| `*.cpp` | Source questions with comments |
| `scripts/build_questions.py` | Parser → `website/data/questions.json` |
| `website/` | HTML/CSS/JS study UI |

## Deploy (live website)

**Full steps:** see [DEPLOY.md](DEPLOY.md)

1. Create a public repo on GitHub (empty, no README).
2. Push this project:

   ```powershell
   git remote add origin https://github.com/YOUR_USERNAME/YOUR_REPO.git
   git push -u origin main
   ```

3. Repo **Settings → Pages → Source:** choose **GitHub Actions**.
4. After the workflow runs, your site is at `https://YOUR_USERNAME.github.io/YOUR_REPO/`

**Quick alternative:** drag the `website` folder to [Netlify Drop](https://app.netlify.com/drop) (no Git needed).
