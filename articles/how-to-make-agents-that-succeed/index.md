# How to make agents that succeed

Most software teams don't have a lot of automated tests, and they get away with it because
traditional software is deterministic. If it works once, it'll keep working the same way, and just
eyeballing behavior before releases can feel good enough.

But AI products are different. They're probabilistic, so their behavior can shift in unexpected ways
every time you use them.

Controlled iteration is the only way to ship a reliable autonomous product and actually improve it
over time.

For example, one [Autonomy](https://autonomy.computer) customer, a fintech, recently shipped agents
that analyze bank statements and other documents submitted with a business loan application.

Their agents use large language models to extract key data points from those documents. Their agents
also do precise math on the extracted data (for example, calculate the total payroll spend) by
autonomously invoking tools written in Python.

Initially, when they tried the first few documents, extraction wasn't always correct. The agents
would sometimes hallucinate the wrong tool call, so the computed values were wrong.

They also weren't sure which language model to use. Did they really need the newest, most expensive
models, or could a cheaper one work just as well?

And this is how all AI products begin. To make progress, you need a systematic approach: one
document at a time.

This fintech started with the most capable language model and an initial development dataset of 30
documents. For each document, they manually analyzed it, labeled the correct output, and then
refined the agent's prompts and tool descriptions to ensure the output matched the labeled expected
result.

Once they got one document to work, they added it to their CI-driven automated evaluation suite.
That way, as they moved on to the next document, the automated checks ensured they weren't breaking
what was already working for previous documents.

Since agent outputs are probabilistic, each evaluation produced a metric (for example, a success
percentage) rather than a simple pass/fail. Each document was checked multiple times to compute
those percentages, which let them handle variability and still measure when things were stable,
degrading, or improving.

They defined success thresholds (for example, 95% extraction accuracy and 99% tool-call success).
Once all 30 documents were passing these thresholds, they made the agents live.

In production, they gathered traces of how the agents behaved on real-world documents, found new
document types that caused issues, and then iterated on prompts and inputs again to fix those.
Because they had that automated evaluation suite, it ensured prior behavior never broke.

With automated evals, you can also confidently experiment with cheaper or latest models, knowing the
tests will catch regressions. To make agents succeed, embrace this step by step scientific method.
