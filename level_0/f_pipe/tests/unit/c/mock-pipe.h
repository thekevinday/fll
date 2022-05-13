/**
 * FLL - Level 0
 *
 * Project: Path
 * API Version: 0.5
 * Licenses: lgpl-2.1-or-later
 *
 * Test the pipe project.
 */
#ifndef _MOCK__pipe_h
#define _MOCK__pipe_h

// Libc includes.
#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <stdint.h>

// cmocka includes.
#include <cmocka.h>

// FLL-0 includes.
#include <fll/level_0/pipe.h>

#ifdef __cplusplus
extern "C" {
#endif

const static int mock_errno_generic = 32767;

extern int __wrap_fstat(int fd, struct stat *statbuf);

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _MOCK__pipe_h
