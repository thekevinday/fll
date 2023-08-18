#include "test-print.h"
#include "test-print-dynamic_partial_raw.h"

#ifdef __cplusplus
extern "C" {
#endif

void test__f_print_dynamic_partial_raw__fails(void **state) {

  const f_string_static_t test = macro_f_string_static_t_initialize_1("test", 0, 4);
  const f_string_range_t partial = macro_f_string_range_t_initialize_1(0, 2);
  const f_file_t output = macro_f_file_t_initialize_2(F_type_output_d, F_type_descriptor_output_d, F_file_flag_write_only_d);

  {
    will_return(__wrap_fwrite_unlocked, true);
    will_return(__wrap_fwrite_unlocked, 0);
    will_return(__wrap_ferror_unlocked, true);

    const f_status_t status = f_print_dynamic_partial_raw(test, partial, output);

    assert_int_equal(status, F_status_set_error(F_output));
  }
}

void test__f_print_dynamic_partial_raw__returns_data_not(void **state) {

  const f_string_range_t partial = macro_f_string_range_t_initialize_1(0, 2);
  const f_file_t output = macro_f_file_t_initialize_2(F_type_output_d, F_type_descriptor_output_d, F_file_flag_write_only_d);

  {
    const f_status_t status = f_print_dynamic_partial_raw(f_string_empty_s, partial, output);

    assert_int_equal(status, F_data_not);
  }
}

void test__f_print_dynamic_partial_raw__returns_stream_not(void **state) {

  const f_string_static_t test = macro_f_string_static_t_initialize_1("test", 0, 4);
  const f_string_range_t partial = macro_f_string_range_t_initialize_1(0, 2);
  const f_file_t output = macro_f_file_t_initialize_2(0, -1, F_file_flag_write_only_d);

  {
    const f_status_t status = f_print_dynamic_partial_raw(test, partial, output);

    assert_int_equal(F_status_set_fine(status), F_stream_not);
  }
}

void test__f_print_dynamic_partial_raw__works(void **state) {

  const f_string_static_t test = macro_f_string_static_t_initialize_1("test", 0, 4);
  const f_string_range_t partial = macro_f_string_range_t_initialize_1(0, 2);
  const f_file_t output = macro_f_file_t_initialize_2(F_type_output_d, F_type_descriptor_output_d, F_file_flag_write_only_d);

  {
    will_return(__wrap_fwrite_unlocked, false);
    will_return(__wrap_fwrite_unlocked, 3);
    will_return(__wrap_ferror_unlocked, false);

    const f_status_t status = f_print_dynamic_partial_raw(test, partial, output);

    assert_int_equal(status, F_okay);
  }
}

#ifdef __cplusplus
} // extern "C"
#endif
