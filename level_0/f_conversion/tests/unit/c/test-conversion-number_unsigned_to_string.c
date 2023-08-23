#include "test-conversion.h"
#include "test-conversion-number_unsigned_to_string.h"

#ifdef __cplusplus
extern "C" {
#endif

void test__f_conversion_number_unsigned_to_string__parameter_checking(void **state) {

  {
    const f_conversion_data_t data = macro_f_conversion_data_t_initialize_1(2, 0, 0);

    const f_status_t status = f_conversion_number_unsigned_to_string(0, data, 0);

    assert_int_equal(status, F_status_set_error(F_parameter));
  }

  {
    f_string_dynamic_t string;
    const f_conversion_data_t data = macro_f_conversion_data_t_initialize_1(1, 0, 0);

    const f_status_t status = f_conversion_number_unsigned_to_string(0, data, &string);

    assert_int_equal(status, F_status_set_error(F_parameter));
  }
}

void test__f_conversion_number_unsigned_to_string__works(void **state) {

  f_string_dynamic_t destination = f_string_dynamic_t_initialize;

  {
    const f_conversion_data_t data = macro_f_conversion_data_t_initialize_1(10, 0, 0);

    const f_status_t status = f_conversion_number_unsigned_to_string(1, data, &destination);

    assert_int_equal(status, F_okay);
    assert_string_equal(destination.string, "1");
  }

  free((void *) destination.string);
}

void test__f_conversion_number_unsigned_to_string__works_for_prepend(void **state) {

  f_string_dynamic_t destination = f_string_dynamic_t_initialize;

  {
    const f_conversion_data_t data = macro_f_conversion_data_t_initialize_1(2, F_conversion_data_flag_base_prepend_d, 0);

    const f_status_t status = f_conversion_number_unsigned_to_string(1, data, &destination);

    assert_int_equal(status, F_okay);
    assert_string_equal(destination.string, "0b1");
  }

  destination.used = 0;
  memset(destination.string, 0, sizeof(f_char_t) * destination.size);

  {
    const f_conversion_data_t data = macro_f_conversion_data_t_initialize_1(2, F_conversion_data_flag_base_prepend_d | F_conversion_data_flag_base_upper_d, 0);

    const f_status_t status = f_conversion_number_unsigned_to_string(1, data, &destination);

    assert_int_equal(status, F_okay);
    assert_string_equal(destination.string, "0B1");
  }

  destination.used = 0;
  memset(destination.string, 0, sizeof(f_char_t) * destination.size);

  {
    const f_conversion_data_t data = macro_f_conversion_data_t_initialize_1(8, F_conversion_data_flag_base_prepend_d, 0);

    const f_status_t status = f_conversion_number_unsigned_to_string(1, data, &destination);

    assert_int_equal(status, F_okay);
    assert_string_equal(destination.string, "0o1");
  }

  destination.used = 0;
  memset(destination.string, 0, sizeof(f_char_t) * destination.size);

  {
    const f_conversion_data_t data = macro_f_conversion_data_t_initialize_1(8, F_conversion_data_flag_base_prepend_d | F_conversion_data_flag_base_upper_d, 0);

    const f_status_t status = f_conversion_number_unsigned_to_string(1, data, &destination);

    assert_int_equal(status, F_okay);
    assert_string_equal(destination.string, "0O1");
  }

  destination.used = 0;
  memset(destination.string, 0, sizeof(f_char_t) * destination.size);

  {
    const f_conversion_data_t data = macro_f_conversion_data_t_initialize_1(10, F_conversion_data_flag_base_prepend_d, 0);

    const f_status_t status = f_conversion_number_unsigned_to_string(1, data, &destination);

    assert_int_equal(status, F_okay);
    assert_string_equal(destination.string, "0t1");
  }

  destination.used = 0;
  memset(destination.string, 0, sizeof(f_char_t) * destination.size);

  {
    const f_conversion_data_t data = macro_f_conversion_data_t_initialize_1(10, F_conversion_data_flag_base_prepend_d | F_conversion_data_flag_base_upper_d, 0);

    const f_status_t status = f_conversion_number_unsigned_to_string(1, data, &destination);

    assert_int_equal(status, F_okay);
    assert_string_equal(destination.string, "0T1");
  }

  destination.used = 0;
  memset(destination.string, 0, sizeof(f_char_t) * destination.size);

  {
    const f_conversion_data_t data = macro_f_conversion_data_t_initialize_1(12, F_conversion_data_flag_base_prepend_d, 0);

    const f_status_t status = f_conversion_number_unsigned_to_string(1, data, &destination);

    assert_int_equal(status, F_okay);
    assert_string_equal(destination.string, "0d1");
  }

  destination.used = 0;
  memset(destination.string, 0, sizeof(f_char_t) * destination.size);

  {
    const f_conversion_data_t data = macro_f_conversion_data_t_initialize_1(12, F_conversion_data_flag_base_prepend_d | F_conversion_data_flag_base_upper_d, 0);

    const f_status_t status = f_conversion_number_unsigned_to_string(1, data, &destination);

    assert_int_equal(status, F_okay);
    assert_string_equal(destination.string, "0D1");
  }

  destination.used = 0;
  memset(destination.string, 0, sizeof(f_char_t) * destination.size);

  {
    const f_conversion_data_t data = macro_f_conversion_data_t_initialize_1(16, F_conversion_data_flag_base_prepend_d, 0);

    const f_status_t status = f_conversion_number_unsigned_to_string(1, data, &destination);

    assert_int_equal(status, F_okay);
    assert_string_equal(destination.string, "0x1");
  }

  destination.used = 0;
  memset(destination.string, 0, sizeof(f_char_t) * destination.size);

  {
    const f_conversion_data_t data = macro_f_conversion_data_t_initialize_1(16, F_conversion_data_flag_base_prepend_d | F_conversion_data_flag_base_upper_d, 0);

    const f_status_t status = f_conversion_number_unsigned_to_string(1, data, &destination);

    assert_int_equal(status, F_okay);
    assert_string_equal(destination.string, "0X1");
  }

  free((void *) destination.string);
}

void test__f_conversion_number_unsigned_to_string__works_for_zero(void **state) {

  f_string_dynamic_t destination = f_string_dynamic_t_initialize;

  {
    const f_conversion_data_t data = macro_f_conversion_data_t_initialize_1(10, 0, 0);

    const f_status_t status = f_conversion_number_unsigned_to_string(0, data, &destination);

    assert_int_equal(status, F_okay);
    assert_string_equal(destination.string, "");
  }

  destination.used = 0;
  memset(destination.string, 0, sizeof(f_char_t) * destination.size);

  {
    const f_conversion_data_t data = macro_f_conversion_data_t_initialize_1(10, 0, 1);

    const f_status_t status = f_conversion_number_unsigned_to_string(0, data, &destination);

    assert_int_equal(status, F_okay);
    assert_string_equal(destination.string, "0");
  }

  destination.used = 0;
  memset(destination.string, 0, sizeof(f_char_t) * destination.size);

  {
    const f_conversion_data_t data = macro_f_conversion_data_t_initialize_1(10, F_conversion_data_flag_zeros_leading_d, 1);

    const f_status_t status = f_conversion_number_unsigned_to_string(0, data, &destination);

    assert_int_equal(status, F_okay);
    assert_string_equal(destination.string, "0");
  }

  destination.used = 0;
  memset(destination.string, 0, sizeof(f_char_t) * destination.size);

  {
    const f_conversion_data_t data = macro_f_conversion_data_t_initialize_1(10, 0, 2);

    const f_status_t status = f_conversion_number_unsigned_to_string(0, data, &destination);

    assert_int_equal(status, F_okay);
    assert_string_equal(destination.string, " 0");
  }

  destination.used = 0;
  memset(destination.string, 0, sizeof(f_char_t) * destination.size);

  {
    const f_conversion_data_t data = macro_f_conversion_data_t_initialize_1(10, F_conversion_data_flag_zeros_leading_d, 2);

    const f_status_t status = f_conversion_number_unsigned_to_string(0, data, &destination);

    assert_int_equal(status, F_okay);
    assert_string_equal(destination.string, "00");
  }

  destination.used = 0;
  memset(destination.string, 0, sizeof(f_char_t) * destination.size);

  {
    const f_conversion_data_t data = macro_f_conversion_data_t_initialize_1(10, F_conversion_data_flag_sign_pad_d, 0);

    const f_status_t status = f_conversion_number_unsigned_to_string(0, data, &destination);

    assert_int_equal(status, F_okay);
    assert_string_equal(destination.string, "");
  }

  destination.used = 0;
  memset(destination.string, 0, sizeof(f_char_t) * destination.size);

  {
    const f_conversion_data_t data = macro_f_conversion_data_t_initialize_1(10, F_conversion_data_flag_sign_pad_d, 1);

    const f_status_t status = f_conversion_number_unsigned_to_string(0, data, &destination);

    assert_int_equal(status, F_okay);
    assert_string_equal(destination.string, " 0");
  }

  destination.used = 0;
  memset(destination.string, 0, sizeof(f_char_t) * destination.size);

  {
    const f_conversion_data_t data = macro_f_conversion_data_t_initialize_1(10, F_conversion_data_flag_sign_always_d, 0);

    const f_status_t status = f_conversion_number_unsigned_to_string(0, data, &destination);

    assert_int_equal(status, F_okay);
    assert_string_equal(destination.string, "");
  }

  destination.used = 0;
  memset(destination.string, 0, sizeof(f_char_t) * destination.size);

  {
    const f_conversion_data_t data = macro_f_conversion_data_t_initialize_1(10, F_conversion_data_flag_sign_always_d, 1);

    const f_status_t status = f_conversion_number_unsigned_to_string(0, data, &destination);

    assert_int_equal(status, F_okay);
    assert_string_equal(destination.string, " 0");
  }

  destination.used = 0;
  memset(destination.string, 0, sizeof(f_char_t) * destination.size);

  {
    const f_conversion_data_t data = macro_f_conversion_data_t_initialize_1(10, F_conversion_data_flag_sign_always_d | F_conversion_data_flag_zeros_leading_d, 2);

    const f_status_t status = f_conversion_number_unsigned_to_string(0, data, &destination);

    assert_int_equal(status, F_okay);
    assert_string_equal(destination.string, " 00");
  }

  free((void *) destination.string);
}

#ifdef __cplusplus
} // extern "C"
#endif
