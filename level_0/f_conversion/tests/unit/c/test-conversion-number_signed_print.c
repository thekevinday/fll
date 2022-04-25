#include "test-conversion.h"
#include "test-conversion-number_signed_print.h"

#ifdef __cplusplus
extern "C" {
#endif

void test__f_conversion_number_signed_print__fails(void **state) {

  {
    const f_conversion_data_t data = macro_f_conversion_data_t_initialize(10, 0, 1);

    will_return(__wrap_fwrite_unlocked, true);
    will_return(__wrap_fwrite_unlocked, 0);

    const f_status_t status = f_conversion_number_signed_print(1, data, F_type_output_d);

    assert_int_equal(F_status_set_fine(status), F_output);
  }
}

void test__f_conversion_number_signed_print__fails_for_prepend(void **state) {

  {
    const f_conversion_data_t data = macro_f_conversion_data_t_initialize(10, F_conversion_data_flag_base_prepend_d, 0);

    will_return(__wrap_fwrite_unlocked, true);
    will_return(__wrap_fwrite_unlocked, 0);

    const f_status_t status = f_conversion_number_signed_print(1, data, F_type_output_d);

    assert_int_equal(F_status_set_fine(status), F_output);
  }
}

void test__f_conversion_number_signed_print__fails_for_zero(void **state) {

  {
    const f_conversion_data_t data = macro_f_conversion_data_t_initialize(10, 0, 0);

    will_return(__wrap_fwrite_unlocked, true);
    will_return(__wrap_fwrite_unlocked, 0);

    const f_status_t status = f_conversion_number_signed_print(0, data, F_type_output_d);

    assert_int_equal(F_status_set_fine(status), F_output);
  }
}

#ifndef _di_level_0_parameter_checking_
  void test__f_conversion_number_signed_print__parameter_checking(void **state) {

    {
      const f_conversion_data_t data = macro_f_conversion_data_t_initialize(2, 0, 0);

      const f_status_t status = f_conversion_number_signed_print(0, data, 0);

      assert_int_equal(F_status_set_fine(status), F_parameter);
    }

    {
      FILE *file = 0;
      const f_conversion_data_t data = macro_f_conversion_data_t_initialize(1, 0, 0);

      const f_status_t status = f_conversion_number_signed_print(0, data, file);

      assert_int_equal(F_status_set_fine(status), F_parameter);
    }
  }
#endif // _di_level_0_parameter_checking_

void test__f_conversion_number_signed_print__works(void **state) {

  {
    const f_conversion_data_t data = macro_f_conversion_data_t_initialize(10, 0, 0);

    const f_status_t status = f_conversion_number_signed_print(1, data, F_type_output_d);

    will_return(__wrap_fwrite_unlocked, false);

    expect_string(__wrap_fwrite_unlocked, ptr, "1");

    assert_int_equal(status, F_none);
  }
}

#ifdef __cplusplus
} // extern "C"
#endif
