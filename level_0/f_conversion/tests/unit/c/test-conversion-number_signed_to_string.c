#include "test-conversion.h"
#include "test-conversion-number_signed_to_string.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_level_0_parameter_checking_
  void test__f_conversion_number_signed_to_string__parameter_checking(void **state) {

    {
      const f_conversion_data_t data = macro_f_conversion_data_t_initialize(2, 0, 0);

      const f_status_t status = f_conversion_number_signed_to_string(0, data, 0);

      assert_int_equal(status, F_status_set_error(F_parameter));
    }

    {
      f_string_dynamic_t string;
      const f_conversion_data_t data = macro_f_conversion_data_t_initialize(1, 0, 0);

      const f_status_t status = f_conversion_number_signed_to_string(0, data, &string);

      assert_int_equal(status, F_status_set_error(F_parameter));
    }
  }
#endif // _di_level_0_parameter_checking_

void test__f_conversion_number_signed_to_string__works(void **state) {

  f_string_dynamic_t destination = f_string_dynamic_t_initialize;

  {
    const f_conversion_data_t data = macro_f_conversion_data_t_initialize(10, 0, 0);

    const f_status_t status = f_conversion_number_signed_to_string(1, data, &destination);

    assert_int_equal(status, F_none);
    assert_string_equal(destination.string, "1");
  }

  f_string_dynamic_resize(0, &destination);
}

void test__f_conversion_number_signed_to_string__works_for_prepend(void **state) {

  f_string_dynamic_t destination = f_string_dynamic_t_initialize;

  {
    const f_conversion_data_t data = macro_f_conversion_data_t_initialize(2, F_conversion_data_flag_base_prepend_d, 0);

    const f_status_t status = f_conversion_number_signed_to_string(1, data, &destination);

    assert_int_equal(status, F_none);
    assert_string_equal(destination.string, "0b1");
  }

  destination.used = 0;
  memset(destination.string, 0, sizeof(f_char_t) * destination.size);

  {
    const f_conversion_data_t data = macro_f_conversion_data_t_initialize(2, F_conversion_data_flag_base_prepend_d | F_conversion_data_flag_base_upper_d, 0);

    const f_status_t status = f_conversion_number_signed_to_string(1, data, &destination);

    assert_int_equal(status, F_none);
    assert_string_equal(destination.string, "0B1");
  }

  destination.used = 0;
  memset(destination.string, 0, sizeof(f_char_t) * destination.size);

  {
    const f_conversion_data_t data = macro_f_conversion_data_t_initialize(8, F_conversion_data_flag_base_prepend_d, 0);

    const f_status_t status = f_conversion_number_signed_to_string(1, data, &destination);

    assert_int_equal(status, F_none);
    assert_string_equal(destination.string, "0o1");
  }

  destination.used = 0;
  memset(destination.string, 0, sizeof(f_char_t) * destination.size);

  {
    const f_conversion_data_t data = macro_f_conversion_data_t_initialize(8, F_conversion_data_flag_base_prepend_d | F_conversion_data_flag_base_upper_d, 0);

    const f_status_t status = f_conversion_number_signed_to_string(1, data, &destination);

    assert_int_equal(status, F_none);
    assert_string_equal(destination.string, "0O1");
  }

  destination.used = 0;
  memset(destination.string, 0, sizeof(f_char_t) * destination.size);

  {
    const f_conversion_data_t data = macro_f_conversion_data_t_initialize(10, F_conversion_data_flag_base_prepend_d, 0);

    const f_status_t status = f_conversion_number_signed_to_string(1, data, &destination);

    assert_int_equal(status, F_none);
    assert_string_equal(destination.string, "0t1");
  }

  destination.used = 0;
  memset(destination.string, 0, sizeof(f_char_t) * destination.size);

  {
    const f_conversion_data_t data = macro_f_conversion_data_t_initialize(10, F_conversion_data_flag_base_prepend_d | F_conversion_data_flag_base_upper_d, 0);

    const f_status_t status = f_conversion_number_signed_to_string(1, data, &destination);

    assert_int_equal(status, F_none);
    assert_string_equal(destination.string, "0T1");
  }

  destination.used = 0;
  memset(destination.string, 0, sizeof(f_char_t) * destination.size);

  {
    const f_conversion_data_t data = macro_f_conversion_data_t_initialize(12, F_conversion_data_flag_base_prepend_d, 0);

    const f_status_t status = f_conversion_number_signed_to_string(1, data, &destination);

    assert_int_equal(status, F_none);
    assert_string_equal(destination.string, "0d1");
  }

  destination.used = 0;
  memset(destination.string, 0, sizeof(f_char_t) * destination.size);

  {
    const f_conversion_data_t data = macro_f_conversion_data_t_initialize(12, F_conversion_data_flag_base_prepend_d | F_conversion_data_flag_base_upper_d, 0);

    const f_status_t status = f_conversion_number_signed_to_string(1, data, &destination);

    assert_int_equal(status, F_none);
    assert_string_equal(destination.string, "0D1");
  }

  destination.used = 0;
  memset(destination.string, 0, sizeof(f_char_t) * destination.size);

  {
    const f_conversion_data_t data = macro_f_conversion_data_t_initialize(16, F_conversion_data_flag_base_prepend_d, 0);

    const f_status_t status = f_conversion_number_signed_to_string(1, data, &destination);

    assert_int_equal(status, F_none);
    assert_string_equal(destination.string, "0x1");
  }

  destination.used = 0;
  memset(destination.string, 0, sizeof(f_char_t) * destination.size);

  {
    const f_conversion_data_t data = macro_f_conversion_data_t_initialize(16, F_conversion_data_flag_base_prepend_d | F_conversion_data_flag_base_upper_d, 0);

    const f_status_t status = f_conversion_number_signed_to_string(1, data, &destination);

    assert_int_equal(status, F_none);
    assert_string_equal(destination.string, "0X1");
  }

  f_string_dynamic_resize(0, &destination);
}

void test__f_conversion_number_signed_to_string__works_for_zero(void **state) {

  f_string_dynamic_t destination = f_string_dynamic_t_initialize;

  {
    const f_conversion_data_t data = macro_f_conversion_data_t_initialize(10, 0, 0);

    const f_status_t status = f_conversion_number_signed_to_string(0, data, &destination);

    assert_int_equal(status, F_none);
    assert_string_equal(destination.string, "");
  }

  destination.used = 0;
  memset(destination.string, 0, sizeof(f_char_t) * destination.size);

  {
    const f_conversion_data_t data = macro_f_conversion_data_t_initialize(10, 0, 1);

    const f_status_t status = f_conversion_number_signed_to_string(0, data, &destination);

    assert_int_equal(status, F_none);
    assert_string_equal(destination.string, "0");
  }

  destination.used = 0;
  memset(destination.string, 0, sizeof(f_char_t) * destination.size);

  {
    const f_conversion_data_t data = macro_f_conversion_data_t_initialize(10, F_conversion_data_flag_zeros_leading_d, 1);

    const f_status_t status = f_conversion_number_signed_to_string(0, data, &destination);

    assert_int_equal(status, F_none);
    assert_string_equal(destination.string, "0");
  }

  destination.used = 0;
  memset(destination.string, 0, sizeof(f_char_t) * destination.size);

  {
    const f_conversion_data_t data = macro_f_conversion_data_t_initialize(10, 0, 2);

    const f_status_t status = f_conversion_number_signed_to_string(0, data, &destination);

    assert_int_equal(status, F_none);
    assert_string_equal(destination.string, " 0");
  }

  destination.used = 0;
  memset(destination.string, 0, sizeof(f_char_t) * destination.size);

  {
    const f_conversion_data_t data = macro_f_conversion_data_t_initialize(10, F_conversion_data_flag_zeros_leading_d, 2);

    const f_status_t status = f_conversion_number_signed_to_string(0, data, &destination);

    assert_int_equal(status, F_none);
    assert_string_equal(destination.string, "00");
  }

  destination.used = 0;
  memset(destination.string, 0, sizeof(f_char_t) * destination.size);

  {
    const f_conversion_data_t data = macro_f_conversion_data_t_initialize(10, F_conversion_data_flag_sign_pad_d, 0);

    const f_status_t status = f_conversion_number_signed_to_string(0, data, &destination);

    assert_int_equal(status, F_none);
    assert_string_equal(destination.string, "");
  }

  destination.used = 0;
  memset(destination.string, 0, sizeof(f_char_t) * destination.size);

  {
    const f_conversion_data_t data = macro_f_conversion_data_t_initialize(10, F_conversion_data_flag_sign_pad_d, 1);

    const f_status_t status = f_conversion_number_signed_to_string(0, data, &destination);

    assert_int_equal(status, F_none);
    assert_string_equal(destination.string, " 0");
  }

  destination.used = 0;
  memset(destination.string, 0, sizeof(f_char_t) * destination.size);

  {
    const f_conversion_data_t data = macro_f_conversion_data_t_initialize(10, F_conversion_data_flag_sign_always_d, 0);

    const f_status_t status = f_conversion_number_signed_to_string(0, data, &destination);

    assert_int_equal(status, F_none);
    assert_string_equal(destination.string, "");
  }

  destination.used = 0;
  memset(destination.string, 0, sizeof(f_char_t) * destination.size);

  {
    const f_conversion_data_t data = macro_f_conversion_data_t_initialize(10, F_conversion_data_flag_sign_always_d, 1);

    const f_status_t status = f_conversion_number_signed_to_string(0, data, &destination);

    assert_int_equal(status, F_none);
    assert_string_equal(destination.string, " 0");
  }

  destination.used = 0;
  memset(destination.string, 0, sizeof(f_char_t) * destination.size);

  {
    const f_conversion_data_t data = macro_f_conversion_data_t_initialize(10, F_conversion_data_flag_sign_always_d | F_conversion_data_flag_zeros_leading_d, 2);

    const f_status_t status = f_conversion_number_signed_to_string(0, data, &destination);

    assert_int_equal(status, F_none);
    assert_string_equal(destination.string, " 00");
  }

  f_string_dynamic_resize(0, &destination);
}

#ifdef __cplusplus
} // extern "C"
#endif
