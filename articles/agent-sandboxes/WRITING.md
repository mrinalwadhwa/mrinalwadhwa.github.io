# Article-Writing Patterns

Learnings accumulated across 26 sessions of writing the Agent Sandboxes article. These patterns apply when writing or editing any article on this site.

## Voice

- "we" for the team's actions and needs. "I" for Mrinal's personal exploration. Impersonal for tool limitations.
- Present tense for requirements ("We need"), conditional for options not taken ("would be", "We could run").
- When the user provides new phrasing, use it EXACTLY.
- Prefer surgical edits over wholesale rewrites.
- When the user rejects a change, don't persist. Move on.

## Prose

- Never use em-dashes. Commas, periods, semicolons, or restructure.
- Curly apostrophes (U+2019) in body text, straight in code. The edit tool produces straight ones; fix after each edit.
- Cut filler. If a sentence doesn't drive the narrative forward, cut it or fold it into one that does.
- Establish what something IS before explaining what it DOES.
- Prose before code. Describe what the reader will see, then show it.
- Punchlines land at the end of the paragraph that builds the case, not at the start of the next.
- When a closing transition re-argues the article's premise, replace it with a pure pivot. The reader already has the context.
- Compressed closings land harder. Strip taxonomy, keep punchlines.
- Sentences should end on interesting words, not filler.
- Vary sentence length. Short punches after longer explanations.
- No rhetorical "What if" questions. Use direct statements.
- Avoid unexplained abbreviations on first use.
- Concrete examples over abstract descriptions.
- Active verbs over passive. Clear pronoun antecedents.
- End sections and articles on strong statements, not meta commentary.
- Build explicit causal chains, not implicit ones.
- One idea per paragraph. Don't mix distinct points.
- Don't repeat facts already established earlier in the article.

## Structure

- Connect sections to each other explicitly. Each section's limitation motivates the next.
- Don't forward-reference things not yet introduced in the article flow.
- Limitations should serve the narrative (motivate the next section), not be standalone caveats.
- Code examples should be snippets with concrete names, not full runnable programs.
- Each technical section should state what a thing protects and what it can't.
- Attack examples should each demonstrate a different isolation dimension (filesystem, resources, PID namespace, network).

## Tables

- Three-indicator system for comparison tables: ✅ (works), ❌ (deal-breaker), — (not applicable).
- Values should be human-readable where possible ("~5 milliseconds" over "~5-10ms", "Isolated" over "Own rootfs").

## Column Balance

Articles using multi-column layout (`column-count: 2`) need attention to balance:

- Full-width elements (`column-span: all`) break the column flow. Each chunk of prose between full-width elements is its own balanced column context.
- When a chunk looks unbalanced, split a paragraph at a natural seam.
- At `max-width: 768px`, columns collapse to single-column, so balance only matters on wider viewports.

## Visual Patterns

Each article has its own color palette and custom CSS, but some patterns recur:

- Left-aligned layout on wide viewports (`margin-left: 0` on the container).
- Code blocks: `border-radius: 8px`, subtle `box-shadow`, white or near-white background.
- Quote/image boxes: white background, subtle border, matching shadow for lift.
- Non-text elements in fixed-height wrappers whose heights are multiples of the 1.5em baseline unit.
- Border compensation: subtract border width from padding to stay on the baseline grid (`calc(1.5em - 1px)`).

## Typography

- Body text in a serif font (adobe-garamond-pro).
- Titles in a display font that varies per article.
- Syntax highlighting in a light theme (Atom One Light palette or similar).
- Selection color should match the article's accent color.

## OG Images

- 1200×630 for social previews.
- Use `agent-browser` CLI to screenshot or record animations.
- Add `og:image`, `og:image:width`, `og:image:height`, `twitter:card`, and `twitter:image` meta tags.