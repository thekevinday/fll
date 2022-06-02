#include "test-fss.h"
#include "test-fss-count_lines_range.h"

#ifdef __cplusplus
extern "C" {
#endif

void test__f_fss_count_lines_range__parameter_checking(void **state) {

  f_state_t state_data = f_state_t_initialize;
  const f_string_range_t range = f_string_range_t_initialize;

  {
    const f_status_t status = f_fss_count_lines_range(state_data, f_string_empty_s, range, 0);

    assert_int_equal(status, F_status_set_error(F_parameter));
  }
}

void test__f_fss_count_lines_range__returns_data_not(void **state) {

  const f_string_static_t test = macro_f_string_static_t_initialize("test", 0, 4);
  f_state_t state_data = f_state_t_initialize;

  {
    f_array_length_t line = 0;
    f_string_range_t range = f_string_range_t_initialize;

    const f_status_t status = f_fss_count_lines_range(state_data, f_string_empty_s, range, &line);

    assert_int_equal(status, F_data_not);
  }

  {
    f_array_length_t line = 0;
    f_string_range_t range = f_string_range_t_initialize;

    const f_status_t status = f_fss_count_lines_range(state_data, test, range, &line);

    assert_int_equal(status, F_data_not);
  }

  {
    f_array_length_t line = 0;
    f_string_range_t range = macro_f_string_range_t_initialize(0, test.used - 1);

    const f_status_t status = f_fss_count_lines_range(state_data, f_string_empty_s, range, &line);

    assert_int_equal(status, F_data_not);
  }
}

void test__f_fss_count_lines_range__works(void **state) {

  f_state_t state_data = f_state_t_initialize;

  const f_string_static_t buffers[] = {
    macro_f_string_static_t_initialize("zero", 0, 4),
    macro_f_string_static_t_initialize("one\n", 0, 4),
    macro_f_string_static_t_initialize("\ntwo\n", 0, 5),
    macro_f_string_static_t_initialize("\nthree\n\n", 0, 8),
    macro_f_string_static_t_initialize("\n⸙\nfour\n全\n", 0, 14),
  };

  f_array_length_t line = 0;
  f_array_length_t expect = 0;

  for (uint8_t i = 0; i < 5; expect += ++i) {

    f_string_range_t range = macro_f_string_range_t_initialize(0, buffers[i].used - 1);

    const f_status_t status = f_fss_count_lines_range(state_data, buffers[i], range, &line);

    assert_int_equal(status, F_none);
    assert_int_equal(line, expect);
  } // for
}

#ifdef __cplusplus
} // extern "C"
#endif
