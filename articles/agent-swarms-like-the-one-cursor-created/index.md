Cursor made headlines last week for using a swarm of AI agents to build a web browser. The swarm ran
uninterrupted for a week, producing three million lines of code and the resulting browser
["kind of worked"](https://x.com/mntruell/status/2012825801381580880).

It was a first glimpse of a pattern that applies beyond generating code. Swarms of agents that
thwart security attacks in realtime, drive regulatory submissions for drug approvals, sift through
thousands of documents to build a legal case. Problems too complex for a single agent.

Last night, I used [Autonomy](https://autonomy.computer) to build a swarm of deep [code review
agents](https://github.com/build-trust/autonomy/tree/main/examples/code-review/011) that assess a codebase in parallel. Each file gets a quick scan. Flagged files get four
specialized reviewers: security, quality, complexity, and documentation. High-risk findings spawn
sub-reviewers. Imported dependencies get pulled in and reviewed the same way.

The video below is a time-lapse of a swarm that grows to 5,136 agents as it conducts a deep review
of vue.js core. Each circle is an agent. The force-directed graph expands as new agents are spawned.

[Video](https://www.youtube.com/watch?v=N9zZKyz9W38)

Checkout the [source code](https://github.com/build-trust/autonomy/tree/main/examples/code-review/011) on GitHub
and try the [live code-review app](https://a9eb812238f753132652ae09963a05e9-example011.cluster.autonomy.computer/).

Agents built in the last two years can only handle a few autonomous turns. Deep autonomous work over
a long horizon needs more: a filesystem to use as a workspace, progress files to create plans that
bridge context windows, structured notes that persist outside the context window, a sandboxed shell
to run command line tools, and sub-agents that handle focused tasks with clean context.

Harnesses like Claude Code and Autonomy close this gap for a single agent: filesystem tools, memory
compaction, shell access, sub-agent delegation. With these capabilities, a single agent can stay
focused and take thousands of autonomous steps.

But Cursor didn't use one agent. They used hundreds, working in parallel for days. Going from one
agent to a swarm demands more than a harness of python code. Agents need to run in parallel without
blocking, create new agents dynamically, discover each other across machines, pass messages, maintain
isolated workspaces, and collaborate over secure channels. That takes infrastructure.

```python
# Discover runner machines and distribute work
runners = await Zone.nodes(node, filter="runner")
batches = split_list_into_n_parts(files, len(runners))

for runner, batch in zip(runners, batches):
    await runner.start_worker("reviewer", FileReviewWorker())
    mailbox = await node.send("reviewer", request, node=runner.name)

...

# Each worker spawns agents with an isolated filesystem, a sandboxed shell, the ability to spawn sub-agents
class FileReviewWorker:
    async def review_file(self, file_info, reviewers):
        agent = await Agent.start(
            node=self.node,
            instructions="Review this file for security and quality ...",
            model=Model("claude-opus-4-5"),
            tools=[FilesystemTools(), ShellTools(), ...],
            subagents={
                "security": {
                    "instructions": "Deep assessment of security vulnerabilities ...",
                    "model": Model("claude-opus-4-5"),
                    "tools": [FilesystemTools(), ShellTools(), ...],
                },
                "quality": {
                    "instructions": "Deep assessment of code quality ...",
                    "model": Model("claude-opus-4-5"),
                    "tools": [FilesystemTools(), ShellTools(), ...],
                },
            },
        )
        ...
```

Agents spend most of their life I/O-bound, waiting on tools or models. In
Autonomy, each agent is a concurrent actor with isolated state. The
runtime schedules an actor only when it has a message to process, so thousands of agents can run in
parallel on a single machine.

Autonomy lets apps spin up new machines on demand and automatically connects them over secure
channels. Agents can spawn other agents on any machine and discover each other. In our code review
swarm, a simple for loop distributed work to over 5,000 agents across five containers.

Building swarms into a product requires this complete infrastructure. And a product doesn't run one
swarm. It runs a swarm for each user and for each task that user delegates. The infrastructure
problem only grows.

AI agent products developed in the last two years will soon see challengers that throw
coordinated swarms of long-horizon agents to perform better and tackle use cases that were
previously too difficult.



