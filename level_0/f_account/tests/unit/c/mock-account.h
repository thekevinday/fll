/**
 * FLL - Level 0
 *
 * Project: Account
 * API Version: 0.5
 * Licenses: lgpl-2.1-or-later
 *
 * Test the account project.
 */
#ifndef _MOCK__account_h
#define _MOCK__account_h

// Libc includes.
#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <stdint.h>

// cmocka includes.
#include <cmocka.h>

// FLL-0 includes.
#include <fll/level_0/account.h>

#ifdef __cplusplus
extern "C" {
#endif

const static int mock_errno_generic = 32767;

extern int __wrap_getpwnam_r(const char * const name, struct passwd *pwd, char *buf, size_t buflen, struct passwd **result);
extern int __wrap_getpwuid_r(uid_t uid, struct passwd *pwd, char *buf, size_t buflen, struct passwd **result);
extern int __wrap_getgrgid_r(uid_t uid, struct group *grp, char *buf, size_t buflen, struct group **result);
extern int __wrap_getgrnam_r(const char * const name, struct group *grp, char *buf, size_t buflen, struct group **result);
extern long __wrap_sysconf(int name);

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _MOCK__account_h
