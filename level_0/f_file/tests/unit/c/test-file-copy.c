#include "test-file.h"
#include "test-file-copy.h"

#ifdef __cplusplus
extern "C" {
#endif

void test__f_file_copy__fails_during_read_write(void **state) {

  const f_string_static_t path = macro_f_string_static_t_initialize_1("test", 0, 4);
  const f_mode_t mode = f_mode_t_initialize;

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

    const f_status_t status = f_file_copy(path, path, mode, 0, 0);

    assert_int_equal(F_status_set_fine(status), F_file_write);
  }
}

void test__f_file_copy__fails_for_block(void **state) {

  const f_string_static_t path = macro_f_string_static_t_initialize_1("test", 0, 4);
  const f_mode_t mode = f_mode_t_initialize;

  {
    int errnos[] = {
      EACCES,
      EDQUOT,
      EEXIST,
      EFAULT,
      EINVAL,
      ELOOP,
      ENAMETOOLONG,
      ENOENT,
      ENOMEM,
      ENOSPC,
      ENOTDIR,
      EPERM,
      EROFS,
      ETXTBSY,
      mock_errno_generic,
    };

    f_status_t statuss[] = {
      F_access_denied,
      F_filesystem_quota_block,
      F_file_found,
      F_buffer,
      F_parameter,
      F_loop,
      F_name,
      F_file_found_not,
      F_memory_not,
      F_space_not,
      F_directory_not,
      F_prohibited,
      F_read_only,
      F_busy,
      F_failure,
    };

    struct stat statistics;

    memset(&statistics, 0, sizeof(struct stat));

    statistics.st_mode = 1 | F_file_type_block_d;

    for (int i = 0; i < 15; ++i) {

      will_return(__wrap_stat, false);
      will_return(__wrap_stat, &statistics);
      will_return(__wrap_stat, 0);

      will_return(__wrap_mknod, true);
      will_return(__wrap_mknod, errnos[i]);

      if (statuss[i] == F_file_found) {
        will_return(__wrap_chmod, false);
        will_return(__wrap_chmod, 0);
      }

      const f_status_t status = f_file_copy(path, path, mode, 0, 0);

      if (statuss[i] == F_file_found) {
        assert_int_equal(status, F_none);
      }
      else {
        assert_int_equal(status, F_status_set_error(statuss[i]));
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

    statistics.st_mode = 1 | F_file_type_block_d;

    f_char_t buffer[1];

    memset(buffer, 0, sizeof(f_char_t));

    for (int i = 0; i < 11; ++i) {

      will_return(__wrap_stat, false);
      will_return(__wrap_stat, &statistics);
      will_return(__wrap_stat, 0);

      will_return(__wrap_mknod, false);
      will_return(__wrap_mknod, 0);

      will_return(__wrap_chmod, true);
      will_return(__wrap_chmod, errnos[i]);

      const f_status_t status = f_file_copy(path, path, mode, 0, 0);

      if (statuss[i] == F_file_found) {
        assert_int_equal(status, F_none);
      }
      else {
        assert_int_equal(status, F_status_set_error(statuss[i]));
      }
    } // for
  }
}

void test__f_file_copy__fails_for_character(void **state) {

  const f_string_static_t path = macro_f_string_static_t_initialize_1("test", 0, 4);
  const f_mode_t mode = f_mode_t_initialize;

  {
    int errnos[] = {
      EACCES,
      EDQUOT,
      EEXIST,
      EFAULT,
      EINVAL,
      ELOOP,
      ENAMETOOLONG,
      ENOENT,
      ENOMEM,
      ENOSPC,
      ENOTDIR,
      EPERM,
      EROFS,
      ETXTBSY,
      mock_errno_generic,
    };

    f_status_t statuss[] = {
      F_access_denied,
      F_filesystem_quota_block,
      F_file_found,
      F_buffer,
      F_parameter,
      F_loop,
      F_name,
      F_file_found_not,
      F_memory_not,
      F_space_not,
      F_directory_not,
      F_prohibited,
      F_read_only,
      F_busy,
      F_failure,
    };

    struct stat statistics;

    memset(&statistics, 0, sizeof(struct stat));

    statistics.st_mode = 1 | F_file_type_character_d;

    for (int i = 0; i < 15; ++i) {

      will_return(__wrap_stat, false);
      will_return(__wrap_stat, &statistics);
      will_return(__wrap_stat, 0);

      will_return(__wrap_mknod, true);
      will_return(__wrap_mknod, errnos[i]);

      if (statuss[i] == F_file_found) {
        will_return(__wrap_chmod, false);
        will_return(__wrap_chmod, 0);
      }

      const f_status_t status = f_file_copy(path, path, mode, 0, 0);

      if (statuss[i] == F_file_found) {
        assert_int_equal(status, F_none);
      }
      else {
        assert_int_equal(status, F_status_set_error(statuss[i]));
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

    statistics.st_mode = 1 | F_file_type_character_d;

    f_char_t buffer[1];

    memset(buffer, 0, sizeof(f_char_t));

    for (int i = 0; i < 11; ++i) {

      will_return(__wrap_stat, false);
      will_return(__wrap_stat, &statistics);
      will_return(__wrap_stat, 0);

      will_return(__wrap_mknod, false);
      will_return(__wrap_mknod, 0);

      will_return(__wrap_chmod, true);
      will_return(__wrap_chmod, errnos[i]);

      const f_status_t status = f_file_copy(path, path, mode, 0, 0);

      if (statuss[i] == F_file_found) {
        assert_int_equal(status, F_none);
      }
      else {
        assert_int_equal(status, F_status_set_error(statuss[i]));
      }
    } // for
  }
}

void test__f_file_copy__fails_for_directory(void **state) {

  const f_string_static_t path = macro_f_string_static_t_initialize_1("test", 0, 4);
  const f_mode_t mode = f_mode_t_initialize;

  {
    int errnos[] = {
      EACCES,
      EDQUOT,
      EEXIST,
      EFAULT,
      EINVAL,
      ELOOP,
      EMLINK,
      ENAMETOOLONG,
      ENOENT,
      ENOMEM,
      ENOSPC,
      ENOTDIR,
      EPERM,
      EROFS,
      mock_errno_generic,
    };

    f_status_t statuss[] = {
      F_access_denied,
      F_filesystem_quota_block,
      F_file_found,
      F_buffer,
      F_parameter,
      F_loop,
      F_directory_link_max,
      F_name,
      F_file_found_not,
      F_memory_not,
      F_space_not,
      F_directory_not,
      F_prohibited,
      F_read_only,
      F_failure,
    };

    struct stat statistics;

    memset(&statistics, 0, sizeof(struct stat));

    statistics.st_mode = 1 | F_file_type_directory_d;

    for (int i = 0; i < 15; ++i) {

      will_return(__wrap_stat, false);
      will_return(__wrap_stat, &statistics);
      will_return(__wrap_stat, 0);

      will_return(__wrap_mkdir, true);
      will_return(__wrap_mkdir, errnos[i]);

      if (statuss[i] == F_file_found) {
        will_return(__wrap_chmod, false);
        will_return(__wrap_chmod, 0);
      }

      const f_status_t status = f_file_copy(path, path, mode, 0, 0);

      if (statuss[i] == F_file_found) {
        assert_int_equal(status, F_none);
      }
      else {
        assert_int_equal(status, F_status_set_error(statuss[i]));
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

    statistics.st_mode = 1 | F_file_type_directory_d;

    f_char_t buffer[1];

    memset(buffer, 0, sizeof(f_char_t));

    for (int i = 0; i < 11; ++i) {

      will_return(__wrap_stat, false);
      will_return(__wrap_stat, &statistics);
      will_return(__wrap_stat, 0);

      will_return(__wrap_mkdir, false);
      will_return(__wrap_mkdir, 0);

      will_return(__wrap_chmod, true);
      will_return(__wrap_chmod, errnos[i]);

      const f_status_t status = f_file_copy(path, path, mode, 0, 0);

      if (statuss[i] == F_file_found) {
        assert_int_equal(status, F_none);
      }
      else {
        assert_int_equal(status, F_status_set_error(statuss[i]));
      }
    } // for
  }
}

void test__f_file_copy__fails_for_fifo(void **state) {

  const f_string_static_t path = macro_f_string_static_t_initialize_1("test", 0, 4);
  const f_mode_t mode = f_mode_t_initialize;

  {
    int errnos[] = {
      EACCES,
      EDQUOT,
      EEXIST,
      ENAMETOOLONG,
      ENOENT,
      ENOSPC,
      ENOTDIR,
      EPERM,
      EROFS,
      mock_errno_generic,
    };

    f_status_t statuss[] = {
      F_access_denied,
      F_filesystem_quota_block,
      F_file_found,
      F_name,
      F_file_found_not,
      F_space_not,
      F_directory_not,
      F_prohibited,
      F_read_only,
      F_failure,
    };

    struct stat statistics;

    memset(&statistics, 0, sizeof(struct stat));

    statistics.st_mode = 1 | F_file_type_fifo_d;

    for (int i = 0; i < 10; ++i) {

      will_return(__wrap_stat, false);
      will_return(__wrap_stat, &statistics);
      will_return(__wrap_stat, 0);

      will_return(__wrap_mkfifo, true);
      will_return(__wrap_mkfifo, errnos[i]);

      if (statuss[i] == F_file_found) {
        will_return(__wrap_chmod, false);
        will_return(__wrap_chmod, 0);
      }

      const f_status_t status = f_file_copy(path, path, mode, 0, 0);

      if (statuss[i] == F_file_found) {
        assert_int_equal(status, F_none);
      }
      else {
        assert_int_equal(status, F_status_set_error(statuss[i]));
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

    statistics.st_mode = 1 | F_file_type_fifo_d;

    f_char_t buffer[1];

    memset(buffer, 0, sizeof(f_char_t));

    for (int i = 0; i < 11; ++i) {

      will_return(__wrap_stat, false);
      will_return(__wrap_stat, &statistics);
      will_return(__wrap_stat, 0);

      will_return(__wrap_mkfifo, false);
      will_return(__wrap_mkfifo, 0);

      will_return(__wrap_chmod, true);
      will_return(__wrap_chmod, errnos[i]);

      const f_status_t status = f_file_copy(path, path, mode, 0, 0);

      if (statuss[i] == F_file_found) {
        assert_int_equal(status, F_none);
      }
      else {
        assert_int_equal(status, F_status_set_error(statuss[i]));
      }
    } // for
  }
}

void test__f_file_copy__fails_for_link(void **state) {

  const f_string_static_t path = macro_f_string_static_t_initialize_1("test", 0, 4);
  const f_mode_t mode = f_mode_t_initialize;

  {
    int errnos[] = {
      EACCES,
      EFAULT,
      EINVAL,
      EIO,
      ELOOP,
      ENAMETOOLONG,
      ENOENT,
      ENOMEM,
      ENOTDIR,
      mock_errno_generic,
    };

    f_status_t statuss[] = {
      F_access_denied,
      F_buffer,
      F_parameter,
      F_input_output,
      F_loop,
      F_name,
      F_file_found_not,
      F_memory_not,
      F_directory_not,
      F_failure,
    };

    struct stat statistics;

    memset(&statistics, 0, sizeof(struct stat));

    statistics.st_mode = 1 | F_file_type_link_d;
    statistics.st_size = 1;

    for (int i = 0; i < 10; ++i) {

      will_return(__wrap_stat, false);
      will_return(__wrap_stat, &statistics);
      will_return(__wrap_stat, 0);

      will_return(__wrap_readlink, true);
      will_return(__wrap_readlink, errnos[i]);

      const f_status_t status = f_file_copy(path, path, mode, 0, 0);

      assert_int_equal(status, F_status_set_error(statuss[i]));
    } // for
  }

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
    statistics.st_size = 1;

    f_char_t buffer[1];

    memset(buffer, 0, sizeof(f_char_t));

    for (int i = 0; i < 18; ++i) {

      will_return(__wrap_stat, false);
      will_return(__wrap_stat, &statistics);
      will_return(__wrap_stat, 0);

      will_return(__wrap_readlink, false);
      will_return(__wrap_readlink, (void *) buffer);
      will_return(__wrap_readlink, 0);

      will_return(__wrap_symlink, true);
      will_return(__wrap_symlink, errnos[i]);

      const f_status_t status = f_file_copy(path, path, mode, 0, 0);

      if (statuss[i] == F_file_found) {
        assert_int_equal(status, F_none);
      }
      else {
        assert_int_equal(status, F_status_set_error(statuss[i]));
      }
    } // for
  }
}

void test__f_file_copy__fails_for_regular(void **state) {

  const f_string_static_t path = macro_f_string_static_t_initialize_1("test", 0, 4);
  const f_mode_t mode = f_mode_t_initialize;

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

      const f_status_t status = f_file_copy(path, path, mode, 0, 0);

      assert_int_equal(status, F_status_set_error(statuss[i]));
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
      F_support_not,
      F_number_overflow,
      F_prohibited,
      F_read_only,
      F_busy,
      F_failure,
    };

    struct stat statistics;

    memset(&statistics, 0, sizeof(struct stat));

    statistics.st_mode = 1 | F_file_type_regular_d;
    statistics.st_size = 1;

    for (int i = 0; i < 21; ++i) {

      will_return(__wrap_stat, false);
      will_return(__wrap_stat, &statistics);
      will_return(__wrap_stat, 0);

      will_return(__wrap_open, true);
      will_return(__wrap_open, errnos[i]);

      const f_status_t status = f_file_copy(path, path, mode, 0, 0);

      assert_int_equal(status, F_status_set_error(statuss[i]));
    } // for
  }

  {
    int errnos[] = {
      EBADF,
      EINTR,
      EIO,
      ENOSPC,
      EDQUOT,
      mock_errno_generic,
    };

    f_status_t statuss[] = {
      F_file_descriptor,
      F_interrupt,
      F_input_output,
      F_space_not,
      F_filesystem_quota_block,
      F_file_close,
    };

    struct stat statistics;

    memset(&statistics, 0, sizeof(struct stat));

    statistics.st_mode = 1 | F_file_type_regular_d;
    statistics.st_size = 1;

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

      const f_status_t status = f_file_copy(path, path, mode, 0, 0);

      assert_int_equal(status, F_status_set_error(statuss[i]));
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
    statistics.st_size = 1;

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

      const f_status_t status = f_file_copy(path, path, mode, 0, 0);

      assert_int_equal(status, F_status_set_error(statuss[i]));
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
      F_support_not,
      F_number_overflow,
      F_prohibited,
      F_read_only,
      F_busy,
      F_failure,
    };

    struct stat statistics;

    memset(&statistics, 0, sizeof(struct stat));

    statistics.st_mode = 1 | F_file_type_regular_d;
    statistics.st_size = 1;

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

      const f_status_t status = f_file_copy(path, path, mode, 0, 0);

      assert_int_equal(status, F_status_set_error(statuss[i]));
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
      F_support_not,
      F_number_overflow,
      F_prohibited,
      F_read_only,
      F_busy,
      F_failure,
    };

    struct stat statistics;

    memset(&statistics, 0, sizeof(struct stat));

    statistics.st_mode = 1 | F_file_type_regular_d;
    statistics.st_size = 1;

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

      const f_status_t status = f_file_copy(path, path, mode, 0, 0);

      assert_int_equal(status, F_status_set_error(statuss[i]));
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
    statistics.st_size = 1;

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

      const f_status_t status = f_file_copy(path, path, mode, 0, 0);

      assert_int_equal(status, F_status_set_error(statuss[i]));
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
    statistics.st_size = 1;

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

      const f_status_t status = f_file_copy(path, path, mode, 0, f_file_stat_flag_exclusive_e);

      assert_int_equal(status, F_status_set_error(statuss[i]));
    } // for
  }
}

void test__f_file_copy__fails_for_socket(void **state) {

  const f_string_static_t path = macro_f_string_static_t_initialize_1("test", 0, 4);
  const f_mode_t mode = f_mode_t_initialize;

  {
    int errnos[] = {
      EACCES,
      EDQUOT,
      EEXIST,
      EFAULT,
      EINVAL,
      ELOOP,
      ENAMETOOLONG,
      ENOENT,
      ENOMEM,
      ENOSPC,
      ENOTDIR,
      EPERM,
      EROFS,
      ETXTBSY,
      mock_errno_generic,
    };

    f_status_t statuss[] = {
      F_access_denied,
      F_filesystem_quota_block,
      F_file_found,
      F_buffer,
      F_parameter,
      F_loop,
      F_name,
      F_file_found_not,
      F_memory_not,
      F_space_not,
      F_directory_not,
      F_prohibited,
      F_read_only,
      F_busy,
      F_failure,
    };

    struct stat statistics;

    memset(&statistics, 0, sizeof(struct stat));

    statistics.st_mode = 1 | F_file_type_socket_d;
    statistics.st_size = 1;

    for (int i = 0; i < 15; ++i) {

      will_return(__wrap_stat, false);
      will_return(__wrap_stat, &statistics);
      will_return(__wrap_stat, 0);

      will_return(__wrap_mknod, true);
      will_return(__wrap_mknod, errnos[i]);

      if (statuss[i] == F_file_found) {
        will_return(__wrap_chmod, false);
        will_return(__wrap_chmod, 0);
      }

      const f_status_t status = f_file_copy(path, path, mode, 0, 0);

      if (statuss[i] == F_file_found) {
        assert_int_equal(status, F_none);
      }
      else {
        assert_int_equal(status, F_status_set_error(statuss[i]));
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

    statistics.st_mode = 1 | F_file_type_socket_d;
    statistics.st_size = 1;

    f_char_t buffer[1];

    memset(buffer, 0, sizeof(f_char_t));

    for (int i = 0; i < 11; ++i) {

      will_return(__wrap_stat, false);
      will_return(__wrap_stat, &statistics);
      will_return(__wrap_stat, 0);

      will_return(__wrap_mknod, false);
      will_return(__wrap_mknod, 0);

      will_return(__wrap_chmod, true);
      will_return(__wrap_chmod, errnos[i]);

      const f_status_t status = f_file_copy(path, path, mode, 0, 0);

      if (statuss[i] == F_file_found) {
        assert_int_equal(status, F_none);
      }
      else {
        assert_int_equal(status, F_status_set_error(statuss[i]));
      }
    } // for
  }
}

void test__f_file_copy__returns_data_not(void **state) {

  const f_string_static_t path = macro_f_string_static_t_initialize_1("test", 0, 4);
  const f_mode_t mode = f_mode_t_initialize;

  {
    const f_status_t status = f_file_copy(f_string_empty_s, f_string_empty_s, mode, 0, 0);

    assert_int_equal(status, F_data_not);
  }

  {
    const f_status_t status = f_file_copy(path, f_string_empty_s, mode, 0, 0);

    assert_int_equal(status, F_data_not);
  }

  {
    const f_status_t status = f_file_copy(f_string_empty_s, path, mode, 0, 0);

    assert_int_equal(status, F_data_not);
  }
}

void test__f_file_copy__works_for_block(void **state) {

  const f_string_static_t path = macro_f_string_static_t_initialize_1("test", 0, 4);
  const f_mode_t mode = f_mode_t_initialize;

  {
    struct stat statistics;

    memset(&statistics, 0, sizeof(struct stat));

    statistics.st_mode = 1 | F_file_type_block_d;
    statistics.st_size = 1;

    will_return(__wrap_stat, false);
    will_return(__wrap_stat, &statistics);
    will_return(__wrap_stat, 0);

    will_return(__wrap_mknod, false);
    will_return(__wrap_mknod, 0);

    will_return(__wrap_chmod, false);
    will_return(__wrap_chmod, 0);

    const f_status_t status = f_file_copy(path, path, mode, 0, 0);

    assert_int_equal(status, F_none);
  }
}

void test__f_file_copy__works_for_character(void **state) {

  const f_string_static_t path = macro_f_string_static_t_initialize_1("test", 0, 4);
  const f_mode_t mode = f_mode_t_initialize;

  {
    struct stat statistics;

    memset(&statistics, 0, sizeof(struct stat));

    statistics.st_mode = 1 | F_file_type_character_d;
    statistics.st_size = 1;

    will_return(__wrap_stat, false);
    will_return(__wrap_stat, &statistics);
    will_return(__wrap_stat, 0);

    will_return(__wrap_mknod, false);
    will_return(__wrap_mknod, 0);

    will_return(__wrap_chmod, false);
    will_return(__wrap_chmod, 0);

    const f_status_t status = f_file_copy(path, path, mode, 0, 0);

    assert_int_equal(status, F_none);
  }
}

void test__f_file_copy__works_for_directory(void **state) {

  const f_string_static_t path = macro_f_string_static_t_initialize_1("test", 0, 4);
  const f_mode_t mode = f_mode_t_initialize;

  {
    struct stat statistics;

    memset(&statistics, 0, sizeof(struct stat));

    statistics.st_mode = 1 | F_file_type_directory_d;
    statistics.st_size = 1;

    will_return(__wrap_stat, false);
    will_return(__wrap_stat, &statistics);
    will_return(__wrap_stat, 0);

    will_return(__wrap_mkdir, false);
    will_return(__wrap_mkdir, 0);

    will_return(__wrap_chmod, false);
    will_return(__wrap_chmod, 0);

    const f_status_t status = f_file_copy(path, path, mode, 0, 0);

    assert_int_equal(status, F_none);
  }
}

void test__f_file_copy__works_for_fifo(void **state) {

  const f_string_static_t path = macro_f_string_static_t_initialize_1("test", 0, 4);
  const f_mode_t mode = f_mode_t_initialize;

  {
    struct stat statistics;

    memset(&statistics, 0, sizeof(struct stat));

    statistics.st_mode = 1 | F_file_type_fifo_d;
    statistics.st_size = 1;

    will_return(__wrap_stat, false);
    will_return(__wrap_stat, &statistics);
    will_return(__wrap_stat, 0);

    will_return(__wrap_mkfifo, false);
    will_return(__wrap_mkfifo, 0);

    will_return(__wrap_chmod, false);
    will_return(__wrap_chmod, 0);

    const f_status_t status = f_file_copy(path, path, mode, 0, 0);

    assert_int_equal(status, F_none);
  }
}

void test__f_file_copy__works_for_link(void **state) {

  const f_string_static_t path = macro_f_string_static_t_initialize_1("test", 0, 4);
  const f_mode_t mode = f_mode_t_initialize;

  {
    struct stat statistics;

    memset(&statistics, 0, sizeof(struct stat));

    statistics.st_mode = 1 | F_file_type_link_d;
    statistics.st_size = 1;

    f_char_t buffer[1];

    memset(buffer, 0, sizeof(f_char_t));

    will_return(__wrap_stat, false);
    will_return(__wrap_stat, &statistics);
    will_return(__wrap_stat, 0);

    will_return(__wrap_readlink, false);
    will_return(__wrap_readlink, (void *) buffer);
    will_return(__wrap_readlink, 0);

    will_return(__wrap_symlink, false);
    will_return(__wrap_symlink, 0);

    const f_status_t status = f_file_copy(path, path, mode, 0, 0);

    assert_int_equal(status, F_none);
  }
}

void test__f_file_copy__works_for_regular(void **state) {

  const f_string_static_t path = macro_f_string_static_t_initialize_1("test", 0, 4);
  const f_mode_t mode = f_mode_t_initialize;

  {
    struct stat statistics;

    memset(&statistics, 0, sizeof(struct stat));

    statistics.st_mode = 1 | F_file_type_regular_d;
    statistics.st_size = 1;

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

    const f_status_t status = f_file_copy(path, path, mode, 0, 0);

    assert_int_equal(status, F_none);
  }
}

void test__f_file_copy__works_for_socket(void **state) {

  const f_string_static_t path = macro_f_string_static_t_initialize_1("test", 0, 4);
  const f_mode_t mode = f_mode_t_initialize;

  {
    struct stat statistics;

    memset(&statistics, 0, sizeof(struct stat));

    statistics.st_mode = 1 | F_file_type_socket_d;
    statistics.st_size = 1;

    will_return(__wrap_stat, false);
    will_return(__wrap_stat, &statistics);
    will_return(__wrap_stat, 0);

    will_return(__wrap_mknod, false);
    will_return(__wrap_mknod, 0);

    will_return(__wrap_chmod, false);
    will_return(__wrap_chmod, 0);

    const f_status_t status = f_file_copy(path, path, mode, 0, 0);

    assert_int_equal(status, F_none);
  }
}

#ifdef __cplusplus
} // extern "C"
#endif
