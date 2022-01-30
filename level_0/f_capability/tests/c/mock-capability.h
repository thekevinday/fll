/**
 * FLL - Level 0
 *
 * Project: Capability
 * API Version: 0.5
 * Licenses: lgpl-2.1-or-later
 *
 * Test the capability project.
 */
#ifndef _MOCK__capability_h
#define _MOCK__capability_h

// Libc includes.
#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <stdint.h>

// cmocka includes.
#include <cmocka.h>

// FLL-0 includes.
#include <fll/level_0/capability.h>

#ifdef __cplusplus
extern "C" {
#endif

const static int mock_errno_generic = 32767;

extern int __wrap_cap_get_ambient(cap_value_t value);
extern int __wrap_cap_clear(cap_t capability);
extern int __wrap_cap_clear_flag(cap_t capability, cap_flag_value_t flag_value);
extern int __wrap_cap_compare(cap_t capability_1, cap_t capability_2);
extern ssize_t __wrap_cap_copy_ext(void *data, cap_t capability, ssize_t size);
extern cap_t __wrap_cap_copy_int(void *data);
extern int __wrap_cap_drop_bound(cap_value_t value);
extern cap_t __wrap_cap_dup(cap_t capability);
extern int __wrap_cap_free(void *pointer);
extern int __wrap_cap_from_name(const char *name, cap_value_t *value);
extern cap_t __wrap_cap_from_text(const char *text);
extern int __wrap_cap_get_bound(cap_value_t value);
extern cap_t __wrap_cap_get_fd(int descriptor);
extern cap_t __wrap_cap_get_file(const char *path);
extern int __wrap_cap_get_flag(cap_t capability, cap_value_t value, cap_flag_t flag, cap_flag_value_t *flag_value);
extern cap_mode_t __wrap_cap_get_mode(void);
extern uid_t __wrap_cap_get_nsowner(cap_t capability);
extern cap_t __wrap_cap_init(void);
extern const char *__wrap_cap_mode_name(cap_mode_t mode);
extern cap_t __wrap_cap_get_pid(pid_t pid);
extern cap_t __wrap_cap_get_proc(void);
extern unsigned __wrap_cap_get_secbits(void);
extern int __wrap_cap_reset_ambient(void);
extern int __wrap_cap_set_ambient(cap_value_t value, cap_flag_value_t flag_value);
extern int __wrap_cap_set_fd(int descriptor, cap_t capability);
extern int __wrap_cap_set_file(const char *path, cap_t capability);
extern int __wrap_cap_set_flag(cap_t capability, cap_flag_t flag, int number, const cap_value_t *value, cap_flag_value_t flag_value);
extern int __wrap_cap_set_mode(cap_mode_t mode);
extern int __wrap_cap_set_nsowner(cap_t capability, uid_t id);
extern int __wrap_cap_set_proc(cap_t capability);
extern int __wrap_cap_set_secbits(unsigned bits);
extern int __wrap_cap_setgroups(gid_t gid, size_t total, const gid_t groups[]);
extern int __wrap_cap_setuid(uid_t uid);
extern ssize_t __wrap_cap_size(cap_t capability);
extern char * __wrap_cap_to_text(cap_t capability, ssize_t *size);
extern char * __wrap_cap_to_name(cap_value_t value);

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _MOCK__capability_h
