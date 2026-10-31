#ifndef STD_LINUX_H
#define STD_LINUX_H

#include "std.common.h"
#include "std.linux.tables.h"

// from linux-7.2/tools/include/nolibc/types.h
#define WEXITSTATUS(status) (((status) & 0xff00) >> 8)
#define WIFEXITED(status)   (((status) & 0x7f) == 0)
#define WTERMSIG(status)    ((status) & 0x7f)
#define WIFSIGNALED(status) ((status) - 1 < 0xff)


#define X(NUMBER, _, NAME) static const i64 SYSCALL_##NAME = NUMBER;
    SYSCALL_TABLE
#undef X

// a wrapper returns the raw kernel result: negative is a negated errno, positive is the output
i64 syscall_generic(u64 code, u64 arg1, u64 arg2, u64 arg3, u64 arg4, u64 arg5, u64 arg6);


#define X(NAME, VALUE, DESCRIPTION) static const i64 ERRNO_##NAME = VALUE;
    ERRNO_TABLE
#undef X
i64 errno_decode(i64 errno, char** name, char** description);
i64 print_errno(i64 errno, const char* file, i64 line);


void syscall_exit(i64 exit_code);


#define X(NAME, VALUE) static const i64 SIGNAL_##NAME = VALUE;
    SIGNAL_CODES
#undef X
i64 syscall_kill(i64 pid, i64 signal);


i64 syscall_getpid(void);
i64 syscall_gettid(void);


i64 syscall_read(i64 file_descriptor, u8* buffer, u64 length);
i64 syscall_write(i64 destination, u8* message, u64 length);


#define X(NAME, VALUE) static const i64 OPEN_FLAG_##NAME = VALUE;
    OPEN_FLAGS
#undef X
i64 syscall_open(const char* filename, i64 flags, u64 mode);
i64 syscall_close(i64 file_descriptor);


struct time_value_old {
    i64 seconds;
    i64 microseconds;
};
struct resource_usage {
    struct time_value_old ru_utime; /* user time used */
    struct time_value_old ru_stime; /* system time used */
    i64 ru_maxrss;   /* maximum resident set size */
    i64 ru_ixrss;    /* integral shared memory size */
    i64 ru_idrss;    /* integral unshared data size */
    i64 ru_isrss;    /* integral unshared stack size */
    i64 ru_minflt;   /* page reclaims */
    i64 ru_majflt;   /* page faults */
    i64 ru_nswap;    /* swaps */
    i64 ru_inblock;  /* block input operations */
    i64 ru_oublock;  /* block output operations */
    i64 ru_msgsnd;   /* messages sent */
    i64 ru_msgrcv;   /* messages received */
    i64 ru_nsignals; /* signals received */
    i64 ru_nvcsw;    /* voluntary context switches */
    i64 ru_nivcsw;   /* involuntary " */
};
i64 syscall_wait4(i64 pid, i64* status, i64 options, struct resource_usage* usage);

#define X(NAME, VALUE) static const i64 CLOCK_##NAME = VALUE;
    CLOCK_TYPES
#undef X
i64 syscall_clock_gettime(i64 clock_type, struct time_value* tv);


#define X(NAME, VALUE) static const i64 MMAP_PROT_##NAME = VALUE;
    MMAP_PROTECTIONS
#undef X
#define X(NAME, VALUE) static const i64 MMAP_FLAG_##NAME = VALUE;
    MMAP_FLAGS
#undef X
#define X(NAME, VALUE) static const i64 MADVISE_FLAG_##NAME = VALUE;
    MADVISE_FLAGS
#undef X
#define X(NAME, VALUE) static const i64 MREMAP_FLAG_##NAME = VALUE;
    MREMAP_FLAGS
#undef X
i64 syscall_mmap(void* address, i64 size, i64 protection, i64 flags, i64 file_descriptor, i64 offset);
i64 syscall_mprotect(void* start, i64 size, i64 protection);
i64 syscall_madvise(void* start, i64 size, i64 behavior);
i64 syscall_mremap(void* old_address, i64 old_size, i64 new_size, i64 flags, void* new_address);
i64 syscall_munmap(void* address, i64 size);

// from linux kernel source: arch/x86/include/uapi/asm/stat.h
struct stat {
    u64 filesystem_device_id;
    u64 file_serial_number;
    u64 hard_link_count;
    u32 file_mode;
    u32 owner_user_id;
    u32 owner_group_id;
    u32 padding_for_alignment;
    u64 special_device_id;
    i64 file_size;
    i64 io_block_size_bytes; /* Preferred block size for file input and output. */
    i64 allocated_blocks;    /* Number of allocated 512-byte blocks. */
    u64 access_time_seconds;
    u64 access_time_nanoseconds;
    u64 modification_time_seconds;
    u64 modification_time_nanoseconds;
    u64 status_change_time_seconds;
    u64 status_change_time_nanoseconds;
    i64 reserved_for_future_use[3];
};
i64 syscall_stat(const char* filename, struct stat* buffer);
i64 syscall_fstat(i64 file_descriptor, struct stat* buffer);


i64 syscall_fork(void);
i64 syscall_vfork(void); // TODO: for some reason causes a segfault at execve, not fork()
i64 syscall_execve(const char* path, char** argv, char** envp);
i64 syscall_execveat(i64 directory_file_descriptor, const char* path, char** argv, char** envp, i64 flags);


i64 syscall_rename(char* old, char* new);
i64 syscall_mkdir(char* path, i64 mode);
i64 syscall_unlink(char* path);

// from linux-7.2/tools/include/nolibc/types.h
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


i64 syscall_kill(i64 pid, i64 signal) {
    return syscall_generic(SYSCALL_KILL, pid, signal, 0, 0, 0, 0);
}


i64 syscall_getpid(void) {
    return syscall_generic(SYSCALL_GETPID, 0, 0, 0, 0, 0, 0);
}
i64 syscall_gettid(void) {
    return syscall_generic(SYSCALL_GETTID, 0, 0, 0, 0, 0, 0);
}


i64 syscall_read(i64 file_descriptor, u8* buffer, u64 length) {
    return syscall_generic(SYSCALL_READ, file_descriptor, (u64)buffer, length, 0, 0, 0);
}
i64 syscall_write(i64 destination, u8* message, u64 length) {
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


i64 syscall_clock_gettime(i64 clock_type, struct time_value* tv) {
    return syscall_generic(SYSCALL_CLOCK_GETTIME, clock_type, (i64)tv, 0, 0, 0, 0);
}


i64 syscall_mmap(void* address, i64 size, i64 protection, i64 flags, i64 file_descriptor, i64 offset) {
    return syscall_generic(SYSCALL_MMAP, (u64)address, size, protection, flags, file_descriptor, offset);
}
i64 syscall_mprotect(void* start, i64 size, i64 protection) {
    return syscall_generic(SYSCALL_MPROTECT, (u64)start, size, protection, 0, 0, 0);
}
i64 syscall_madvise(void* start, i64 size, i64 behavior) {
    return syscall_generic(SYSCALL_MADVISE, (u64)start, size, behavior, 0, 0, 0);
}
i64 syscall_mremap(void* old_address, i64 old_size, i64 new_size, i64 flags, void* new_address) {
    return syscall_generic(SYSCALL_MREMAP, (u64)old_address, old_size, new_size, flags, (u64)new_address, 0);
}
i64 syscall_munmap(void* address, i64 size) {
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


void abort(void) {
    syscall_kill(syscall_getpid(), SIGNAL_ABRT);
    UNREACHABLE();
}


i64 get_clock_time(struct time_value* tv) {
    return syscall_clock_gettime(CLOCK_MONOTONIC, tv);
}


i64 errno_decode(i64 errno, char** name, char** description) {
    switch (errno) {
    #define X(NAME, VALUE, DESCRIPTION)                                        \
    case -VALUE: {                                                             \
        if (name != NIL) *name = #NAME;                                        \
        if (description != NIL) *description = DESCRIPTION;                    \
        return 0;                                                              \
    }
        ERRNO_TABLE
    #undef X
    }
    return -1;
}
i64 print_errno(i64 errno, const char* file, i64 line) {
    char* name = NIL;
    char* description = NIL;
    i64 ret = errno_decode(errno, &name, &description);
    if (ret < 0) { ERROR("Could not decode the errno %ld (%ld)", errno, ret); return -1; }
    if (name == NIL || description == NIL) { ERROR("Could not find the errno %ld", errno); return -2; }

    return eprint("[ERROR] %s:%d\tERRNO %s (%ld) - %s\n", file, line, name, -errno, description);
}


i64 vfprint(i64 fd, const char* format, va_list va) {
    u8 buffer[4096];
    if (format == NIL) return -1;

    const i64 length = stb_vsnprintf((char*)buffer, sizeof(buffer), format, va);
    if (length < 0) return -2;
    if (length == 0) return 0;

    // the formatted output is longer than the buffer, a write would go out of bounds
    if (length >= (i64)sizeof(buffer)) {
        ERROR("The formatted output does not fit into the print buffer (%ld bytes)", length);
        return -3;
    }

    const i64 written = syscall_write(fd, buffer, length);
    if (written < 0) return written;
    if (written != length) return -4;

    return 0;
}
i64 fprint(i64 fd, const char* format, ...) {
    if (format == NIL) return -1;

    va_list va;
    va_start(va, format);
    i64 ret = vfprint(fd, format, va);
    va_end(va);

    return ret;
}
i64 print(const char* format, ...) {
    if (format == NIL) return -1;

    va_list va;
    va_start(va, format);
    i64 ret = vfprint(1, format, va); // stdout
    va_end(va);

    return ret;
}
i64 eprint(const char* format, ...) {
    if (format == NIL) return -1;

    va_list va;
    va_start(va, format);
    i64 ret = vfprint(2, format, va); // stderr
    va_end(va);

    return ret;
}



i64 cmd_await(i64 pid) {
    if (pid <= 0) return -1;

    while (1) {
        i64 wstatus = 0;
        i64 ret = syscall_wait4(pid, &wstatus, 0, NIL);
        if (ret < 0) { ERROR("Could not wait on the command (pid %ld): %ld", pid, ret); return ret; }

        if (WIFEXITED(wstatus)) {
            const i64 exit_status = WEXITSTATUS(wstatus);
            if (exit_status != 0) { ERROR("The command exited with exit code %ld", exit_status); return -2; }
            break;
        }

        if (WIFSIGNALED(wstatus)) { ERROR("The command was terminated by signal %ld", (i64)WTERMSIG(wstatus)); return -3; }
    }

    return 0;
}
i64 cmd_run(struct shell_command* cmd) {
    if (cmd == NIL) return -1;
    if (cmd->arena == NIL) return -2;
    if (cmd->items == NIL || cmd->len <= 0) { ERROR("Cannot run an empty command"); return -3; }

    print("[DEBUG] Running:");
    for (i64 i = 0; i < cmd->len; i++) {
        print(" %s", cmd->items[i]);
    }
    print("\n");

    // execve expects a NIL after the last argument, it is not counted so the command is reusable
    i64 ret = _cmd_reserve(cmd, 1);
    if (ret < 0) return ret;
    cmd->items[cmd->len] = NIL;

    const i64 pid = syscall_fork();
    if (pid < 0) { ERROR("Could not fork the command (%ld)", pid); return -4; }

    if (pid == 0) {
        char program_path_buffer[4096] = {0};
        char* program_path = NIL;

        ret = find_executable(cmd->items[0], __envp, program_path_buffer, sizeof(program_path_buffer), &program_path);
        if (ret < 0) {
            print("[ERROR] Could not find the executable `%s` (%ld)\n", cmd->items[0], ret);
            syscall_exit(127);
        }
        ret = syscall_execve(program_path, cmd->items, __envp);
        print("[ERROR] Could not exec child process for %s: %ld\n", cmd->items[0], ret);
        syscall_exit(127);
    }

    ret = cmd_await(pid);
    if (ret < 0) { ERROR("Could not await the process (pid %ld)", pid); return ret; }

    cmd->len = 0;

    return 0;
}
i64 rebuild_needed(char* path_input, char* path_output, i32* out_is_needed) {
    struct stat statbuf = {0};
    i64 ret_code = 0;

    if (path_input == NIL) return -1;
    if (path_output == NIL) return -2;
    if (out_is_needed == NIL) return -3;

    *out_is_needed = 0;

    if ((ret_code = syscall_stat(path_output, &statbuf)) < 0) {
        if (ret_code == -ERRNO_ENOENT) { *out_is_needed = 1; return 0; } // a missing output needs a build
        ERROR("Could not stat %s: %ld", path_output, ret_code);
        return -3;
    }
    const i64 output_seconds = statbuf.modification_time_seconds;
    const i64 output_nanoseconds = statbuf.modification_time_nanoseconds;

    if ((ret_code = syscall_stat(path_input, &statbuf)) < 0) {
        // a missing input is an error, the build needs it
        ERROR("Could not stat %s: %ld", path_input, ret_code);
        return -4;
    }
    const i64 input_seconds = statbuf.modification_time_seconds;
    const i64 input_nanoseconds = statbuf.modification_time_nanoseconds;

    // Compare the whole timestamp, not just the fractional part of a second.
    *out_is_needed = input_seconds > output_seconds ||
        (input_seconds == output_seconds && input_nanoseconds > output_nanoseconds);

    return 0;
}
i64 rebuild_thyself(struct arena* arena, i32 argc, char** argv, char* path_input) {
    if (arena == NIL) return -1;
    if (argv == NIL) return -2;
    if (argc <= 0) return -3;
    if (path_input == NIL) return -4;

    char* path_output = SHIFT(argc, argv);
    if (path_output == NIL) return -5;

    i32 is_needed = 0;
    i64 ret = rebuild_needed(path_input, path_output, &is_needed);
    if (ret < 0) return ret;
    if (!is_needed) return 0;

    char path_output_old[1024] = {0};
    struct shell_command cmd = {0};

    TRY(cmd_init(&cmd, arena), "Could not initialize the command", ret, -6);

    const i64 written = stb_snprintf(path_output_old, 1024, "%s.old", path_output);
    if (written < 0 || written >= 1024) { ERROR("Could not build the backup path for %s", path_output); return -7; }

    ret = syscall_rename(path_output, path_output_old);
    if (ret < 0) { ERROR("Could not rename %s: %ld", path_output, ret); return -8; }

    TRY(cmd_append(&cmd, "cc"), "Could not append to the command", ret, -9);
    TRY(cmd_append(&cmd, path_input, "std.linux.s", "-o", path_output), "Could not append to the command", ret, -10);
    TRY(cmd_append(&cmd, "-nostdlib"), "Could not append to the command", ret, -11);
    TRY(cmd_append(&cmd, "-fno-stack-protector"), "Could not append to the command", ret, -12);

    ret = cmd_run(&cmd);
    if (ret < 0) {
        ERROR("Could not rebuild, restoring the previous binary");
        syscall_rename(path_output_old, path_output);
        return ret;
    }

    syscall_unlink(path_output_old);

    TRY(cmd_append(&cmd, path_output), "Could not append to the command", ret, -13);
    TRY(cmd_append_array(&cmd, argv, argc), "Could not append to the command", ret, -14);

    ret = cmd_run(&cmd);
    if (ret < 0) return ret;

    return 1; // only the replacement builder may continue the build
}
i64 init_ignored_dir(char* path_dir, char* path_ignore) {
    if (path_dir == NIL) return -1;
    if (path_ignore == NIL) return -2;

    char buf[1024] = {0};
    i64 fd = -1;

    const i64 ret_code = syscall_mkdir(path_dir, 0755);
    if (ret_code < 0 && ret_code != -ERRNO_EEXIST) {
        ERROR("Could not create the directory `%s`: %ld", path_dir, ret_code);
        return -3;
    }

    const i64 written = stb_snprintf(buf, sizeof(buf), "%s%s", path_dir, path_ignore);
    if (written < 0 || written >= (i64)sizeof(buf)) { ERROR("Could not build the ignore file path"); return -4; }

    fd = syscall_open(buf, OPEN_FLAG_RDWR|OPEN_FLAG_CREAT|OPEN_FLAG_TRUNC, 0644);
    if (fd < 0) { ERROR("Could not open the file %s for writing: %ld", buf, fd); return -5; }

    const char* contents = "*";
    const i64 written_contents = syscall_write(fd, (u8*)contents, 1);
    if (written_contents < 0) {
        ERROR("Could not write into the file %s: %ld", buf, written_contents);
        syscall_close(fd);
        return -6;
    }

    const i64 closed = syscall_close(fd);
    if (closed < 0) { ERROR("Could not close the file %s: %ld", buf, closed); return -7; }

    return 0;
}
i64 find_executable(char* name, char** envp, char* result_buffer, i64 result_buffer_capacity, char** out_program_path) {
    if (name == NIL) return -1;
    if (result_buffer == NIL) return -2;
    if (result_buffer_capacity <= 0) return -3;
    if (out_program_path == NIL) return -4;

    *out_program_path = NIL;

    i64 name_length = 0;
    const i64 ret = zstr_length(name, &name_length);
    if (ret < 0) return -5;
    if (name_length == 0) return -6;

    // the name already contains a path => it is used as it is
    for (i64 i = 0; i < name_length; i++) {
        if (name[i] == '/') { *out_program_path = name; return 0; }
    }

    // find `PATH` in the environment
    char* path = NIL;
    if (envp != NIL) {
        for (char** env = envp; *env != NIL; env++) {
            char* entry = *env;
            if (entry[0] == 'P' && entry[1] == 'A' && entry[2] == 'T' && entry[3] == 'H' && entry[4] == '=') {
                path = entry + 5; // skip `PATH=`
                break;
            }
        }
    }
    if (path == NIL) path = "/usr/local/bin:/usr/bin:/bin"; // some default value

    char buffer_path[4096] = {0};
    static char buffer_dirent[4096] = {0};

    // the last `PATH` entry has no delimiter
    while (1) {
        i64 delimiter_index = 0;
        while (path[delimiter_index] != 0 && path[delimiter_index] != ':') delimiter_index += 1;
        const i64 is_last_entry = path[delimiter_index] == 0;

        if (delimiter_index > 0 && delimiter_index < (i64)sizeof(buffer_path)) {
            memcpy(buffer_path, path, delimiter_index);
            buffer_path[delimiter_index] = 0;
            const i64 buffer_path_len = delimiter_index;
            path += is_last_entry ? delimiter_index : delimiter_index + 1;

            const i64 fd = syscall_open(buffer_path, OPEN_FLAG_RDONLY | OPEN_FLAG_DIRECTORY, 0644);
            if (fd < 0) {
                // a directory that does not open cannot contain the executable
                ERROR("Could not open the directory `%s`: %ld, skipping it", buffer_path, fd);
            } else {
                i64 found = 0;
                while (!found) {
                    const i64 read_count = syscall_getdents64(fd, (void*)buffer_dirent, sizeof(buffer_dirent));
                    if (read_count < 0) { ERROR("Could not read the directory `%s`: %ld", buffer_path, read_count); syscall_close(fd); return -7; }
                    if (read_count == 0) break;

                    for (i64 offset = 0; offset < read_count;) {
                        struct directory_entry* dirent = (struct directory_entry*)(buffer_dirent + offset);
                        if (dirent->self_size <= 0) break;
                        offset += dirent->self_size;

                        if (dirent->type != ENTRY_TYPE_REGULAR_FILE && dirent->type != ENTRY_TYPE_SYMBOLIC_LINK) continue;

                        i64 dirent_name_length = 0;
                        if (zstr_length(dirent->name, &dirent_name_length) < 0) continue;
                        if (dirent_name_length != name_length) continue;
                        if (memcmp(name, dirent->name, (u64)name_length) != 0) continue;

                        if (buffer_path_len + 1 + name_length + 1 > result_buffer_capacity) {
                            ERROR("The given buffer is too short: need %ld - was given %ld", buffer_path_len + 1 + name_length + 1, result_buffer_capacity);
                            syscall_close(fd);
                            return -8;
                        }
                        memcpy(result_buffer, buffer_path, (u64)buffer_path_len);
                        result_buffer[buffer_path_len] = '/';
                        memcpy(result_buffer + buffer_path_len + 1, name, (u64)name_length);
                        result_buffer[buffer_path_len + 1 + name_length] = 0;

                        found = 1;
                        break;
                    }
                }

                const i64 closed = syscall_close(fd);
                if (closed < 0) { ERROR("Could not close the directory `%s`: %ld", buffer_path, closed); return -9; }

                if (found) { *out_program_path = result_buffer; return 0; }
            }
        }

        if (is_last_entry) break;
        if (delimiter_index == 0) continue;
        if (delimiter_index >= (i64)sizeof(buffer_path)) path += delimiter_index + 1;
    }

    return -10; // not found
}

i64 vmem(vmem_action action, u8** ptr, u64 size) {
    if (ptr == NIL) { ERROR("Passed a NIL pointer to the memory (%ld)", (i64)size); return -1; }
    if ((i64)size < 0) { ERROR("Passed a negative size (%ld)", (i64)size); return -2; }

    switch (action) {
        case VMEM_RESERVE: {
            if (*ptr != NIL) { ERROR("Cannot reserve over an already reserved range"); return -3; }

            const i64 reserve_size = ROUND_UP_TO((i64)size, STD_PAGE_SIZE);
            if (reserve_size <= 0) { ERROR("Cannot reserve the requested amount of memory (%ld)", (i64)size); return -4; }

            const i64 result = syscall_mmap(NIL, reserve_size, MMAP_PROT_NONE, MMAP_FLAG_PRIVATE|MMAP_FLAG_ANONYMOUS, -1, 0);
            if (result < 0) { ERROR("Could not mmap (%ld)", result); print_errno(result, __FILE__, __LINE__); return -5; }

            *ptr = (u8*)result;
            return 0;
        }; break;
        case VMEM_COMMIT: {
            if (*ptr == NIL) { ERROR("Cannot commit a NIL range"); return -6; }
            if (size == 0) { ERROR("Cannot commit an empty range"); return -7; }

            // the kernel maps whole pages, so the range is expanded to the page boundaries
            const i64 start = ROUND_DOWN_TO((i64)*ptr, STD_PAGE_SIZE);
            const i64 end   = ROUND_UP_TO((i64)*ptr + (i64)size, STD_PAGE_SIZE);
            if (end <= start) { ERROR("Cannot commit an empty range"); return -8; }

            const i64 result = syscall_mprotect((void*)start, end - start, MMAP_PROT_READ|MMAP_PROT_WRITE);
            if (result < 0) { ERROR("Could not mprotect (%ld)", result); print_errno(result, __FILE__, __LINE__); return -9; }

            return 0;
        }; break;
        case VMEM_DECOMMIT: {
            if (*ptr == NIL) { ERROR("Cannot decommit a NIL range"); return -10; }
            if (size == 0) { ERROR("Cannot decommit an empty range"); return -11; }

            // only the pages that are fully inside the range can be given back
            const i64 start = ROUND_UP_TO((i64)*ptr, STD_PAGE_SIZE);
            const i64 end   = ROUND_DOWN_TO((i64)*ptr + (i64)size, STD_PAGE_SIZE);
            if (end <= start) return 0; // only parts of pages, nothing to give back

            i64 result = syscall_madvise((void*)start, end - start, MADVISE_FLAG_DONTNEED);
            if (result < 0) { ERROR("Could not madvise (%ld)", result); print_errno(result, __FILE__, __LINE__); return -12; }

            result = syscall_mprotect((void*)start, end - start, MMAP_PROT_NONE);
            if (result < 0) { ERROR("Could not mprotect (%ld)", result); print_errno(result, __FILE__, __LINE__); return -13; }

            return 0;
        }; break;
        case VMEM_RELEASE: {
            if (*ptr == NIL) { ERROR("Cannot release a NIL range"); return -14; }
            if (size == 0) { ERROR("Cannot release an empty range"); return -15; }

            const i64 release_size = ROUND_UP_TO((i64)size, STD_PAGE_SIZE);
            if (release_size <= 0) { ERROR("Cannot release the requested amount of memory (%ld)", (i64)size); return -16; }

            const i64 result = syscall_munmap(*ptr, release_size);
            if (result < 0) { ERROR("Could not munmap (%ld)", result); print_errno(result, __FILE__, __LINE__); return -17; }

            *ptr = NIL;
            return 0;
        }; break;
        default: { ERROR("Unknown memory action (%ld)", (i64)action); return -18; } break;
    }

    return 0;
}

#endif // STD_LINUX_IMPLEMENTATION_GUARD
#endif // STD_LINUX_IMPLEMENTATION

#endif // STD_LINUX_H
