#ifndef STD_COMMON_H
#define STD_COMMON_H

#ifdef STD_COMMON_IMPLEMENTATION
#   define STB_SPRINTF_IMPLEMENTATION
#   define STB_SPRINTF_NOUNALIGNED
#endif /* STD_COMMON_IMPLEMENTATION */
#include "stb_sprintf.h"

#ifndef NULL
#   define NULL ((void*)0)
#endif

#define UNREACHABLE() __builtin_unreachable()
#define ASSERT(CONDITION) ((CONDITION) ? (void)0 : UNREACHABLE())

#define ROUND_UP_4K(X) (((X) + 0xFFF) & ~0xFFF)

#define SHIFT(argc, argv) (--(argc), *(argv)++)
#define REBUILD_THYSELF(ARGC, ARGV) rebuild_thyself((ARGC), (ARGV), __FILE__)

/* from linux-7.2/tools/include/nolibc/types.h */
#define WEXITSTATUS(status) (((status) & 0xff00) >> 8)
#define WIFEXITED(status)   (((status) & 0x7f) == 0)
#define WTERMSIG(status)    ((status) & 0x7f)
#define WIFSIGNALED(status) ((status) - 1 < 0xff)

#define da_append(xs, x)                                                       \
    do {                                                                       \
        if ((xs)->len >= (xs)->cap) {                                          \
            (xs)->cap *= 2;                                                    \
            if ((xs)->cap == 0) (xs)->cap = 64;                                \
            block_resize(&(xs)->buffer, sizeof(*(xs)->items) * (xs)->cap);     \
            (xs)->items = (xs)->buffer.ptr;                                    \
        }                                                                      \
        (xs)->items[(xs)->len++] = (x);                                        \
    } while (0)

typedef signed   char  i8;
typedef unsigned char  u8;
typedef signed   short i16;
typedef unsigned short u16;
typedef signed   int   i32;
typedef unsigned int   u32;
typedef signed   long  i64;
typedef unsigned long  u64;
typedef float          f32;
typedef double         f64;

static const i64 CODE_OK    =  0;
static const i64 CODE_ERROR = -1;
static const i64 CODE_NOOP  =  2 * CODE_ERROR; /* TODO: remove this shit */

/* HACK: provide some functions from C std so that the compiler does not shit itself */
void* memset(void* dst, i32  byte, u64 length);
void* memcpy(void* dst, const void* src, u64 length);
i32 memcmp(const void* a, const void* b, u64 length);

i64 zstr_length(char* zstr);

void print(const char* format, ...);


struct block {
    void* ptr;
    i64 cap;
    i64 len;
};
i64 block_make(struct block* mb, i64 size);
i64 block_destroy(struct block* mb);
i64 block_resize(struct block* mb, i64 new_size);



/* adapted from github:tsoding/nob.h */
char** __envp; /* must pass this to execve; set up in INSERT_ENTRY_POINT */
struct shell_command {
    struct block buffer;
    char** items;
    i64 len, cap;
};
void cmd_append_fn(struct shell_command* cmd, i64 argc, char** argv);
i64 cmd_await(i64 pid);
i64 cmd_run(struct shell_command* cmd);
i64 rebuild_needed(char* path_input, char* path_output);
void rebuild_thyself(i32 argc, char** argv, char* path_input);
i32 init_ignored_dir(char* path_dir, char* path_ignore);
i64 find_executable(char* name, char* envp[], char* result_buffer, i64 result_buffer_capacity);

#define cmd_append(cmd, ...)                          \
    cmd_append_fn((cmd),                              \
        sizeof((char*[]){__VA_ARGS__})/sizeof(char*), \
        (char*[]){__VA_ARGS__}                        \
    )

#define cmd_append_array(cmd, xs, n)                                          \
    do {                                                                      \
        if ((cmd)->cap - (cmd)->len < (n)) {                                  \
            if ((cmd)->cap == 0) (cmd)->cap = 64;                             \
            while (((cmd)->cap - (cmd)->len) < (n)) (cmd)->cap *= 2;          \
            block_resize(&(cmd)->buffer, sizeof(*(cmd)->items) * (cmd)->cap); \
            (cmd)->items = (cmd)->buffer.ptr;                                 \
        }                                                                     \
        memcpy((cmd)->items+(cmd)->len, (xs), (n)*sizeof(*(cmd)->items));     \
        (cmd)->len += n;                                                      \
    } while (0)



#ifdef STD_COMMON_IMPLEMENTATION
#ifndef STD_COMMON_IMPLEMENTATION_GUARD
#define STD_COMMON_IMPLEMENTATION_GUARD

void* memset(void* dst, i32 byte, u64 length) {
    u64 i;
    for (i = 0; i < length; i++) {
        ((u8*)dst)[i] = (u8)byte;
    }
    return dst;
}
void* memcpy(void* dst, const void* src, u64 length) {
    u64 i;
    for (i = 0; i < length; i++) {
        ((u8*)dst)[i] = ((u8*)src)[i];
    }
    return dst;
}
i32 memcmp(const void* a, const void* b, u64 length) {
    i32 i = 0;
    u8* A = (u8*)a;
    u8* B = (u8*)b;

    if (a == NULL || b == NULL || length == 0) return 1;

    for (i = 0; i < (i64)length; i++) {
        if (A[i] > B[i]) return 1;
        if (A[i] < B[i]) return -1;
    }
    return 0;
}

i64 zstr_length(char* zstr) {
    static const i64 MAX_STRING_LENGTH = 4096;
    i64 i;

    if (zstr == NULL) return -1;
    for (i = 0; i < MAX_STRING_LENGTH; i++) {
        if (zstr[i] == 0) return i;
    }
    return MAX_STRING_LENGTH;
}

void cmd_append_fn(struct shell_command* cmd, i64 argc, char** argv) {
    i64 i = 0;
    for (i = 0; i < argc; i ++) {
        da_append(cmd, argv[i]);
    }
}

#endif /* STD_COMMON_IMPLEMENTATION_GUARD */
#endif /* STD_COMMON_IMPLEMENTATION */

#endif /* STD_COMMON_H */