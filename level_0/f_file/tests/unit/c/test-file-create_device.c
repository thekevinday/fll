#include "test-file.h"
#include "test-file-create_device.h"

#ifdef __cplusplus
extern "C" {
#endif

void test__f_file_create_device__fails(void **state) {

  const f_string_static_t path = macro_f_string_static_t_initialize_1("test", 0, 4);

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

    const int modes[] = {
      F_file_type_block_d,
      F_file_type_character_d,
      F_file_type_fifo_d,
    };

    for (uint8_t j = 0; j < 3; ++j) {

      for (int i = 0; i < 15; ++i) {

        will_return(__wrap_mknod, true);
        will_return(__wrap_mknod, errnos[i]);

        const f_status_t status = f_file_create_device(path, modes[j], 1, 1);

        assert_int_equal(status, F_status_set_error(statuss[i]));
      } // for
    } // for
  }
}

void test__f_file_create_device__returns_data_not(void **state) {

  {
    const f_status_t status = f_file_create_device(f_string_empty_s, 0, 0, 0);

    assert_int_equal(status, F_data_not);
  }
}

void test__f_file_create_device__returns_supported_not(void **state) {

  const f_string_static_t path = macro_f_string_static_t_initialize_1("test", 0, 4);

  const int modes[] = {
    F_file_type_directory_d,
    F_file_type_link_d,
    F_file_type_mask_d,
    F_file_type_regular_d,
    F_file_type_socket_d,
  };

  {
    for (uint8_t i = 0; i < 5; ++i) {

      const f_status_t status = f_file_create_device(path, modes[i], 0, 0);

      assert_int_equal(F_status_set_fine(status), F_support_not);
    } // for
  }
}

void test__f_file_create_device__works(void **state) {

  const f_string_static_t path = macro_f_string_static_t_initialize_1("test", 0, 4);

  const int modes[] = {
    F_file_type_block_d,
    F_file_type_character_d,
    F_file_type_fifo_d,
  };

  {
    for (uint8_t i = 0; i < 3; ++i) {

      will_return(__wrap_mknod, false);
      will_return(__wrap_mknod, 0);

      const f_status_t status = f_file_create_device(path, modes[i], 1, 1);

      assert_int_equal(status, F_none);
    } // for
  }
}

#ifdef __cplusplus
} // extern "C"
#endif
