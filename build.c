#define STD_IMPLEMENTATION
#include "std.h"

// std.linux.s supplies _start and initializes __envp before calling main.

#define BUILD_DIR ".build/"

struct arena SCRATCH = {0};

struct shell_command CMD = {0};
i32 main(i32 argc, char* argv[], char* envp[]) {
    if (arena_init(&SCRATCH, 64*MB) < 0) return 1;
    if (cmd_init(&CMD, &SCRATCH) < 0) return 1;

    const i64 rebuilt = REBUILD_THYSELF(&SCRATCH, argc, argv);
    if (rebuilt < 0) return 1;
    if (rebuilt > 0) return 0; // the replacement builder has already run
    if (init_ignored_dir(BUILD_DIR, ".gitignore") < 0) return 1;
    (void)envp;

    if (cmd_append(&CMD, "gcc") < 0) return 1;
    cmd_append(&CMD, "std.linux.s", "test_usage.c", "-o", BUILD_DIR"test_usage.exe");
    cmd_append(&CMD, "-nostdinc", "-ffreestanding");       /* mandatory */
    cmd_append(&CMD, "-nostdlib");       /* mandatory */
    cmd_append(&CMD, "-fno-stack-protector");       /* mandatory */
    cmd_append(&CMD, "-no-pie", "-static", "-ggdb"); /* optional  */
    cmd_append(&CMD, "-Wall", "-Wextra");
    if (cmd_run(&CMD) < 0) return 1;

    #if 0
    cmd_append(&CMD, "clang");
    cmd_append(&CMD, "test_usage.c", "-o", BUILD_DIR"test_usage.exe");
    cmd_append(&CMD, "-nostdlib");
    /* cmd_append(&CMD, "-fno-stack-protector"); */
    cmd_append(&CMD, "-ffreestanding");
    cmd_append(&CMD, "-fno-pic");
    cmd_append(&CMD, "-no-pie");
    cmd_append(&CMD, "-fno-builtin");
    cmd_append(&CMD, "-g");
    /* cmd_append(&CMD, "-std=c89", "-no-pie", "-static", "-ggdb"); */
    cmd_append(&CMD, "-Wall", "-Wextra");
    if (cmd_run(&CMD) < 0) return 1;
    #endif

    cmd_append(&CMD, BUILD_DIR"test_usage.exe");
    if (cmd_run(&CMD) < 0) return 1;

    if (arena_free(&SCRATCH) < 0) return 1;
    return 0;
}
