/**
 * FLL - Level 0
 *
 * Project: File
 * API Version: 0.5
 * Licenses: lgpl-2.1-or-later
 *
 * Test the file project.
 */
#ifndef _MOCK__file_h
#define _MOCK__file_h

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

extern int __wrap_access(const char *pathname, int mode);
extern int __wrap_chmod(const char *pathname, mode_t mode);
extern int __wrap_chown(const char *pathname, uid_t owner, gid_t group);
extern int __wrap_close(int fd);
extern int __wrap_faccessat(int dirfd, const char *pathname, int mode, int flags);
extern int __wrap_fchmod(const char *pathname, mode_t mode);
extern int __wrap_fchmodat(int dirfd, const char *pathname, mode_t mode, int flags);
extern int __wrap_fchown(int fd, uid_t owner, gid_t group);
extern int __wrap_fchownat(int dirfd, const char *pathname, uid_t owner, gid_t group, int flags);
extern int __wrap_fclose(FILE *stream);
extern FILE *__wrap_fopen(const char *pathname, const char *mode);
extern FILE *__wrap_fdopen(int fd, const char *mode);
extern FILE *__wrap_freopen(const char *pathname, const char *mode, FILE *stream);
extern int __wrap_feof_unlocked(FILE *stream);
extern int __wrap_ferror_unlocked(FILE *stream);
extern int __wrap_fflush(FILE *stream);
extern int __wrap_fileno(FILE *stream);
extern void __wrap_flockfile(FILE *filehandle);
extern size_t __wrap_fread_unlocked(void *ptr, size_t size, size_t nmemb, FILE *stream);
extern int __wrap_fstat(int fd, struct stat *statbuf);
extern int __wrap_fstatat(int dirfd, const char *pathname, struct stat *statbuf, int flags);
extern int __wrap_fsync(int fd);
extern void __wrap_funlockfile(FILE *filehandle);
extern size_t __wrap_fwrite_unlocked(const void *ptr, size_t size, size_t nmemb, FILE *stream);
extern int __wrap_lchown(const char *pathname, uid_t owner, gid_t group);
extern int __wrap_link(const char *oldpath, const char *newpath);
extern int __wrap_linkat(const char *oldpath, const char *newpath);
extern off_t __wrap_lseek(int fd, off_t offset, int whence);
extern int __wrap_lstat(const char *pathname, struct stat *statbuf);
extern int __wrap_mkdir(const char *pathname, mode_t mode);
extern int __wrap_mkdirat(int dirfd, const char *pathname, mode_t mode);
extern int __wrap_mkfifo(const char *pathname, mode_t mode);
extern int __wrap_mkfifoat(int dirfd, const char *pathname, mode_t mode);
extern int __wrap_mknod(const char *pathname, mode_t mode, dev_t dev);
extern int __wrap_mknodat(int dirfd, const char *pathname, mode_t mode, dev_t dev);
extern int __wrap_open(const char *pathname, int flags, mode_t mode);
extern int __wrap_openat(int dirfd, const char *pathname, int flags, mode_t mode);
extern ssize_t __wrap_read(int fd, void *buf, size_t count);
extern ssize_t __wrap_readlink(const char *pathname, char *buf, size_t bufsiz);
extern ssize_t __wrap_readlinkat(int dirfd, const char *pathname, char *buf, size_t bufsiz);
extern int __wrap_rename(const char *oldpath, const char *newpath);
extern int __wrap_renameat(int olddirfd, const char *oldpath, int newdirfd, const char *newpath);
extern int __wrap_renameat2(int olddirfd, const char *oldpath, int newdirfd, const char *newpath, unsigned int flags);
extern int __wrap_stat(const char *pathname, struct stat *statbuf);
extern int __wrap_symlink(const char *target, const char *linkpath);
extern int __wrap_symlinkat(const char *target, int newdirfd, const char *linkpath);
extern int __wrap_unlink(const char *pathname);
extern int __wrap_unlinkat(int dirfd, const char *pathname, int flags);
extern mode_t __wrap_umask(mode_t mask);
extern int __wrap_utimensat(int dirfd, const char *pathname, const struct timespec times[2], int flags);
extern ssize_t __wrap_write(int fd, const void *buf, size_t count);

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _MOCK__file_h
