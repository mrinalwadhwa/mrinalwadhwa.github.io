# Instructions for AI Coding Agents

This is a static personal website for Mrinal Wadhwa at mrinal.com. It uses pure HTML/CSS with no build system or templating.

## Adding a New Article

1. **Create the post directory and file:**
   ```
   articles/
   └── your-post-slug/
       └── index.html
   ```
   Use lowercase, hyphenated slugs (e.g., `my-new-post`).

2. **Copy the structure from an existing post** (e.g., `articles/example-post/index.html`) and update:
   - `<title>` - "Post Title – Mrinal Wadhwa"
   - `<meta name="description">` - Brief description
   - `<link rel="canonical">` - https://mrinal.com/articles/your-post-slug/
   - Open Graph and Twitter Card meta tags
   - `.article-meta` - Update the date
   - `.article-title` - The article title
   - `.article-content` - Your content

3. **Create a markdown version** at `articles/your-post-slug/index.md` with the article's plain text content (no HTML). This is used by `llms.txt` for LLM-readable access.

4. **Update llms.txt:**
   Add a new entry under `## Pages`:
   ```
   - [Article Title](/articles/your-post-slug/index.md)
   ```

5. **Update index.html articles listing:**
   Add a new `<li>` inside `.article-list`, newest first:
   ```html
   <li>
       <a href="/articles/your-post-slug/">Article Title</a>
       <span class="article-date">January 18, 2026</span>
   </li>
   ```

6. **Update articles/index.html listing:**
   Add the same `<li>` inside `.article-list-page`, newest first.

7. **Update follow/rss.xml:**
   Add a new `<item>` after the comment, newest first:
   ```xml
   <item>
       <title>Article Title</title>
       <link>https://mrinal.com/articles/your-post-slug/</link>
       <guid>https://mrinal.com/articles/your-post-slug/</guid>
       <pubDate>Sat, 18 Jan 2026 00:00:00 GMT</pubDate>
       <description>Brief description of the article.</description>
   </item>
   ```

8. **Update sitemap.xml:**
   Add a new `<url>` entry:
   ```xml
   <url>
       <loc>https://mrinal.com/articles/your-post-slug/</loc>
       <lastmod>2026-01-18</lastmod>
       <changefreq>monthly</changefreq>
       <priority>0.6</priority>
   </url>
   ```

## Date Formats

- **index.html listing:** "January 18, 2026"
- **Blog post meta:** "January 18, 2026"
- **RSS pubDate:** RFC 822 format - "Sat, 18 Jan 2026 00:00:00 GMT"

## URL Structure

- Articles: `/articles/post-slug/` (directory with index.html)
- RSS feed: `/follow/rss.xml`

## Writing Style

- Never use em-dashes. Use commas, periods, semicolons, or restructure the sentence instead.

## Styling

The site uses a modular scale with ratio 1.625:
- 0.379em, 0.616em, 1em, 1.625em, 2.641em, 4.291em, 6.973em

Each blog post can have custom CSS in `<style>` tags and custom JS in `<script>` tags at the bottom.

## Vertical Rhythm & Baseline Grid

The site maintains a consistent vertical rhythm based on a 1.5em baseline unit.

### Base Unit
- **1 unit = 1.5em** (24px at 16px base)
- All vertical spacing should be multiples: 0.75em (0.5u), 1.5em (1u), 3em (2u), 4.5em (3u), 6em (4u), etc.

### Debug Tool
Press **'g'** to toggle a baseline grid overlay for visual alignment checking.

### Key Principles

1. **Scaled font sizes need adjusted line-heights**
   When using a font-size other than 1em, calculate line-height to produce rhythm-aligned lines:
   ```
   line-height = target_line_em / font_size
   ```
   Example for `.content` (font-size: 1.275em, target: 2em per line):
   ```css
   line-height: 1.568628; /* 2em / 1.275em */
   ```

2. **Margins in scaled contexts**
   Margins are relative to the element's font-size. To get 1.5em in base units:
   ```
   margin = 1.5 / font_size
   ```
   Example for `.content p` (font-size: 1.275em):
   ```css
   margin: 0 0 1.176471em; /* 1.5em / 1.275 */
   ```

3. **Fixed-height wrappers for non-text elements**
   Photos, display fonts, and videos break rhythm. Contain them in wrappers with heights that are multiples of 1.5em:
   ```css
   .profile-photo-wrapper { height: 12em; /* 8 units */ }
   .video-carousel { height: 24em; /* 16 units */ }
   ```

4. **Border compensation**
   Borders add pixels that break rhythm. Subtract from padding:
   ```css
   padding-top: calc(1.5em - 1px); /* 1 unit minus border */
   border-top: 1px solid #ddd;
   ```

5. **Multi-line rhythm alignment**
   When exact per-line alignment isn't possible, align every N lines:
   - 3 lines = 4 units: `line-height = 2em / font_size` (each line 2em, 3 lines = 6em = 4 units)
   
6. **Avoid vertical-align offsets on inline elements**
   `vertical-align: -0.125em` on icons expands line boxes. Use flexbox with `align-items: center` instead.

7. **Last element margin**
   Remove default margin from last elements, then add back what's needed to hit the grid:
   ```css
   .content p:last-child {
       margin-bottom: 1.568628em; /* completes rhythm cycle */
   }
   ```

### Use Python for Calculations
Always use Python to verify rhythm calculations - avoid rounding errors:
```python
font_size = 1.275
target_line = 2.0  # em in base units
line_height = target_line / font_size
print(f'line-height: {line_height:.6f}')
# Verify: font_size * line_height should equal target
```

### Common Pitfalls
- Forgetting that em-based margins scale with the element's font-size
- Using line-heights that don't produce unit multiples (e.g., 1.25 doesn't align)
- Icon vertical-align pushing line boxes taller
- Margin collapsing causing unexpected spacing
- Rounding errors accumulating across many lines - use precise decimal values

## Generating OG Images for Social Sharing

Use the `agent-browser` CLI to generate Open Graph images (1200×630) for article previews on Reddit, Twitter, etc.

### Setup
```bash
export PATH="$HOME/.npm-packages/bin:$PATH"
```

### Generate an OG image for an article
```bash
agent-browser open "https://mrinal.com/articles/your-post-slug/"
agent-browser set viewport 1200 630
agent-browser eval "<JS to adjust layout for screenshot>"
agent-browser screenshot articles/your-post-slug/og.png
```

The JS will vary per article layout. Typically you'll want to hide non-essential elements and expand the main content to fill the 1200×630 viewport.

### Add meta tags to the article's index.html
```html
<!-- In Open Graph section -->
<meta property="og:image" content="https://mrinal.com/articles/your-post-slug/og.png" />
<meta property="og:image:width" content="1200" />
<meta property="og:image:height" content="630" />

<!-- In Twitter Card section -->
<meta name="twitter:card" content="summary_large_image" />
<meta name="twitter:image" content="https://mrinal.com/articles/your-post-slug/og.png" />
```

## Markdown Versions and llms.txt

Every content page has a corresponding `.md` file alongside its `index.html`. These markdown files provide LLM-readable plain text versions of the site content.

- Keep markdown versions in sync with their HTML counterparts. When editing an article's HTML, update its `index.md` to match.
- When adding or removing pages, update `/llms.txt` to reflect the current set of markdown files.
- `/llms.txt` lists all markdown pages and serves as the entry point for LLM access to site content.

## Key Files

- `/index.html` - Homepage with articles listing
- `/index.md` - Homepage markdown version
- `/articles/index.html` - Articles listing page
- `/articles/index.md` - Articles listing markdown version
- `/styles.css` - Global styles
- `/scripts/` - JavaScript files
- `/follow/rss.xml` - RSS feed
- `/sitemap.xml` - Sitemap for search engines
- `/llms.txt` - LLM-readable index of all markdown pages
- `/articles/*/index.html` - Individual articles
- `/articles/*/index.md` - Article markdown versions
