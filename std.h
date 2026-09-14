#ifndef STD_H
#define STD_H

#ifdef STD_IMPLEMENTATION
#define STD_COMMON_IMPLEMENTATION
#endif
#include "std.common.h"

#ifdef STD_IMPLEMENTATION
#define STD_LINUX_IMPLEMENTATION
#endif
#include "std.linux.h"

#endif /* STD_H */