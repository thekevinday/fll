/**
 * FLL - Level 0
 *
 * Project: FSS
 * API Version: 0.6
 * Licenses: lgpl-2.1-or-later
 *
 * Test the fss project.
 */
#ifndef _MOCK__fss_h
#define _MOCK__fss_h

// Libc includes.
#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <stdint.h>

// cmocka includes.
#include <cmocka.h>

// FLL-0 includes.
#include <fll/level_0/fss.h>

#ifdef __cplusplus
extern "C" {
#endif

const static int mock_errno_generic = 32767;

//extern long __wrap_sysconf(int name);

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _MOCK__fss_h
