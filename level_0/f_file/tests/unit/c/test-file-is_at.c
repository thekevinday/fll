#include "test-file.h"
#include "test-file-is.h"

#ifdef __cplusplus
extern "C" {
#endif

void test__f_file_is_at__fails(void **state) {

  const f_file_t file = macro_f_file_t_initialize_2(F_type_output_d, F_type_descriptor_output_d, F_file_flag_write_only_d);
  const f_string_static_t path = macro_f_string_static_t_initialize_1("test", 0, 4);

  int errnos[] = {
    EACCES,
    EBADF,
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
    F_status_set_error(F_access_denied),
    F_status_set_error(F_directory_descriptor),
    F_status_set_error(F_buffer),
    F_status_set_error(F_loop),
    F_status_set_error(F_name),
    F_file_found_not,
    F_status_set_error(F_memory_not),
    F_status_set_error(F_directory_not),
    F_status_set_error(F_number_overflow),
    F_status_set_error(F_file_stat),
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

    for (int i = 0; i < 10; ++i) {

      will_return(__wrap_fstatat, true);
      will_return(__wrap_fstatat, errnos[i]);

      const f_status_t status = f_file_is_at(file, path, types[j], 0);

      assert_int_equal(status, statuss[i]);
    } // for
  } // for
}

void test__f_file_is_at__returns_data_not(void **state) {

  const f_file_t file = macro_f_file_t_initialize_2(F_type_output_d, F_type_descriptor_output_d, F_file_flag_write_only_d);

  {
    const f_status_t status = f_file_is_at(file, f_string_empty_s, 0, 0);

    assert_int_equal(status, F_data_not);
  }
}

void test__f_file_is_at__returns_file_descriptor_not(void **state) {

  const f_file_t file = macro_f_file_t_initialize_2(F_type_output_d, -1, F_file_flag_write_only_d);

  {
    const f_status_t status = f_file_is_at(file, f_string_empty_s, 0, 0);

    assert_int_equal(status, F_file_descriptor_not);
  }
}

void test__f_file_is_at__returns_false(void **state) {

  const f_file_t file = macro_f_file_t_initialize_2(F_type_output_d, F_type_descriptor_output_d, F_file_flag_write_only_d);
  const f_string_static_t path = macro_f_string_static_t_initialize_1("test", 0, 4);

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

      will_return(__wrap_fstatat, false);
      will_return(__wrap_fstatat, &statistics);
      will_return(__wrap_fstatat, 0);

      const f_status_t status = f_file_is_at(file, path, types[i], 0);

      assert_int_equal(status, F_false);
    } // for
  } // for
}

void test__f_file_is_at__returns_true(void **state) {

  const f_file_t file = macro_f_file_t_initialize_2(F_type_output_d, F_type_descriptor_output_d, F_file_flag_write_only_d);
  const f_string_static_t path = macro_f_string_static_t_initialize_1("test", 0, 4);

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

      // Skip what would return false.
      if (j != i) continue;

      will_return(__wrap_fstatat, false);
      will_return(__wrap_fstatat, &statistics);
      will_return(__wrap_fstatat, 0);

      const f_status_t status = f_file_is_at(file, path, types[i], 0);

      assert_int_equal(status, F_true);
    } // for
  } // for
}

#ifdef __cplusplus
} // extern "C"
#endif
