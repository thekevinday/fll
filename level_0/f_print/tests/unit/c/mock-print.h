/**
 * FLL - Level 0
 *
 * Project: Print
 * API Version: 0.5
 * Licenses: lgpl-2.1-or-later
 *
 * Test the print project.
 */
#ifndef _MOCK__print_h
#define _MOCK__print_h

// Libc includes.
#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <stdint.h>

// cmocka includes.
#include <cmocka.h>

// FLL-0 includes.
#include <fll/level_0/print.h>

#ifdef __cplusplus
extern "C" {
#endif

const static int mock_errno_generic = 32767;

extern void __wrap_clearerr_unlocked(FILE *stream);
extern int __wrap_ferror_unlocked(FILE *stream);
extern size_t __wrap_fwrite_unlocked(const void *ptr, size_t size, size_t nmemb, FILE *stream);
extern ssize_t __wrap_write(int fd, const void *buf, size_t count);

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _MOCK__print_h
