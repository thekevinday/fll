/**
 * FLL - Level 0
 *
 * Project: Color
 * API Version: 0.5
 * Licenses: lgpl-2.1-or-later
 *
 * Test the color project.
 */
#ifndef _MOCK__color_h
#define _MOCK__color_h

// libc includes.
#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <stdint.h>

// cmocka includes.
#include <cmocka.h>

// fll-0 includes.
#include <fll/level_0/color.h>

#ifdef __cplusplus
extern "C" {
#endif

const static int mock_errno_generic = 32767;

extern char * __wrap_getenv(char *name);

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _MOCK__color_h
