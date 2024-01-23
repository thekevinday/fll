/**
 * FLL - Level 0
 *
 * Project: Random
 * API Version: 0.7
 * Licenses: lgpl-2.1-or-later
 *
 * Test the random project.
 */
#ifndef _MOCK__random_h
#define _MOCK__random_h

// Libc includes.
#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <stdint.h>

// cmocka includes.
#include <cmocka.h>

// FLL-0 includes.
#include <fll/level_0/random.h>

#ifdef __cplusplus
extern "C" {
#endif

const static int mock_errno_generic = 32767;

extern ssize_t __wrap_getrandom(void *buf, size_t buflen, unsigned int flags);
extern long __wrap_random(void);
extern void __wrap_srandom(unsigned seed);

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _MOCK__random_h