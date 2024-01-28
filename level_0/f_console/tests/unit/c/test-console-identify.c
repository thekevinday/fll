#include "test-console.h"

#ifdef __cplusplus
extern "C" {
#endif

void test__f_console_identify__parameter_checking(void **state) {

  const f_string_t input = f_string_t_initialize;

  {
    const f_status_t status = f_console_identify(input, 0);

    assert_int_equal(status, F_status_set_error(F_parameter));
  }
}

void test__f_console_identify__works(void **state) {

  f_console_result_t result = f_console_result_t_initialize;

  {
    const f_string_t input = f_string_t_initialize;

    const f_status_t status = f_console_identify(input, &result);

    assert_int_equal(status, F_data_not);
    assert_int_equal(result, f_console_result_none_e);
  }

  {
    const f_status_t status = f_console_identify("input", &result);

    assert_int_equal(status, F_okay);
    assert_int_equal(result, f_console_result_none_e);
  }

  {
    const f_status_t status = f_console_identify("-", &result);

    assert_int_equal(status, F_okay);
    assert_int_equal(result, f_console_result_found_e | f_console_result_normal_e | f_console_result_short_e | f_console_result_alone_e);
  }

  {
    const f_status_t status = f_console_identify("+", &result);

    assert_int_equal(status, F_okay);
    assert_int_equal(result, f_console_result_found_e | f_console_result_inverse_e | f_console_result_short_e | f_console_result_alone_e);
  }

  {
    const f_status_t status = f_console_identify("-i", &result);

    assert_int_equal(status, F_okay);
    assert_int_equal(result, f_console_result_found_e | f_console_result_normal_e | f_console_result_short_e);
  }

  {
    const f_status_t status = f_console_identify("+i", &result);

    assert_int_equal(status, F_okay);
    assert_int_equal(result, f_console_result_found_e | f_console_result_inverse_e | f_console_result_short_e);
  }

  {
    const f_status_t status = f_console_identify("--input", &result);

    assert_int_equal(status, F_okay);
    assert_int_equal(result, f_console_result_found_e | f_console_result_normal_e | f_console_result_long_e);
  }

  {
    const f_status_t status = f_console_identify("++input", &result);

    assert_int_equal(status, F_okay);
    assert_int_equal(result, f_console_result_found_e | f_console_result_inverse_e | f_console_result_long_e);
  }

  {
    const f_status_t status = f_console_identify("--", &result);

    assert_int_equal(status, F_okay);
    assert_int_equal(result, f_console_result_found_e | f_console_result_normal_e | f_console_result_long_e | f_console_result_alone_e);
  }

  {
    const f_status_t status = f_console_identify("++", &result);

    assert_int_equal(status, F_okay);
    assert_int_equal(result, f_console_result_found_e | f_console_result_inverse_e | f_console_result_long_e | f_console_result_alone_e);
  }
}

#ifdef __cplusplus
} // extern "C"
#endif
