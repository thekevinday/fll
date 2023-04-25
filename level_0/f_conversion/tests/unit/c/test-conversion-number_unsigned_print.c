#include "test-conversion.h"
#include "test-conversion-number_unsigned_print.h"

#ifdef __cplusplus
extern "C" {
#endif

void test__f_conversion_number_unsigned_print__fails(void **state) {

  const f_file_t output = macro_f_file_t_initialize_2(F_type_output_d, F_type_descriptor_output_d, F_file_flag_write_only_d);

  {
    const f_conversion_data_t data = macro_f_conversion_data_t_initialize_1(10, 0, 1);

    will_return(__wrap_fwrite_unlocked, true);
    will_return(__wrap_fwrite_unlocked, 0);
    will_return(__wrap_ferror_unlocked, true);

    const f_status_t status = f_conversion_number_unsigned_print(1, data, output);

    assert_int_equal(status, F_status_set_error(F_output));
  }
}

void test__f_conversion_number_unsigned_print__fails_for_prepend(void **state) {

  const f_file_t output = macro_f_file_t_initialize_2(F_type_output_d, F_type_descriptor_output_d, F_file_flag_write_only_d);

  {
    const f_conversion_data_t data = macro_f_conversion_data_t_initialize_1(10, F_conversion_data_flag_base_prepend_d, 0);

    will_return(__wrap_fwrite_unlocked, true);
    will_return(__wrap_fwrite_unlocked, 0);
    will_return(__wrap_ferror_unlocked, true);

    const f_status_t status = f_conversion_number_unsigned_print(1, data, output);

    assert_int_equal(status, F_status_set_error(F_output));
  }
}

void test__f_conversion_number_unsigned_print__fails_for_zero(void **state) {

  const f_file_t output = macro_f_file_t_initialize_2(F_type_output_d, F_type_descriptor_output_d, F_file_flag_write_only_d);

  {
    const f_conversion_data_t data = macro_f_conversion_data_t_initialize_1(10, 0, 1);

    will_return(__wrap_fwrite_unlocked, true);
    will_return(__wrap_fwrite_unlocked, 0);
    will_return(__wrap_ferror_unlocked, true);

    const f_status_t status = f_conversion_number_unsigned_print(0, data, output);

    assert_int_equal(status, F_status_set_error(F_output));
  }
}

void test__f_conversion_number_unsigned_print__parameter_checking(void **state) {

  f_file_t output = macro_f_file_t_initialize_2(0, F_type_descriptor_output_d, F_file_flag_write_only_d);

  {
    const f_conversion_data_t data = macro_f_conversion_data_t_initialize_1(2, 0, 0);

    const f_status_t status = f_conversion_number_unsigned_print(0, data, output);

    assert_int_equal(status, F_status_set_error(F_parameter));
  }

  {
    const f_conversion_data_t data = macro_f_conversion_data_t_initialize_1(1, 0, 0);

    output.stream = F_type_output_d;

    const f_status_t status = f_conversion_number_unsigned_print(0, data, output);

    assert_int_equal(status, F_status_set_error(F_parameter));
  }
}

void test__f_conversion_number_unsigned_print__works(void **state) {

  const f_file_t output = macro_f_file_t_initialize_2(F_type_output_d, F_type_descriptor_output_d, F_file_flag_write_only_d);

  {
    const f_conversion_data_t data = macro_f_conversion_data_t_initialize_1(10, 0, 1);

    will_return(__wrap_fwrite_unlocked, false);
    will_return(__wrap_fwrite_unlocked, 1);
    will_return(__wrap_ferror_unlocked, false);

    expect_string(__wrap_fwrite_unlocked, ptr, "1");

    const f_status_t status = f_conversion_number_unsigned_print(1, data, output);

    assert_int_equal(status, F_none);
  }
}

void test__f_conversion_number_unsigned_print__works_for_zero(void **state) {

  const f_file_t output = macro_f_file_t_initialize_2(F_type_output_d, F_type_descriptor_output_d, F_file_flag_write_only_d);

  {
    const f_conversion_data_t data = macro_f_conversion_data_t_initialize_1(10, 0, 1);

    will_return(__wrap_fwrite_unlocked, false);
    will_return(__wrap_fwrite_unlocked, 1);
    will_return(__wrap_ferror_unlocked, false);

    expect_string(__wrap_fwrite_unlocked, ptr, "0");

    const f_status_t status = f_conversion_number_unsigned_print(0, data, output);

    assert_int_equal(status, F_none);
  }
}

void test__f_conversion_number_unsigned_print__works_for_zero_with_width_zero(void **state) {

  const f_file_t output = macro_f_file_t_initialize_2(F_type_output_d, F_type_descriptor_output_d, F_file_flag_write_only_d);

  {
    const f_conversion_data_t data = macro_f_conversion_data_t_initialize_1(10, 0, 0);

    const f_status_t status = f_conversion_number_unsigned_print(0, data, output);

    assert_int_equal(status, F_none);
  }
}

#ifdef __cplusplus
} // extern "C"
#endif
