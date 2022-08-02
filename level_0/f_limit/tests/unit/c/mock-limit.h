/**
 * FLL - Level 0
 *
 * Project: Limit
 * API Version: 0.7
 * Licenses: lgpl-2.1-or-later
 *
 * Test the limit project.
 */
#ifndef _MOCK__limit_h
#define _MOCK__limit_h

// Libc includes.
#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <stdint.h>

// cmocka includes.
#include <cmocka.h>

// FLL-0 includes.
#include <fll/level_0/limit.h>

#ifdef __cplusplus
extern "C" {
#endif

const static int mock_errno_generic = 32767;

extern int __wrap_prlimit(pid_t pid, int resource, const struct rlimit *new_limit, struct rlimit *old_limit);

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _MOCK__limit_h
