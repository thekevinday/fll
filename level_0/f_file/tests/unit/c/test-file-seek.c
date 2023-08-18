#include "test-file.h"
#include "test-file-seek.h"

#ifdef __cplusplus
extern "C" {
#endif

void test__f_file_seek__fails(void **state) {

  const f_file_t file = macro_f_file_t_initialize_2(F_type_output_d, F_type_descriptor_output_d, F_file_flag_write_only_d);

  int errnos[] = {
    EBADF,
    EINVAL,
    ENXIO,
    EOVERFLOW,
    ESPIPE,
    mock_errno_generic,
  };

  f_status_t statuss[] = {
    F_file_descriptor,
    F_parameter,
    F_bound_not,
    F_number_overflow,
    F_file_type_pipe,
    F_failure,
  };

  for (int i = 0; i < 6; ++i) {

    off_t seeked = 0;

    will_return(__wrap_lseek, true);
    will_return(__wrap_lseek, errnos[i]);

    const f_status_t status = f_file_seek(file, 0, 0, &seeked);

    assert_int_equal(status, F_status_set_error(statuss[i]));
  } // for
}

void test__f_file_seek__parameter_checking(void **state) {

  const f_file_t file = macro_f_file_t_initialize_2(F_type_output_d, F_type_descriptor_output_d, F_file_flag_write_only_d);
  off_t seeked = 0;

  {
    const f_status_t status = f_file_seek(file, -1, 0, 0);

    assert_int_equal(status, F_status_set_error(F_parameter));
  }

  {
    const f_status_t status = f_file_seek(file, -1, 0, &seeked);

    assert_int_equal(status, F_status_set_error(F_parameter));
  }

  {
    const f_status_t status = f_file_seek(file, 0, 0, 0);

    assert_int_equal(status, F_status_set_error(F_parameter));
  }
}

void test__f_file_seek__returns_file_descriptor_not(void **state) {

  const f_file_t file = macro_f_file_t_initialize_2(F_type_output_d, -1, F_file_flag_write_only_d);

  {
    off_t seeked = 0;

    const f_status_t status = f_file_seek(file, 0, 0, &seeked);

    assert_int_equal(status, F_file_descriptor_not);
  }
}

void test__f_file_seek__works(void **state) {

  const f_file_t file = macro_f_file_t_initialize_2(F_type_output_d, F_type_descriptor_output_d, F_file_flag_write_only_d);

  {
    off_t seeked = 0;

    will_return(__wrap_lseek, false);
    will_return(__wrap_lseek, 0);

    const f_status_t status = f_file_seek(file, 0, 0, &seeked);

    assert_int_equal(status, F_okay);
  }
}

#ifdef __cplusplus
} // extern "C"
#endif
