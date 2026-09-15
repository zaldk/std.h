#define STD_IMPLEMENTATION
#include "std.h"

INSERT_ENTRY_POINT()

#define BUILD_DIR ".build/"

struct shell_command CMD = {0};
void start(i64 argc, char** argv, char** envp) {
    REBUILD_THYSELF(argc, argv);

    init_ignored_dir(BUILD_DIR, ".gitignore", 1);

    cmd_append(&CMD, "/usr/bin/gcc");
    cmd_append(&CMD, "entry.c", "-o", BUILD_DIR"entry.exe");
    cmd_append(&CMD, "-nostdlib", "-masm=intel", "-fno-stack-protector");
    cmd_append(&CMD, "-std=c89", "-no-pie", "-static", "-ggdb");
    cmd_append(&CMD, "-Wall", "-Wextra", "-Wno-builtin-declaration-mismatch");

    if (!cmd_run(&CMD)) syscall_exit(1);

    syscall_exit(0);
}