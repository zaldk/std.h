#ifndef STD_LINUX_H
#define STD_LINUX_H

#include "std.common.h"
#include "std.linux.tables.h"

#define INSERT_ENTRY_POINT() __asm__ (MULTILINE_STRING( \
    .globl _start                      \n            \
    _start:                            \n            \
    \t xor     rbp, rbp                \n            \
    \t mov     rdi, [rsp]              \n /* argc */ \
    \t lea     rsi, [rsp + 8]          \n /* argv */ \
    \t lea     rdx, [rsp + rdi*8 + 16] \n /* envp */ \
    \t mov     [rip + __envp], rdx     \n            \
    \t and     rsp, -16                \n            \
    \t call    start                   \n            \
    \t mov     rdi, rax                \n            \
    \t mov     rax, 60                 \n /* exit */ \
    \t syscall                         \n            \
));


#define X(NUMBER, _, NAME) static const i64 SYSCALL_##NAME = NUMBER;
    SYSCALL_TABLE
#undef X
i64 syscall_generic(u64 code, u64 arg1, u64 arg2, u64 arg3, u64 arg4, u64 arg5, u64 arg6);


void syscall_exit(i64 exit_code);


i64 syscall_read(i64 file_descriptor, char* buffer, u64 length);
i64 syscall_write(i64 destination, char* message, u64 length);


#define X(NAME, VALUE) static const i64 OPEN_FLAG_##NAME = VALUE;
    OPEN_FLAGS
#undef X
i64 syscall_open(const char* filename, i64 flags, u64 mode);
i64 syscall_close(i64 file_descriptor);


struct time_value {
    i64 seconds;
    i64 microseconds;
};
struct resource_usage {
	struct time_value ru_utime;	/* user time used */
	struct time_value ru_stime;	/* system time used */
	i64	ru_maxrss;	/* maximum resident set size */
	i64	ru_ixrss;	/* integral shared memory size */
	i64	ru_idrss;	/* integral unshared data size */
	i64	ru_isrss;	/* integral unshared stack size */
	i64	ru_minflt;	/* page reclaims */
	i64	ru_majflt;	/* page faults */
	i64	ru_nswap;	/* swaps */
	i64	ru_inblock;	/* block input operations */
	i64	ru_oublock;	/* block output operations */
	i64	ru_msgsnd;	/* messages sent */
	i64	ru_msgrcv;	/* messages received */
	i64	ru_nsignals;	/* signals received */
	i64	ru_nvcsw;	/* voluntary context switches */
	i64	ru_nivcsw;	/* involuntary " */
};
i64 syscall_wait4(i64 pid, i64* status, i64 options, struct resource_usage* usage);


#define X(NAME, VALUE) static const i64 MMAP_PROT_##NAME = VALUE;
    MMAP_PROTECTIONS
#undef X
#define X(NAME, VALUE) static const i64 MMAP_FLAG_##NAME = VALUE;
    MMAP_FLAGS
#undef X
i64 syscall_mmap(void* address, u64 size, i64 protection, i64 flags, i64 file_descriptor, i64 offset);
i64 syscall_munmap(void* address, u64 size);


struct stat {
    u64 device;
    u64 file_serial_number;
    u32 file_mode;
    u32 link_count;
    u32 user_id;                 /* ID of the file's owner */
    u32 group_id;                /* ID of the file's group */
    u64 device_number;           /* Device number, if device */
    u64 __pad1;
    i64 file_size;               /* in bytes */
    i32 block_size;              /* Optimal for I/O */
    i32 __pad2;
    i64 blocks;                  /* Number 512-byte blocks allocated */
    i64 time_access;             /* Time of last access */
    u64 time_access_nsec;
    i64 time_modification;       /* Time of last modification */
    u64 time_modification_nsec;
    i64 time_status_change;      /* Time of last status change */
    u64 time_status_change_nsec;
    u32 __unused4;
    u32 __unused5;
};
i64 syscall_stat(const char* filename, struct stat* buffer);
i64 syscall_fstat(i64 file_descriptor, struct stat* buffer);


i64 syscall_fork(void);
i64 syscall_vfork(void); /* TODO: for some reason causes a segfault at execve, not fork() */
i64 syscall_execve(const char* path, char** argv, char** envp);
i64 syscall_execveat(i64 directory_file_descriptor, const char* path, char** argv, char** envp, i64 flags);


i64 syscall_rename(char* old, char* new);
i64 syscall_mkdir(char* path, i64 mode);
i64 syscall_unlink(char* path);




#ifdef STD_LINUX_IMPLEMENTATION
#ifndef STD_LINUX_IMPLEMENTATION_GUARD
#define STD_LINUX_IMPLEMENTATION_GUARD

i64 syscall_generic(u64 code, u64 arg1, u64 arg2, u64 arg3, u64 arg4, u64 arg5, u64 arg6) {
    register u64 rax __asm__("rax") = code;
    register u64 rdi __asm__("rdi") = arg1;
    register u64 rsi __asm__("rsi") = arg2;
    register u64 rdx __asm__("rdx") = arg3;
    register u64 r10 __asm__("r10") = arg4;
    register u64 r8  __asm__("r8")  = arg5;
    register u64 r9  __asm__("r9")  = arg6;

    i64 result = 0;
    __asm__ volatile (
        "syscall"
        : "=a"(result)
        : "r"(rax),
          "r"(rdi),
          "r"(rsi),
          "r"(rdx),
          "r"(r10),
          "r"(r8),
          "r"(r9)
        : "cc", "memory", "rcx", "r11"
    );
    return result;
}


i64 syscall_read(i64 file_descriptor, char* buffer, u64 length) {
    return syscall_generic(SYSCALL_READ, file_descriptor, (u64)buffer, length, 0, 0, 0);
}
i64 syscall_write(i64 destination, char* message, u64 length) {
    return syscall_generic(SYSCALL_WRITE, destination, (u64)message, length, 0, 0, 0);
}


i64 syscall_open(const char* filename, i64 flags, u64 mode) {
    return (i64)syscall_generic(SYSCALL_OPEN, (u64)filename, flags, mode, 0, 0, 0);
}
i64 syscall_close(i64 file_descriptor) {
    return syscall_generic(SYSCALL_CLOSE, file_descriptor, 0, 0, 0, 0, 0);
}


i64 syscall_wait4(i64 pid, i64* status, i64 options, struct resource_usage* usage) {
    return syscall_generic(SYSCALL_WAIT4, pid, (u64)status, options, (u64)usage, 0, 0);
}


i64 syscall_mmap(void* address, u64 size, i64 protection, i64 flags, i64 file_descriptor, i64 offset) {
    return syscall_generic(SYSCALL_MMAP, (u64)address, size, protection, flags, file_descriptor, offset);
}
i64 syscall_munmap(void* address, u64 size) {
    return syscall_generic(SYSCALL_MUNMAP, (u64)address, size, 0, 0, 0, 0);
}


i64 syscall_stat(const char* filename, struct stat* buffer) {
    return syscall_generic(SYSCALL_STAT, (u64)filename, (u64)buffer, 0, 0, 0, 0);
}
i64 syscall_fstat(i64 file_descriptor, struct stat* buffer) {
    return syscall_generic(SYSCALL_FSTAT, file_descriptor, (u64)buffer, 0, 0, 0, 0);
}


i64 syscall_fork(void) {
    return syscall_generic(SYSCALL_FORK, 0, 0, 0, 0, 0, 0);
}
i64 syscall_vfork(void) {
    return syscall_generic(SYSCALL_VFORK, 0, 0, 0, 0, 0, 0);
}
i64 syscall_execve(const char* path, char** argv, char** envp) {
    return syscall_generic(SYSCALL_EXECVE, (u64)path, (u64)argv, (u64)envp, 0, 0, 0);
}
i64 syscall_execveat(i64 directory_file_descriptor, const char* path, char** argv, char** envp, i64 flags) {
    return syscall_generic(SYSCALL_EXECVE, directory_file_descriptor, (u64)path, (u64)argv, (u64)envp, flags, 0);
}


i64 syscall_rename(char* old, char* new) {
    return syscall_generic(SYSCALL_RENAME, (u64)old, (u64)new, 0, 0, 0, 0);
}
i64 syscall_mkdir(char* path, i64 mode) {
    return syscall_generic(SYSCALL_MKDIR, (u64)path, mode, 0, 0, 0, 0);
}
i64 syscall_unlink(char* path) {
    return syscall_generic(SYSCALL_UNLINK, (u64)path, 0, 0, 0, 0, 0);
}

__attribute__((noreturn))
void syscall_exit(i64 exit_code) {
    (void)syscall_generic(SYSCALL_EXIT, exit_code, 0, 0, 0, 0, 0);
    UNREACHABLE();
}



void print(const char* format, ...) {
    static char print_buffer[4096];
    va_list va;
    va_start(va, format);
    i64 print_length = stbsp_vsnprintf(print_buffer, sizeof(print_buffer), format, va);
    va_end(va);
    syscall_write(1, print_buffer, print_length);
}


i64 get_file_size(const char* filename) {
    struct stat buffer = {0};
    i64 ret = syscall_stat(filename, &buffer);
    if (ret < 0) return -CODE_ERROR;
    return buffer.file_size;
}


i64 pool_try_init(struct pool* pool) {
    if (pool->ptr != NULL) return CODE_NOOP;

    i64 result = syscall_mmap(
        NULL, POOL_DEFAULT_CAPACITY,
        MMAP_PROT_READ | MMAP_PROT_WRITE,
        MMAP_FLAG_ANONYMOUS | MMAP_FLAG_PRIVATE,
        -1, 0
    );
    if (result < 0) return CODE_ERROR;

    pool->ptr  = (u8*)result;
    pool->next = NULL;
    pool->len  = 0;
    pool->cap  = POOL_DEFAULT_CAPACITY;

    return CODE_OK;
}
i64 pool_try_destroy(struct pool* pool) {
    if (pool == NULL) return CODE_NOOP;

    if (pool->next != NULL) {
        i64 return_code = pool_try_destroy(pool->next);
        if (return_code == CODE_ERROR) return CODE_ERROR;
    }

    if (pool->ptr == NULL) return CODE_NOOP;

    i64 result = syscall_munmap(pool->ptr, pool->cap);
    if (result < 0) return CODE_ERROR;

    return CODE_OK;
}

i64 block_make(struct block* block, i64 size) {
    i64 actual_size = ROUND_UP_4K(size);
    i64 result = syscall_mmap(
        NULL, actual_size,
        MMAP_PROT_READ | MMAP_PROT_WRITE,
        MMAP_FLAG_ANONYMOUS | MMAP_FLAG_PRIVATE,
        -1, 0
    );
    if (result < 0) return CODE_ERROR;
    block->ptr = (u8*)result;
    block->len = actual_size;
    return CODE_OK;
}
i64 block_destroy(struct block* block) {
    if (block->ptr == NULL) return CODE_NOOP;
    i64 result = syscall_munmap(block->ptr, block->len);
    if (result < 0) return CODE_ERROR;
    return CODE_OK;
}
i64 block_resize(struct block* block, i64 new_size) {
    if (block->len > new_size) return CODE_NOOP;

    if (block->ptr == NULL) return block_make(block, new_size);

    struct block new_block = {0};
    block_make(&new_block, new_size);
    memcpy(new_block.ptr, block->ptr, block->len);

    block_destroy(block);
    *block = new_block;

    return CODE_OK;
}

i64 cmd_await(i64 pid) {
    for (;;) {
        i64 wstatus = 0;
        if (syscall_wait4(pid, &wstatus, 0, 0) < 0) {
            print("[ERROR] could not wait on command (pid %d)\n", pid);
            return 0;
        }

        if (WIFEXITED(wstatus)) {
            i64 exit_status = WEXITSTATUS(wstatus);
            if (exit_status != 0) {
                print("[ERROR] command exited with exit code %d\n", exit_status);
                return 0;
            }
            break;
        }

        if (WIFSIGNALED(wstatus)) {
            print("[ERROR] command process was terminated by signal %d\n", WTERMSIG(wstatus));
            return 0;
        }
    }
    return 1;
}
i64 cmd_run(struct shell_command* cmd) {
    i64 i;
    print("[DEBUG] Running:");
    for (i = 0; i < cmd->len; i++) {
        print(" %s", cmd->items[i]);
    }
    print("\n");

    i64 pid = syscall_fork();
    if (pid < 0) {
        print("[ERROR] Could not fork.\n");
        return 0;
    }

    if (pid == 0) {
        struct shell_command cmd_null = {0};
        cmd_append_array(&cmd_null, cmd->items, cmd->len);
        cmd_append(&cmd_null, NULL);

        i64 result = syscall_execve(cmd_null.items[0], (char **) cmd_null.items, __envp);
        if (result < 0) {
            print("[ERROR] Could not exec child process for %s: %ld\n", cmd_null.items[0], result);
            syscall_exit(42);
        }
        UNREACHABLE();
    }

    i64 ret = cmd_await(pid);
    if (!ret) {
        print("[ERROR] Could not await process pid=%d\n", pid);
        return 0;
    }

    cmd->len = 0;

    return 1;
}
i64 rebuild_needed(char* path_input, char* path_output) {
    struct stat statbuf = {0};
    i64 ret_code = 0;

    if ((ret_code = syscall_stat(path_output, &statbuf)) < 0) {
        /* NOTE: if output does not exist it 100% must be rebuilt */
        if (ret_code == -2) return 1; /* ENOENT = 2 */
        print("[ERROR] could not stat %s: %ld\n", path_output, ret_code);
        return -1;
    }
    i64 path_output_time = statbuf.time_modification;

    if ((ret_code = syscall_stat(path_input, &statbuf)) < 0) {
        /* NOTE: non-existing input is an error cause it is needed for building in the first place */
        print("[ERROR] could not stat %s: %ld\n", path_input, ret_code);
        return -1;
    }
    i64 path_input_time = statbuf.time_modification;
    if (path_input_time > path_output_time) return 1;

    return 0;
}
void rebuild_thyself(int argc, char** argv, char* path_input) {
    char* path_output = SHIFT(argc, argv);
    i64 ret_code = 0;
    char path_output_old[1024] = {0};
    struct shell_command cmd = {0};

    ret_code = rebuild_needed(path_input, path_output);
    if (ret_code < 0) syscall_exit(1); /* error occured */
    if (ret_code == 0) return; /* rebuild is not needed */

    path_output_old[stbsp_snprintf(path_output_old, 1024, "%s.old", path_output)] = 0;
    if (syscall_rename(path_output, path_output_old) != 0) {
        print("[ERROR] Could not rename: %s\n", ret_code);
        syscall_exit(1);
    }

    cmd_append(&cmd, "/bin/gcc");
    cmd_append(&cmd, path_input);
    cmd_append(&cmd, "-o", path_output);
    cmd_append(&cmd, "-nostdlib", "-masm=intel", "-fno-stack-protector");
    cmd_append(&cmd, "-Wno-builtin-declaration-mismatch");
    if (!cmd_run(&cmd)) {
        print("[ERROR] Could not rebuild.\n");
        syscall_rename(path_output_old, path_output);
    }

    syscall_unlink(path_output_old);

    cmd_append(&cmd, path_output);
    cmd_append_array(&cmd, argv, argc);
    if (!cmd_run(&cmd)) syscall_exit(2);
    syscall_exit(0);
}
int init_ignored_dir(char* path_dir, char* path_ignore, int force) {
    i64 ret_code = 0;

    if (force) syscall_unlink(path_dir);

    ret_code = syscall_mkdir(path_dir, 0755);
    if (ret_code < 0) {
        if (ret_code == -17) return 1; /* EEXIST = 17 */
        print("[ERROR] could not create directory `%s`: %ld\n", path_dir, ret_code);
    }

    char buf[1024] = {0};
    buf[stbsp_snprintf(buf, sizeof(buf), "%s%s", path_dir, path_ignore)] = 0;
    i64 fd = syscall_open(buf, OPEN_FLAG_RDWR|OPEN_FLAG_CREAT|OPEN_FLAG_TRUNC, 0644);
    if (fd < 0) {
        print("[ERROR] Could not open file %s for writing: %ld\n", buf, fd);
        goto defer;
    }

    i64 n = syscall_write(fd, "*", 1);
    if (n < 0) {
        print("[ERROR] Could not write into file %s: %ld\n", buf, n);
        goto defer;
    }

defer:
    if (fd) syscall_close(fd);
    return 1;
}


#endif /* STD_LINUX_IMPLEMENTATION_GUARD */
#endif /* STD_LINUX_IMPLEMENTATION */

#endif /* STD_LINUX_H */