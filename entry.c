#define STD_IMPLEMENTATION
#include "std.h"

INSERT_ENTRY_POINT()

i32 start(void) {
    /* stb snprint test */
    /* {
        char buf[64] = {0};
        i32 len = stbsp_snprintf(buf, sizeof(buf), "Hello, world! %c\n", 69);
        syscall_write(1, buf, len);
    } */

    /* file read test */
    /* {
        i64 fd = syscall_open("entry.c", 0, MODE_READONLY);
        char buf[4096] = {0};
        i64 read_bytes = syscall_read(fd, buf, sizeof(buf));
        buf[read_bytes++] = '\n';
        syscall_write(1, buf, read_bytes);
        syscall_close(fd);
    } */

    /* mmap test */
    {
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

    syscall_exit(69);
}