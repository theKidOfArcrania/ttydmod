#ifndef PLACEHOLDER_H
#define PLACEHOLDER_H

#include <platform.h>

#include <m2c_macros.h> // IWYU pragma: export

/// A label in a jump table
typedef void (*jmp_t)(void);

/// A jump table
typedef jmp_t jtbl_t[];

#if defined(__clang__) || defined(__GNUC__)
#include <dolphin/os/OSError.h>
#define NOT_IMPLEMENTED                                                       \
    OSPanic(__FILE__, __LINE__, "%s is not implemented!", __func__)
#elif defined(__MWERKS__) && !defined(BUGFIX)
#define NOT_IMPLEMENTED asm { nop }
#else
#include <dolphin/OSError.h>
#define NOT_IMPLEMENTED
OSPanic(__FILE__, __LINE__, "Function is not implemented!")
#endif

#ifndef UNK_T
#ifdef M2CTX
#define UNK_T M2C_UNK
#else
#define UNK_T void*
#endif
#endif

#ifndef UNK_RET
#ifdef M2CTX
#define UNK_RET M2C_UNK
#else
#define UNK_RET void
#endif
#endif

#ifndef UNK_PARAMS
#ifdef M2CTX
#define UNK_PARAMS
#else
#define UNK_PARAMS void
#endif
#endif

#ifndef UNK_SIZE_ARRAY
#if defined(__MWERKS__) && !defined(M2CTX)
#define UNK_SIZE_ARRAY []
#else
#define UNK_SIZE_ARRAY [0]
#endif
#endif

#define U32_TO_F32 4503599627370496.0
#define S32_TO_F32 4503601774854144.0

#ifdef MWERKS_GEKKO
#define ASM asm
#else
#define ASM
#endif

#ifndef UNUSED
#if defined(__clang__) || defined(__GNUC__)
#define UNUSED __attribute__((unused))
#else
#define UNUSED
#endif
#endif
#define UNUSED_PARAM(x) ((void)x)

// For if we want to convert a var-arg and append to some function-like call
#if defined(__clang__) || defined(__GNUC__)
#define __VA_ARGS_FIX__(...) __VA_OPT__(,) __VA_ARGS__
#elif defined(__MWERKS__)
// mwcc *annoyingly* requires all var-arg macros to have a trailing comma if you
// want to pass a no-arg version, which is obviously trouble if we don't want
// that comma for further calls. We fix that by emulating a __VA_OPT__ of sorts
// but it's nasty because we have to do a lot of C macro voodoo
//
// See: http://jhnet.co.uk/articles/cpp_magic
#define __FIRST(a, ...) a
#define __SECOND(a, b, ...) b
#define __IS_PROBE(...) __SECOND(__VA_ARGS__, 0,)
#define __PROBE() ~, 1
#define __CAT(a, b) a ## b
#define __CAT2(a, b) __CAT(a, b)
#define __NOT(x) __IS_PROBE(__CAT(__NOT_, x))
#define __NOT_0 __PROBE()
#define __BOOL__(a) __NOT(__NOT(a))

#define __IS_EMPTY_HELPER() 0
#define __IS_FIRST_EMPTY__(a, ...) __NOT(__BOOL__(__FIRST(__IS_EMPTY_HELPER a (),)))

#define __VA_ARGS_FIX__(...) __CAT2(__VA_ARGS_FIX__, __IS_FIRST_EMPTY__(__VA_ARGS__,)) __VA_ARGS__
#define __VA_ARGS_FIX__0 ,
#define __VA_ARGS_FIX__1
#endif

#define PAD_STACK(bytes)                                                      \
    do {                                                                      \
        UNUSED unsigned char _[(bytes)];                                      \
    } while (0)

/// @warning Creates fake @c .rodata entries!
#define FORCE_PAD_STACK(bytes)                                                \
    do {                                                                      \
        UNUSED unsigned char _[(bytes)] = { 0 };                              \
    } while (0)

#define FORCE_PAD_STACK_8                                                     \
    do {                                                                      \
        UNUSED u64 _0 = 0;                                                    \
    } while (0)

#define FORCE_PAD_STACK_16                                                    \
    do {                                                                      \
        UNUSED u64 _0 = 0, _1 = 0;                                            \
    } while (0)

#define FORCE_PAD_STACK_32                                                    \
    do {                                                                      \
        UNUSED u64 _0 = 0, _1 = 0, _2 = 0, _3 = 0;                            \
    } while (0)
#endif
