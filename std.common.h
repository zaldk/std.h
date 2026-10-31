#ifndef STD_COMMON_H
#define STD_COMMON_H

#ifdef STD_COMMON_IMPLEMENTATION
#   define STB_SPRINTF_IMPLEMENTATION
#   define STB_SPRINTF_NOUNALIGNED
#endif // STD_COMMON_IMPLEMENTATION
#define STB_SPRINTF_DECORATE(name) stb_##name
#include "stb_sprintf.h"

#ifndef NIL
# define NIL ((void*)0)
#endif

#define UNREACHABLE() do { eprint("%s:%d: UNREACHABLE\n", __FILE__, __LINE__); abort(); } while(0)
#define TODO(message) do { eprint("%s:%d: TODO: %s\n", __FILE__, __LINE__, message); abort(); } while(0)
#define ASSERT(CONDITION) do { if (!(CONDITION)) UNREACHABLE(); } while (0)

#define ROUND_UP_TO(X, N) (((X) + (N-1)) & ~(N-1))
#define ROUND_DOWN_TO(X, N) ((X) & ~(N-1))

#define STD_ENUM(TYPE, NAME) typedef TYPE NAME; enum
#define SHIFT(argc, argv) (--(argc), *(argv)++)
#define REBUILD_THYSELF(ARENA, ARGC, ARGV) rebuild_thyself((ARENA), (ARGC), (ARGV), __FILE__)

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

// the compiler can emit calls to these, so the C std replacements live here
void* memset(void* dst, i32  byte, u64 length);
void* memcpy(void* dst, const void* src, u64 length);
i32 memcmp(const void* a, const void* b, u64 length);

void abort(void);

struct time_value {
    i64 seconds;
    i64 nanoseconds;
};
i64 get_clock_time(struct time_value* tv);

static inline i64 __time_profile_init(void);
static inline i64 __time_profile_fini(void);
static i64 __TIME_PROFILE_LATCH, __TIME_PROFILE_SECONDS, __TIME_PROFILE_NANOS;
#define TIME_PROFILE() \
    for ( \
        __TIME_PROFILE_LATCH = (__time_profile_init(), 0); \
        __TIME_PROFILE_LATCH < 1; \
        __TIME_PROFILE_LATCH = (__time_profile_fini(), 1) \
    )


struct string {
    u8* store;
    i64 len;
};
i64 utf_to_i32(u8* buffer, i32* rune, i32* length);

// a negative i64 is an error, 0 is a success, the outputs are references
i64 zstr_length(char* zstr, i64* out_length);
i64 zstr_equal(char* zstr1, char* zstr2, i32* out_is_equal);

i64 vfprint(i64 fd, const char* format, va_list va);
i64 fprint(i64 fd, const char* format, ...);
i64 print(const char* format, ...);
i64 eprint(const char* format, ...);
#define ERROR(MSG, ...) eprint("[ERROR] %s:%d\t" MSG "\n", __FILE__, __LINE__, ##__VA_ARGS__)
#define ERROR_CODE(MSG, ERROR_VAR, RETURN_VALUE, ...) do { \
    if (ERROR_VAR < 0) { \
        eprint("[ERROR] %s:%d\t" MSG " (%ld)\n", __FILE__, __LINE__, ##__VA_ARGS__, ERROR_VAR); \
        return (RETURN_VALUE); \
    } } while (0)
#define TRY(EXPR, MSG, ERROR_VAR, RETURN_VALUE) do { ERROR_VAR = EXPR; ERROR_CODE(MSG, ERROR_VAR, RETURN_VALUE); } while (0)


// adapted from github:tsoding/nob.h
char** __envp; // must be passed to execve, it is set up in INSERT_ENTRY_POINT

struct arena; // the definition is below
// the items live in the arena, so a command owns nothing and the arena must outlive it
struct shell_command {
    struct arena* arena;
    char** items;
    i64 len, cap;
};
i64 cmd_init(struct shell_command* cmd, struct arena* arena);
i64 cmd_append_fn(struct shell_command* cmd, i64 argc, char** argv);
i64 cmd_append_array(struct shell_command* cmd, char** items, i64 count);
i64 cmd_await(i64 pid);
i64 cmd_run(struct shell_command* cmd);
i64 rebuild_needed(char* path_input, char* path_output, i32* out_is_needed);
i64 rebuild_thyself(struct arena* arena, i32 argc, char** argv, char* path_input);
i64 init_ignored_dir(char* path_dir, char* path_ignore);
i64 find_executable(char* name, char** envp, char* result_buffer, i64 result_buffer_capacity, char** out_program_path);

#define cmd_append(cmd, ...)                          \
    cmd_append_fn((cmd),                              \
        sizeof((char*[]){__VA_ARGS__})/sizeof(char*), \
        (char*[]){__VA_ARGS__}                        \
    )


#define KB 1024
#define MB KB*KB
#define GB MB*KB

// commit and decommit work with whole pages only
#define STD_PAGE_SIZE (4*KB)

STD_ENUM(i64, vmem_action) {
    VMEM_RESERVE,
    VMEM_COMMIT,
    VMEM_DECOMMIT,
    VMEM_RELEASE,
};
i64 vmem(vmem_action action, u8** ptr, u64 size);

// use it through vmem: reserve more than you need and commit on demand
struct arena {
    u8* store __attribute__((aligned(4096))); // align to page size
    i64 len;
    i64 committed;
    i64 reserved;
};
i64 arena_init(struct arena* arena, i64 initial_size);
i64 arena_push(struct arena* arena, i64 size, u8** out);
i64 arena_free(struct arena* arena);
i64 arena_clear(struct arena* arena);




#ifdef STD_COMMON_IMPLEMENTATION
#ifndef STD_COMMON_IMPLEMENTATION_GUARD
#define STD_COMMON_IMPLEMENTATION_GUARD

// gcc knows the nonnull attribute of the C std functions and warns about a NIL check
// in the function itself, so the check gets its own function without the attribute
static inline i32 _is_nil(const void* ptr) { return ptr == NIL; }

// an optimizing gcc turns these loops back into calls to these functions, the
// volatile store stops that (a plain loop calls itself until the stack ends)
void* memset(void* dst, i32 byte, u64 length) {
    u64 i;
    volatile u8* out;
    if (_is_nil(dst)) return NIL;

    out = (volatile u8*)dst;
    for (i = 0; i < length; i++) {
        out[i] = (u8)byte;
    }
    return dst;
}
void* memcpy(void* dst, const void* src, u64 length) {
    u64 i;
    volatile u8* out;
    const u8* in;
    if (_is_nil(dst) || _is_nil(src)) return NIL;

    out = (volatile u8*)dst;
    in = (const u8*)src;
    for (i = 0; i < length; i++) {
        out[i] = in[i];
    }
    return dst;
}
i32 memcmp(const void* a, const void* b, u64 length) {
    // the comparison result is the return value, so a NIL argument counts as an empty range
    if (_is_nil(a) || _is_nil(b) || length == 0) return 0;

    const u8* A = (const u8*)a;
    const u8* B = (const u8*)b;
    for (u64 i = 0; i < length; i++) {
        if (A[i] > B[i]) return 1;
        if (A[i] < B[i]) return -1;
    }
    return 0;
}

static inline i64 __time_profile_init(void) {
    i64 ret = 0;
    struct time_value tv = {0};
    TRY(get_clock_time(&tv), "Could not get time (_time_profile_init)", ret, -1);
    __TIME_PROFILE_SECONDS = tv.seconds;
    __TIME_PROFILE_NANOS = tv.nanoseconds;
    return 0;
}
static inline i64 __time_profile_fini(void) {
    i64 ret = 0;
    struct time_value s = {__TIME_PROFILE_SECONDS, __TIME_PROFILE_NANOS}, e = {0}, d = {0};
    TRY(get_clock_time(&e), "Could not get time (_time_profile_fini)", ret, -1);
    d.seconds     = e.seconds     - s.seconds;
    d.nanoseconds = e.nanoseconds - s.nanoseconds;

    print("[TIME] START: %6ld (s) %03ld (ms) %03ld (us) %03ld (ns)\n",
        s.seconds, s.nanoseconds/1000000, (s.nanoseconds % 1000000)/1000, s.nanoseconds % 1000);
    print("[TIME]   END: %6ld (s) %03ld (ms) %03ld (us) %03ld (ns)\n",
        e.seconds, e.nanoseconds/1000000, (e.nanoseconds % 1000000)/1000, e.nanoseconds % 1000);
    print("[TIME]  DIFF: %6ld (s) %03ld (ms) %03ld (us) %03ld (ns)\n",
        d.seconds, d.nanoseconds/1000000, (d.nanoseconds % 1000000)/1000, d.nanoseconds % 1000);

    return 0;
}

i64 utf_to_i32(u8* buffer, i32* rune, i32* length) {
    if (buffer == NIL) return -1;

    // from https://git.mr4th.com/mr4th-public/4coder/src/commit/
    // d67546b4b2d5772b8659353ff3b84133f52c1da8/4coder_lib/4coder_utf8.h
    static const i32 surrogate_min = 0xD800;
    static const i32 surrogate_max = 0xDFFF;
    // static const i32 nonchar_min = 0xFDD0;
    // static const i32 nonchar_max = 0xFDEF;
    static const i32 min_utf8_length[] = { 0x0, 0x0, 0x80, 0x800, 0x10000 };

    i32 _rune, _length;

    if (buffer[0] < 0x80) {
        _rune = (i32)buffer[0];
        _length = 1;
    } else if (buffer[0] < 0xE0) {
        _rune = ((i32)((buffer[0]) & 0x1F)) << 6;
        _rune |= ((i32)((buffer[1]) & 0x3F));
        _length = 2;
    } else if (buffer[0] < 0xF0) {
        _rune = ((i32)((buffer[0]) & 0x0F)) << 12;
        _rune |= ((i32)((buffer[1]) & 0x3F)) << 6;
        _rune |= ((i32)((buffer[2]) & 0x3F));
        _length = 3;
    } else {
        _rune = ((i32)((buffer[0]) & 0x07)) << 18;
        _rune |= ((i32)((buffer[1]) & 0x3F)) << 12;
        _rune |= ((i32)((buffer[2]) & 0x3F)) << 6;
        _rune |= ((i32)((buffer[3]) & 0x3F));
        _length = 4;
    }

    if (_rune < min_utf8_length[_length] ||
        (_rune >= surrogate_min && _rune <= surrogate_max)
    ) {
        _rune = 0;
        _length = 0;
        ERROR("Invalid UTF codepoint");
        return -2;
    }

    if (rune != NIL) *rune = _rune;
    if (length != NIL) *length = _length;
    return 0;
}

i64 zstr_length(char* zstr, i64* out_length) {
    // a string above the cap reports the cap as its length, an error would lose the length
    static const i64 MAX_STRING_LENGTH = 4096;

    if (zstr == NIL) return -1;
    if (out_length == NIL) return -2;

    for (i64 i = 0; i < MAX_STRING_LENGTH; i++) {
        if (zstr[i] == 0) { *out_length = i; return 0; }
    }

    *out_length = MAX_STRING_LENGTH;
    return 0;
}

i64 zstr_equal(char* zstr1, char* zstr2, i32* out_is_equal) {
    i64 len1 = 0, len2 = 0;
    i64 ret;

    if (zstr1 == NIL) return -1;
    if (zstr2 == NIL) return -2;
    if (out_is_equal == NIL) return -3;

    *out_is_equal = 0;

    TRY(zstr_length(zstr1, &len1), "Could not get the length", ret, -4);
    TRY(zstr_length(zstr2, &len2), "Could not get the length", ret, -5);

    if (len1 != len2) return 0;

    *out_is_equal = 1;
    for (i64 i = 0; i < len1; i += 1) {
        if (zstr1[i] != zstr2[i]) { *out_is_equal = 0; return 0; }
    }

    return 0;
}

// private: the padding is wasted, an arena only ever moves forward
static inline i64 _arena_push_aligned(struct arena* arena, i64 size, i64 alignment, u8** out) {
    if (arena == NIL) return -1;
    if (out == NIL) return -2;
    if (size < 0) return -3;
    if (alignment <= 0 || (alignment & (alignment - 1)) != 0) return -4;

    const i64 padding = ROUND_UP_TO(arena->len, alignment) - arena->len;
    if (padding > 0) {
        u8* unused = NIL;
        const i64 ret = arena_push(arena, padding, &unused);
        if (ret < 0) return ret;
    }

    return arena_push(arena, size, out);
}

i64 cmd_init(struct shell_command* cmd, struct arena* arena) {
    if (cmd == NIL) return -1;
    if (arena == NIL) return -2;

    cmd->arena = arena;
    cmd->items = NIL;
    cmd->len = 0;
    cmd->cap = 0;

    return 0;
}

// private: growing pushes a bigger array and copies the old items, the old array
// stays in the arena and cannot be given back
static inline i64 _cmd_reserve(struct shell_command* cmd, i64 additional) {
    if (cmd == NIL) return -1;
    if (cmd->arena == NIL) return -2;
    if (additional < 0) return -3;
    if (cmd->cap - cmd->len >= additional) return 0;

    i64 new_cap = cmd->cap > 0 ? cmd->cap : 8;
    while (new_cap - cmd->len < additional) new_cap *= 2;

    u8* new_items = NIL;
    const i64 ret = _arena_push_aligned(cmd->arena, new_cap * (i64)sizeof(char*), _Alignof(char*), &new_items);
    if (ret < 0) { ERROR("Could not push the command items into the arena (%ld)", ret); return ret; }

    if (cmd->items != NIL && cmd->len > 0) {
        memcpy(new_items, cmd->items, cmd->len * (i64)sizeof(char*));
    }

    cmd->items = (char**)new_items;
    cmd->cap = new_cap;

    return 0;
}

i64 cmd_append_fn(struct shell_command* cmd, i64 argc, char** argv) {
    if (cmd == NIL) return -1;
    if (argv == NIL) return -2;
    if (argc < 0) return -3;

    const i64 ret = _cmd_reserve(cmd, argc);
    if (ret < 0) return ret;

    for (i64 i = 0; i < argc; i++) cmd->items[cmd->len++] = argv[i];

    return 0;
}
i64 cmd_append_array(struct shell_command* cmd, char** items, i64 count) {
    return cmd_append_fn(cmd, count, items);
}

i64 arena_init(struct arena* arena, i64 initial_size) {
    i64 ret;

    if (arena == NIL) return -1;
    if (initial_size < 0) return -2;
    if (arena->store != NIL) { ERROR("The arena is already initialized"); return -3; }

    arena->len = 0;
    arena->committed = 0; // always a multiple of a page, `len` is the actually used part
    arena->reserved = ROUND_UP_TO(initial_size, 64*MB);
    if (arena->reserved <= 0) arena->reserved = 64*MB;

    ret = vmem(VMEM_RESERVE, &arena->store, arena->reserved);
    if (ret < 0) { ERROR("Could not reserve memory for an arena (%ld)", ret); return ret; }

    return 0;
}
i64 arena_push(struct arena* arena, i64 size, u8** out) {
    i64 ret;

    if (arena == NIL) return -1;
    if (size < 0) return -2;
    if (out == NIL) return -3;
    if (arena->len + size > arena->reserved) return -4;

    // commit as many whole pages as the new allocation needs
    const i64 required_committed = ROUND_UP_TO(arena->len + size, STD_PAGE_SIZE);
    if (required_committed > arena->committed) {
        u8* commit_start = arena->store + arena->committed; // `committed` is page aligned
        const i64 commit_size = required_committed - arena->committed;

        ret = vmem(VMEM_COMMIT, &commit_start, commit_size);
        if (ret < 0) { ERROR("Could not commit to an arena (%ld)", ret); return ret; }

        arena->committed = required_committed;
    }

    *out = arena->store + arena->len;
    arena->len += size;

    return 0;
}
i64 arena_clear(struct arena* arena) {
    if (arena == NIL) return -1;

    // the committed pages are kept around, the next pushes reuse them
    arena->len = 0;

    return 0;
}
i64 arena_free(struct arena* arena) {
    i64 ret;

    if (arena == NIL) return -1;
    if (arena->store == NIL) return 0;

    if (arena->committed > 0) {
        u8* decommit_start = arena->store; // `committed` is page aligned, so it is decommitted as a whole
        ret = vmem(VMEM_DECOMMIT, &decommit_start, arena->committed);
        if (ret < 0) { ERROR("Could not decommit an arena (%ld)", ret); return ret; }
        arena->committed = 0;
    }

    ret = vmem(VMEM_RELEASE, &arena->store, arena->reserved);
    if (ret < 0) { ERROR("Could not release an arena (%ld)", ret); return ret; }

    arena->store = NIL;
    arena->len = 0;
    arena->reserved = 0;

    return 0;
}

#endif // STD_COMMON_IMPLEMENTATION_GUARD
#endif // STD_COMMON_IMPLEMENTATION

#endif // STD_COMMON_H
