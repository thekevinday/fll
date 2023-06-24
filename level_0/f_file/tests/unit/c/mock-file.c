#include "mock-file.h"

#ifdef __cplusplus
extern "C" {
#endif

int __wrap_access(const char *pathname, int mode) {

  const bool failure = mock_type(bool);

  if (failure) {
    errno = mock_type(int);

    return -1;
  }

  return mock_type(int);
}

int __wrap_chmod(const char *pathname, mode_t mode) {

  const bool failure = mock_type(bool);

  if (failure) {
    errno = mock_type(int);

    return -1;
  }

  return mock_type(int);
}

int __wrap_chown(const char *pathname, uid_t owner, gid_t group) {

  const bool failure = mock_type(bool);

  if (failure) {
    errno = mock_type(int);

    return -1;
  }

  return mock_type(int);
}

int __wrap_close(int fd) {

  const bool failure = mock_type(bool);

  if (failure) {
    errno = mock_type(int);

    return -1;
  }

  return mock_type(int);
}

int __wrap_faccessat(int dirfd, const char *pathname, int mode, int flags) {

  const bool failure = mock_type(bool);

  if (failure) {
    errno = mock_type(int);

    return -1;
  }

  return mock_type(int);
}

int __wrap_fchmod(const char *pathname, mode_t mode) {

  const bool failure = mock_type(bool);

  if (failure) {
    errno = mock_type(int);

    return -1;
  }

  return mock_type(int);
}

int __wrap_fchmodat(int dirfd, const char *pathname, mode_t mode, int flags) {

  const bool failure = mock_type(bool);

  if (failure) {
    errno = mock_type(int);

    return -1;
  }

  return mock_type(int);
}

int __wrap_fchown(int fd, uid_t owner, gid_t group) {

  const bool failure = mock_type(bool);

  if (failure) {
    errno = mock_type(int);

    return -1;
  }

  return mock_type(int);
}

int __wrap_fchownat(int dirfd, const char *pathname, uid_t owner, gid_t group, int flags) {

  const bool failure = mock_type(bool);

  if (failure) {
    errno = mock_type(int);

    return -1;
  }

  return mock_type(int);
}

int __wrap_fclose(FILE *stream) {

  const bool failure = mock_type(bool);

  if (failure) {
    errno = mock_type(int);

    return EOF;
  }

  return mock_type(int);
}

FILE *__wrap_fopen(const char *pathname, const char *mode) {

  const bool failure = mock_type(bool);

  if (failure) {
    errno = mock_type(int);

    return 0;
  }

  return mock_type(FILE *);
}

FILE *__wrap_fdopen(int fd, const char *mode) {

  const bool failure = mock_type(bool);

  if (failure) {
    errno = mock_type(int);

    return 0;
  }

  return mock_type(FILE *);
}

FILE *__wrap_freopen(const char *pathname, const char *mode, FILE *stream) {

  const bool failure = mock_type(bool);

  if (failure) {
    errno = mock_type(int);

    return 0;
  }

  return mock_type(FILE *);
}

int __wrap_feof_unlocked(FILE *stream) {

  return mock_type(int);
}

int __wrap_ferror_unlocked(FILE *stream) {

  return mock_type(int);
}

int __wrap_fflush(FILE *stream) {

  const bool failure = mock_type(bool);

  if (failure) {
    errno = mock_type(int);

    return EOF;
  }

  return mock_type(int);
}

int __wrap_fileno(FILE *stream) {

  return mock_type(int);
}

void __wrap_flockfile(FILE *filehandle) {

}

int __wrap_fcntl(int fd, int cmd, ...) {

  const bool failure = mock_type(bool);

  if (failure) {
    errno = mock_type(int);

    return -1;
  }

  return 0;
}

size_t __wrap_fread_unlocked(void *ptr, size_t size, size_t nmemb, FILE *stream) {

  return mock_type(int);
}

int __wrap_fstat(int fd, struct stat *statbuf) {

  const bool failure = mock_type(bool);

  if (failure) {
    errno = mock_type(int);

    return -1;
  }

  struct stat * const mocked_stat = mock_type(struct stat *);

  statbuf->st_dev = mocked_stat->st_dev;
  statbuf->st_ino = mocked_stat->st_ino;
  statbuf->st_mode = mocked_stat->st_mode;
  statbuf->st_nlink = mocked_stat->st_nlink;
  statbuf->st_uid = mocked_stat->st_uid;
  statbuf->st_gid = mocked_stat->st_gid;
  statbuf->st_rdev = mocked_stat->st_rdev;
  statbuf->st_size = mocked_stat->st_size;
  statbuf->st_blksize = mocked_stat->st_blksize;
  statbuf->st_blocks = mocked_stat->st_blocks;
  statbuf->st_atime = mocked_stat->st_atime;
  statbuf->st_mtime = mocked_stat->st_mtime;
  statbuf->st_ctime = mocked_stat->st_ctime;

  return mock_type(int);
}

int __wrap_fstatat(int dirfd, const char *pathname, struct stat *statbuf, int flags) {

  const bool failure = mock_type(bool);

  if (failure) {
    errno = mock_type(int);

    return -1;
  }

  struct stat * const mocked_stat = mock_type(struct stat *);

  statbuf->st_dev = mocked_stat->st_dev;
  statbuf->st_ino = mocked_stat->st_ino;
  statbuf->st_mode = mocked_stat->st_mode;
  statbuf->st_nlink = mocked_stat->st_nlink;
  statbuf->st_uid = mocked_stat->st_uid;
  statbuf->st_gid = mocked_stat->st_gid;
  statbuf->st_rdev = mocked_stat->st_rdev;
  statbuf->st_size = mocked_stat->st_size;
  statbuf->st_blksize = mocked_stat->st_blksize;
  statbuf->st_blocks = mocked_stat->st_blocks;
  statbuf->st_atime = mocked_stat->st_atime;
  statbuf->st_mtime = mocked_stat->st_mtime;
  statbuf->st_ctime = mocked_stat->st_ctime;

  return mock_type(int);
}

int __wrap_fsync(int fd) {

  const bool failure = mock_type(bool);

  if (failure) {
    errno = mock_type(int);

    return -1;
  }

  return mock_type(int);
}

void __wrap_funlockfile(FILE *filehandle) {

}

size_t __wrap_fwrite_unlocked(const void *ptr, size_t size, size_t nmemb, FILE *stream) {

  const bool failure = mock_type(bool);

  if (failure) {
    return mock_type(size_t);
  }

  return mock_type(size_t);
}

int __wrap_lchown(const char *pathname, uid_t owner, gid_t group) {

  const bool failure = mock_type(bool);

  if (failure) {
    errno = mock_type(int);

    return -1;
  }

  return mock_type(int);
}

int __wrap_link(const char *oldpath, const char *newpath) {

  const bool failure = mock_type(bool);

  if (failure) {
    errno = mock_type(int);

    return -1;
  }

  return mock_type(int);
}

int __wrap_linkat(const char *oldpath, const char *newpath) {

  const bool failure = mock_type(bool);

  if (failure) {
    errno = mock_type(int);

    return -1;
  }

  return mock_type(int);
}

off_t __wrap_lseek(int fd, off_t offset, int whence) {

  const bool failure = mock_type(bool);

  if (failure) {
    errno = mock_type(int);

    return -1;
  }

  return mock_type(int);
}

int __wrap_lstat(const char *pathname, struct stat *statbuf) {

  const bool failure = mock_type(bool);

  if (failure) {
    errno = mock_type(int);

    return -1;
  }

  struct stat * const mocked_stat = mock_type(struct stat *);

  statbuf->st_dev = mocked_stat->st_dev;
  statbuf->st_ino = mocked_stat->st_ino;
  statbuf->st_mode = mocked_stat->st_mode;
  statbuf->st_nlink = mocked_stat->st_nlink;
  statbuf->st_uid = mocked_stat->st_uid;
  statbuf->st_gid = mocked_stat->st_gid;
  statbuf->st_rdev = mocked_stat->st_rdev;
  statbuf->st_size = mocked_stat->st_size;
  statbuf->st_blksize = mocked_stat->st_blksize;
  statbuf->st_blocks = mocked_stat->st_blocks;
  statbuf->st_atime = mocked_stat->st_atime;
  statbuf->st_mtime = mocked_stat->st_mtime;
  statbuf->st_ctime = mocked_stat->st_ctime;

  return mock_type(int);
}

int __wrap_mkdir(const char *pathname, mode_t mode) {

  const bool failure = mock_type(bool);

  if (failure) {
    errno = mock_type(int);

    return -1;
  }

  return mock_type(int);
}

int __wrap_mkdirat(int dirfd, const char *pathname, mode_t mode) {

  const bool failure = mock_type(bool);

  if (failure) {
    errno = mock_type(int);

    return -1;
  }

  return mock_type(int);
}

int __wrap_mkfifo(const char *pathname, mode_t mode) {

  const bool failure = mock_type(bool);

  if (failure) {
    errno = mock_type(int);

    return -1;
  }

  return mock_type(int);
}

int __wrap_mkfifoat(int dirfd, const char *pathname, mode_t mode) {

  const bool failure = mock_type(bool);

  if (failure) {
    errno = mock_type(int);

    return -1;
  }

  return mock_type(int);
}

int __wrap_mknod(const char *pathname, mode_t mode, dev_t dev) {

  const bool failure = mock_type(bool);

  if (failure) {
    errno = mock_type(int);

    return -1;
  }

  return mock_type(int);
}

int __wrap_mknodat(int dirfd, const char *pathname, mode_t mode, dev_t dev) {

  const bool failure = mock_type(bool);

  if (failure) {
    errno = mock_type(int);

    return -1;
  }

  return mock_type(int);
}

int __wrap_open(const char *pathname, int flags, mode_t mode) {

  const bool failure = mock_type(bool);

  if (failure) {
    errno = mock_type(int);

    return -1;
  }

  return mock_type(int);
}

int __wrap_openat(int dirfd, const char *pathname, int flags, mode_t mode) {

  const bool failure = mock_type(bool);

  if (failure) {
    errno = mock_type(int);

    return -1;
  }

  return mock_type(int);
}

int __wrap_poll(struct pollfd *fds, nfds_t nfds, int timeout) {

  const bool failure = mock_type(bool);

  if (failure) {
    errno = mock_type(int);

    return -1;
  }

  fds->revents = mock_type(short);

  return mock_type(int);
}

ssize_t __wrap_read(int fd, void *buf, size_t count) {

  const bool failure = mock_type(bool);

  if (failure) {
    errno = mock_type(int);

    return -1;
  }

  char *buffer = mock_type(char *);
  size_t size = mock_type(size_t);

  if (size) {
    memcpy(buf, buffer, size);
  }

  return mock_type(int);
}

ssize_t __wrap_readlink(const char *pathname, char *buf, size_t bufsiz) {

  const bool failure = mock_type(bool);

  if (failure) {
    errno = mock_type(int);

    return -1;
  }

  char *buffer = mock_type(char *);

  memcpy(buf, buffer, bufsiz);

  return mock_type(int);
}

ssize_t __wrap_readlinkat(int dirfd, const char *pathname, char *buf, size_t bufsiz) {

  const bool failure = mock_type(bool);

  if (failure) {
    errno = mock_type(int);

    return -1;
  }

  char *buffer = mock_type(char *);

  memcpy(buf, buffer, bufsiz);

  return mock_type(int);
}

int __wrap_rename(const char *oldpath, const char *newpath) {

  const bool failure = mock_type(bool);

  if (failure) {
    errno = mock_type(int);

    return -1;
  }

  return mock_type(int);
}

int __wrap_renameat(int olddirfd, const char *oldpath, int newdirfd, const char *newpath) {

  const bool failure = mock_type(bool);

  if (failure) {
    errno = mock_type(int);

    return -1;
  }

  return mock_type(int);
}

int __wrap_renameat2(int olddirfd, const char *oldpath, int newdirfd, const char *newpath, unsigned int flags) {

  const bool failure = mock_type(bool);

  if (failure) {
    errno = mock_type(int);

    return -1;
  }

  return mock_type(int);
}

int __wrap_stat(const char *pathname, struct stat *statbuf) {

  const bool failure = mock_type(bool);

  if (failure) {
    errno = mock_type(int);

    return -1;
  }

  struct stat * const mocked_stat = mock_type(struct stat *);

  statbuf->st_dev = mocked_stat->st_dev;
  statbuf->st_ino = mocked_stat->st_ino;
  statbuf->st_mode = mocked_stat->st_mode;
  statbuf->st_nlink = mocked_stat->st_nlink;
  statbuf->st_uid = mocked_stat->st_uid;
  statbuf->st_gid = mocked_stat->st_gid;
  statbuf->st_rdev = mocked_stat->st_rdev;
  statbuf->st_size = mocked_stat->st_size;
  statbuf->st_blksize = mocked_stat->st_blksize;
  statbuf->st_blocks = mocked_stat->st_blocks;
  statbuf->st_atime = mocked_stat->st_atime;
  statbuf->st_mtime = mocked_stat->st_mtime;
  statbuf->st_ctime = mocked_stat->st_ctime;

  return mock_type(int);
}

int __wrap_symlink(const char *target, const char *linkpath) {

  const bool failure = mock_type(bool);

  if (failure) {
    errno = mock_type(int);

    return -1;
  }

  return mock_type(int);
}

int __wrap_symlinkat(const char *target, int newdirfd, const char *linkpath) {

  const bool failure = mock_type(bool);

  if (failure) {
    errno = mock_type(int);

    return -1;
  }

  return mock_type(int);
}

int __wrap_unlink(const char *pathname) {

  const bool failure = mock_type(bool);

  if (failure) {
    errno = mock_type(int);

    return -1;
  }

  return mock_type(int);
}

int __wrap_unlinkat(int dirfd, const char *pathname, int flags) {

  const bool failure = mock_type(bool);

  if (failure) {
    errno = mock_type(int);

    return -1;
  }

  return mock_type(int);
}

int __wrap_utimensat(int dirfd, const char *pathname, const struct timespec times[2], int flags) {

  const bool failure = mock_type(bool);

  if (failure) {
    errno = mock_type(int);

    return -1;
  }

  return mock_type(int);
}

mode_t __wrap_umask(mode_t mask) {

  return mock_type(mode_t);
}

ssize_t __wrap_write(int fd, const void *buf, size_t count) {

  const bool failure = mock_type(bool);

  if (failure) {
    errno = mock_type(int);

    return -1;
  }

  return mock_type(int);
}

#ifdef __cplusplus
} // extern "C"
#endif
