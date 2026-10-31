#define STD_IMPLEMENTATION
#include "std.h"

// INSERT_ENTRY_POINT()

#define BUILD_DIR ".build/"

struct arena SCRATCH = {0};

struct shell_command CMD = {0};
i32 main(i32 argc, char* argv[], char* envp[]) {
    arena_init(&SCRATCH, 64*MB);

    REBUILD_THYSELF(&SCRATCH, argc, argv);
    init_ignored_dir(BUILD_DIR, ".gitignore");
    (void)envp;

    /* #if 0 */
    cmd_append(&CMD, "clang");
    cmd_append(&CMD, "std.linux.s", "test_usage.c", "-o", BUILD_DIR"test_usage.exe");
    cmd_append(&CMD, "-nostdinc", "-ffreestanding");       /* mandatory */
    cmd_append(&CMD, "-nostdlib");       /* mandatory */
    cmd_append(&CMD, "-fno-stack-protector");       /* mandatory */
    cmd_append(&CMD, "-no-pie", "-static", "-ggdb"); /* optional  */
    cmd_append(&CMD, "-Wall", "-Wextra");
    if (!cmd_run(&CMD)) syscall_exit(1);
    /* #endif */

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
    if (!cmd_run(&CMD)) syscall_exit(1);
    #endif

    cmd_append(&CMD, BUILD_DIR"test_usage.exe");
    if (!cmd_run(&CMD)) syscall_exit(1);

    arena_free(&SCRATCH);
    return 0;
}
