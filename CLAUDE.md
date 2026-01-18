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

3. **Update index.html articles listing:**
   Add a new `<li>` inside `.article-list`, newest first:
   ```html
   <li>
       <a href="/articles/your-post-slug/">Article Title</a>
       <span class="article-date">January 18, 2026</span>
   </li>
   ```

4. **Update articles/index.html listing:**
   Add the same `<li>` inside `.article-list-page`, newest first.

5. **Update feed/index.xml:**
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

6. **Update sitemap.xml:**
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
- RSS feed: `/feed` (feed/index.xml)

## Styling

The site uses a modular scale with ratio 1.625:
- 0.379em, 0.616em, 1em, 1.625em, 2.641em, 4.291em, 6.973em

Each blog post can have custom CSS in `<style>` tags and custom JS in `<script>` tags at the bottom.

## Key Files

- `/index.html` - Homepage with articles listing
- `/articles/index.html` - Articles listing page
- `/styles.css` - Global styles
- `/feed/index.xml` - RSS feed
- `/sitemap.xml` - Sitemap for search engines
- `/articles/*/index.html` - Individual articles
