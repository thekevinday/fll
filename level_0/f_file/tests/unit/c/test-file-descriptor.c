#include "test-file.h"
#include "test-file-descriptor.h"

#ifdef __cplusplus
extern "C" {
#endif

void test__f_file_descriptor__fails(void **state) {

  {
    f_file_t file = macro_f_file_t_initialize_2(F_type_output_d, F_type_descriptor_output_d, F_file_flag_write_only_d);

    will_return(__wrap_fileno, -1);

    const f_status_t status = f_file_descriptor(&file);

    assert_int_equal(F_status_set_fine(status), F_file_descriptor_not);
  }
}

void test__f_file_descriptor__parameter_checking(void **state) {

  {
    const f_status_t status = f_file_descriptor(0);

    assert_int_equal(status, F_status_set_error(F_parameter));
  }
}

void test__f_file_descriptor__returns_stream_not(void **state) {

  f_file_t file = macro_f_file_t_initialize_2(0, F_type_descriptor_output_d, F_file_flag_write_only_d);

  {
    const f_status_t status = f_file_descriptor(&file);

    assert_int_equal(status, F_stream_not);
  }
}

void test__f_file_descriptor__works(void **state) {

  {
    f_file_t file = macro_f_file_t_initialize_2(F_type_output_d, F_type_descriptor_output_d, F_file_flag_write_only_d);

    will_return(__wrap_fileno, F_type_descriptor_output_d);

    const f_status_t status = f_file_descriptor(&file);

    assert_int_equal(status, F_none);
    assert_int_equal(file.id, F_type_descriptor_output_d);
  }
}

#ifdef __cplusplus
} // extern "C"
#endif
