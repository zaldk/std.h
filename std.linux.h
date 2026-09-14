#ifndef STD_LINUX_H
#define STD_LINUX_H

#include "std.common.h"
#include "std.linux.tables.h"

#define INSERT_ENTRY_POINT() __asm__ (MULTILINE_STRING( \
    .globl _start                        \n            \
    _start:                              \n            \
    \t xor     rbp, rbp                  \n            \
    \t mov     rdi, rsp                  \n /* argc */ \
    \t lea     rsi, [rsp + 8]            \n /* argv */ \
    \t lea     rdx, [rsp + 16 + rdi*8]   \n /* envp */ \
    \t call    start                     \n            \
    \t mov     rdi, rax                  \n            \
    \t mov     rax, 60                   \n /* exit */ \
    \t syscall                           \n            \
));


#define X(NUMBER, _, NAME) static const i64 SYSCALL_##NAME = NUMBER;
    SYSCALL_TABLE
#undef X
i64 syscall_generic(u64 code, u64 arg1, u64 arg2, u64 arg3, u64 arg4, u64 arg5, u64 arg6);


i64 syscall_read(i64 file_descriptor, char* buffer, u64 length);
i64 syscall_write(i64 destination, char* message, u64 length);


#define X(NAME, VALUE) static const i64 MODE_##NAME = VALUE;
    OPEN_MODES
#undef X
i64 syscall_open(const char* filename, i64 flags, u64 mode);
i64 syscall_close(i64 file_descriptor);



#define X(NAME, VALUE) static const i64 MMAP_PROT_##NAME = VALUE;
    MMAP_PROTECTIONS
#undef X


#define X(NAME, VALUE) static const i64 MMAP_FLAG_##NAME = VALUE;
    MMAP_FLAGS
#undef X
i64 syscall_mmap(void* address, u64 size, i64 protection, i64 flags, i64 file_descriptor, i64 offset);
i64 syscall_munmap(void* address, u64 size);


void syscall_exit(i64 exit_code);



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


i64 syscall_mmap(void* address, u64 size, i64 protection, i64 flags, i64 file_descriptor, i64 offset) {
    return syscall_generic(SYSCALL_MMAP, (u64)address, size, protection, flags, file_descriptor, offset);
}

i64 syscall_munmap(void* address, u64 size) {
    return syscall_generic(SYSCALL_MUNMAP, (u64)address, size, 0, 0, 0, 0);
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


#endif /* STD_LINUX_IMPLEMENTATION_GUARD */
#endif /* STD_LINUX_IMPLEMENTATION */

#endif /* STD_LINUX_H */