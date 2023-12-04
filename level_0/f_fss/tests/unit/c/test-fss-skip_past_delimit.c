#include "test-fss.h"
#include "test-fss-skip_past_delimit.h"

#ifdef __cplusplus
extern "C" {
#endif

void test__f_fss_skip_past_delimit__parameter_checking(void **state) {

  const f_string_static_t test = macro_f_string_static_t_initialize_1("test", 0, 4);
  f_state_t state_data = f_state_t_initialize;

  {
    f_fss_skip_past_delimit(test, 0, &state_data);

    assert_int_equal(state_data.status, F_status_set_error(F_parameter));
  }
}

void test__f_fss_skip_past_delimit__returns_data_not(void **state) {

  const f_string_static_t test = macro_f_string_static_t_initialize_1("test", 0, 4);
  f_state_t state_data = f_state_t_initialize;

  {
    f_range_t range = f_range_t_initialize;

    f_fss_skip_past_delimit(f_string_empty_s, &range, &state_data);

    assert_int_equal(state_data.status, F_data_not);
  }

  {
    f_range_t range = f_range_t_initialize;

    f_fss_skip_past_delimit(test, &range, &state_data);

    assert_int_equal(state_data.status, F_data_not);
  }

  {
    f_range_t range = macro_f_range_t_initialize_1(0, test.used - 1);

    f_fss_skip_past_delimit(f_string_empty_s, &range, &state_data);

    assert_int_equal(state_data.status, F_data_not);
  }

  {
    f_range_t range = macro_f_range_t_initialize_1(test.used, test.used + 2);

    f_fss_skip_past_delimit(test, &range, &state_data);

    assert_int_equal(state_data.status, F_data_not);
  }
}

void test__f_fss_skip_past_delimit__works(void **state) {

  f_state_t state_data = f_state_t_initialize;

  f_string_static_t tests[] = {
    macro_f_string_static_t_initialize_1("test", 0, 4),
    macro_f_string_static_t_initialize_1("\0test", 0, 5),
    macro_f_string_static_t_initialize_1("\0\0\0test", 0, 7),
    macro_f_string_static_t_initialize_1("\0\0\0test\0\0", 0, 9),
  };

  f_number_unsigned_t expects[] = {
    0,
    1,
    3,
    3,
  };

  for (uint8_t i = 0; i < 4; ++i) {

    f_range_t range = macro_f_range_t_initialize_1(0, tests[i].used - 1);

    f_fss_skip_past_delimit(tests[i], &range, &state_data);

    assert_int_equal(state_data.status, F_okay);
    assert_int_equal(range.start, expects[i]);
  } // for
}

#ifdef __cplusplus
} // extern "C"
#endif
