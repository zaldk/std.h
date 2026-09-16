#ifndef STD_LINUX_H
#define STD_LINUX_H

#include "std.common.h"
#include "std.linux.tables.h"

#define INSERT_ENTRY_POINT() __asm__ ( \
    ".intel_syntax noprefix              \n"            \
    ".weak _start                        \n "           \
    "_start:                             \n"            \
    "    xor     rbp, rbp                \n"            \
    "    mov     rdi, [rsp]              \n" /* argc */ \
    "    lea     rsi, [rsp + 8]          \n" /* argv */ \
    "    lea     rdx, [rsp + rdi*8 + 16] \n" /* envp */ \
    "    mov     [rip + __envp], rdx     \n"            \
    "    and     rsp, -16                \n"            \
    "    call    main                    \n"            \
    "    mov     rdi, rax                \n"            \
    "    mov     rax, 60                 \n" /* exit */ \
    "    syscall                         \n"            \
    ".att_syntax prefix                  \n"            \
);


#define X(NUMBER, _, NAME) static const i64 SYSCALL_##NAME = NUMBER;
    SYSCALL_TABLE
#undef X
i64 syscall_generic(u64 code, u64 arg1, u64 arg2, u64 arg3, u64 arg4, u64 arg5, u64 arg6);


#define X(NAME, VALUE) static const i64 ERRNO_##NAME = VALUE;
    ERRNO_VALUES
#undef X


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
#define X(NAME, VALUE) static const i64 MREMAP_FLAG_##NAME = VALUE;
    MREMAP_FLAGS
#undef X
i64 syscall_mmap(void* address, u64 size, i64 protection, i64 flags, i64 file_descriptor, i64 offset);
i64 syscall_mremap(void* old_address, u64 old_size, u64 new_size, u64 flags, void* new_address);
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

/* from linux-7.2/tools/include/nolibc/types.h */
struct directory_entry {
	u64            inode;
	i64            _weird_value; /* should not use */
	unsigned short self_size;    /* no idea how to use */
	unsigned char  type;
	char           name[];
};
#define X(NAME, VALUE) static const i64 ENTRY_TYPE_##NAME = VALUE;
    DIR_ENTRY_TYPES
#undef X
i64 syscall_getdents64(i64 file_descriptor, struct directory_entry* dirent, u64 count);





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


__attribute__((noreturn))
void syscall_exit(i64 exit_code) {
    (void)syscall_generic(SYSCALL_EXIT, exit_code, 0, 0, 0, 0, 0);
    UNREACHABLE();
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
i64 syscall_mremap(void* old_address, u64 old_size, u64 new_size, u64 flags, void* new_address) {
    return syscall_generic(SYSCALL_MREMAP, (u64)old_address, old_size, new_size, flags, (u64)new_address, 0);
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


i64 syscall_getdents64(i64 file_descriptor, struct directory_entry* dirent, u64 count) {
    return syscall_generic(SYSCALL_GETDENTS64, file_descriptor, (u64)dirent, count, 0, 0, 0);
}


void print(const char* format, ...) {
    i64 print_length;
    static char print_buffer[4096];
    va_list va;
    va_start(va, format);
    print_length = stbsp_vsnprintf(print_buffer, sizeof(print_buffer), format, va);
    va_end(va);
    syscall_write(1, print_buffer, print_length);
}


i64 block_make(struct block* block, i64 requested_size) {
    i64 actual_size = ROUND_UP_4K(requested_size);
    i64 result = syscall_mmap(
        NULL, actual_size,
        MMAP_PROT_READ | MMAP_PROT_WRITE,
        MMAP_FLAG_ANONYMOUS | MMAP_FLAG_PRIVATE,
        -1, 0
    );
    if (result < 0) return CODE_ERROR;
    block->ptr = (u8*)result;
    block->cap = actual_size;
    block->len = 0;
    return CODE_OK;
}
i64 block_resize(struct block* block, i64 new_size) {
    i64 actual_new_size, result;

    if (block->cap > new_size) return CODE_NOOP;
    if (block->ptr == NULL) return block_make(block, new_size);

    actual_new_size = ROUND_UP_4K(new_size);
    result = syscall_mremap(block->ptr, block->cap, actual_new_size, MREMAP_FLAG_MAYMOVE, NULL);
    if (result < 0) {
        print("[ERROR] Count not resize: %ld\n", result);
        return CODE_ERROR;
    }
    block->ptr = (u8*)result;
    block->cap = actual_new_size;

    return CODE_OK;
}
i64 block_destroy(struct block* block) {
    i64 result;
    if (block->ptr == NULL) return CODE_NOOP;
    result = syscall_munmap(block->ptr, block->cap);
    if (result < 0) return CODE_ERROR;
    return CODE_OK;
}


i64 cmd_await(i64 pid) {
    while (1) {
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
    i64 pid;
    i64 ret;

    print("[DEBUG] Running:");
    for (i = 0; i < cmd->len; i++) {
        print(" %s", cmd->items[i]);
    }
    print("\n");

    pid = syscall_fork();
    if (pid < 0) {
        print("[ERROR] Could not fork.\n");
        return CODE_OK;
    }

    if (pid == 0) {
        i64 result = 0;
        char* program_path;
        struct shell_command cmd_null = {0};
        char program_path_buffer[4096] = {0};
        cmd_append_array(&cmd_null, cmd->items, cmd->len);
        cmd_append(&cmd_null, NULL);

        program_path = cmd_null.items[0];
        result = find_executable(cmd_null.items[0], __envp, program_path_buffer, sizeof(program_path_buffer));
        if (result == CODE_ERROR) {
            print("[ERROR] Could not find the executable `%s`\n", cmd_null.items[0]);
            return CODE_ERROR;
        } else if (result == CODE_OK) {
            program_path = program_path_buffer;
        }
        result = syscall_execve(program_path, (char **) cmd_null.items, __envp);
        if (result < 0) {
            print("[ERROR] Could not exec child process for %s: %ld\n", cmd_null.items[0], result);
            return CODE_ERROR;
        }
        UNREACHABLE();
    }

    ret = cmd_await(pid);
    if (!ret) {
        print("[ERROR] Could not await process pid=%d\n", pid);
        return CODE_OK;
    }

    cmd->len = 0;

    return CODE_ERROR;
}
i64 rebuild_needed(char* path_input, char* path_output) {
    struct stat statbuf = {0};
    i64 ret_code = 0;
    i64 path_output_time;
    i64 path_input_time;

    if ((ret_code = syscall_stat(path_output, &statbuf)) < 0) {
        /* NOTE: if output does not exist it 100% must be rebuilt */
        if (ret_code == -ERRNO_ENOENT) return 1;
        print("[ERROR] could not stat %s: %ld\n", path_output, ret_code);
        return -1;
    }
    path_output_time = statbuf.time_modification;

    if ((ret_code = syscall_stat(path_input, &statbuf)) < 0) {
        /* NOTE: non-existing input is an error cause it is needed for building in the first place */
        print("[ERROR] could not stat %s: %ld\n", path_input, ret_code);
        return -1;
    }
    path_input_time = statbuf.time_modification;
    if (path_input_time > path_output_time) return 1;

    return 0;
}
void rebuild_thyself(i32 argc, char** argv, char* path_input) {
    char* path_output = SHIFT(argc, argv);
    i64 ret_code = 0;
    char path_output_old[1024] = {0};
    struct shell_command cmd = {0};
    i64 written;

    ret_code = rebuild_needed(path_input, path_output);
    if (ret_code < 0) syscall_exit(1); /* error occured */
    if (ret_code == 0) return; /* rebuild is not needed */

    written = stbsp_snprintf(path_output_old, 1024, "%s.old", path_output);
    if (written >= 1024) UNREACHABLE();
    if (syscall_rename(path_output, path_output_old) != 0) {
        print("[ERROR] Could not rename: %s\n", ret_code);
        syscall_exit(1);
    }

    cmd_append(&cmd, "gcc");
    cmd_append(&cmd, path_input, "-o", path_output);
    cmd_append(&cmd, "-nostdlib");
    cmd_append(&cmd, "-fno-stack-protector"); /* TODO: figure out a way to remove this flag */
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
i32 init_ignored_dir(char* path_dir, char* path_ignore) {
    i64 ret_code = 0;
    char buf[1024] = {0};
    i64 written;
    i64 fd;

    ret_code = syscall_mkdir(path_dir, 0755);
    if (ret_code < 0) {
        if (ret_code == -ERRNO_EEXIST) return 1;
        print("[ERROR] could not create directory `%s`: %ld\n", path_dir, ret_code);
    }

    written = stbsp_snprintf(buf, sizeof(buf), "%s%s", path_dir, path_ignore);
    if (written >= 1024) UNREACHABLE();
    fd = syscall_open(buf, OPEN_FLAG_RDWR|OPEN_FLAG_CREAT|OPEN_FLAG_TRUNC, 0644);
    if (fd < 0) {
        print("[ERROR] Could not open file %s for writing: %ld\n", buf, fd);
        goto defer;
    }

    written = syscall_write(fd, "*", 1);
    if (written < 0) {
        print("[ERROR] Could not write into file %s: %ld\n", buf, written);
        goto defer;
    }

defer:
    if (fd) syscall_close(fd);
    return 1;
}
i64 find_executable(char* name, char* envp[], char* result_buffer, i64 result_buffer_capacity) {
    char** env = envp;
    char* path = NULL;
    char* path_temp = *env;
    i64 name_length = 0;
    i64 found = 0;
    i64 return_code = 0;
    i64 i;

    name_length = zstr_length(name);
    for (i = 0; i < name_length; i++) {
        if (name[i] == '/') return CODE_NOOP;
    }

    for (; path_temp != NULL; path_temp = *env++) {
        if (path_temp[0] == 'P' && path_temp[1] == 'A' && path_temp[2] == 'T' && path_temp[3] == 'H') {
            path = path_temp + 5; /* skip `PATH=` */
            break;
        }
    }

    if (path == NULL) path = "/usr/local/bin:/usr/bin:/bin"; /* some default value */

    while (1) {
        i64 delimiter_index = 0;
        i64 fd = 0;
        static char buffer_path[4096] = {0};
        i64 buffer_path_len = 0;
        static char buffer_dirent[4096] = {0};

        while (path[delimiter_index] != 0) {
            if (path[delimiter_index] == ':') break;
            delimiter_index += 1;
        }
        if (path[delimiter_index] == 0) break;
        memcpy(buffer_path, path, delimiter_index);
        buffer_path_len = delimiter_index;
        buffer_path[buffer_path_len] = 0;
        path += delimiter_index + 1;

        fd = syscall_open(buffer_path, OPEN_FLAG_RDONLY | OPEN_FLAG_DIRECTORY, 0644);
        if (fd < 0) {
            print("[ERROR] Could not open directory `%s`: %ld\n", buffer_path, fd);
            return CODE_ERROR; /* TODO: maybe skip? */
        }

        while (1) {
            i64 offset = 0;
            i64 read_count = syscall_getdents64(fd, (void*)buffer_dirent, sizeof(buffer_dirent));

            if (read_count < 0) {
                print("[ERROR] Could not syscall getdents64\n");
                return CODE_ERROR;
            }
            if (read_count == 0) break;

            for (offset = 0; offset < read_count;) {
                struct directory_entry* dirent;
                i64 dirent_name_len = 0;

                dirent = (struct directory_entry*)(buffer_dirent + offset);
                offset += dirent->self_size;

                if (
                    dirent->type != ENTRY_TYPE_REGULAR_FILE &&
                    dirent->type != ENTRY_TYPE_SYMBOLIC_LINK
                ) continue;

                dirent_name_len = zstr_length(dirent->name);
                if (
                    memcmp(name, dirent->name, name_length) == 0 &&
                    dirent_name_len == name_length
                ) {
                    i64 written_length = 0;
                    found = 1;
                    written_length = stbsp_snprintf(
                        buffer_path+buffer_path_len,
                        sizeof(buffer_path)-buffer_path_len,
                        "/%s", dirent->name
                    );
                    if (written_length-1 != dirent_name_len) {
                        print("[WARN] print length mismatch: %ld vs %ld\n", written_length, dirent_name_len);
                        return CODE_ERROR; /* TODO: overreaction? */
                    }
                    buffer_path_len += written_length;
                    break;
                }
            }

            if (found == 1) break;
        }

        return_code = syscall_close(fd);
        if (return_code < 0) {
            print("[ERROR] Could not close file: %ld\n", return_code);
            return CODE_ERROR; /* TODO: overreaction? */
        }

        if (found) {
            if (result_buffer_capacity < buffer_path_len) {
                print("[ERROR] Given buffer is too short: need %ld - was given %ld", buffer_path_len, result_buffer_capacity);
                return CODE_ERROR;
            }
            memcpy(result_buffer, buffer_path, buffer_path_len);
            return CODE_OK;
        }
    }

    return CODE_ERROR;
}

#endif /* STD_LINUX_IMPLEMENTATION_GUARD */
#endif /* STD_LINUX_IMPLEMENTATION */

#endif /* STD_LINUX_H */