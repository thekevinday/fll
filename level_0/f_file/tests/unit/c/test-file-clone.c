#include "test-file.h"
#include "test-file-clone.h"

#ifdef __cplusplus
extern "C" {
#endif

void test__f_file_clone__fails_during_read_write(void **state) {

  const f_string_static_t path = macro_f_string_static_t_initialize("test", 0, 4);

  {
    struct stat statistics;

    memset(&statistics, 0, sizeof(struct stat));

    statistics.st_mode = 1 | F_file_type_regular_d;

    f_char_t buffer[1];

    memset(buffer, 0, sizeof(f_char_t));

    will_return(__wrap_stat, false);
    will_return(__wrap_stat, &statistics);
    will_return(__wrap_stat, 0);

    will_return(__wrap_open, false);
    will_return(__wrap_open, 0);

    will_return(__wrap_fsync, false);
    will_return(__wrap_fsync, 0);

    will_return(__wrap_close, false);
    will_return(__wrap_close, 0);

    will_return(__wrap_chmod, false);
    will_return(__wrap_chmod, 0);

    will_return(__wrap_open, false);
    will_return(__wrap_open, 0);

    will_return(__wrap_open, false);
    will_return(__wrap_open, 0);

    will_return(__wrap_read, false);
    will_return(__wrap_read, buffer);
    will_return(__wrap_read, 1);
    will_return(__wrap_read, 1);

    will_return(__wrap_write, false);
    will_return(__wrap_write, 0);

    will_return(__wrap_fsync, false);
    will_return(__wrap_fsync, 0);

    will_return(__wrap_close, false);
    will_return(__wrap_close, 0);

    will_return(__wrap_fsync, false);
    will_return(__wrap_fsync, 0);

    will_return(__wrap_close, false);
    will_return(__wrap_close, 0);

    const f_status_t status = f_file_clone(path, path, 0, 0);

    assert_int_equal(F_status_set_fine(status), F_file_write);
  }
}

void test__f_file_clone__fails_for_link(void **state) {

  const f_string_static_t path = macro_f_string_static_t_initialize("test", 0, 4);

  {
    int errnos[] = {
      EACCES,
      EFBIG,
      EDQUOT,
      EEXIST,
      EFAULT,
      EINTR,
      EINVAL,
      ELOOP,
      ENAMETOOLONG,
      ENOENT,
      ENOMEM,
      ENOSPC,
      ENOTDIR,
      EOVERFLOW,
      EPERM,
      EROFS,
      ETXTBSY,
      mock_errno_generic,
    };

    f_status_t statuss[] = {
      F_access_denied,
      F_number_overflow,
      F_filesystem_quota_block,
      F_file_found,
      F_buffer,
      F_interrupt,
      F_parameter,
      F_loop,
      F_name,
      F_file_found_not,
      F_memory_not,
      F_space_not,
      F_directory_not,
      F_number_overflow,
      F_prohibited,
      F_read_only,
      F_busy,
      F_failure,
    };

    struct stat statistics;

    memset(&statistics, 0, sizeof(struct stat));

    statistics.st_mode = 1 | F_file_type_link_d;

    f_char_t buffer[1];

    memset(buffer, 0, sizeof(f_char_t));

    for (int i = 0; i < 18; ++i) {

      will_return(__wrap_stat, false);
      will_return(__wrap_stat, &statistics);
      will_return(__wrap_stat, 0);

      will_return(__wrap_symlink, true);
      will_return(__wrap_symlink, errnos[i]);

      if (statuss[i] == F_file_found) {
        will_return(__wrap_chmod, false);
        will_return(__wrap_chmod, 0);
      }

      const f_status_t status = f_file_clone(path, path, 0, 0);

      if (statuss[i] == F_file_found) {
        assert_int_equal(status, F_none);
      }
      else {
        assert_int_equal(F_status_set_fine(status), statuss[i]);
      }
    } // for
  }

  {
    int errnos[] = {
      EACCES,
      EFAULT,
      EIO,
      ELOOP,
      ENAMETOOLONG,
      ENOENT,
      ENOMEM,
      ENOTDIR,
      EPERM,
      EROFS,
      mock_errno_generic,
    };

    f_status_t statuss[] = {
      F_access_denied,
      F_buffer,
      F_input_output,
      F_loop,
      F_name,
      F_file_found_not,
      F_memory_not,
      F_directory_not,
      F_access_mode,
      F_read_only,
      F_failure,
    };

    struct stat statistics;

    memset(&statistics, 0, sizeof(struct stat));

    statistics.st_mode = 1 | F_file_type_link_d;

    f_char_t buffer[1];

    memset(buffer, 0, sizeof(f_char_t));

    for (int i = 0; i < 11; ++i) {

      will_return(__wrap_stat, false);
      will_return(__wrap_stat, &statistics);
      will_return(__wrap_stat, 0);

      will_return(__wrap_symlink, false);
      will_return(__wrap_symlink, 0);

      will_return(__wrap_chmod, true);
      will_return(__wrap_chmod, errnos[i]);

      const f_status_t status = f_file_clone(path, path, 0, 0);

      assert_int_equal(F_status_set_fine(status), statuss[i]);
    } // for
  }

  {
    int errnos[] = {
      EACCES,
      EFAULT,
      EIO,
      ELOOP,
      ENAMETOOLONG,
      ENOENT,
      ENOMEM,
      ENOTDIR,
      EPERM,
      EROFS,
      mock_errno_generic,
    };

    f_status_t statuss[] = {
      F_access_denied,
      F_buffer,
      F_input_output,
      F_loop,
      F_name,
      F_file_found_not,
      F_memory_not,
      F_directory_not,
      F_access_owner,
      F_read_only,
      F_failure,
    };

    struct stat statistics;

    memset(&statistics, 0, sizeof(struct stat));

    statistics.st_mode = 1 | F_file_type_link_d;
    statistics.st_uid = 1;
    statistics.st_gid = 1;

    f_char_t buffer[1];

    memset(buffer, 0, sizeof(f_char_t));

    for (int i = 0; i < 11; ++i) {

      will_return(__wrap_lstat, false);
      will_return(__wrap_lstat, &statistics);
      will_return(__wrap_lstat, 0);

      will_return(__wrap_symlink, false);
      will_return(__wrap_symlink, 0);

      will_return(__wrap_chmod, false);
      will_return(__wrap_chmod, 0);

      will_return(__wrap_lchown, true);
      will_return(__wrap_lchown, errnos[i]);

      const f_status_t status = f_file_clone(path, path, 0, f_file_stat_flag_reference_e | f_file_stat_flag_group_e | f_file_stat_flag_owner_e);

      assert_int_equal(F_status_set_fine(status), statuss[i]);
    } // for
  }

  {
    int errnos[] = {
      EACCES,
      EFAULT,
      EIO,
      ELOOP,
      ENAMETOOLONG,
      ENOENT,
      ENOMEM,
      ENOTDIR,
      EPERM,
      EROFS,
      mock_errno_generic,
    };

    f_status_t statuss[] = {
      F_access_denied,
      F_buffer,
      F_input_output,
      F_loop,
      F_name,
      F_file_found_not,
      F_memory_not,
      F_directory_not,
      F_access_group,
      F_read_only,
      F_failure,
    };

    struct stat statistics;

    memset(&statistics, 0, sizeof(struct stat));

    statistics.st_mode = 1 | F_file_type_link_d;
    statistics.st_uid = 1;
    statistics.st_gid = 1;

    f_char_t buffer[1];

    memset(buffer, 0, sizeof(f_char_t));

    for (int i = 0; i < 11; ++i) {

      will_return(__wrap_lstat, false);
      will_return(__wrap_lstat, &statistics);
      will_return(__wrap_lstat, 0);

      will_return(__wrap_symlink, false);
      will_return(__wrap_symlink, 0);

      will_return(__wrap_chmod, false);
      will_return(__wrap_chmod, 0);

      will_return(__wrap_lchown, false);
      will_return(__wrap_lchown, 0);

      will_return(__wrap_lchown, true);
      will_return(__wrap_lchown, errnos[i]);

      const f_status_t status = f_file_clone(path, path, 0, f_file_stat_flag_reference_e | f_file_stat_flag_group_e | f_file_stat_flag_owner_e);

      assert_int_equal(F_status_set_fine(status), statuss[i]);
    } // for
  }
}

void test__f_file_clone__fails_for_other(void **state) {

  const f_string_static_t path = macro_f_string_static_t_initialize("test", 0, 4);

  {
    int types[] = {
      F_file_type_block_d,
      F_file_type_character_d,
      F_file_type_directory_d,
      F_file_type_fifo_d,
      F_file_type_mask_d,
      F_file_type_socket_d,
    };

    struct stat statistics;

    memset(&statistics, 0, sizeof(struct stat));

    f_char_t buffer[1];

    memset(buffer, 0, sizeof(f_char_t));

    for (int i = 0; i < 6; ++i) {

      statistics.st_mode = 1 | types[i];

      will_return(__wrap_stat, false);
      will_return(__wrap_stat, &statistics);
      will_return(__wrap_stat, 0);

      const f_status_t status = f_file_clone(path, path, 0, f_file_stat_flag_exclusive_e);

      assert_int_equal(F_status_set_fine(status), F_supported_not);
    } // for
  }
}

void test__f_file_clone__fails_for_regular(void **state) {

  const f_string_static_t path = macro_f_string_static_t_initialize("test", 0, 4);

  {
    int errnos[] = {
      EACCES,
      EFAULT,
      ELOOP,
      ENAMETOOLONG,
      ENOENT,
      ENOMEM,
      ENOTDIR,
      EOVERFLOW,
      mock_errno_generic,
    };

    f_status_t statuss[] = {
      F_access_denied,
      F_buffer,
      F_loop,
      F_name,
      F_file_found_not,
      F_memory_not,
      F_directory_not,
      F_number_overflow,
      F_file_stat,
    };

    for (int i = 0; i < 9; ++i) {

      will_return(__wrap_stat, true);
      will_return(__wrap_stat, errnos[i]);

      const f_status_t status = f_file_clone(path, path, 0, 0);

      assert_int_equal(F_status_set_fine(status), statuss[i]);
    } // for
  }

  {
    int errnos[] = {
      EACCES,
      EEXIST,
      EFAULT,
      EFBIG,
      EDQUOT,
      EINTR,
      EINVAL,
      EISDIR,
      ELOOP,
      ENAMETOOLONG,
      ENFILE,
      ENOENT,
      ENOMEM,
      ENOSPC,
      ENOTDIR,
      EOPNOTSUPP,
      EOVERFLOW,
      EPERM,
      EROFS,
      ETXTBSY,
      mock_errno_generic,
    };

    f_status_t statuss[] = {
      F_access_denied,
      F_file_found,
      F_buffer,
      F_number_overflow,
      F_filesystem_quota_block,
      F_interrupt,
      F_parameter,
      F_directory,
      F_loop,
      F_name,
      F_file_open_max,
      F_file_found_not,
      F_memory_not,
      F_space_not,
      F_file_type_not_directory,
      F_supported_not,
      F_number_overflow,
      F_prohibited,
      F_read_only,
      F_busy,
      F_failure,
    };

    struct stat statistics;

    memset(&statistics, 0, sizeof(struct stat));

    statistics.st_mode = 1 | F_file_type_regular_d;

    for (int i = 0; i < 21; ++i) {

      will_return(__wrap_stat, false);
      will_return(__wrap_stat, &statistics);
      will_return(__wrap_stat, 0);

      will_return(__wrap_open, true);
      will_return(__wrap_open, errnos[i]);

      const f_status_t status = f_file_clone(path, path, 0, 0);

      assert_int_equal(F_status_set_fine(status), statuss[i]);
    } // for
  }

  {
    int errnos[] = {
      EBADF,
      EDQUOT,
      EINTR,
      EIO,
      ENOSPC,
      mock_errno_generic,
    };

    f_status_t statuss[] = {
      F_file_descriptor,
      F_filesystem_quota_block,
      F_interrupt,
      F_input_output,
      F_space_not,
      F_file_close,
    };

    struct stat statistics;

    memset(&statistics, 0, sizeof(struct stat));

    statistics.st_mode = 1 | F_file_type_regular_d;

    for (int i = 0; i < 6; ++i) {

      will_return(__wrap_stat, false);
      will_return(__wrap_stat, &statistics);
      will_return(__wrap_stat, 0);

      will_return(__wrap_open, false);
      will_return(__wrap_open, 0);

      will_return(__wrap_fsync, false);
      will_return(__wrap_fsync, 0);

      will_return(__wrap_close, true);
      will_return(__wrap_close, errnos[i]);

      const f_status_t status = f_file_clone(path, path, 0, 0);

      assert_int_equal(F_status_set_fine(status), statuss[i]);
    } // for
  }

  {
    int errnos[] = {
      EACCES,
      EFAULT,
      EIO,
      ELOOP,
      ENAMETOOLONG,
      ENOENT,
      ENOMEM,
      ENOTDIR,
      EPERM,
      EROFS,
      mock_errno_generic,
    };

    f_status_t statuss[] = {
      F_access_denied,
      F_buffer,
      F_input_output,
      F_loop,
      F_name,
      F_file_found_not,
      F_memory_not,
      F_directory_not,
      F_access_mode,
      F_read_only,
      F_failure,
    };

    struct stat statistics;

    memset(&statistics, 0, sizeof(struct stat));

    statistics.st_mode = 1 | F_file_type_regular_d;

    for (int i = 0; i < 11; ++i) {

      will_return(__wrap_stat, false);
      will_return(__wrap_stat, &statistics);
      will_return(__wrap_stat, 0);

      will_return(__wrap_open, false);
      will_return(__wrap_open, 0);

      will_return(__wrap_fsync, false);
      will_return(__wrap_fsync, 0);

      will_return(__wrap_close, false);
      will_return(__wrap_close, 0);

      will_return(__wrap_chmod, true);
      will_return(__wrap_chmod, errnos[i]);

      const f_status_t status = f_file_clone(path, path, 0, 0);

      assert_int_equal(F_status_set_fine(status), statuss[i]);
    } // for
  }

  {
    int errnos[] = {
      EACCES,
      EFAULT,
      EIO,
      ELOOP,
      ENAMETOOLONG,
      ENOENT,
      ENOMEM,
      ENOTDIR,
      EPERM,
      EROFS,
      mock_errno_generic,
    };

    f_status_t statuss[] = {
      F_access_denied,
      F_buffer,
      F_input_output,
      F_loop,
      F_name,
      F_file_found_not,
      F_memory_not,
      F_directory_not,
      F_access_owner,
      F_read_only,
      F_failure,
    };

    struct stat statistics;

    memset(&statistics, 0, sizeof(struct stat));

    statistics.st_mode = 1 | F_file_type_regular_d;

    for (int i = 0; i < 11; ++i) {

      will_return(__wrap_lstat, false);
      will_return(__wrap_lstat, &statistics);
      will_return(__wrap_lstat, 0);

      will_return(__wrap_open, false);
      will_return(__wrap_open, 0);

      will_return(__wrap_fsync, false);
      will_return(__wrap_fsync, 0);

      will_return(__wrap_close, false);
      will_return(__wrap_close, 0);

      will_return(__wrap_chmod, false);
      will_return(__wrap_chmod, 0);

      will_return(__wrap_lchown, true);
      will_return(__wrap_lchown, errnos[i]);

      const f_status_t status = f_file_clone(path, path, 0, f_file_stat_flag_reference_e | f_file_stat_flag_owner_e | f_file_stat_flag_group_e);

      assert_int_equal(F_status_set_fine(status), statuss[i]);
    } // for
  }

  {
    int errnos[] = {
      EACCES,
      EFAULT,
      EIO,
      ELOOP,
      ENAMETOOLONG,
      ENOENT,
      ENOMEM,
      ENOTDIR,
      EPERM,
      EROFS,
      mock_errno_generic,
    };

    f_status_t statuss[] = {
      F_access_denied,
      F_buffer,
      F_input_output,
      F_loop,
      F_name,
      F_file_found_not,
      F_memory_not,
      F_directory_not,
      F_access_group,
      F_read_only,
      F_failure,
    };

    struct stat statistics;

    memset(&statistics, 0, sizeof(struct stat));

    statistics.st_mode = 1 | F_file_type_regular_d;

    for (int i = 0; i < 11; ++i) {

      will_return(__wrap_lstat, false);
      will_return(__wrap_lstat, &statistics);
      will_return(__wrap_lstat, 0);

      will_return(__wrap_open, false);
      will_return(__wrap_open, 0);

      will_return(__wrap_fsync, false);
      will_return(__wrap_fsync, 0);

      will_return(__wrap_close, false);
      will_return(__wrap_close, 0);

      will_return(__wrap_chmod, false);
      will_return(__wrap_chmod, 0);

      will_return(__wrap_lchown, false);
      will_return(__wrap_lchown, 0);

      will_return(__wrap_lchown, true);
      will_return(__wrap_lchown, errnos[i]);

      const f_status_t status = f_file_clone(path, path, 0, f_file_stat_flag_reference_e | f_file_stat_flag_owner_e | f_file_stat_flag_group_e);

      assert_int_equal(F_status_set_fine(status), statuss[i]);
    } // for
  }

  {
    int errnos[] = {
      EACCES,
      EEXIST,
      EFAULT,
      EFBIG,
      EDQUOT,
      EINTR,
      EINVAL,
      EISDIR,
      ELOOP,
      ENAMETOOLONG,
      ENFILE,
      ENOENT,
      ENOMEM,
      ENOSPC,
      ENOTDIR,
      EOPNOTSUPP,
      EOVERFLOW,
      EPERM,
      EROFS,
      ETXTBSY,
      mock_errno_generic,
    };

    f_status_t statuss[] = {
      F_access_denied,
      F_file_found,
      F_buffer,
      F_number_overflow,
      F_filesystem_quota_block,
      F_interrupt,
      F_parameter,
      F_directory,
      F_loop,
      F_name,
      F_file_open_max,
      F_file_found_not,
      F_memory_not,
      F_space_not,
      F_file_type_not_directory,
      F_supported_not,
      F_number_overflow,
      F_prohibited,
      F_read_only,
      F_busy,
      F_failure,
    };

    struct stat statistics;

    memset(&statistics, 0, sizeof(struct stat));

    statistics.st_mode = 1 | F_file_type_regular_d;

    for (int i = 0; i < 11; ++i) {

      will_return(__wrap_stat, false);
      will_return(__wrap_stat, &statistics);
      will_return(__wrap_stat, 0);

      will_return(__wrap_open, false);
      will_return(__wrap_open, 0);

      will_return(__wrap_fsync, false);
      will_return(__wrap_fsync, 0);

      will_return(__wrap_close, false);
      will_return(__wrap_close, 0);

      will_return(__wrap_chmod, false);
      will_return(__wrap_chmod, 0);

      will_return(__wrap_open, true);
      will_return(__wrap_open, errnos[i]);

      const f_status_t status = f_file_clone(path, path, 0, 0);

      assert_int_equal(F_status_set_fine(status), statuss[i]);
    } // for
  }

  {
    int errnos[] = {
      EACCES,
      EEXIST,
      EFAULT,
      EFBIG,
      EDQUOT,
      EINTR,
      EINVAL,
      EISDIR,
      ELOOP,
      ENAMETOOLONG,
      ENFILE,
      ENOENT,
      ENOMEM,
      ENOSPC,
      ENOTDIR,
      EOPNOTSUPP,
      EOVERFLOW,
      EPERM,
      EROFS,
      ETXTBSY,
      mock_errno_generic,
    };

    f_status_t statuss[] = {
      F_access_denied,
      F_file_found,
      F_buffer,
      F_number_overflow,
      F_filesystem_quota_block,
      F_interrupt,
      F_parameter,
      F_directory,
      F_loop,
      F_name,
      F_file_open_max,
      F_file_found_not,
      F_memory_not,
      F_space_not,
      F_file_type_not_directory,
      F_supported_not,
      F_number_overflow,
      F_prohibited,
      F_read_only,
      F_busy,
      F_failure,
    };

    struct stat statistics;

    memset(&statistics, 0, sizeof(struct stat));

    statistics.st_mode = 1 | F_file_type_regular_d;

    for (int i = 0; i < 11; ++i) {

      will_return(__wrap_stat, false);
      will_return(__wrap_stat, &statistics);
      will_return(__wrap_stat, 0);

      will_return(__wrap_open, false);
      will_return(__wrap_open, 0);

      will_return(__wrap_fsync, false);
      will_return(__wrap_fsync, 0);

      will_return(__wrap_close, false);
      will_return(__wrap_close, 0);

      will_return(__wrap_chmod, false);
      will_return(__wrap_chmod, 0);

      will_return(__wrap_open, false);
      will_return(__wrap_open, 0);

      will_return(__wrap_open, true);
      will_return(__wrap_open, errnos[i]);

      // The file gets closed on failure, and any error result is ignored.
      will_return(__wrap_fsync, false);
      will_return(__wrap_fsync, 0);

      will_return(__wrap_close, false);
      will_return(__wrap_close, 0);

      const f_status_t status = f_file_clone(path, path, 0, 0);

      assert_int_equal(F_status_set_fine(status), statuss[i]);
    } // for
  }

  {
    int errnos[] = {
      EAGAIN,
      EBADF,
      EFAULT,
      EINTR,
      EINVAL,
      EIO,
      EISDIR,
      EWOULDBLOCK,
      mock_errno_generic,
    };

    f_status_t statuss[] = {
      F_file_read,
      F_file_read,
      F_file_read,
      F_file_read,
      F_file_read,
      F_file_read,
      F_file_read,
      F_file_read,
      F_file_read,
    };

    struct stat statistics;

    memset(&statistics, 0, sizeof(struct stat));

    statistics.st_mode = 1 | F_file_type_regular_d;

    f_char_t buffer[1];

    memset(buffer, 0, sizeof(f_char_t));

    for (int i = 0; i < 9; ++i) {

      will_return(__wrap_stat, false);
      will_return(__wrap_stat, &statistics);
      will_return(__wrap_stat, 0);

      will_return(__wrap_open, false);
      will_return(__wrap_open, 0);

      will_return(__wrap_fsync, false);
      will_return(__wrap_fsync, 0);

      will_return(__wrap_close, false);
      will_return(__wrap_close, 0);

      will_return(__wrap_chmod, false);
      will_return(__wrap_chmod, 0);

      will_return(__wrap_open, false);
      will_return(__wrap_open, 0);

      will_return(__wrap_open, false);
      will_return(__wrap_open, 0);

      will_return(__wrap_read, true);
      will_return(__wrap_read, errnos[i]);

      // The file gets closed on failure, and any error result is ignored (for both source and destination files).
      will_return(__wrap_fsync, false);
      will_return(__wrap_fsync, 0);

      will_return(__wrap_close, false);
      will_return(__wrap_close, 0);

      will_return(__wrap_fsync, false);
      will_return(__wrap_fsync, 0);

      will_return(__wrap_close, false);
      will_return(__wrap_close, 0);

      const f_status_t status = f_file_clone(path, path, 0, 0);

      assert_int_equal(F_status_set_fine(status), statuss[i]);
    } // for
  }

  {
    int errnos[] = {
      EAGAIN,
      EBADF,
      EDESTADDRREQ,
      EDQUOT,
      EFAULT,
      EFBIG,
      EINTR,
      EINVAL,
      EIO,
      ENOSPC,
      EPERM,
      EPIPE,
      EWOULDBLOCK,
      mock_errno_generic,
    };

    f_status_t statuss[] = {
      F_file_write,
      F_file_write,
      F_file_write,
      F_file_write,
      F_file_write,
      F_file_write,
      F_file_write,
      F_file_write,
      F_file_write,
      F_file_write,
      F_file_write,
      F_file_write,
      F_file_write,
      F_file_write,
    };

    struct stat statistics;

    memset(&statistics, 0, sizeof(struct stat));

    statistics.st_mode = 1 | F_file_type_regular_d;

    f_char_t buffer[1];

    memset(buffer, 0, sizeof(f_char_t));

    for (int i = 0; i < 14; ++i) {

      will_return(__wrap_stat, false);
      will_return(__wrap_stat, &statistics);
      will_return(__wrap_stat, 0);

      will_return(__wrap_open, false);
      will_return(__wrap_open, 0);

      will_return(__wrap_fsync, false);
      will_return(__wrap_fsync, 0);

      will_return(__wrap_close, false);
      will_return(__wrap_close, 0);

      will_return(__wrap_chmod, false);
      will_return(__wrap_chmod, 0);

      will_return(__wrap_open, false);
      will_return(__wrap_open, 0);

      will_return(__wrap_open, false);
      will_return(__wrap_open, 0);

      will_return(__wrap_read, false);
      will_return(__wrap_read, buffer);
      will_return(__wrap_read, 1);
      will_return(__wrap_read, 1);

      will_return(__wrap_write, true);
      will_return(__wrap_write, errnos[i]);

      // The file gets closed on failure, and any error result is ignored (for both source and destination files).
      will_return(__wrap_fsync, false);
      will_return(__wrap_fsync, 0);

      will_return(__wrap_close, false);
      will_return(__wrap_close, 0);

      will_return(__wrap_fsync, false);
      will_return(__wrap_fsync, 0);

      will_return(__wrap_close, false);
      will_return(__wrap_close, 0);

      const f_status_t status = f_file_clone(path, path, 0, f_file_stat_flag_exclusive_e);

      assert_int_equal(F_status_set_fine(status), statuss[i]);
    } // for
  }
}

void test__f_file_clone__returns_data_not(void **state) {

  const f_string_static_t path = macro_f_string_static_t_initialize("test", 0, 4);

  {
    const f_status_t status = f_file_clone(f_string_empty_s, f_string_empty_s, 0, 0);

    assert_int_equal(status, F_data_not);
  }

  {
    const f_status_t status = f_file_clone(path, f_string_empty_s, 0, 0);

    assert_int_equal(status, F_data_not);
  }

  {
    const f_status_t status = f_file_clone(f_string_empty_s, path, 0, 0);

    assert_int_equal(status, F_data_not);
  }
}

void test__f_file_clone__works_for_link(void **state) {

  const f_string_static_t path = macro_f_string_static_t_initialize("test", 0, 4);

  {
    struct stat statistics;

    memset(&statistics, 0, sizeof(struct stat));

    statistics.st_mode = 1 | F_file_type_link_d;

    will_return(__wrap_stat, false);
    will_return(__wrap_stat, &statistics);
    will_return(__wrap_stat, 0);

    will_return(__wrap_symlink, false);
    will_return(__wrap_symlink, 0);

    will_return(__wrap_chmod, false);
    will_return(__wrap_chmod, 0);

    const f_status_t status = f_file_clone(path, path, 0, 0);

    assert_int_equal(status, F_none);
  }
}

void test__f_file_clone__works_for_regular(void **state) {

  const f_string_static_t path = macro_f_string_static_t_initialize("test", 0, 4);

  {
    struct stat statistics;

    memset(&statistics, 0, sizeof(struct stat));

    statistics.st_mode = 1 | F_file_type_regular_d;

    f_char_t buffer[1];

    memset(buffer, 0, sizeof(f_char_t));

    will_return(__wrap_stat, false);
    will_return(__wrap_stat, &statistics);
    will_return(__wrap_stat, 0);

    will_return(__wrap_open, false);
    will_return(__wrap_open, 0);

    will_return(__wrap_fsync, false);
    will_return(__wrap_fsync, 0);

    will_return(__wrap_close, false);
    will_return(__wrap_close, 0);

    will_return(__wrap_chmod, false);
    will_return(__wrap_chmod, 0);

    will_return(__wrap_open, false);
    will_return(__wrap_open, 0);

    will_return(__wrap_open, false);
    will_return(__wrap_open, 0);

    will_return(__wrap_read, false);
    will_return(__wrap_read, buffer);
    will_return(__wrap_read, 1);
    will_return(__wrap_read, 1);

    will_return(__wrap_write, false);
    will_return(__wrap_write, 1);

    will_return(__wrap_read, false);
    will_return(__wrap_read, buffer);
    will_return(__wrap_read, 0);
    will_return(__wrap_read, 0);

    will_return(__wrap_fsync, false);
    will_return(__wrap_fsync, 0);

    will_return(__wrap_close, false);
    will_return(__wrap_close, 0);

    will_return(__wrap_fsync, false);
    will_return(__wrap_fsync, 0);

    will_return(__wrap_close, false);
    will_return(__wrap_close, 0);

    const f_status_t status = f_file_clone(path, path, 0, 0);

    assert_int_equal(status, F_none);
  }
}

#ifdef __cplusplus
} // extern "C"
#endif
