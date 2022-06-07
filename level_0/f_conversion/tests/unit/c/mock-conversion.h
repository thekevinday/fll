/**
 * FLL - Level 0
 *
 * Project: Conversion
 * API Version: 0.5
 * Licenses: lgpl-2.1-or-later
 *
 * Test the conversion project.
 */
#ifndef _MOCK__conversion_h
#define _MOCK__conversion_h

// Libc includes.
#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <stdint.h>

// cmocka includes.
#include <cmocka.h>

// FLL-0 includes.
#include <fll/level_0/conversion.h>

#ifdef __cplusplus
extern "C" {
#endif

const static int mock_errno_generic = 32767;

extern int __wrap_ferror_unlocked(FILE *stream);
extern size_t __wrap_fwrite_unlocked(const void * const ptr, size_t size, size_t nmemb, FILE *stream);

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _MOCK__conversion_h
