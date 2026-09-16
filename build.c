#define STD_IMPLEMENTATION
#include "std.h"

INSERT_ENTRY_POINT()

#define BUILD_DIR ".build/"

struct shell_command CMD = {0};
i32 main(i32 argc, char* argv[], char* envp[]) {
    REBUILD_THYSELF(argc, argv);
    init_ignored_dir(BUILD_DIR, ".gitignore");
    (void)envp;

    cmd_append(&CMD, "gcc");
    cmd_append(&CMD, "test_usage.c", "-o", BUILD_DIR"test_usage.exe");
    cmd_append(&CMD, "-nostdlib", "-fno-stack-protector");       /* mandatory */
    cmd_append(&CMD, "-std=c89", "-no-pie", "-static", "-ggdb"); /* optional  */
    cmd_append(&CMD, "-Wall", "-Wextra");
    if (!cmd_run(&CMD)) syscall_exit(1);

    cmd_append(&CMD, BUILD_DIR"test_usage.exe");
    if (!cmd_run(&CMD)) syscall_exit(1);

    return 0;
}