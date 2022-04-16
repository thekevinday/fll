#include "test-file.h"
#include "test-file-is.h"

#ifdef __cplusplus
extern "C" {
#endif

void test__f_file_is__fails(void **state) {

  const f_string_static_t path = macro_f_string_static_t_initialize("test", 0, 4);

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

  f_status_t types[] = {
    F_file_type_block_d,
    F_file_type_character_d,
    F_file_type_directory_d,
    F_file_type_fifo_d,
    F_file_type_link_d,
    F_file_type_mask_d,
    F_file_type_regular_d,
    F_file_type_socket_d,
  };

  for (int j = 0; j < 8; ++j) {

    for (int i = 0; i < 9; ++i) {

      will_return(__wrap_lstat, true);
      will_return(__wrap_lstat, errnos[i]);

      const f_status_t status = f_file_is(path, types[j], F_false);

      assert_int_equal(F_status_set_fine(status), statuss[i]);
    } // for
  } // for

  for (int j = 0; j < 8; ++j) {

    for (int i = 0; i < 9; ++i) {

      will_return(__wrap_stat, true);
      will_return(__wrap_stat, errnos[i]);

      const f_status_t status = f_file_is(path, types[j], F_true);

      assert_int_equal(F_status_set_fine(status), statuss[i]);
    } // for
  } // for
}

void test__f_file_is__returns_data_not(void **state) {

  {
    const f_status_t status = f_file_is(f_string_empty_s, 0, F_false);

    assert_int_equal(status, F_data_not);
  }
}

void test__f_file_is__returns_false(void **state) {

  const f_string_static_t path = macro_f_string_static_t_initialize("test", 0, 4);

  f_status_t types[] = {
    F_file_type_block_d,
    F_file_type_character_d,
    F_file_type_directory_d,
    F_file_type_fifo_d,
    F_file_type_link_d,
    F_file_type_mask_d,
    F_file_type_regular_d,
    F_file_type_socket_d,
  };

  for (int j = 0; j < 8; ++j) {

    struct stat statistics;

    memset(&statistics, 0, sizeof(struct stat));

    statistics.st_mode = 1 | types[j];

    for (int i = 0; i < 8; ++i) {

      // Skip what would return true.
      if (j == i) continue;

      will_return(__wrap_lstat, false);
      will_return(__wrap_lstat, &statistics);
      will_return(__wrap_lstat, 0);

      const f_status_t status = f_file_is(path, types[i], F_false);

      assert_int_equal(status, F_false);
    } // for
  } // for
}

void test__f_file_is__returns_true(void **state) {

  const f_string_static_t path = macro_f_string_static_t_initialize("test", 0, 4);

  f_status_t types[] = {
    F_file_type_block_d,
    F_file_type_character_d,
    F_file_type_directory_d,
    F_file_type_fifo_d,
    F_file_type_link_d,
    F_file_type_mask_d,
    F_file_type_regular_d,
    F_file_type_socket_d,
  };

  for (int i = 0; i < 8; ++i) {

    struct stat statistics;

    memset(&statistics, 0, sizeof(struct stat));

    statistics.st_mode = 1 | types[i];

    will_return(__wrap_lstat, false);
    will_return(__wrap_lstat, &statistics);
    will_return(__wrap_lstat, 0);

    const f_status_t status = f_file_is(path, types[i], F_false);

    assert_int_equal(status, F_true);
  } // for
}

#ifdef __cplusplus
} // extern "C"
#endif
