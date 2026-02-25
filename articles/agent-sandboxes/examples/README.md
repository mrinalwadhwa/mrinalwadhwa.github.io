# Sandbox Examples

Working examples from the [Agent Sandboxes](https://mrinal.com/articles/agent-sandboxes/) article.

## macOS (Seatbelt)

```bash
cd seatbelt-shell
./test.sh
```

Uses `sandbox-exec` with an SBPL profile.

## Linux (Landlock)

```bash
cd landlock-c
gcc -o sandbox sandbox.c
mkdir -p /tmp/workspace
./sandbox /bin/bash
# Inside: write to /tmp/workspace works, write elsewhere blocked
```

Requires Linux kernel 5.13+.

## Linux (Seccomp)

```bash
cd seccomp-c
gcc -o block_network block_network.c
./block_network /bin/bash
# Inside: network syscalls blocked
```

## Testing on macOS with Docker

```bash
docker run -it --rm -v "$(pwd):/examples" ubuntu:22.04 bash
apt-get update && apt-get install -y gcc
cd /examples/landlock-c && gcc -o sandbox sandbox.c
```
