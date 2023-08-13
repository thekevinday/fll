#include "mock-directory.h"

#ifdef __cplusplus
extern "C" {
#endif

int mock_unwrap = 0;

f_status_t __wrap_f_string_dynamic_adjust(const f_number_unsigned_t length, f_string_dynamic_t * const structure) {

  if (mock_unwrap) {
    return __real_f_string_dynamic_adjust(length, structure);
  }

  if (!structure) return F_status_set_error(F_parameter_not);

  const bool failure = mock_type(bool);

  if (failure) return mock_type(f_status_t);

  structure->size = length;

  return mock_type(f_status_t);
}

f_status_t __wrap_f_string_dynamic_resize(const f_number_unsigned_t length, f_string_dynamic_t * const structure) {

  if (mock_unwrap) {
    return __real_f_string_dynamic_resize(length, structure);
  }

  if (!structure) return F_status_set_error(F_parameter_not);

  const bool failure = mock_type(bool);

  if (failure) return mock_type(f_status_t);

  structure->size = length;

  return mock_type(f_status_t);
}

f_status_t __wrap_f_string_dynamics_adjust(const f_number_unsigned_t length, f_string_dynamics_t * const structure) {

  if (mock_unwrap) {
    return __real_f_string_dynamics_adjust(length, structure);
  }

  if (!structure) return F_status_set_error(F_parameter_not);

  const bool failure = mock_type(bool);

  if (failure) return mock_type(f_status_t);

  structure->size = length;

  return mock_type(f_status_t);
}

f_status_t __wrap_f_string_dynamics_resize(const f_number_unsigned_t length, f_string_dynamics_t * const structure) {

  if (mock_unwrap) {
    return __real_f_string_dynamics_resize(length, structure);
  }

  if (!structure) return F_status_set_error(F_parameter_not);

  const bool failure = mock_type(bool);

  if (failure) return mock_type(f_status_t);

  structure->size = length;

  return mock_type(f_status_t);
}

int __wrap_alphasort(const struct dirent **a, const struct dirent **b) {

  const bool failure = mock_type(bool);

  if (failure) {
    errno = mock_type(int);

    return -1;
  }

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

int __wrap_nftw(const char *dirpath, int (*fn) (const char *fpath, const struct stat *sb, int typeflag, struct FTW *ftwbuf), int nopenfd, int flags) {

  const bool failure = mock_type(bool);

  if (failure) {
    errno = mock_type(int);

    return -1;
  }

  return mock_type(int);
}

int __wrap_open(const char *pathname, int flags) {

  const bool failure = mock_type(bool);

  if (failure) {
    errno = mock_type(int);

    return -1;
  }

  return mock_type(int);
}

int __wrap_openat(int dirfd, const char *pathname, int flags) {

  const bool failure = mock_type(bool);

  if (failure) {
    errno = mock_type(int);

    return -1;
  }

  return mock_type(int);
}

int __wrap_remove(const char *pathname) {

  const bool failure = mock_type(bool);

  if (failure) {
    errno = mock_type(int);

    return -1;
  }

  return mock_type(int);
}

int __wrap_scandir(const char *dirp, struct dirent ***namelist, int (*filter)(const struct dirent *), int (*compar)(const struct dirent **, const struct dirent **)) {

  const bool failure = mock_type(bool);

  if (failure) {
    errno = mock_type(int);

    return -1;
  }

  *namelist = mock_type(struct dirent **);

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

int __wrap_utimensat(int dirfd, const char *pathname, const struct timespec times[2], int flags) {

  const bool failure = mock_type(bool);

  if (failure) {
    errno = mock_type(int);

    return -1;
  }

  return mock_type(int);
}

int __wrap_versionsort(const struct dirent **a, const struct dirent **b) {

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
