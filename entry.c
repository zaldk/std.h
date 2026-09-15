#define STD_IMPLEMENTATION
#include "std.h"

INSERT_ENTRY_POINT()

void start(i64 argc, char* argv[], char* envp[]) {
    /* stb snprint test */
    if (0) {
        char buf[64] = {0};
        i32 len = stbsp_snprintf(buf, sizeof(buf), "%s\n", "some text");
        syscall_write(1, buf, len);
    }

    /* file read test */
    if (0) {
        i64 fd = syscall_open("entry.c", OPEN_FLAG_RDONLY, 0644);
        char buf[4096] = {0};
        i64 read_bytes = syscall_read(fd, buf, sizeof(buf));
        buf[read_bytes++] = '\n';
        syscall_write(1, buf, read_bytes);
        syscall_close(fd);
    }

    /* mmap test */
    if (0) {
        char* buffer = NULL;
        i64 buffer_size = 4096;
        buffer = (char*)syscall_mmap(NULL, buffer_size, MMAP_PROT_READ | MMAP_PROT_WRITE, MMAP_FLAG_ANONYMOUS | MMAP_FLAG_PRIVATE, -1, 0);
        if ((i64)buffer == -1) {
            print("[ERROR] MMAP failed\n");
            UNREACHABLE();
        }

        print("[INFO] MMAP result: %p\n", buffer);

        i64 unmap_error = syscall_munmap(buffer, buffer_size);
        if (unmap_error != 0) {
            print("[ERROR] MUNMAP failed: %ld\n", unmap_error);
        }
    }

    /* file ops test */
    if (0) {
        const char* filename = "build.sh";
        i64 size = get_file_size(filename);
        print("[INFO] '%s' ~ %ld\n", filename, size);
    }

    /* string builder (+ pool + block) test */
    if (0) {
        struct string_builder sb = {0};
        SB_APPEND(&sb, "HALLO");
        SB_APPEND(&sb, " ");
        SB_APPEND(&sb, "WORLD");

        print("[INFO] sb.len: `%ld`\n", sb.len);
        i64 required_size = sb_to_string(&sb, NULL);
        struct block block = {0};
        block_make(&block, required_size);
        print("[INFO] sb_to_string needs a buffer of size = `%ld`\n", required_size);
        print("[INFO] sb_to_string wrote = `%ld` bytes\n", sb_to_string(&sb, block.ptr));
        print("[INFO] string: `%.*s`\n", block.len, block);

        sb_destroy(&sb);
    }

    /* main args test */
    if (0) {
        i64 i = 0;
        print("Arguments (%ld):\n", argc);
        for (i = 0; i < argc; i++) {
            print("argv[%d] = %s\n", i, argv[i]);
        }
        i = 0;
        print("\nEnvironment variables:\n");
        for (i = 0; envp[i] != NULL; i++) {
            print("envp[%d] = %s\n", i, envp[i]);
        }
    }

    syscall_exit(69);
}