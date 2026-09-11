#ifndef STD_X86_64
#define STD_X86_64

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

static const i32 CODE_OK    = 0;
static const i32 CODE_ERROR = 1;

i32 check_integers(void) {
    if (sizeof(i8)  != 1) return CODE_ERROR;
    if (sizeof(u8)  != 1) return CODE_ERROR;
    if (sizeof(i16) != 2) return CODE_ERROR;
    if (sizeof(u16) != 2) return CODE_ERROR;
    if (sizeof(i32) != 4) return CODE_ERROR;
    if (sizeof(u32) != 4) return CODE_ERROR;
    if (sizeof(i64) != 8) return CODE_ERROR;
    if (sizeof(u64) != 8) return CODE_ERROR;
    if (sizeof(f32) != 4) return CODE_ERROR;
    if (sizeof(f64) != 8) return CODE_ERROR;
    return CODE_OK;
}

struct string_t {
    u64 len;
    char* ptr;
};


#endif /* STD_X86_64 */