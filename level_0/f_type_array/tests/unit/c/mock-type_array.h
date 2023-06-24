/**
 * FLL - Level 0
 *
 * Project: Type
 * API Version: 0.7
 * Licenses: lgpl-2.1-or-later
 *
 * Test the type_array project.
 */
#ifndef _MOCK__type_array_h
#define _MOCK__type_array_h

// Libc includes.
#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <stdint.h>

// cmocka includes.
#include <cmocka.h>

// FLL-0 includes.
#include <fll/level_0/type.h>
#include <fll/level_0/type_array.h>

#ifdef __cplusplus
extern "C" {
#endif

const static int mock_errno_generic = 32767;

extern int __wrap_poll(f_poll_t *fds, nfds_t nfds, int timeout);

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _MOCK__type_array_h
