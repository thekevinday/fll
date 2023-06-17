#include "test-fss.h"
#include "test-fss-count_lines_range.h"

#ifdef __cplusplus
extern "C" {
#endif

void test__f_fss_count_lines_range__parameter_checking(void **state) {

  f_state_t state_data = f_state_t_initialize;
  const f_string_range_t range = f_string_range_t_initialize;

  {
    f_fss_count_lines_range(f_string_empty_s, range, 0, &state_data);

    assert_int_equal(state_data.status, F_status_set_error(F_parameter));
  }
}

void test__f_fss_count_lines_range__returns_data_not(void **state) {

  const f_string_static_t test = macro_f_string_static_t_initialize_1("test", 0, 4);
  f_state_t state_data = f_state_t_initialize;

  {
    f_number_unsigned_t line = 0;
    f_string_range_t range = f_string_range_t_initialize;

    f_fss_count_lines_range(f_string_empty_s, range, &line, &state_data);

    assert_int_equal(state_data.status, F_data_not);
  }

  {
    f_number_unsigned_t line = 0;
    f_string_range_t range = f_string_range_t_initialize;

    f_fss_count_lines_range(test, range, &line, &state_data);

    assert_int_equal(state_data.status, F_data_not);
  }

  {
    f_number_unsigned_t line = 0;
    f_string_range_t range = macro_f_string_range_t_initialize_1(0, test.used - 1);

    f_fss_count_lines_range(f_string_empty_s, range, &line, &state_data);

    assert_int_equal(state_data.status, F_data_not);
  }
}

void test__f_fss_count_lines_range__works(void **state) {

  f_state_t state_data = f_state_t_initialize;

  const f_string_static_t buffers[] = {
    macro_f_string_static_t_initialize_1("zero", 0, 4),
    macro_f_string_static_t_initialize_1("one\n", 0, 4),
    macro_f_string_static_t_initialize_1("\ntwo\n", 0, 5),
    macro_f_string_static_t_initialize_1("\nthree\n\n", 0, 8),
    macro_f_string_static_t_initialize_1("\n⸙\nfour\n全\n", 0, 14),
  };

  f_number_unsigned_t line = 0;
  f_number_unsigned_t expect = 0;

  for (uint8_t i = 0; i < 5; expect += ++i) {

    f_string_range_t range = macro_f_string_range_t_initialize_1(0, buffers[i].used - 1);

    f_fss_count_lines_range(buffers[i], range, &line, &state_data);

    assert_int_equal(state_data.status, F_none);
    assert_int_equal(line, expect);
  } // for
}

#ifdef __cplusplus
} // extern "C"
#endif
