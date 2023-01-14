#include "test-console.h"
#include "test-console-identify.h"

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

  f_console_result_t id = f_console_result_t_initialize;

  {
    const f_string_t input = f_string_t_initialize;

    const f_status_t status = f_console_identify(input, &id);

    assert_int_equal(status, F_data_not);
    assert_int_equal(id, f_console_none_e);
  }

  {
    const f_status_t status = f_console_identify("input", &id);

    assert_int_equal(status, F_none);
    assert_int_equal(id, f_console_none_e);
  }

  {
    const f_status_t status = f_console_identify("-", &id);

    assert_int_equal(status, F_none);
    assert_int_equal(id, f_console_empty_short_enable_e);
  }

  {
    const f_status_t status = f_console_identify("+", &id);

    assert_int_equal(status, F_none);
    assert_int_equal(id, f_console_empty_short_disable_e);
  }

  {
    const f_status_t status = f_console_identify("-i", &id);

    assert_int_equal(status, F_none);
    assert_int_equal(id, f_console_short_enable_e);
  }

  {
    const f_status_t status = f_console_identify("+i", &id);

    assert_int_equal(status, F_none);
    assert_int_equal(id, f_console_short_disable_e);
  }

  {
    const f_status_t status = f_console_identify("--input", &id);

    assert_int_equal(status, F_none);
    assert_int_equal(id, f_console_long_enable_e);
  }

  {
    const f_status_t status = f_console_identify("++input", &id);

    assert_int_equal(status, F_none);
    assert_int_equal(id, f_console_long_disable_e);
  }

  {
    const f_status_t status = f_console_identify("--", &id);

    assert_int_equal(status, F_none);
    assert_int_equal(id, f_console_empty_long_enable_e);
  }

  {
    const f_status_t status = f_console_identify("++", &id);

    assert_int_equal(status, F_none);
    assert_int_equal(id, f_console_empty_long_disable_e);
  }
}

#ifdef __cplusplus
} // extern "C"
#endif
