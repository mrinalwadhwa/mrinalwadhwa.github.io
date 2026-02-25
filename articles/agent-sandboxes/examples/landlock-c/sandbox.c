// sandbox.c - Minimal Landlock example
// Compile: gcc -o sandbox sandbox.c
// Run: ./sandbox /bin/bash

#define _GNU_SOURCE
#include <errno.h>
#include <fcntl.h>
#include <linux/landlock.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/prctl.h>
#include <sys/syscall.h>
#include <unistd.h>

static inline int landlock_create_ruleset(
    const struct landlock_ruleset_attr *attr, size_t size, __u32 flags) {
    return syscall(__NR_landlock_create_ruleset, attr, size, flags);
}

static inline int landlock_add_rule(
    int ruleset_fd, enum landlock_rule_type type,
    const void *attr, __u32 flags) {
    return syscall(__NR_landlock_add_rule, ruleset_fd, type, attr, flags);
}

static inline int landlock_restrict_self(int ruleset_fd, __u32 flags) {
    return syscall(__NR_landlock_restrict_self, ruleset_fd, flags);
}

int add_path_rule(int ruleset_fd, const char *path, __u64 allowed_access) {
    struct landlock_path_beneath_attr pb = { .allowed_access = allowed_access };
    pb.parent_fd = open(path, O_PATH | O_CLOEXEC);
    if (pb.parent_fd < 0) return -1;
    int ret = landlock_add_rule(ruleset_fd, LANDLOCK_RULE_PATH_BENEATH, &pb, 0);
    close(pb.parent_fd);
    return ret;
}

int main(int argc, char *argv[]) {
    if (argc < 2) { fprintf(stderr, "Usage: %s <cmd>\n", argv[0]); return 1; }

    struct landlock_ruleset_attr ra = {
        .handled_access_fs = LANDLOCK_ACCESS_FS_EXECUTE | LANDLOCK_ACCESS_FS_READ_FILE |
            LANDLOCK_ACCESS_FS_READ_DIR | LANDLOCK_ACCESS_FS_WRITE_FILE
    };

    int fd = landlock_create_ruleset(&ra, sizeof(ra), 0);
    if (fd < 0) { perror("landlock_create_ruleset"); return 1; }

    __u64 rx = LANDLOCK_ACCESS_FS_EXECUTE | LANDLOCK_ACCESS_FS_READ_FILE | LANDLOCK_ACCESS_FS_READ_DIR;
    __u64 rw = rx | LANDLOCK_ACCESS_FS_WRITE_FILE;

    add_path_rule(fd, "/usr", rx);
    add_path_rule(fd, "/lib", rx);
    add_path_rule(fd, "/bin", rx);
    add_path_rule(fd, "/etc", rx);
    add_path_rule(fd, "/tmp/workspace", rw);

    prctl(PR_SET_NO_NEW_PRIVS, 1, 0, 0, 0);
    landlock_restrict_self(fd, 0);
    close(fd);

    execvp(argv[1], &argv[1]);
    return 1;
}
