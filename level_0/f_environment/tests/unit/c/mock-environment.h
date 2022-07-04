/**
 * FLL - Level 0
 *
 * Project: Environment
 * API Version: 0.6
 * Licenses: lgpl-2.1-or-later
 *
 * Test the environment project.
 */
#ifndef _MOCK__environment_h
#define _MOCK__environment_h

// Libc includes.
#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <stdint.h>

#ifndef _di_libcap_
  #include <sys/capability.h>
#endif // _di_libcap_

// cmocka includes.
#include <cmocka.h>

// FLL-0 includes.
#include <fll/level_0/environment.h>

#ifdef __cplusplus
extern "C" {
#endif

const static int mock_errno_generic = 32767;

#ifndef _di_libcap_
  extern int __wrap_cap_free(void *obj_d);
  extern int __wrap_cap_get_flag(cap_t cap_p, cap_value_t cap, cap_flag_t flag, cap_flag_value_t *value_p);
  extern cap_t __wrap_cap_get_proc(void);
  extern int __wrap_cap_set_proc(cap_t cap_p);
#endif // _di_libcap_

extern int __wrap_clearenv(void);
extern int __wrap_getegid(void);
extern char *__wrap_getenv(const char *name);
extern int __wrap_geteuid(void);
extern int __wrap_getgid(void);
extern int __wrap_getuid(void);
extern int __wrap_setenv(const char *name, const char *value, int overwrite);
extern int __wrap_unsetenv(const char *name);

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _MOCK__environment_h
