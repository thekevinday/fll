/**
 * FLL - Level 0
 *
 * Project: Path
 * API Version: 0.7
 * Licenses: lgpl-2.1-or-later
 *
 * Test the path project.
 */
#ifndef _MOCK__path_h
#define _MOCK__path_h

// Libc includes.
#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <stdint.h>

// cmocka includes.
#include <cmocka.h>

// FLL-0 includes.
#include <fll/level_0/path.h>

#ifdef __cplusplus
extern "C" {
#endif

const static int mock_errno_generic = 32767;

extern int __wrap_chdir(const char *path);
extern int __wrap_fchdir(int fd);
extern char *__wrap_getcwd(char *buf, size_t size);
extern char *__wrap_realpath(const char *path, char *resolved_path);

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _MOCK__path_h
