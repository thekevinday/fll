/**
 * FLL - Level 0
 *
 * Project: Directory
 * API Version: 0.5
 * Licenses: lgpl-2.1-or-later
 *
 * Test the directory project.
 */
#ifndef _MOCK__directory_h
#define _MOCK__directory_h

// Libc includes.
#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <stdint.h>

// cmocka includes.
#include <cmocka.h>

// FLL-0 includes.
#include <fll/level_0/directory.h>

#ifdef __cplusplus
extern "C" {
#endif

const static int mock_errno_generic = 32767;

extern int __wrap_alphasort(const struct dirent **a, const struct dirent **b);
extern int __wrap_fstatat(int dirfd, const char *pathname, struct stat *statbuf, int flags);
extern int __wrap_mkdir(const char *pathname, mode_t mode);
extern int __wrap_mkdirat(int dirfd, const char *pathname, mode_t mode);
extern int __wrap_nftw(const char *dirpath, int (*fn) (const char *fpath, const struct stat *sb, int typeflag, struct FTW *ftwbuf), int nopenfd, int flags);
extern int __wrap_open(const char *pathname, int flags);
extern int __wrap_openat(int dirfd, const char *pathname, int flags);
extern int __wrap_remove(const char *pathname);
extern int __wrap_scandir(const char *dirp, struct dirent ***namelist, int (*filter)(const struct dirent *), int (*compar)(const struct dirent **, const struct dirent **));
extern int __wrap_stat(const char *pathname, struct stat *statbuf);
extern int __wrap_strncmp(const char *s1, const char *s2, size_t n);
extern size_t __wrap_strnlen(const char *s, size_t maxlen);
extern int __wrap_utimensat(int dirfd, const char *pathname, const struct timespec times[2], int flags);
extern int __wrap_versionsort(const struct dirent **a, const struct dirent **b);

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _MOCK__directory_h
