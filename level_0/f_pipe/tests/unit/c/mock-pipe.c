#include "mock-pipe.h"

#ifdef __cplusplus
extern "C" {
#endif

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

#ifdef __cplusplus
} // extern "C"
#endif
