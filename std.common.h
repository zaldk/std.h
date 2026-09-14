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

#define UNREACHABLE() do { *(volatile int *)0 = 0; __builtin_unreachable(); } while (0)
#define ASSERT(CONDITION) ((CONDITION) ? (void)0 : UNREACHABLE())

#define MULTILINE_STRING(...) #__VA_ARGS__

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

#define RETURN_CODES \
    X(OK,       0) \
    X(ERROR,    1)
#define X(NAME, VALUE) \
    static const i64 CODE_##NAME = VALUE;
RETURN_CODES
#undef X

/* HACK: provide some function from C std so that the compiler does not shit itself */
void* memset(char* dst, char character, u64 length);

void print(const char* format, ...);



#ifdef STD_COMMON_IMPLEMENTATION
#ifndef STD_COMMON_IMPLEMENTATION_GUARD
#define STD_COMMON_IMPLEMENTATION_GUARD

void* memset(char* dst, char character, u64 length) {
    u64 i = 0;
    for (; i < length; i++) {
        dst[i] = (char)character;
    }
    return dst;
}

#endif /* STD_COMMON_IMPLEMENTATION_GUARD */
#endif /* STD_COMMON_IMPLEMENTATION */

#endif /* STD_COMMON_H */